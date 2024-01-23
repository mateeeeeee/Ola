#pragma once
#include "Instruction.h"

namespace ola
{
	class UnaryInstruction : public Instruction
	{
	public:

		static bool ClassOf(Value const* V)
		{
			switch (V->GetKind())
			{
			case ValueKind::Alloca:
				return true;
			default:
				return false;
			}
			return false;
		}

	protected:
		UnaryInstruction(ValueKind kind, IRType* type, Value* op, Instruction* position);
		UnaryInstruction(ValueKind kind, IRType* type, Value* op, BasicBlock* bb = nullptr);
	};

	class AllocaInst : public UnaryInstruction
	{
	public:
		explicit AllocaInst(IRType* type, Value* array_size = nullptr)
			: UnaryInstruction(ValueKind::Alloca, PointerType::Get(type), array_size), allocated_type(type) {}

		AllocaInst(IRType* type, Value* array_size, Instruction* insert_before)
			: UnaryInstruction(ValueKind::Alloca, PointerType::Get(type), array_size, insert_before), allocated_type(type) {}
		AllocaInst(IRType* type, Value* array_size, BasicBlock* insert_at_end)
			: UnaryInstruction(ValueKind::Alloca, PointerType::Get(type), array_size, insert_at_end), allocated_type(type) {}
		AllocaInst(IRType* type, Instruction* insert_before)
			: AllocaInst(type, nullptr, insert_before) {}
		AllocaInst(IRType* type, BasicBlock* insert_at_end)
			: AllocaInst(type, nullptr, insert_at_end) {}

		bool IsArrayAllocation() const
		{
			return false;
		}

		PointerType* GetPtrType() const
		{
			return cast<PointerType>(GetType());
		}
		IRType* GetAllocatedType() const { return allocated_type; }

		Value const* GetArraySize() const { return GetOperand(0); }
		Value* GetArraySize() { return GetOperand(0); }

		static bool ClassOf(Value* V) { return V->GetKind() == ValueKind::Alloca; }

	private:
		IRType* allocated_type;
	};

}