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
		fp_regs = target_reg_info.GetFPCalleeSavedRegisters();
		frame_register = target_reg_info.GetFramePointerRegister();

		for (LiveInterval& LI : live_intervals)
		{
			ExpireOldIntervals(LI);
			if ((LI.is_float && fp_regs.empty()) || (!LI.is_float && gp_regs.empty()))
			{
				OLA_ASSERT_MSG(false, "Register spilling not yet implemented!");
				SpillAtInterval(LI);
			}
			else
			{
				if (LI.is_float)
				{
					Uint32 reg = fp_regs.back();
					fp_regs.pop_back();
					LI.reg = reg;
					used_registers_info.fpr_used_registers.insert(reg);
				}
				else
				{
					Uint32 reg = gp_regs.back();
					gp_regs.pop_back();
					LI.reg = reg;
					used_registers_info.gpr_used_registers.insert(reg);
				}
				vreg2reg_map[LI.vreg] = LI.reg;

				active.push_back(&LI);
				std::sort(active.begin(), active.end(), [](LiveInterval* L, LiveInterval* R) { return L->end < R->end; });
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
		Uint32 i = 0;
		for (; i < active.size(); ++i)
		{
			LiveInterval* interval = active[i];
			if (interval->end >= LI.begin) break;
			if (interval->is_float)
			{
				fp_regs.push_back(interval->reg);
			}
			else
			{
				gp_regs.push_back(interval->reg);
			}
		}
		active = std::vector<LiveInterval*>(active.begin() + i, active.end());
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
		auto spill = active.back();
		if (spill->end > LI.end)
		{
			Uint32 vreg = LI.vreg;
			LI.reg = spill->reg;
			vreg2reg_map[LI.vreg] = LI.reg;
			spill->spilled = true;
			vreg2reg_map.erase(spill->vreg);
			active.push_back(&LI);
			sort(active.begin(), active.end(), [](LiveInterval* L, LiveInterval* R) { return L->end < R->end; });
		}
		else
		{
			LI.spilled = true;
		}
	}

	void LinearScanRegisterAllocator::Finalize(MachineFunction& MF, std::vector<LiveInterval>& intervals)
	{
		TargetInstInfo const& target_inst_info = M.GetTarget().GetInstInfo();

		for (auto& MBB : MF.Blocks())
		{
			for (MachineInstruction& MI : MBB->Instructions())
			{
				InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);
				for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
				{
					MachineOperand& MO = MI.GetOperand(idx);
					if (!IsOperandVReg(MO)) continue;
					Uint32 vreg_id = MO.GetReg().reg;

					//spilling
					if (!vreg2reg_map.contains(vreg_id))
					{
						MachineOperand& MO = MF.AllocateLocalStack(MachineType::Int64);
						Int32 stack_offset = MO.GetStackOffset();
						Uint32 frame_reg = frame_register;

						//todo
					}
					else
					{
						Uint32 reg_id = vreg2reg_map[vreg_id];
						MO = MachineOperand::ISAReg(reg_id, MO.GetType());
					}
				}
			}
		}
	}

}
