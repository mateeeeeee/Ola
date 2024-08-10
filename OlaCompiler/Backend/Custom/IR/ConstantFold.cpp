#include "ConstantFold.h"
#include "Constant.h"

namespace ola
{

	Value* TryConstantFold_BinaryInst(Opcode opcode, Value* lhs, Value* rhs)
	{
		ConstantInt* C1 = dyn_cast<ConstantInt>(lhs);
		ConstantInt* C2 = dyn_cast<ConstantInt>(rhs);
		if (C1 && C2)
		{
			switch (opcode)
			{
			case Opcode::Add:  return new ConstantInt(lhs->GetType(), C1->GetValue() + C2->GetValue());
			case Opcode::Sub:  return new ConstantInt(lhs->GetType(), C1->GetValue() - C2->GetValue());
			case Opcode::SMul: return new ConstantInt(lhs->GetType(), C1->GetValue() * C2->GetValue());
			case Opcode::SDiv: return new ConstantInt(lhs->GetType(), C1->GetValue() / C2->GetValue());
			case Opcode::Shl:  return new ConstantInt(lhs->GetType(), C1->GetValue() << C2->GetValue());
			case Opcode::AShr: return new ConstantInt(lhs->GetType(), C1->GetValue() >> C2->GetValue());
			}
		}
		return nullptr;
	}

	Value* TryConstantFold_UnaryInst(Opcode opcode, Value* operand)
	{
		ConstantInt* C = dyn_cast<ConstantInt>(operand);
		if (C)
		{
			switch (opcode)
			{
			case Opcode::Neg:  return new ConstantInt(operand->GetType(), -C->GetValue());
			case Opcode::Not:  return new ConstantInt(operand->GetType(), ~C->GetValue());
			}
		}
		return nullptr;
	}

	Value* TryConstantFold_CompareInst(Opcode opcode, Value* lhs, Value* rhs)
	{
		ConstantInt* C1 = dyn_cast<ConstantInt>(lhs);
		ConstantInt* C2 = dyn_cast<ConstantInt>(rhs);

		IRType* bool_type = IRIntType::Get(lhs->GetContext(), 1);
		if (C1 && C2)
		{
			switch (opcode)
			{
			case Opcode::ICmpEQ:  return new ConstantInt(bool_type, C1->GetValue() == C2->GetValue());
			case Opcode::ICmpNE:  return new ConstantInt(bool_type, C1->GetValue() != C2->GetValue());
			case Opcode::ICmpSGE: return new ConstantInt(bool_type, C1->GetValue() >= C2->GetValue());
			case Opcode::ICmpSGT: return new ConstantInt(bool_type, C1->GetValue() > C2->GetValue());
			case Opcode::ICmpSLE: return new ConstantInt(bool_type, C1->GetValue() <= C2->GetValue());
			case Opcode::ICmpSLT: return new ConstantInt(bool_type, C1->GetValue() < C2->GetValue());
			}
		}
		return nullptr;
	}

}
