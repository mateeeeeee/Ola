#include <algorithm>
#include "LivenessAnalysis.h"
#include "MIRGlobal.h"
#include "MIRBasicBlock.h"
#include "MIRModule.h"

namespace ola
{
	static inline uint32 GetRegAsUint(MIROperand const& operand)
	{
		OLA_ASSERT(operand.IsReg() && (IsVirtualReg(operand.GetReg().reg) || IsISAReg(operand.GetReg().reg)));
		return static_cast<uint32>(operand.GetReg().reg);
	}

	static void AssignInstNum(MIRFunction& MF, std::unordered_map<MIRInstruction*, uint64>& inst_number_map)
	{
		uint64 current = 0;
		for (auto& block : MF.Blocks())
		{
			for (MIRInstruction& inst : block->Instructions()) 
			{
				inst_number_map[&inst] = current;
				current += 4;
			}
		}
	}


	LivenessAnalysisResult DoLivenessAnalysis(MIRModule& M, MIRFunction& MF)
	{
		LivenessAnalysisResult result{};
		AssignInstNum(MF, result.instruction_numbering_map);

		std::unordered_map<uint32, uint64> reg_def_map;
		std::unordered_map<uint32, uint64> reg_use_map;
		std::unordered_map<uint32, LiveInterval> live_interval_map;
		for (auto& MBB : MF.Blocks())
		{
			for (MIRInstruction& MI : MBB->Instructions())
			{
				uint64 const instruction_idx = result.instruction_numbering_map[&MI];
				MIRInstructionInfo const& inst_info = M.GetInstInfo(MI);

				for (uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
				{
					MIROperand& MO = MI.GetOperand(idx);
					if (!IsOperandVReg(MO)) continue;
					uint32 reg_id = GetRegAsUint(MO);

					if (inst_info.HasOpFlag(idx, OperandFlagDef))
					{
						OLA_ASSERT(!reg_def_map.contains(reg_id));
						reg_def_map[reg_id] = instruction_idx;
					}
					else if (inst_info.HasOpFlag(idx, OperandFlagUse))
					{
						reg_use_map[reg_id] = instruction_idx + 1;
					}
					live_interval_map[reg_id] = LiveInterval{ reg_def_map[reg_id], reg_use_map[reg_id] };
				}
			}
		}

		std::vector<LiveInterval> live_intervals;
		for (auto&& [reg, interval] : live_interval_map)
		{
			live_intervals.push_back(LiveInterval{ .begin = interval.begin, .end = interval.end, .reg = reg, .spilled = false });
		}
		std::sort(std::begin(live_intervals), std::end(live_intervals));
		result.live_intervals = std::move(live_intervals);
		return result;
	}

}


