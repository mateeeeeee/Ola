#include <algorithm>
#include <limits>
#include "GraphColoringRegisterAllocator.h"
#include "CopyCoalescer.h"
#include "LivenessAnalysis.h"
#include "Backend/Custom/Codegen/MachineModule.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/Targets/Target.h"
#include "Core/Log.h"

namespace ola
{
	GraphColoringRegisterAllocator::GraphColoringRegisterAllocator(MachineModule& M) : RegisterAllocator(M) {}
	GraphColoringRegisterAllocator::~GraphColoringRegisterAllocator() = default;

	// GraphColoringRegisterAllocation
	//     Build interference graph from live intervals
	//     ComputeSpillCosts for each node
	//     MakeWorklists (categorize nodes by degree)
	//     while simplify_worklist or spill_worklist not empty do
	//         if simplify_worklist not empty then
	//             Simplify()
	//         else if move_worklist not empty then
	//             Coalesce()
	//         else if freeze_worklist not empty then
	//             Freeze()
	//         else
	//             select spill candidate and move to simplify_worklist
	//     Select: assign colors to nodes on stack
	//     Finalize: rewrite vregs with physical registers
	void GraphColoringRegisterAllocator::AssignRegisters(MachineFunction& MF)
	{
		TargetRegisterInfo const& target_reg_info = M.GetTarget().GetRegisterInfo();

		//Allocator pool covers all user-allocatable GPRs (callee-saved + caller-saved)
		//Liveness now tracks physreg uses/defs, so vregs live across calls or across
		//idiv/cqo etc. get those caller-saved physregs added to forbidden_colors and
		//won't be assigned to them
		//Scratch registers are excluded from the pool because spill code emitted during
		//Finalize clobbers them; a vreg assigned to scratch would be silently corrupted
		Uint32 const gp_scratch = target_reg_info.GetGPScratchRegister();
		Uint32 const fp_scratch = target_reg_info.GetFPScratchRegister();
		std::vector<Uint32> gp_colors;
		{
			auto callee = target_reg_info.GetGPCalleeSavedRegisters();
			auto caller = target_reg_info.GetGPCallerSavedRegisters();
			for (Uint32 reg : callee) 
			{
				if (reg != gp_scratch) 
				{
					gp_colors.push_back(reg);
				}
			}
			for (Uint32 reg : caller) 
			{
				if (reg != gp_scratch) 
				{
					gp_colors.push_back(reg);
				}
			}
		}
		std::vector<Uint32> fp_colors;
		{
			auto callee = target_reg_info.GetFPCalleeSavedRegisters();
			auto caller = target_reg_info.GetFPCallerSavedRegisters();
			for (Uint32 reg : callee) 
			{
				if (reg != fp_scratch) 
				{
					fp_colors.push_back(reg);
				}
			}
			for (Uint32 reg : caller) 
			{
				if (reg != fp_scratch) 
				{
					fp_colors.push_back(reg);
				}
			}
		}

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

		if (enable_coalescing)
		{
			SetupCoalescer(MF, IG);
			OLA_ASSERT(coalescer != nullptr);
		}
		MakeWorklists(IG);

		auto HasCoalesceWork = [&]()
		{
			return enable_coalescing && (coalescer->HasWorklistMoves() || coalescer->HasFreezeWorklist());
		};

		while (!simplify_worklist.empty() || HasCoalesceWork() || !spill_worklist.empty())
		{
			if (!simplify_worklist.empty())
			{
				Simplify(IG);
			}
			else if (enable_coalescing && coalescer->HasWorklistMoves())
			{
				coalescer->Coalesce();
			}
			else if (enable_coalescing && coalescer->HasFreezeWorklist())
			{
				coalescer->Freeze();
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

	void GraphColoringRegisterAllocator::SetupCoalescer(MachineFunction& MF, InterferenceGraph& IG)
	{
		TargetInstInfo const& target_inst_info = M.GetTarget().GetInstInfo();

		coalescer = std::make_unique<CopyCoalescer>(IG, K_gp, K_fp);
		coalescer->CollectMoves(MF, target_inst_info);
		coalescer->InitWorklists();

		coalescer->OnAddToSimplifyWorklist = [this](Uint32 vreg) 
		{
			spill_worklist.erase(vreg);
			simplify_worklist.insert(vreg);
		};
		coalescer->OnAddToSpillWorklist = [this](Uint32 vreg) 
		{
			spill_worklist.insert(vreg);
		};
		coalescer->IsInSpillWorklist = [this](Uint32 vreg) 
		{
			return spill_worklist.contains(vreg);
		};
	}


	// Build(liveness)
	//     for each vreg live interval i do
	//         add node for vreg[i] to IG
	//     for each pair (i, j) of live intervals do
	//         if same register class and intervals overlap then
	//             vreg vs vreg: add interference edge
	//             vreg vs physreg: add physreg to vreg's forbidden_colors
	//             physreg vs physreg: ignore (they're never assigned by us)
	void GraphColoringRegisterAllocator::Build(MachineFunction& MF, LivenessAnalysisResult& liveness, InterferenceGraph& IG)
	{
		for (LiveInterval& LI : liveness.live_intervals)
		{
			if (IsVirtualReg(LI.vreg))
			{
				IG.AddNode(LI.vreg, LI.is_float);
			}
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
				if (!overlap) 
				{
					continue;
				}

				Bool i_phys = IsISAReg(LI_i.vreg);
				Bool j_phys = IsISAReg(LI_j.vreg);
				if (i_phys && j_phys) continue;
				if (!i_phys && !j_phys)
				{
					IG.AddInterference(LI_i.vreg, LI_j.vreg);
				}
				else
				{
					Uint32 vreg = i_phys ? LI_j.vreg : LI_i.vreg;
					Uint32 phys = i_phys ? LI_i.vreg : LI_j.vreg;
					if (IGNode* node = IG.GetNode(vreg))
					{
						node->forbidden_colors.insert(phys);
					}
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
	//         else if n is move-related then
	//             add n to freeze_worklist
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
			else if (enable_coalescing && coalescer->IsMoveRelated(vreg))
			{
				coalescer->AddToFreezeWorklist(vreg);
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
	//             enable moves for m
	//             move m from spill_worklist to simplify_worklist (or freeze_worklist if move-related)
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
				if (enable_coalescing)
				{
					coalescer->EnableMoves(neighbor);
					for (Uint32 nn : neighbor_node->neighbors)
					{
						coalescer->EnableMoves(nn);
					}
				}

				spill_worklist.erase(neighbor);
				if (enable_coalescing && coalescer->IsMoveRelated(neighbor))
				{
					coalescer->AddToFreezeWorklist(neighbor);
				}
				else
				{
					simplify_worklist.insert(neighbor);
				}
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
	//         used_colors ← colors of all colored neighbors (following aliases)
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
				// follow alias chain for coalesced nodes
				Uint32 actual_neighbor = enable_coalescing ? coalescer->GetAlias(neighbor) : neighbor;
				IGNode* neighbor_node = IG.GetNode(actual_neighbor);
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
				if (used_colors.contains(color)) 
				{
					continue;
				}
				if (node->forbidden_colors.contains(color)) 
				{
					continue;
				}
				assigned = color;
				break;
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
	//         if instruction is a coalesced move, delete it
	//         for each vreg operand do
	//             resolve alias to get canonical vreg
	//             if vreg has color then
	//                 replace vreg with physical register
	//             else
	//                 replace vreg with stack slot
	void GraphColoringRegisterAllocator::Finalize(MachineFunction& MF, InterferenceGraph& IG)
	{
		TargetInstInfo const& target_inst_info = M.GetTarget().GetInstInfo();
		TargetRegisterInfo const& target_reg_info = M.GetTarget().GetRegisterInfo();
		auto GetSpillSlot = [&](Uint32 vreg_id, MachineType type) -> MachineOperand
		{
			auto it = spill_slots.find(vreg_id);
			if (it != spill_slots.end())
			{
				return it->second;
			}
			MachineOperand& new_stack_loc = MF.AllocateLocalStack(type);
			MachineOperand copy = new_stack_loc;
			spill_slots[vreg_id] = copy;
			return copy;
		};
		auto ResolveAlias = [&](Uint32 vreg) -> Uint32
		{
			return enable_coalescing ? coalescer->GetAlias(vreg) : vreg;
		};
		auto IsSpilledVReg = [&](MachineOperand const& MO) -> Bool
		{
			if (!IsOperandVReg(MO)) return false;
			Uint32 vreg_id = ResolveAlias(MO.GetReg().reg);
			IGNode* node = IG.GetNode(vreg_id);
			return !node || node->color == INVALID_REG;
		};

		std::unordered_set<MachineInstruction*> const* coalesced_moves =
			enable_coalescing ? &coalescer->GetCoalescedMoves() : nullptr;

		for (auto& MBB : MF.Blocks())
		{
			auto& instructions = MBB->Instructions();
			for (auto it = instructions.begin(); it != instructions.end(); )
			{
				MachineInstruction& MI = *it;

				// Delete coalesced moves
				if (coalesced_moves && coalesced_moves->contains(&MI))
				{
					it = instructions.erase(it);
					continue;
				}

				InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);

				if (MI.GetOpcode() == InstStore)
				{
					MachineOperand& addr_op = MI.GetOperand(0);
					Bool addr_spilled = IsSpilledVReg(addr_op);
					if (addr_spilled)
					{
						Uint32 vreg_id = ResolveAlias(addr_op.GetReg().reg);
						MachineOperand spill_slot = GetSpillSlot(vreg_id, addr_op.GetType());
						Uint32 scratch = target_reg_info.GetGPScratchRegister();
						MachineInstruction load_inst(InstLoad);
						load_inst.SetOp<0>(MachineOperand::ISAReg(scratch, addr_op.GetType()));
						load_inst.SetOp<1>(spill_slot);
						instructions.insert(it, load_inst);
						MI.SetOperand(0, MachineOperand::ISAReg(scratch, addr_op.GetType()));
					}
					MachineOperand& val_op = MI.GetOperand(1);
					if (IsSpilledVReg(val_op))
					{
						Uint32 vreg_id = ResolveAlias(val_op.GetReg().reg);
						MachineOperand spill_slot = GetSpillSlot(vreg_id, val_op.GetType());
						Bool is_float = (val_op.GetType() == MachineType::Float64);
						Uint32 scratch = is_float ? target_reg_info.GetFPScratchRegister() :
							(addr_spilled ? target_reg_info.GetReturnRegister() : target_reg_info.GetGPScratchRegister());
						MachineInstruction load_inst(InstLoad);
						load_inst.SetOp<0>(MachineOperand::ISAReg(scratch, val_op.GetType()));
						load_inst.SetOp<1>(spill_slot);
						instructions.insert(it, load_inst);
						MI.SetOperand(1, MachineOperand::ISAReg(scratch, val_op.GetType()));
					}
				}
				else if (MI.GetOpcode() == InstLoad)
				{
					MachineOperand& dst_op = MI.GetOperand(0);
					Bool dst_spilled = IsSpilledVReg(dst_op);
					MachineOperand dst_spill_slot;
					Uint32 dst_scratch = 0;
					if (dst_spilled)
					{
						Uint32 vreg_id = ResolveAlias(dst_op.GetReg().reg);
						dst_spill_slot = GetSpillSlot(vreg_id, dst_op.GetType());

						Bool is_float = (dst_op.GetType() == MachineType::Float64);
						dst_scratch = is_float ? target_reg_info.GetFPScratchRegister() : target_reg_info.GetGPScratchRegister();
						MI.SetOperand(0, MachineOperand::ISAReg(dst_scratch, dst_op.GetType()));
					}

					MachineOperand& addr_op = MI.GetOperand(1);
					if (IsSpilledVReg(addr_op))
					{
						Uint32 vreg_id = ResolveAlias(addr_op.GetReg().reg);
						MachineOperand spill_slot = GetSpillSlot(vreg_id, addr_op.GetType());
						Uint32 scratch = target_reg_info.GetGPScratchRegister();
						MachineInstruction load_ptr_inst(InstLoad);
						load_ptr_inst.SetOp<0>(MachineOperand::ISAReg(scratch, addr_op.GetType()));
						load_ptr_inst.SetOp<1>(spill_slot);
						instructions.insert(it, load_ptr_inst);
						MI.SetOperand(1, MachineOperand::ISAReg(scratch, addr_op.GetType()));
					}

					if (dst_spilled)
					{
						auto next_it = std::next(it);
						MachineInstruction store_inst(InstStore);
						store_inst.SetOp<0>(dst_spill_slot);
						store_inst.SetOp<1>(MachineOperand::ISAReg(dst_scratch, dst_spill_slot.GetType()));
						instructions.insert(next_it, store_inst);
					}
				}

				struct OperandRewrite
				{
					Uint32 idx;
					Uint32 vreg_id;
					MachineType type;
					Bool is_use;
					Bool is_def;
					Bool is_colored;
					Uint32 color;
					Bool is_float;
					Uint32 assigned_scratch = INVALID_REG;
				};
				std::vector<OperandRewrite> rewrites;
				rewrites.reserve(inst_info.GetOperandCount());

				for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
				{
					MachineOperand& MO = MI.GetOperand(idx);
					if (!IsOperandVReg(MO))
					{
						continue;
					}

					Uint32 vreg_id = ResolveAlias(MO.GetReg().reg);
					IGNode* node = IG.GetNode(vreg_id);
					OperandRewrite r{};
					r.idx = idx;
					r.vreg_id = vreg_id;
					r.type = MO.GetType();
					r.is_use = inst_info.HasOpFlag(idx, OperandFlagUse);
					r.is_def = inst_info.HasOpFlag(idx, OperandFlagDef);
					r.is_colored = (node && node->color != INVALID_REG);
					r.color = r.is_colored ? node->color : INVALID_REG;
					r.is_float = node ? node->is_float : (MO.GetType() == MachineType::Float64);
					rewrites.push_back(r);
				}

				Bool gp_scratch_used = false;
				Bool fp_scratch_used = false;

				//Pass 1: rewrite colored vregs and emit USE-side spill loads
				//Process USEs before DEFs so the two USE scratches are distinct
				//(primary + return-reg fallback). DEFs (Pass 2) can safely
				//reuse primary scratch because the instruction's reads happen
				//before its writes
				for (auto& r : rewrites)
				{
					if (r.is_colored)
					{
						MI.SetOperand(r.idx, MachineOperand::ISAReg(r.color, r.type));
						if (!target_reg_info.IsCallerSaved(r.color))
						{
							if (r.is_float)	used_registers_info.fp_used_registers.insert(r.color);
							else			used_registers_info.gp_used_registers.insert(r.color);
						}
					}
					else if (r.is_use)
					{
						MachineOperand spill_slot = GetSpillSlot(r.vreg_id, r.type);
						Bool is_float = r.type == MachineType::Float64;
						Bool& scratch_used = is_float ? fp_scratch_used : gp_scratch_used;
						Uint32 primary_scratch = is_float ? target_reg_info.GetFPScratchRegister() : target_reg_info.GetGPScratchRegister();
						Uint32 scratch = scratch_used ? target_reg_info.GetReturnRegister() : primary_scratch;
						scratch_used = true;
						r.assigned_scratch = scratch;

						MachineInstruction load_inst(InstLoad);
						load_inst.SetOp<0>(MachineOperand::ISAReg(scratch, r.type));
						load_inst.SetOp<1>(spill_slot);
						instructions.insert(it, load_inst);
						MI.SetOperand(r.idx, MachineOperand::ISAReg(scratch, r.type));
					}
				}

				//Pass 2: emit DEF-side spill stores 
				//For USE+DEF operands the store reuses the same scratch 
				//already loaded in Pass 1, for DEF-only operands the store 
				//uses primary scratch
				for (auto const& r : rewrites)
				{
					if (r.is_colored) continue;
					if (!r.is_def) continue;

					MachineOperand spill_slot = GetSpillSlot(r.vreg_id, r.type);
					Bool is_float = r.type == MachineType::Float64;
					Uint32 primary_scratch = is_float ? target_reg_info.GetFPScratchRegister() : target_reg_info.GetGPScratchRegister();
					Uint32 scratch = (r.assigned_scratch != INVALID_REG) ? r.assigned_scratch : primary_scratch;
					MI.SetOperand(r.idx, MachineOperand::ISAReg(scratch, r.type));

					auto next_it = std::next(it);
					MachineInstruction store_inst(InstStore);
					store_inst.SetOp<0>(spill_slot);
					store_inst.SetOp<1>(MachineOperand::ISAReg(scratch, r.type));
					instructions.insert(next_it, store_inst);
				}

				++it;
			}
		}
	}
}
