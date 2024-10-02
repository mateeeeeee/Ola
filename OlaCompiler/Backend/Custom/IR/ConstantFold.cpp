#include "ConstantFold.h"
#include "Constant.h"
#include "IRContext.h"

namespace ola
{

	Value* TryConstantFold_BinaryInst(Opcode opcode, Value* lhs, Value* rhs)
	{
		IRContext& ctx = lhs->GetContext();

		ConstantInt* CI1 = dyn_cast<ConstantInt>(lhs);
		ConstantInt* CI2 = dyn_cast<ConstantInt>(rhs);
		if (CI1 && CI2)
		{
			switch (opcode)
			{
			case Opcode::Add:  return ctx.GetInt(lhs->GetType(), CI1->GetValue() + CI2->GetValue());
			case Opcode::Sub:  return ctx.GetInt(lhs->GetType(), CI1->GetValue() - CI2->GetValue());
			case Opcode::SMul: return ctx.GetInt(lhs->GetType(), CI1->GetValue() * CI2->GetValue());
			case Opcode::SDiv: return ctx.GetInt(lhs->GetType(), CI1->GetValue() / CI2->GetValue());
			case Opcode::Shl:  return ctx.GetInt(lhs->GetType(), CI1->GetValue() << CI2->GetValue());
			case Opcode::AShr: return ctx.GetInt(lhs->GetType(), CI1->GetValue() >> CI2->GetValue());
			}
		}

		ConstantFloat* CF1 = dyn_cast<ConstantFloat>(lhs);
		ConstantFloat* CF2 = dyn_cast<ConstantFloat>(rhs);
		if (CF1 && CF2)
		{
			OLA_ASSERT(lhs->GetType()->IsFloat());
			switch (opcode)
			{
			case Opcode::FAdd:  return ctx.GetFloat(CF1->GetValue() + CF2->GetValue());
			case Opcode::FSub:  return ctx.GetFloat(CF1->GetValue() - CF2->GetValue());
			case Opcode::FMul:  return ctx.GetFloat(CF1->GetValue() * CF2->GetValue());
			case Opcode::FDiv:  return ctx.GetFloat(CF1->GetValue() / CF2->GetValue());
			}
		}
		return nullptr;
	}

	Value* TryConstantFold_UnaryInst(Opcode opcode, Value* operand)
	{
		IRContext& ctx = operand->GetContext();
		ConstantInt* C = dyn_cast<ConstantInt>(operand);
		if (C)
		{
			switch (opcode)
			{
			case Opcode::Neg:  return ctx.GetInt(operand->GetType(), -C->GetValue());
			case Opcode::Not:  return ctx.GetInt(operand->GetType(), ~C->GetValue());
			}
		}
		return nullptr;
	}

	Value* TryConstantFold_CompareInst(Opcode opcode, Value* lhs, Value* rhs)
	{
		IRContext& ctx = lhs->GetContext();

		IRType* bool_type = IRIntType::Get(ctx, 1);

		ConstantInt* CI1 = dyn_cast<ConstantInt>(lhs);
		ConstantInt* CI2 = dyn_cast<ConstantInt>(rhs);
		if (CI1 && CI2)
		{
			switch (opcode)
			{
			case Opcode::ICmpEQ:  return ctx.GetInt(bool_type, CI1->GetValue() == CI2->GetValue());
			case Opcode::ICmpNE:  return ctx.GetInt(bool_type, CI1->GetValue() != CI2->GetValue());
			case Opcode::ICmpSGE: return ctx.GetInt(bool_type, CI1->GetValue() >= CI2->GetValue());
			case Opcode::ICmpSGT: return ctx.GetInt(bool_type, CI1->GetValue() > CI2->GetValue());
			case Opcode::ICmpSLE: return ctx.GetInt(bool_type, CI1->GetValue() <= CI2->GetValue());
			case Opcode::ICmpSLT: return ctx.GetInt(bool_type, CI1->GetValue() < CI2->GetValue());
			}
		}

		ConstantFloat* CF1 = dyn_cast<ConstantFloat>(lhs);
		ConstantFloat* CF2 = dyn_cast<ConstantFloat>(rhs);
		if (CF1 && CF2)
		{
			switch (opcode)
			{
			case Opcode::FCmpOEQ: return ctx.GetInt(bool_type, CF1->GetValue() == CF2->GetValue());
			case Opcode::FCmpONE: return ctx.GetInt(bool_type, CF1->GetValue() != CF2->GetValue());
			case Opcode::FCmpOGE: return ctx.GetInt(bool_type, CF1->GetValue() >= CF2->GetValue());
			case Opcode::FCmpOGT: return ctx.GetInt(bool_type, CF1->GetValue() > CF2->GetValue());
			case Opcode::FCmpOLE: return ctx.GetInt(bool_type, CF1->GetValue() <= CF2->GetValue());
			case Opcode::FCmpOLT: return ctx.GetInt(bool_type, CF1->GetValue() < CF2->GetValue());
			}
		}

		return nullptr;
	}

	Value* TryConstantFold_GetElementPtrInst(Value* base, std::span<Value*> indices)
	{
		if (!base) return nullptr;
		IRContext& ctx = base->GetContext();

		std::vector<ConstantInt*> constant_indices;
		for (Value* idx : indices)
		{
			if (!isa<ConstantInt>(idx)) return nullptr;
			constant_indices.push_back(cast<ConstantInt>(idx));
		}

		Value* base_address = base;
		uint32 offset = 0;
		IRType* current_type = base->GetType();
		for (ConstantInt* idx : constant_indices)
		{
			if (idx->GetType()->IsInteger())
			{
				if (IRArrayType* array_type = dyn_cast<IRArrayType>(current_type))
				{
					current_type = array_type->GetElementType();
				}
				else if (IRPtrType* pointer_type = dyn_cast<IRPtrType>(current_type))
				{
					current_type = pointer_type->GetPointeeType();
				}
			}
			else return nullptr;

			int64 index_value = idx->GetValue();
			offset += index_value * current_type->GetSize();
		}
		IRType* int_type = IRIntType::Get(base->GetContext(), 8);
		return new PtrAddInst(base, ctx.GetInt(int_type, offset), current_type);
	}
}
