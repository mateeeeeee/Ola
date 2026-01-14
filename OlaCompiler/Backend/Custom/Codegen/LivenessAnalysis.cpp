#include <algorithm>
#include <queue>
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

	static void AssignInstNum(MachineFunction& MF, std::unordered_map<MachineInstruction*, Uint64>& inst_number_map,
							  std::unordered_map<MachineBasicBlock*, Uint64>& block_start_map,
							  std::unordered_map<MachineBasicBlock*, Uint64>& block_end_map)
	{
		Uint64 current = 0;
		for (auto& block : MF.Blocks())
		{
			block_start_map[block.get()] = current;
			for (MachineInstruction& MI : block->Instructions())
			{
				inst_number_map[&MI] = current;
				current += 2;
			}
			block_end_map[block.get()] = current;
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

	struct BlockLivenessInfo
	{
		std::unordered_set<Uint32> def;      // Registers defined in this block (before any use)
		std::unordered_set<Uint32> use;      // Registers used in this block (before any def)
		std::unordered_set<Uint32> live_in;  // Registers live at block entry
		std::unordered_set<Uint32> live_out; // Registers live at block exit
	};

	static void ComputeLocalDefUse(MachineBasicBlock* MBB, BlockLivenessInfo& info, TargetInstInfo const& target_inst_info)
	{
		for (MachineInstruction& MI : MBB->Instructions())
		{
			InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);
			// Process uses first (before defs for this instruction)
			for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
			{
				MachineOperand& MO = MI.GetOperand(idx);
				if (!IsOperandVReg(MO)) continue;

				Uint32 reg_id = GetRegAsUint(MO);
				if (inst_info.HasOpFlag(idx, OperandFlagUse))
				{
					// If not already defined in this block, it's a use (upward exposed)
					if (!info.def.contains(reg_id))
					{
						info.use.insert(reg_id);
					}
				}
			}

			// Then process defs
			for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
			{
				MachineOperand& MO = MI.GetOperand(idx);
				if (!IsOperandVReg(MO)) continue;

				Uint32 reg_id = GetRegAsUint(MO);
				if (inst_info.HasOpFlag(idx, OperandFlagDef))
				{
					info.def.insert(reg_id);
				}
			}
		}
	}

	// Backward dataflow analysis:
	// live_out[B] = ∪ live_in[S] for all successors S
	// live_in[B] = use[B] ∪ (live_out[B] - def[B])
	static Bool ComputeLiveInOut(std::unordered_map<MachineBasicBlock*, BlockLivenessInfo>& block_info)
	{

		Bool changed = false;
		for (auto& [MBB, info] : block_info)
		{
			// Compute live_out as union of successors' live_in
			std::unordered_set<Uint32> new_live_out;
			for (MachineBasicBlock* succ : MBB->Successors())
			{
				for (Uint32 reg : block_info[succ].live_in)
				{
					new_live_out.insert(reg);
				}
			}

			// Compute live_in = use ∪ (live_out - def)
			std::unordered_set<Uint32> new_live_in = info.use;
			for (Uint32 reg : new_live_out)
			{
				if (!info.def.contains(reg))
				{
					new_live_in.insert(reg);
				}
			}

			// Check if anything changed
			if (new_live_out != info.live_out || new_live_in != info.live_in)
			{
				changed = true;
				info.live_out = std::move(new_live_out);
				info.live_in = std::move(new_live_in);
			}
		}
		return changed;
	}

	LivenessAnalysisResult DoLivenessAnalysis(MachineModule& M, MachineFunction& MF)
	{
		LivenessAnalysisResult result{};
		TargetInstInfo const& target_inst_info = M.GetTarget().GetInstInfo();
		CFGAnalysis(MF);

		// Assign instruction numbers and track block boundaries
		std::unordered_map<MachineBasicBlock*, Uint64> block_start_map;
		std::unordered_map<MachineBasicBlock*, Uint64> block_end_map;
		AssignInstNum(MF, result.instruction_numbering_map, block_start_map, block_end_map);

		std::unordered_map<MachineBasicBlock*, BlockLivenessInfo> block_info;
		for (auto& MBB : MF.Blocks())
		{
			ComputeLocalDefUse(MBB.get(), block_info[MBB.get()], target_inst_info);
		}

		while (ComputeLiveInOut(block_info)) {}
		
		std::unordered_map<Uint32, LiveInterval> live_interval_map;
		std::unordered_map<Uint32, Bool> reg_is_float;
		for (auto& MBB : MF.Blocks())
		{
			BlockLivenessInfo& info = block_info[MBB.get()];
			Uint64 block_start = block_start_map[MBB.get()];
			Uint64 block_end = block_end_map[MBB.get()];
			for (Uint32 reg : info.live_in)
			{
				if (!live_interval_map.contains(reg))
				{
					live_interval_map[reg].begin = block_start;
					live_interval_map[reg].end = block_start + 1;
				}
				else
				{
					live_interval_map[reg].Extend(block_start);
				}
			}

			for (Uint32 reg : info.live_out)
			{
				if (!live_interval_map.contains(reg))
				{
					live_interval_map[reg].begin = block_end;
					live_interval_map[reg].end = block_end + 1;
				}
				else
				{
					live_interval_map[reg].Extend(block_end);
				}
			}

			std::unordered_set<Uint32> currently_live = info.live_in;
			for (MachineInstruction& MI : MBB->Instructions())
			{
				Uint64 inst_idx = result.instruction_numbering_map[&MI];
				InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);

				for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
				{
					MachineOperand& MO = MI.GetOperand(idx);
					if (!IsOperandVReg(MO)) continue;

					Uint32 reg_id = GetRegAsUint(MO);
					Bool is_float = MO.GetType() == MachineType::Float64;
					reg_is_float[reg_id] = is_float;

					if (inst_info.HasOpFlag(idx, OperandFlagUse))
					{
						if (live_interval_map.contains(reg_id))
						{
							live_interval_map[reg_id].Extend(inst_idx);
						}
						else
						{
							live_interval_map[reg_id].begin = inst_idx;
							live_interval_map[reg_id].end = inst_idx + 1;
						}
					}
				}

				for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
				{
					MachineOperand& MO = MI.GetOperand(idx);
					if (!IsOperandVReg(MO)) continue;

					Uint32 reg_id = GetRegAsUint(MO);
					Bool is_float = MO.GetType() == MachineType::Float64;
					reg_is_float[reg_id] = is_float;

					if (inst_info.HasOpFlag(idx, OperandFlagDef))
					{
						if (!live_interval_map.contains(reg_id))
						{
							live_interval_map[reg_id].begin = inst_idx;
							live_interval_map[reg_id].end = inst_idx + 1;
						}
						else
						{
							live_interval_map[reg_id].Extend(inst_idx);
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
			Bool is_float = reg_is_float.contains(vreg) ? reg_is_float[vreg] : false;
			live_intervals.push_back(LiveInterval{
				.begin = interval.begin,
				.end = interval.end,
				.vreg = vreg,
				.spilled = false,
				.is_float = is_float
			});
		}

		std::sort(std::begin(live_intervals), std::end(live_intervals));
		result.live_intervals = std::move(live_intervals);
		return result;
	}

}
