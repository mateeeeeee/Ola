#include "LoweringContext.h"
#include "MachineBasicBlock.h"
#include "MachineGlobal.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Constant.h"

namespace ola
{
	MachineOperandType GetOperandType(IRType const* type)
	{
		if (type->IsPointer())
		{
			return MachineOperandType::Ptr;
		}
		if (type->IsInteger())
		{
			switch (cast<IRIntType>(type)->GetWidth())
			{
			case 1:
				return MachineOperandType::Int8;
			case 8:
				return MachineOperandType::Int64;
			default:
				OLA_ASSERT(false);
			}
		}
		if (type->IsFloat())
		{
			return MachineOperandType::Float64;
		}
		OLA_ASSERT(false);
		return MachineOperandType::Other;
	}
	MachineOpcode GetMachineOpcode(Opcode opcode)
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
		case Opcode::SMul:
			return InstSMul;
		case Opcode::SDiv:
			return InstSDiv;
		case Opcode::SRem:
			return InstSRem;
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
		case Opcode::ICmpEQ:
			return InstICmpEQ;
		case Opcode::ICmpNE:
			return InstICmpNE;
		case Opcode::ICmpSGE:
			return InstICmpSGE;
		case Opcode::ICmpSGT:
			return InstICmpSGT;
		case Opcode::ICmpSLE:
			return InstICmpSLE;
		case Opcode::ICmpSLT:
			return InstICmpSLT;
		case Opcode::ZExt:
			return InstZExt;
		}
		return InstUnknown;
	}

	MachineOperand LoweringContext::GetOperand(Value const* V)
	{
		if (value_map.contains(V)) return value_map[V];
		OLA_ASSERT(V->IsConstant());
		Constant const* C = cast<Constant>(V);
		if (C->GetConstantID() == ConstantID::Global)
		{
			GlobalValue const* GV = cast<GlobalValue>(C);
			MachineOperand ptr = VirtualReg(MachineOperandType::Int64);
			MachineInstruction minst(InstStore);

			MachineGlobal* machine_global = global_map[GV];
			OLA_ASSERT(machine_global);

			MachineOperand global = MachineOperand::Relocable(machine_global->GetRelocable());
			minst.SetOp<0>(ptr).SetOp<1>(global);
			EmitInst(minst);
			return ptr;
		}
		else if (C->GetConstantID() == ConstantID::Integer)
		{
			ConstantInt const* CI = cast<ConstantInt>(C);
			MachineOperand imm = MachineOperand::Immediate(CI->GetValue(), MachineOperandType::Int64);
			return imm;
		}
		else
		{
			OLA_ASSERT(false);
			return MachineOperand();
		}
	}

	void LoweringContext::EmitInst(MachineInstruction const& MI)
	{
		auto& minst_list = current_block->Instructions();
		minst_list.emplace_back(MI);
	}

}