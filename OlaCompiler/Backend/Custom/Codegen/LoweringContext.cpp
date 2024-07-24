#include "LoweringContext.h"
#include "MIRBasicBlock.h"
#include "MIRGlobal.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Constant.h"

namespace ola
{
	MIROperandType GetOperandType(IRType const* type)
	{
		if (type->IsPointer())
		{
			return MIROperandType::Ptr;
		}
		if (type->IsInteger())
		{
			switch (cast<IRIntType>(type)->GetWidth())
			{
			case 1:
				return MIROperandType::Int8;
			case 8:
				return MIROperandType::Int64;
			default:
				OLA_ASSERT(false);
			}
		}
		if (type->IsFloat())
		{
			return MIROperandType::Float64;
		}
		OLA_ASSERT(false);
		return MIROperandType::Other;
	}
	MachineOpcode GetMachineID(Opcode opcode)
	{
		switch (opcode)
		{
		case Opcode::Neg:
			return InstNeg;
		case Opcode::Not:
			return InstNot;
		case Opcode::FNeg:
			return InstFNeg;
		case Opcode::Add:
			return InstAdd;
		case Opcode::Sub:
			return InstSub;
		case Opcode::Mul:
			return InstMul;
		case Opcode::UDiv:
			return InstUDiv;
		case Opcode::URem:
			return InstURem;
		case Opcode::And:
			return InstAnd;
		case Opcode::Or:
			return InstOr;
		case Opcode::Xor:
			return InstXor;
		case Opcode::Shl:
			return InstShl;
		case Opcode::LShr:
			return InstLShr;
		case Opcode::AShr:
			return InstAShr;
		case Opcode::FAdd:
			return InstFAdd;
		case Opcode::FSub:
			return InstFSub;
		case Opcode::FMul:
			return InstFMul;
		case Opcode::FDiv:
			return InstFDiv;
		}
		return InstUnknown;
	}

	MIROperand LoweringContext::GetOperand(Value const* V)
	{
		if (value_map.contains(V)) return value_map[V];
		OLA_ASSERT(V->IsConstant());
		Constant const* C = cast<Constant>(V);
		if (C->GetConstantID() == ConstantID::Global)
		{
			GlobalValue const* GV = cast<GlobalValue>(C);
			MIROperand ptr = VirtualReg(MIROperandType::Int64);
			MIRInstruction minst(InstStore);

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

	void LoweringContext::EmitInst(MIRInstruction const& MI)
	{
		auto& minst_list = current_block->Instructions();
		minst_list.emplace_back(MI);
	}

}