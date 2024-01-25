#pragma once
#include "Instruction.h"

namespace ola
{
	class BinaryInstruction : public Instruction
	{
	public:

		static bool ClassOf(Instruction const* I)
		{
			return I->IsBinaryOp();
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}

	protected:
		BinaryInstruction(ValueKind kind, IRType* type, Value* op1, Value* op2, Instruction* position);
		BinaryInstruction(ValueKind kind, IRType* type, Value* op1, Value* op2, BasicBlock* bb = nullptr);
	};


	enum BinaryOpcode
	{
		Binary_Add,
		Binary_Sub
	};

	class BinaryOperator : public BinaryInstruction, public OpcodeConverter<BinaryOperator>
	{
		OPCODE_CONVERTER_IMPL(BinaryOperator, BinaryOpcode, ValueKind_Add)
	public:

		BinaryOperator(BinaryOpcode opcode, IRType* type, Value* op1, Value* op2, Instruction* position) : BinaryInstruction(OpcodeToValueKind(opcode), type, op1, op2, position)
		{
			OLA_ASSERT(op1->GetType() == op2->GetType());
		}
		BinaryOperator(BinaryOpcode opcode, IRType* type, Value* op1, Value* op2, BasicBlock* bb = nullptr) : BinaryInstruction(OpcodeToValueKind(opcode), type, op1, op2, bb)
		{
			OLA_ASSERT(op1->GetType() == op2->GetType());
		}
		BinaryOperator(BinaryOpcode opcode, Value* op1, Value* op2, Instruction* position) : BinaryOperator(opcode, op1->GetType(), op1, op2, position)
		{
			OLA_ASSERT(op1->GetType() == op2->GetType());
		}
		BinaryOperator(BinaryOpcode opcode, Value* op1, Value* op2, BasicBlock* bb = nullptr) : BinaryOperator(opcode, op1->GetType(), op1, op2, bb)
		{
			OLA_ASSERT(op1->GetType() == op2->GetType());
		}


		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && cast<Instruction>(V)->IsBinaryOp();
		}
	};
}