#include "LoweringContext.h"
#include "MIRBasicBlock.h"
#include "MIRGlobal.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Constant.h"

namespace ola
{

	MIROperand LoweringContext::GetOperand(Value const* V)
	{
		if (value_map.contains(V)) return value_map[V];
		OLA_ASSERT(V->IsConstant());
		Constant const* C = cast<Constant>(V);
		if (C->GetConstantID() == ConstantID::Global)
		{
			GlobalValue const* GV = cast<GlobalValue>(C);
			MIROperand ptr = VirtualReg(MIROperandType::Int64);
			MIRInstruction minst(InstMove);

			MIRGlobal* mir_global = global_map[GV];
			OLA_ASSERT(mir_global);

			MIROperand global = MIROperand::Relocable(mir_global->GetRelocable());
			minst.SetOp<0>(ptr).SetOp<1>(global);
			EmitInst(minst);
			return ptr;
		}
		else if (C->GetConstantID() == ConstantID::Integer)
		{
			ConstantInt const* CI = cast<ConstantInt>(C);
			MIROperand imm = MIROperand::Immediate(CI->GetValue(), MIROperandType::Int64);
			return imm;
		}
		else
		{
			OLA_ASSERT(false);
			return MIROperand();
		}
	}

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