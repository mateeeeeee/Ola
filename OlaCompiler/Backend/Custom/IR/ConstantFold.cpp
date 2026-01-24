#include "ConstantFold.h"
#include "Constant.h"
#include "IRContext.h"
#include "IRType.h"
#include "BasicBlock.h"

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
		ConstantInt* CI = dyn_cast<ConstantInt>(operand);
		if (CI)
		{
			switch (opcode)
			{
			case Opcode::Neg:  return ctx.GetInt(operand->GetType(), -CI->GetValue());
			case Opcode::Not:  return ctx.GetInt(operand->GetType(), ~CI->GetValue());
			}
		}
		ConstantFloat* CF = dyn_cast<ConstantFloat>(operand);
		if (CF && opcode == Opcode::Neg)
		{
			ctx.GetFloat(-CF->GetValue());
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
		Uint32 offset = 0;
		IRType* current_type = base->GetType();
		for (ConstantInt* idx : constant_indices)
		{
			if (!idx->GetType()->IsInteger())
			{
				return nullptr;
			}

			Int64 index_value = idx->GetValue();
			if (IRArrayType* array_type = dyn_cast<IRArrayType>(current_type))
			{
				current_type = array_type->GetElementType();
				offset += index_value * current_type->GetSize();
			}
			else if (IRPtrType* pointer_type = dyn_cast<IRPtrType>(current_type))
			{
				current_type = pointer_type->GetPointeeType();
				offset += index_value * current_type->GetSize();
			}
			else if (IRStructType* struct_type = dyn_cast<IRStructType>(current_type))
			{
				Uint32 field_offset = 0;
				for (Int64 i = 0; i < index_value; ++i)
				{
					IRType* field_type = struct_type->GetMemberType(i);
					field_offset = OLA_ALIGN_UP(field_offset, field_type->GetAlign());
					field_offset += field_type->GetSize();
				}
				if (index_value < (Int64)struct_type->GetMemberCount())
				{
					IRType* target_field_type = struct_type->GetMemberType(index_value);
					field_offset = OLA_ALIGN_UP(field_offset, target_field_type->GetAlign());
					current_type = target_field_type;
				}
				offset += field_offset;
			}
			else
			{
				return nullptr;
			}
		}
		IRType* int_type = IRIntType::Get(base->GetContext(), 8);
		return new PtrAddInst(base, ctx.GetInt(int_type, offset), current_type);
	}

	Value* TryConstantFold_SelectInst(Value* predicate, Value* lhs, Value* rhs)
	{
		if (!predicate) return nullptr;
		ConstantInt* CI = dyn_cast<ConstantInt>(predicate);
		if (CI)
		{
			return CI->GetValue() != 0 ? lhs : rhs;
		}
		return nullptr;
	}

	Value* TryConstantFold_BranchInst(Value* condition, BasicBlock* true_target, BasicBlock* false_target)
	{
		if (!condition) return nullptr;
		ConstantInt* CI = dyn_cast<ConstantInt>(condition);
		if (CI)
		{
			IRContext& ctx = CI->GetContext();
			return CI->GetValue() != 0 ? new BranchInst(ctx, true_target) : new BranchInst(ctx, false_target);
		}
		return nullptr;
	}

}
