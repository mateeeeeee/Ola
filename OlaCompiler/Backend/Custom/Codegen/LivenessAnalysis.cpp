#include <algorithm>
#include "LivenessAnalysis.h"
#include "MachineFunction.h"
#include "MachineBasicBlock.h"
#include "MachineModule.h"
#include "Target.h"

namespace ola
{
	static inline uint32 GetRegAsUint(MachineOperand const& operand)
	{
		OLA_ASSERT(operand.IsReg() && (IsVirtualReg(operand.GetReg().reg) || IsISAReg(operand.GetReg().reg)));
		return static_cast<uint32>(operand.GetReg().reg);
	}

	static void AssignInstNum(MachineFunction& MF, std::unordered_map<MachineInstruction*, uint64>& inst_number_map)
	{
		uint64 current = 0;
		for (auto& block : MF.Blocks())
		{
			for (MachineInstruction& inst : block->Instructions()) 
			{
				inst_number_map[&inst] = current;
				current += 4;
			}
		}
	}


	LivenessAnalysisResult DoLivenessAnalysis(MachineModule& M, MachineFunction& MF)
	{
		LivenessAnalysisResult result{};
		AssignInstNum(MF, result.instruction_numbering_map);

		TargetInstInfo const& target_inst_info = M.GetTarget().GetInstInfo();

		std::unordered_map<uint32, uint64> reg_def_map;
		std::unordered_map<uint32, uint64> reg_use_map;
		std::unordered_map<uint32, LiveInterval> live_interval_map;
		for (auto& MBB : MF.Blocks())
		{
			for (MachineInstruction& MI : MBB->Instructions())
			{
				uint64 const instruction_idx = result.instruction_numbering_map[&MI];
				InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);
				for (uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
				{
					MachineOperand& MO = MI.GetOperand(idx);
					if (!IsOperandVReg(MO)) continue;
					uint32 reg_id = GetRegAsUint(MO);
					bool is_float_reg = MO.GetType() == MachineOperandType::Float64;

					if (inst_info.HasOpFlag(idx, OperandFlagDef) && !MI.HasIgnoreDef())
					{
						OLA_ASSERT(!reg_def_map.contains(reg_id));
						reg_def_map[reg_id] = instruction_idx;
					}
					else if (inst_info.HasOpFlag(idx, OperandFlagUse))
					{
						if (reg_use_map.contains(reg_id))
						{
							live_interval_map[reg_id].end = instruction_idx;
						}
						else
						{
							live_interval_map[reg_id] = LiveInterval{ .begin = reg_def_map[reg_id], .end = instruction_idx, .is_float = is_float_reg };
						}
						reg_use_map[reg_id] = instruction_idx;
					}
				}
			}
		}

		std::vector<LiveInterval> live_intervals;
		for (auto&& [vreg, interval] : live_interval_map)
		{
			live_intervals.push_back(LiveInterval{ .begin = interval.begin, .end = interval.end, .vreg = vreg, .spilled = false });
		}
		for (auto&& [reg, instruction_idx] : reg_def_map)
		{
			if (!reg_use_map.contains(reg))
			{
				live_intervals.push_back(LiveInterval{ .begin = instruction_idx, .end = instruction_idx + 3, .vreg = reg, .spilled = false });
			}
		}

		std::sort(std::begin(live_intervals), std::end(live_intervals));
		result.live_intervals = std::move(live_intervals);
		return result;
	}

}


