#include <algorithm>
#include <queue>
#include "LivenessAnalysis.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineModule.h"
#include "Backend/Custom/Codegen/Targets/Target.h"
#include "Core/Log.h"

namespace ola
{
	static inline Uint32 GetRegAsUint(MachineOperand const& operand)
	{
		OLA_ASSERT(operand.IsReg() && (IsVirtualReg(operand.GetReg().reg) || IsISAReg(operand.GetReg().reg)));
		return static_cast<Uint32>(operand.GetReg().reg);
	}

	static inline Bool IsTrackableRegOperand(MachineOperand const& MO)
	{
		if (!MO.IsReg()) 
		{
			return false;
		}
		Uint32 r = MO.GetReg().reg;
		return IsVirtualReg(r) || IsISAReg(r);
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
		auto& blocks = MF.Blocks();
		for (auto block_iter = blocks.begin(); block_iter != blocks.end(); ++block_iter)
		{
			auto& block = *block_iter;
			Bool terminates = false;
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
					if (opcode == InstJump) terminates = true;
				}
				else if (opcode == InstRet)
				{
					terminates = true;
				}
			}
			if (!terminates)
			{
				auto next_iter = std::next(block_iter);
				if (next_iter != blocks.end())
				{
					block->AddSuccessor(next_iter->get());
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

	static void ComputeLocalDefUse(MachineBasicBlock* MBB, BlockLivenessInfo& info,
								   TargetInstInfo const& target_inst_info,
								   TargetRegisterInfo const& target_reg_info)
	{
		for (MachineInstruction& MI : MBB->Instructions())
		{
			InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);
			for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
			{
				MachineOperand& MO = MI.GetOperand(idx);
				if (!IsTrackableRegOperand(MO)) 
				{
					continue;
				}
				if (!inst_info.HasOpFlag(idx, OperandFlagUse)) 
				{
					continue;
				}

				Uint32 reg_id = GetRegAsUint(MO);
				if (!info.def.contains(reg_id))
				{
					info.use.insert(reg_id);
				}
			}
			for (Uint32 idx = 0; idx < inst_info.GetImplicitUseCount(); ++idx)
			{
				Uint32 reg_id = inst_info.GetImplicitUse(idx);
				if (!info.def.contains(reg_id))
				{
					info.use.insert(reg_id);
				}
			}

			for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
			{
				MachineOperand& MO = MI.GetOperand(idx);
				if (!IsTrackableRegOperand(MO)) 
				{
					continue;
				}
				if (!inst_info.HasOpFlag(idx, OperandFlagDef)) 
				{
					continue;
				}

				Uint32 reg_id = GetRegAsUint(MO);
				info.def.insert(reg_id);
			}
			for (Uint32 idx = 0; idx < inst_info.GetImplicitDefCount(); ++idx)
			{
				info.def.insert(inst_info.GetImplicitDef(idx));
			}

			//Calls clobber all caller-saved regs
			if (inst_info.HasInstFlag(InstFlagCall))
			{
				for (Uint32 reg : target_reg_info.GetGPCallerSavedRegisters())
				{
					info.def.insert(reg);
				}
				for (Uint32 reg : target_reg_info.GetFPCallerSavedRegisters())
				{
					info.def.insert(reg);
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
		TargetRegisterInfo const& target_reg_info = M.GetTarget().GetRegisterInfo();
		CFGAnalysis(MF);

		std::unordered_map<MachineBasicBlock*, Uint64> block_start_map;
		std::unordered_map<MachineBasicBlock*, Uint64> block_end_map;
		AssignInstNum(MF, result.instruction_numbering_map, block_start_map, block_end_map);

		std::unordered_map<MachineBasicBlock*, BlockLivenessInfo> block_info;
		for (auto& MBB : MF.Blocks())
		{
			ComputeLocalDefUse(MBB.get(), block_info[MBB.get()], target_inst_info, target_reg_info);
		}

		while (ComputeLiveInOut(block_info)) {}

		std::unordered_map<Uint32, LiveInterval> live_interval_map;
		std::unordered_map<Uint32, Bool> reg_is_float;

		auto RecordReg = [&](Uint32 reg_id, Bool is_float, Uint64 idx)
		{
			reg_is_float[reg_id] = is_float;
			auto it = live_interval_map.find(reg_id);
			if (it == live_interval_map.end())
			{
				live_interval_map[reg_id].begin = idx;
				live_interval_map[reg_id].end = idx + 1;
			}
			else
			{
				it->second.Extend(idx);
			}
		};

		auto IsFloatPhysReg = [&](Uint32 reg) -> Bool
		{
			for (Uint32 fp : target_reg_info.GetFPRegisters())
			{
				if (fp == reg) return true;
			}
			return false;
		};

		for (auto& MBB : MF.Blocks())
		{
			BlockLivenessInfo& info = block_info[MBB.get()];
			Uint64 block_start = block_start_map[MBB.get()];
			Uint64 block_end = block_end_map[MBB.get()];
			for (Uint32 reg : info.live_in)
			{
				Bool is_float = IsISAReg(reg) ? IsFloatPhysReg(reg) : (reg_is_float.contains(reg) ? reg_is_float[reg] : false);
				RecordReg(reg, is_float, block_start);
			}
			for (Uint32 reg : info.live_out)
			{
				Bool is_float = IsISAReg(reg) ? IsFloatPhysReg(reg) : (reg_is_float.contains(reg) ? reg_is_float[reg] : false);
				RecordReg(reg, is_float, block_end);
			}

			for (MachineInstruction& MI : MBB->Instructions())
			{
				Uint64 inst_idx = result.instruction_numbering_map[&MI];
				InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);

				for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
				{
					MachineOperand& MO = MI.GetOperand(idx);
					if (!IsTrackableRegOperand(MO))
					{
						 continue;
					}
					if (!inst_info.HasOpFlag(idx, OperandFlagUse)) 
					{
						continue;
					}

					Uint32 reg_id = GetRegAsUint(MO);
					Bool is_float = MO.GetType() == MachineType::Float64;
					RecordReg(reg_id, is_float, inst_idx);
				}
				for (Uint32 idx = 0; idx < inst_info.GetImplicitUseCount(); ++idx)
				{
					Uint32 reg_id = inst_info.GetImplicitUse(idx);
					RecordReg(reg_id, IsFloatPhysReg(reg_id), inst_idx);
				}

				for (Uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
				{
					MachineOperand& MO = MI.GetOperand(idx);
					if (!IsTrackableRegOperand(MO)) continue;
					if (!inst_info.HasOpFlag(idx, OperandFlagDef)) continue;

					Uint32 reg_id = GetRegAsUint(MO);
					Bool is_float = MO.GetType() == MachineType::Float64;
					RecordReg(reg_id, is_float, inst_idx);
				}
				for (Uint32 idx = 0; idx < inst_info.GetImplicitDefCount(); ++idx)
				{
					Uint32 reg_id = inst_info.GetImplicitDef(idx);
					RecordReg(reg_id, IsFloatPhysReg(reg_id), inst_idx);
				}

				if (inst_info.HasInstFlag(InstFlagCall))
				{
					for (Uint32 reg : target_reg_info.GetGPCallerSavedRegisters())
					{
						RecordReg(reg, false, inst_idx);
					}
					for (Uint32 reg : target_reg_info.GetFPCallerSavedRegisters())
					{
						RecordReg(reg, true, inst_idx);
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
