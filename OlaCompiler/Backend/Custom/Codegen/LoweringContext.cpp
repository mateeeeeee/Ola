#include "LoweringContext.h"
#include "MIRBasicBlock.h"
#include "Backend/Custom/IR/IRType.h"

namespace ola
{

	void LoweringContext::EmitInst(MIRInstruction const& minst)
	{
		auto& minst_list = current_block->Instructions();
		minst_list.emplace_back(minst);
	}

	MIROperandType LoweringContext::GetOperandType(IRType const* type)
	{
		if (type->IsPointerType())
		{
			return MIROperandType::Ptr;
		}
		if (type->IsIntegerType())
		{
			switch (cast<IRIntType>(type)->GetWidth())
			{
			case 1:
				return MIROperandType::Bool;
			case 8:
				return MIROperandType::Int8;
			case 16:
				return MIROperandType::Int16;
			case 32:
				return MIROperandType::Int32;
			case 64:
				return MIROperandType::Int64;
			default:
				OLA_ASSERT(false);
			}
		}
		if (type->IsFloatType()) 
		{
			return MIROperandType::Float64;
		}
		OLA_ASSERT(false);
		return MIROperandType::Other;
	}

}

