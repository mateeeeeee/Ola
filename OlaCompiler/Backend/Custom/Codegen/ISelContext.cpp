#include "ISelContext.h"
#include "MIRGlobal.h"
#include "MIRModule.h"
namespace ola
{

	void ISelContext::Run(MIRFunction& MF)
	{
	}

	std::unordered_map<ola::MIROperand, ola::uint32> ISelContext::GetDefCount(MIRFunction& MF)
	{
		std::unordered_map<MIROperand, uint32> def_count;
		for (auto& block : MF.Blocks())
		{
			auto& instructions = block->Instructions();
			for (MIRInstruction& inst : instructions)
			{
				MIRInstructionInfo const& inst_info = module.GetInstInfo(inst); 
				if (inst_info.HasInstFlag(InstFlagLoadConstant))
				{
					MIROperand& dst = inst.GetOp<0>();
					if (IsOperandVReg(dst)) ++def_count[dst];
				}
				else 
				{
					for (uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
					{
						if (inst_info.HasOpFlag(idx, OperandFlagDef))
						{
							MIROperand& def = inst.GetOperand(idx);
							if (IsOperandVReg(def)) ++def_count[def];
						}
					}
				}
			}
		}
		return def_count;
	}
}

