#include <algorithm>
#include <limits>
#include "GraphColoringRegisterAllocator.h"
#include "LivenessAnalysis.h"
#include "Backend/Custom/Codegen/MachineModule.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/Targets/Target.h"
#include "Core/Log.h"

namespace ola
{
	// GraphColoringRegisterAllocation
	//     Build interference graph from live intervals
	//     ComputeSpillCosts for each node
	//     MakeWorklists (categorize nodes by degree)
	//     while simplify_worklist or spill_worklist not empty do
	//         if simplify_worklist not empty then
	//             Simplify()
	//         else
	//             select spill candidate and move to simplify_worklist
	//     Select: assign colors to nodes on stack
	//     Finalize: rewrite vregs with physical registers
	void GraphColoringRegisterAllocator::AssignRegisters(MachineFunction& MF)
	{
		TargetRegisterInfo const& target_reg_info = M.GetTarget().GetRegisterInfo();

		// Only use callee-saved registers to avoid issues with vregs live across calls
		// (caller-saved registers are clobbered by function calls)
		std::vector<Uint32> gp_colors = target_reg_info.GetGPCalleeSavedRegisters();
#if defined(OLA_PLATFORM_WINDOWS)
		std::vector<Uint32> fp_colors = target_reg_info.GetFPCalleeSavedRegisters();
#else
		std::vector<Uint32> fp_colors = target_reg_info.GetFPRegisters();
#endif

		K_gp = static_cast<Uint32>(gp_colors.size());
		K_fp = static_cast<Uint32>(fp_colors.size());

		simplify_worklist.clear();
		spill_worklist.clear();
		spilled_nodes.clear();
		while (!select_stack.empty()) select_stack.pop();

		LivenessAnalysisResult liveness = DoLivenessAnalysis(M, MF);
		InterferenceGraph IG;
		Build(MF, liveness, IG);
		ComputeSpillCosts(MF, IG, liveness);
		MakeWorklists(IG);

		while (!simplify_worklist.empty() || !spill_worklist.empty())
		{
			if (!simplify_worklist.empty())
			{
				Simplify(IG);
			}
			else if (!spill_worklist.empty())
			{
				Uint32 spill_vreg = SelectSpill(IG);
				simplify_worklist.insert(spill_vreg);
				spill_worklist.erase(spill_vreg);
			}
		}

		Select(IG, gp_colors, fp_colors);
		Finalize(MF, IG);
	}

	// Build(liveness)
	//     for each live interval i do
	//         add node for vreg[i] to IG
	//     for each pair (i, j) of live intervals do
	//         if same register class and intervals overlap then
	//             add interference edge (i, j)
	void GraphColoringRegisterAllocator::Build(MachineFunction& MF, LivenessAnalysisResult& liveness, InterferenceGraph& IG)
	{
		for (LiveInterval& LI : liveness.live_intervals)
		{
			IG.AddNode(LI.vreg, LI.is_float);
		}

		for (Uint64 i = 0; i < liveness.live_intervals.size(); ++i)
		{
			LiveInterval& LI_i = liveness.live_intervals[i];
			for (Uint64 j = i + 1; j < liveness.live_intervals.size(); ++j)
			{
				LiveInterval& LI_j = liveness.live_intervals[j];
				if (LI_i.is_float != LI_j.is_float)
				{
					continue;
				}

				Bool overlap = !(LI_i.end <= LI_j.begin || LI_j.end <= LI_i.begin);
				if (overlap)
				{
					IG.AddInterference(LI_i.vreg, LI_j.vreg);
				}
			}
		}
	}

	// ComputeSpillCosts(IG, liveness)
	//     for each instruction do
	//         for each vreg operand do
	//             spill_cost[vreg] += weight * (uses + defs)
	//     for each very short live interval do
	//         spill_cost[vreg] ← infinity (don't spill)
	void GraphColoringRegisterAllocator::ComputeSpillCosts(MachineFunction& MF, InterferenceGraph& IG, LivenessAnalysisResult& liveness)
	{
		TargetInstInfo const& target_inst_info = M.GetTarget().GetInstInfo();
		for (auto& [vreg, node] : IG)
		{
			node.spill_cost = 0.0;
		}

		static constexpr Float64 USE_WEIGHT = 1.0;
		static constexpr Float64 DEF_WEIGHT = 1.0;

		for (auto& MBB : MF.Blocks())
		{
			Float64 block_weight = 1.0;

			for (MachineInstruction& MI : MBB->Instructions())
			{
				InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);

				for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
				{
					MachineOperand& MO = MI.GetOperand(idx);
					if (!IsOperandVReg(MO))
					{
						continue;
					}

					Uint32 vreg = MO.GetReg().reg;
					IGNode* node = IG.GetNode(vreg);
					if (!node) 
					{
						continue;
					}

					if (inst_info.HasOpFlag(idx, OperandFlagUse))
					{
						node->spill_cost += USE_WEIGHT * block_weight;
					}
					if (inst_info.HasOpFlag(idx, OperandFlagDef))
					{
						node->spill_cost += DEF_WEIGHT * block_weight;
					}
				}
			}
		}

