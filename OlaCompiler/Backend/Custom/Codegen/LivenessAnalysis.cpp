#include <algorithm>
#include "LivenessAnalysis.h"
#include "MachineFunction.h"
#include "MachineBasicBlock.h"
#include "MachineModule.h"
#include "Target.h"
#include "Core/Log.h"

namespace ola
{
	static inline Uint32 GetRegAsUint(MachineOperand const& operand)
	{
		OLA_ASSERT(operand.IsReg() && (IsVirtualReg(operand.GetReg().reg) || IsISAReg(operand.GetReg().reg)));
		return static_cast<Uint32>(operand.GetReg().reg);
	}


	static void AssignInstNum(MachineFunction& MF, std::unordered_map<MachineInstruction*, Uint64>& inst_number_map)
	{
		// Number instructions in their natural block order (linearized program order)
		// This ensures all blocks get numbered, including fallthrough targets
		Uint64 current = 0;
		for (auto& block : MF.Blocks())
		{
			for (MachineInstruction& MI : block->Instructions())
			{
				inst_number_map[&MI] = current;
				current += 2;
			}
		}
	}

	static void CFGAnalysis(MachineFunction& MF) 
	{
		for (auto& block : MF.Blocks())
		{
			for (auto& MI : block->Instructions())
			{
				Uint32 opcode = MI.GetOpcode();
				if (opcode >= InstJump && opcode <= InstJNE)
				{
					MachineOperand MO = MI.GetOp<0>();
					OLA_ASSERT(MO.IsRelocable());
					OLA_ASSERT(MO.GetRelocable()->IsBlock());
					MachineBasicBlock* target = static_cast<MachineBasicBlock*>(MO.GetRelocable());
					block->AddSuccessor(target);
				}
			}
		}
	}

	LivenessAnalysisResult DoLivenessAnalysis(MachineModule& M, MachineFunction& MF)
	{
		LivenessAnalysisResult result{};
		TargetInstInfo const& target_inst_info = M.GetTarget().GetInstInfo();
		CFGAnalysis(MF);

		AssignInstNum(MF, result.instruction_numbering_map);
		std::unordered_map<Uint32, LiveInterval> live_interval_map;
		for (auto& MBB : MF.Blocks())
		{
			for (MachineInstruction& MI : MBB->Instructions())
			{
				Uint64 const instruction_idx = result.instruction_numbering_map[&MI];
				InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);
				for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
				{
					MachineOperand& MO = MI.GetOperand(idx);
					if (!IsOperandVReg(MO)) 
					{
						continue;
					}

					Uint32 reg_id = GetRegAsUint(MO);
					Bool is_float_reg = MO.GetType() == MachineType::Float64;

					if (inst_info.HasOpFlag(idx, OperandFlagDef))
					{
						if (!live_interval_map.contains(reg_id))
						{
							live_interval_map[reg_id].begin = instruction_idx;
							live_interval_map[reg_id].end = instruction_idx + 1;
							live_interval_map[reg_id].is_float = is_float_reg;
						}
						else
						{
							live_interval_map[reg_id].Extend(instruction_idx);
						}
					}
					else if (inst_info.HasOpFlag(idx, OperandFlagUse))
					{
						if (!live_interval_map.contains(reg_id))
						{
							live_interval_map[reg_id].begin = instruction_idx;
							live_interval_map[reg_id].end = instruction_idx + 1;
							live_interval_map[reg_id].is_float = is_float_reg;
						}
						else 
						{
							live_interval_map[reg_id].Extend(instruction_idx);
						}
					}
				}
			}
		}

		std::vector<LiveInterval> live_intervals;
		for (auto&& [vreg, interval] : live_interval_map)
		{
			if (interval.begin > interval.end) 
			{
				std::swap(interval.begin, interval.end);
			}
			live_intervals.push_back(LiveInterval{ .begin = interval.begin, .end = interval.end, .vreg = vreg, .spilled = false, .is_float = interval.is_float });
		}

		std::sort(std::begin(live_intervals), std::end(live_intervals));
		result.live_intervals = std::move(live_intervals);
		return result;
	}

}


