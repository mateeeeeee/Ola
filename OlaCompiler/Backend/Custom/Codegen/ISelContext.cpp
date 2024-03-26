#include "ISelContext.h"
#include "MIRGlobal.h"
#include "MIRModule.h"
namespace ola
{

	void ISelContext::Run(MIRFunction& MF)
	{
		while (true) 
		{
			MIRInstruction* first_illegal_inst = nullptr;
			bool modified = false;
			bool has_illegal = false;
			replace_block_list.clear();
			replace_list.clear();

			constant_mapping.clear();
			use_count.clear();


			auto def_count = GetDefCount(MF);
			for (auto& block : MF.Blocks()) 
			{
				for (MIRInstruction& inst : block->Instructions()) 
				{
					MIRInstructionInfo const& inst_info = module.GetInstInfo(inst);
					if (inst_info.HasInstFlag(InstFlagLoadConstant))
					{
						MIROperand& def = GetInstDef(inst);
						if (IsOperandVReg(def) && def_count[def] <= 1)
							constant_mapping.emplace(def, &inst);
					}

					for (uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx) 
					{
						if (inst_info.HasOpFlag(idx, OperandFlagUse))
						{
							MIROperand& operand = inst.GetOperand(idx);
							if (IsOperandVReg(operand))
							{
								++use_count[operand];
							}
						}
					}
				}
			}


			for (auto& block : MF.Blocks()) 
			{
				instruction_mapping.clear();
				for (MIRInstruction& inst : block->Instructions())
				{
					MIRInstructionInfo const& inst_info = module.GetInstInfo(inst);
					for (uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
						if (inst_info.HasOpFlag(idx, OperandFlagDef))
						{
							MIROperand& operand = inst.GetOperand(idx);
							if (IsOperandVReg(operand))
							{
								if (instruction_mapping.contains(operand)) 
								{
									OLA_ASSERT_MSG(false, "Invalid SSA form");
								}
								instruction_mapping.emplace(operand, &inst);
							}
						}
				}
				current_block = block.get();

				auto& instructions = block->Instructions();
				if (instructions.empty()) continue;

				auto it = std::prev(instructions.end());
				while (true)
				{
					current_ip = it;
					MIRInstruction& inst = *it;
				}

				for (auto& block : MF.Blocks()) 
				{
					for (MIRInstruction& inst : block->Instructions())
					{
						if (replace_block_list.count(&inst)) continue;
						MIRInstructionInfo const& inst_info = module.GetInstInfo(inst);
						for (uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
						{
							MIROperand& operand = inst.GetOperand(idx);
							if (!operand.IsReg()) continue;
							if (auto iter = replace_list.find(operand); iter != replace_list.cend()) operand = iter->second;
						}
					}
				}
			}
		}
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

	MIROperand& ISelContext::GetInstDef(MIRInstruction& inst) const
	{
		MIRInstructionInfo const& inst_info = module.GetInstInfo(inst);
		for (uint32 idx = 0; idx < inst_info.GetOperandCount(); ++idx)
			if (inst_info.HasOpFlag(idx, OperandFlagDef)) return inst.GetOperand(idx);
		OLA_UNREACHABLE();
	}

}