		for (LiveInterval& LI : liveness.live_intervals)
		{
			if (LI.end - LI.begin <= 2)
			{
				IGNode* node = IG.GetNode(LI.vreg);
				if (node)
				{
					node->spill_cost = std::numeric_limits<Float64>::infinity();
				}
			}
		}
	}

	// MakeWorklists(IG)
	//     for each node n in IG do
	//         if degree[n] >= K then
	//             add n to spill_worklist
	//         else
	//             add n to simplify_worklist
	void GraphColoringRegisterAllocator::MakeWorklists(InterferenceGraph& IG)
	{
		for (auto& [vreg, node] : IG)
		{
			Uint32 K = node.is_float ? K_fp : K_gp;
			if (node.degree >= K)
			{
				spill_worklist.insert(vreg);
			}
			else
			{
				simplify_worklist.insert(vreg);
			}
		}
	}

	// Simplify()
	//     remove node n from simplify_worklist
	//     push n onto select_stack
	//     for each neighbor m of n do
	//         decrement degree[m]
	//         if degree[m] was K and is now < K then
	//             move m from spill_worklist to simplify_worklist
	void GraphColoringRegisterAllocator::Simplify(InterferenceGraph& IG)
	{
		Uint32 vreg = *simplify_worklist.begin();
		simplify_worklist.erase(vreg);

		select_stack.push(vreg);
		IGNode* node = IG.GetNode(vreg);
		node->on_stack = true;

		for (Uint32 neighbor : node->neighbors)
		{
			IGNode* neighbor_node = IG.GetNode(neighbor);
			if (!neighbor_node || neighbor_node->on_stack)
				continue;

			Uint32 K = neighbor_node->is_float ? K_fp : K_gp;
			Uint32 old_degree = neighbor_node->degree;

			IG.DecrementDegree(neighbor);

			if (old_degree == K && neighbor_node->degree < K)
			{
				spill_worklist.erase(neighbor);
				simplify_worklist.insert(neighbor);
			}
		}
	}

	// SelectSpill()
	//     for each node n in spill_worklist do
	//         priority[n] = spill_cost[n] / degree[n]
	//     return node with lowest priority (best spill candidate)
	Uint32 GraphColoringRegisterAllocator::SelectSpill(InterferenceGraph& IG)
	{
		Uint32 best_vreg = 0;
		Float64 best_priority = std::numeric_limits<Float64>::max();
		for (Uint32 vreg : spill_worklist)
		{
			IGNode* node = IG.GetNode(vreg);
			if (!node || node->spill_cost == std::numeric_limits<Float64>::infinity())
			{
				continue;
			}

			Float64 priority = node->spill_cost / static_cast<Float64>(node->degree + 1);
			if (priority < best_priority)
			{
				best_priority = priority;
				best_vreg = vreg;
			}
		}

		if (best_vreg == 0 && !spill_worklist.empty())
		{
			best_vreg = *spill_worklist.begin();
		}
		return best_vreg;
	}

	// Select(colors)
	//     while select_stack not empty do
	//         pop node n from stack
	//         used_colors ← colors of all colored neighbors
	//         for each color c in available colors (high-numbered first) do
	//             if c not in used_colors then
	//                 color[n] ← c
	//                 break
	//         if no color assigned then
	//             mark n as spilled
	Bool GraphColoringRegisterAllocator::Select(InterferenceGraph& IG, std::vector<Uint32> const& gp_colors, std::vector<Uint32> const& fp_colors)
	{
		while (!select_stack.empty())
		{
			Uint32 vreg = select_stack.top();
			select_stack.pop();

			IGNode* node = IG.GetNode(vreg);
			node->on_stack = false;
			std::unordered_set<Uint32> used_colors;
			for (Uint32 neighbor : node->neighbors)
			{
				IGNode* neighbor_node = IG.GetNode(neighbor);
				if (neighbor_node && neighbor_node->color != INVALID_REG)
				{
					used_colors.insert(neighbor_node->color);
				}
			}

			std::vector<Uint32> const& available = node->is_float ? fp_colors : gp_colors;
			Uint32 assigned = INVALID_REG;
			// Iterate in reverse to prefer high-numbered registers first (like LinearScan),
			// avoiding argument registers (d0-d7, x0-x7) which are at the front
			for (auto it = available.rbegin(); it != available.rend(); ++it)
			{
				Uint32 color = *it;
				if (!used_colors.contains(color))
				{
					assigned = color;
					break;
				}
			}

			if (assigned == INVALID_REG)
			{
				spilled_nodes.insert(vreg);
				node->spilled = true;
			}
			else
			{
				node->color = assigned;
			}
		}

		return spilled_nodes.empty();
	}

	// Finalize()
	//     for each instruction do
	//         for each vreg operand do
	//             if vreg has color then
	//                 replace vreg with physical register
	//             else
	//                 replace vreg with stack slot
	void GraphColoringRegisterAllocator::Finalize(MachineFunction& MF, InterferenceGraph& IG)
	{
		TargetInstInfo const& target_inst_info = M.GetTarget().GetInstInfo();
		TargetRegisterInfo const& target_reg_info = M.GetTarget().GetRegisterInfo();

		auto GetSpillSlot = [&](Uint32 vreg_id, MachineType type) -> MachineOperand*
		{
			auto it = spill_slots.find(vreg_id);
			if (it != spill_slots.end())
			{
				return it->second;
			}
			MachineOperand& new_stack_loc = MF.AllocateLocalStack(type);
			spill_slots[vreg_id] = &new_stack_loc;
			return &new_stack_loc;
		};

		for (auto& MBB : MF.Blocks())
		{
			auto& instructions = MBB->Instructions();
			for (auto it = instructions.begin(); it != instructions.end(); ++it)
			{
				MachineInstruction& MI = *it;
				InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);

				if (MI.GetOpcode() == InstStore)
				{
					MachineOperand& addr_op = MI.GetOperand(0);
					if (IsOperandVReg(addr_op))
					{
						Uint32 vreg_id = addr_op.GetReg().reg;
						IGNode* node = IG.GetNode(vreg_id);
						if (!node || node->color == INVALID_REG)
						{
							MachineOperand* spill_slot = GetSpillSlot(vreg_id, addr_op.GetType());
							Uint32 scratch = target_reg_info.GetGPScratchRegister();
							MachineInstruction load_inst(InstLoad);
							load_inst.SetOp<0>(MachineOperand::ISAReg(scratch, addr_op.GetType()));
							load_inst.SetOp<1>(*spill_slot);
							instructions.insert(it, load_inst);
							MI.SetOperand(0, MachineOperand::ISAReg(scratch, addr_op.GetType()));
						}
					}
				}
				else if (MI.GetOpcode() == InstLoad)
				{
					MachineOperand& addr_op = MI.GetOperand(1);
					if (IsOperandVReg(addr_op))
					{
						Uint32 vreg_id = addr_op.GetReg().reg;
						IGNode* node = IG.GetNode(vreg_id);
						if (!node || node->color == INVALID_REG)
						{
							MachineOperand* spill_slot = GetSpillSlot(vreg_id, addr_op.GetType());
							Uint32 scratch = target_reg_info.GetGPScratchRegister();
							MachineInstruction load_ptr_inst(InstLoad);
							load_ptr_inst.SetOp<0>(MachineOperand::ISAReg(scratch, addr_op.GetType()));
							load_ptr_inst.SetOp<1>(*spill_slot);
							instructions.insert(it, load_ptr_inst);
							MI.SetOperand(1, MachineOperand::ISAReg(scratch, addr_op.GetType()));
						}
					}
				}

				for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
				{
					MachineOperand& MO = MI.GetOperand(idx);
					if (!IsOperandVReg(MO))
					{
						continue;
					}

					Uint32 vreg_id = MO.GetReg().reg;
					IGNode* node = IG.GetNode(vreg_id);

					if (node && node->color != INVALID_REG)
					{
						MI.SetOperand(idx, MachineOperand::ISAReg(node->color, MO.GetType()));
						if (!target_reg_info.IsCallerSaved(node->color))
						{
							if (node->is_float)
							{
								used_registers_info.fp_used_registers.insert(node->color);
							}
							else
							{
								used_registers_info.gp_used_registers.insert(node->color);
							}
						}
					}
					else
					{
						MachineOperand* spill_slot = GetSpillSlot(vreg_id, MO.GetType());
						MI.SetOperand(idx, *spill_slot);
					}
				}
			}
		}
	}
}
