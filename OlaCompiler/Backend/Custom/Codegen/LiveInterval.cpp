#include "LiveInterval.h"
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


	LivenessAnalysisResult DoLivenessAnalysis(MIRModule& M, MIRFunction& MF)
	{
		LivenessAnalysisResult result{};

		for (auto& block : MF.Blocks()) 
		{
			BlockLivenessInfo& block_info = result.block_info_map[block.get()];
			for (MIRInstruction const& inst : block->Instructions())
			{
				MIRInstructionInfo const& inst_info = M.GetInstInfo(inst);
				for (uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx) 
				{
					MIROperand const& operand = inst.GetOperand(idx);
					if (!IsOperandVReg(operand)) continue;
					uint32 id = GetRegAsUint(operand);
					if (inst_info.HasOpFlag(idx, OperandFlagDef))
					{
						block_info.defs.insert(id);
					}
					else if (inst_info.HasOpFlag(idx, OperandFlagUse))
					{
						if (!block_info.defs.count(id)) block_info.uses.insert(id);
					}
					else OLA_ASSERT(false);
				}
			}
		}

        while (true) 
        {
            bool modified = false;
            for (auto& block : MF.Blocks())
			{
                auto b = block.get();
				BlockLivenessInfo& block_info = result.block_info_map[block.get()];
                std::unordered_set<uint32> outs;
                for (auto* S : b->Successors())
				{
                    for (auto in : result.block_info_map[S].ins) 
					{
                        outs.insert(in);
                    }
                }
                std::swap(block_info.outs, outs);
				std::unordered_set<uint32> ins = block_info.uses;
				for (uint32 out : block_info.outs)
				{
					if (!block_info.defs.contains(out))
					{
						ins.insert(out);
					}
				}
                if (ins != block_info.ins) 
				{
                    std::swap(block_info.ins, ins);
                    modified = true;
                }
            }
            if (!modified) break;
        }

		uint64 current = 0;
		for (auto& block : MF.Blocks()) 
		{
			for (MIRInstruction& inst : block->Instructions()) 
			{
				result.inst_num_map[&inst] = current;
				current += 4;
			}
		}

		for (auto& block : MF.Blocks())
		{
			BlockLivenessInfo& block_info = result.block_info_map[block.get()];
			std::unordered_map<uint32, LiveSegment> current_segment;
			std::unordered_map<uint32, std::pair<MIRInstruction*, std::vector<MIRRegisterFlag*>>> last_use_map;
			uint64 first_inst_num = 0;
			uint64 last_inst_num = 0;
			for (MIRInstruction& inst : block->Instructions()) 
			{
				MIRInstructionInfo const& inst_info = M.GetInstInfo(inst); 
				uint32 inst_num = result.inst_num_map[&inst];
				if (&inst == &block->Instructions().front()) first_inst_num = inst_num;
				last_inst_num = inst_num;

				for (uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx) 
				{
					MIROperand& operand = inst.GetOperand(idx);
					if (!IsOperandVReg(operand)) continue;
					uint32 reg_id = GetRegAsUint(operand);
					if (inst_info.HasOpFlag(idx, OperandFlagUse)) 
					{
						if (auto iter = current_segment.find(reg_id); iter != current_segment.end()) 
						{
							iter->second.end = inst_num + 1;
						}
						else 
						{
							current_segment[reg_id] = { first_inst_num, inst_num + 1 };
						}

						if (auto iter = last_use_map.find(reg_id); iter != last_use_map.cend())
						{
							if (iter->second.first == &inst)
								iter->second.second.push_back(&operand.GetReg().flag);
							else
								iter->second = { &inst, { &operand.GetReg().flag } };
						}
						else 
						{
							last_use_map[reg_id] = { &inst, { &operand.GetReg().flag } };
						}
					}
				}
				for (uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx) 
				{
					MIROperand& operand = inst.GetOperand(idx);
					if (!IsOperandVReg(operand)) continue;
					uint32 reg_id = GetRegAsUint(operand);
					if (inst_info.HasOpFlag(idx, OperandFlagDef))
					{
						if (current_segment.count(reg_id)) 
						{
							LiveSegment& segment = current_segment[reg_id];
							if (segment.end == inst_num + 1) 
							{
								segment.end = inst_num + 2;
							}
							else 
							{
								result.reg_interval_map[reg_id].AddSegment(segment);
								segment = { inst_num + 1, inst_num + 2 };

								if (auto iter = last_use_map.find(reg_id); iter != last_use_map.cend()) 
								{
									for (MIRRegisterFlag* flag : iter->second.second) *flag = MIRRegisterFlag_Dead;
									last_use_map.erase(iter);
								}
							}
						}
						else 
						{
							current_segment[reg_id] = { inst_num + 1, inst_num + 2 };
						}
					}
				}
			}
			for (auto& [id, segment] : current_segment)
			{
				if (block_info.outs.count(id)) 
				{
					segment.end = last_inst_num + 2;
				}
				result.reg_interval_map[id].AddSegment(segment);
			}
			for (auto& [id, flags] : last_use_map) 
			{
				if (block_info.outs.count(id))
					continue;

				for (MIRRegisterFlag* flag : flags.second) *flag = MIRRegisterFlag_Dead;
			}
			for (auto id : block_info.outs)
			{
				if (block_info.ins.contains(id) && !current_segment.contains(id))
					result.reg_interval_map[id].AddSegment({ first_inst_num, last_inst_num + 2 });
			}
		}

		return result;
	}

}


