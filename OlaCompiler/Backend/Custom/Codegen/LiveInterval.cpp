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

		return result;
	}

}


