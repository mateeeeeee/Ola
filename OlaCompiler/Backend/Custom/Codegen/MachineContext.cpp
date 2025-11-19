#include "MachineContext.h"
#include "MachineBasicBlock.h"
#include "MachineGlobal.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Constant.h"

namespace ola
{
	MachineType GetOperandType(IRType const* type)
	{
		if (type->IsPointer())
		{
			return MachineType::Ptr;
		}
		if (type->IsInteger())
		{
			switch (cast<IRIntType>(type)->GetWidth())
			{
			case 1:
				return MachineType::Int8;
			case 8:
				return MachineType::Int64;
			default:
				OLA_ASSERT(false);
			}
		}
		if (type->IsFloat())
		{
			return MachineType::Float64;
		}
		OLA_ASSERT(false);
		return MachineType::Other;
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
		case Opcode::ICmpNE:
		case Opcode::ICmpSGE:
		case Opcode::ICmpSGT:
		case Opcode::ICmpSLE:
		case Opcode::ICmpSLT:
			return InstICmp;
		case Opcode::FCmpOEQ:
		case Opcode::FCmpONE:
		case Opcode::FCmpOGE:
		case Opcode::FCmpOGT:
		case Opcode::FCmpOLE:
		case Opcode::FCmpOLT:
			return InstFCmp;
		case Opcode::ZExt:
			return InstZExt;
		case Opcode::F2S:
			return InstF2S;
		case Opcode::S2F:
			return InstS2F;
		}
		return InstUnknown;
	}

	MachineOperand MachineContext::GetOperand(Value const* V)
	{
		if (value_map.contains(V)) return value_map[V];
		if (Constant const* C = dyn_cast<Constant>(V))
		{
			if (C->GetConstantID() == ConstantID::Global)
			{
				GlobalValue const* GV = cast<GlobalValue>(C);
				if (GV->GetValueType()->IsArray())
				{
					MachineInstruction MI(InstLoadGlobalAddress);
					MachineGlobal* machine_global = global_map[GV];
					OLA_ASSERT(machine_global);
					MachineOperand global = MachineOperand::Relocable(machine_global->GetRelocable());
					MachineOperand ptr = VirtualReg(MachineType::Int64);
					MI.SetOp<0>(ptr).SetOp<1>(global);
					EmitInst(MI);
					return ptr;
				}
				else
				{
					MachineInstruction MI(InstLoad);
					MachineGlobal* machine_global = global_map[GV];
					OLA_ASSERT(machine_global);
					MachineOperand global = MachineOperand::Relocable(machine_global->GetRelocable());
					return global;
				}
			}
			else if (C->GetConstantID() == ConstantID::Integer)
			{
				ConstantInt const* CI = cast<ConstantInt>(C);
				MachineOperand imm = MachineOperand::Immediate(CI->GetValue(), GetOperandType(CI->GetType()));
				return imm;
			}
			else if (C->GetConstantID() == ConstantID::Float)
			{
				ConstantFloat const* CF = cast<ConstantFloat>(C);
				Float64 value = CF->GetValue();
				MachineOperand imm = MachineOperand::Immediate(value, MachineType::Float64);
				return imm;
			}
			else
			{
				OLA_ASSERT(false);
				return MachineOperand::Undefined();
			}
		}
		return MachineOperand::Undefined();
	}

	MachineInstruction& MachineContext::EmitInst(MachineInstruction const& MI)
	{
		auto& MachineInstList = current_block->Instructions();
		return MachineInstList.emplace_back(MI);
	}

	MachineInstruction& MachineContext::EmitInstAtStart(MachineInstruction const& MI)
	{
		auto& MachineInstList = current_block->Instructions();
		return MachineInstList.emplace_front(MI);
	}

	MachineInstruction& MachineContext::EmitInstBeforeTerminator(MachineInstruction const& MI)
	{
		auto& MachineInstList = current_block->Instructions();
		auto it = MachineInstList.end();
		it = std::prev(it, 1);
		return *MachineInstList.insert(it, MI);
	}

	std::list<MachineInstruction>::iterator MachineContext::EmitInst(std::list<MachineInstruction>::iterator where, MachineInstruction const& MI)
	{
		auto& MachineInstList = current_block->Instructions();
		return MachineInstList.insert(where, MI);
	}

}