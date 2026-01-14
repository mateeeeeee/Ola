#include <algorithm>
#include "LinearScanRegisterAllocator.h"
#include "RegisterAllocator.h"
#include "LivenessAnalysis.h"
#include "MachineModule.h"
#include "MachineBasicBlock.h"
#include "MachineFunction.h"
#include "Target.h"
#include "Core/Log.h"

namespace ola
{
	//LinearScanRegisterAllocation
	//	active ←{}
	//	for each live interval i, in order of increasing start point do
	//		ExpireOldIntervals(i)
	//		if length(active) = R then
	//			SpillAtInterval(i)
	//		else
	//			register[i] ← a register removed from pool of free registers
	//			add i to active, sorted by increasing end point
	void LinearScanRegisterAllocator::AssignRegisters(MachineFunction& MF)
	{
		//note that some registers are already non-virtual because of target instruction limitations
		//LivenessAnalysis should return what ISA registers are "taken" and in what interval
		LivenessAnalysisResult liveness = DoLivenessAnalysis(M, MF);
		std::vector<LiveInterval>& live_intervals = liveness.live_intervals;

		TargetRegisterInfo const& target_reg_info = M.GetTarget().GetRegisterInfo();
		//use callee saved regs because we can save them and restore them in prologue and epilogue of a function
		gp_regs = target_reg_info.GetGPCalleeSavedRegisters();

		OLA_TODO("This is temp hack because x64 SysV does not have callee saved FP registers which is causing issues with register allocation");
#if defined(OLA_PLATFORM_WINDOWS)
		fp_regs = target_reg_info.GetFPCalleeSavedRegisters();
#else
		fp_regs = target_reg_info.GetFPRegisters();
#endif
		frame_register = target_reg_info.GetFramePointerRegister();
		for (LiveInterval& LI : live_intervals)
		{
			ExpireOldIntervals(LI);
			if ((LI.is_float && fp_regs.empty()) || (!LI.is_float && gp_regs.empty()))
			{
				SpillAtInterval(LI);
			}
			else
			{
				if (LI.is_float)
				{
					Uint32 reg = fp_regs.back();
					fp_regs.pop_back();
					LI.reg = reg;
					used_registers_info.fp_used_registers.insert(reg);
				}
				else
				{
					Uint32 reg = gp_regs.back();
					gp_regs.pop_back();
					LI.reg = reg;
					used_registers_info.gp_used_registers.insert(reg);
				}
				vreg2reg_map[LI.vreg] = LI.reg;

				if (LI.is_float)
				{
					active_fp.push_back(&LI);
					std::sort(active_fp.begin(), active_fp.end(), [](LiveInterval* L, LiveInterval* R) { return L->end < R->end; });
				}
				else
				{
					active_gp.push_back(&LI);
					std::sort(active_gp.begin(), active_gp.end(), [](LiveInterval* L, LiveInterval* R) { return L->end < R->end; });
				}
			}
		}
		Finalize(MF, live_intervals);
	}

	//ExpireOldIntervals(i)
	//	for each interval j in active, in order of increasing end point do
	//		if endpoint[j] ≥ startpoint[i] then
	//			return
	//			remove j from active
	//			add register[j] to pool of free registers
	void LinearScanRegisterAllocator::ExpireOldIntervals(LiveInterval& LI)
	{
		if (LI.is_float)
		{
			Uint32 i = 0;
			for (; i < active_fp.size(); ++i)
			{
				LiveInterval* interval = active_fp[i];
				if (interval->end >= LI.begin)
				{
					break;
				}
				fp_regs.push_back(interval->reg);
			}
			active_fp = std::vector<LiveInterval*>(active_fp.begin() + i, active_fp.end());
		}
		else
		{
			Uint32 i = 0;
			for (; i < active_gp.size(); ++i)
			{
				LiveInterval* interval = active_gp[i];
				if (interval->end >= LI.begin)
				{
					break;
				}

				gp_regs.push_back(interval->reg);
			}
			active_gp = std::vector<LiveInterval*>(active_gp.begin() + i, active_gp.end());
		}
	}

	//SpillAtInterval(i)
	//	spill ← last interval in active
	//	if endpoint[spill] > endpoint[i] then
	//		register[i] ← register[spill]
	//		location[spill] ← new stack location
	//		remove spill from active
	//		add i to active, sorted by increasing end point
	//	else
	//		location[i] ← new stack location
	void LinearScanRegisterAllocator::SpillAtInterval(LiveInterval& LI)
	{
		if (LI.is_float)
		{
			if(active_fp.empty())
			{
				LI.spilled = true;
				return;
			}

			auto spill = active_fp.back();
			if (spill->end <= LI.end)
			{
				LI.spilled = true;
				return;
			}

			Uint32 vreg = LI.vreg;
			LI.reg = spill->reg;
			vreg2reg_map[LI.vreg] = LI.reg;
			spill->spilled = true;
			vreg2reg_map.erase(spill->vreg);
			active_fp.pop_back();
			active_fp.push_back(&LI);
			sort(active_fp.begin(), active_fp.end(), [](LiveInterval* L, LiveInterval* R) { return L->end < R->end; });
		}
		else
		{
			if(active_gp.empty())
			{
				LI.spilled = true;
				return;
			}

			auto spill = active_gp.back();
			if (spill->end <= LI.end)
			{
				LI.spilled = true;
				return;
			}

			Uint32 vreg = LI.vreg;
			LI.reg = spill->reg;
			vreg2reg_map[LI.vreg] = LI.reg;
			spill->spilled = true;
			vreg2reg_map.erase(spill->vreg);
			active_gp.pop_back();
			active_gp.push_back(&LI);
			sort(active_gp.begin(), active_gp.end(), [](LiveInterval* L, LiveInterval* R) { return L->end < R->end; });
		}
	}

	void LinearScanRegisterAllocator::Finalize(MachineFunction& MF, std::vector<LiveInterval>& intervals)
	{
		TargetInstInfo const& target_inst_info = M.GetTarget().GetInstInfo();
		TargetRegisterInfo const& target_reg_info = M.GetTarget().GetRegisterInfo();
		std::unordered_map<Uint32, MachineOperand*> vreg_stack_map;

		auto GetSpillSlot = [&](Uint32 vreg_id, MachineType type) -> MachineOperand*
		{
			MachineOperand* existing_stack_loc = vreg_stack_map[vreg_id];
			if (existing_stack_loc != nullptr)
			{
				return existing_stack_loc;
			}
			MachineOperand& new_stack_loc = MF.AllocateLocalStack(type);
			vreg_stack_map[vreg_id] = &new_stack_loc;
			return &new_stack_loc;
		};

		for (auto& MBB : MF.Blocks())
		{
			auto& instructions = MBB->Instructions();
			for (auto it = instructions.begin(); it != instructions.end(); ++it)
			{
				MachineInstruction& MI = *it;
				InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);

				// Special handling for Store/Load where address operand is a spilled pointer vreg
				if (MI.GetOpcode() == InstStore)
				{
					// For Store operand 0 is the address, if it's a spilled pointer, we need indirection
					MachineOperand& addr_op = MI.GetOperand(0);
					if (IsOperandVReg(addr_op) && !vreg2reg_map.contains(addr_op.GetReg().reg))
					{
						// Address vreg is spilled, need to load the pointer first
						Uint32 vreg_id = addr_op.GetReg().reg;
						MachineOperand* spill_slot = GetSpillSlot(vreg_id, addr_op.GetType());

						Uint32 scratch = target_reg_info.GetGPScratchRegister();
						MachineInstruction load_inst(InstLoad);
						load_inst.SetOp<0>(MachineOperand::ISAReg(scratch, addr_op.GetType()));
						load_inst.SetOp<1>(*spill_slot);
						instructions.insert(it, load_inst);
						MI.SetOperand(0, MachineOperand::ISAReg(scratch, addr_op.GetType()));
					}
				}
				else if (MI.GetOpcode() == InstLoad)
				{
					// For Load: operand 1 is the address, if it's a spilled pointer, we need indirection
					MachineOperand& addr_op = MI.GetOperand(1);
					if (IsOperandVReg(addr_op) && !vreg2reg_map.contains(addr_op.GetReg().reg))
					{
						// Address vreg is spilled, need to load the pointer first
						Uint32 vreg_id = addr_op.GetReg().reg;
						MachineOperand* spill_slot = GetSpillSlot(vreg_id, addr_op.GetType());

						Uint32 scratch = target_reg_info.GetGPScratchRegister();
						MachineInstruction load_ptr_inst(InstLoad);
						load_ptr_inst.SetOp<0>(MachineOperand::ISAReg(scratch, addr_op.GetType()));
						load_ptr_inst.SetOp<1>(*spill_slot);
						instructions.insert(it, load_ptr_inst);
						MI.SetOperand(1, MachineOperand::ISAReg(scratch, addr_op.GetType()));
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
					if (vreg2reg_map.contains(vreg_id))
					{
						Uint32 reg_id = vreg2reg_map[vreg_id];
						MI.SetOperand(idx, MachineOperand::ISAReg(reg_id, MO.GetType()));
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
