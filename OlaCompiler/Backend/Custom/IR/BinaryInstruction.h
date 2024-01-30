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

	class StoreInst : public BinaryInstruction
	{
	public:
		StoreInst(Value* val, Value* address, Instruction* position) : BinaryInstruction(ValueKind_Store, VoidType::Get(val->GetContext()), val, address, position) {}
		StoreInst(Value* val, Value* address, BasicBlock* bb = nullptr) : BinaryInstruction(ValueKind_Store, VoidType::Get(val->GetContext()), val, address) {}

		Value* GetValueOperand() { return GetOperand(0); }
		Value const* GetValueOperand() const { return GetOperand(0); }

		Value* GetAddressOperand() { return GetOperand(1); }
		Value const* GetAddressOperand() const { return GetOperand(1); }
		IRType* GetAddressOperandType() const { return GetAddressOperand()->GetType(); }

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind_Store;
		}
	};

	enum CmpPredicate : uint16
	{
		FCMP_EQ,
		FCMP_GT,
		FCMP_GE,
		FCMP_LT,
		FCMP_LE,
		FCMP_NE,
		ICMP_EQ,
		ICMP_NE,
		ICMP_UGT,
		ICMP_UGE,
		ICMP_ULT,
		ICMP_ULE,
		ICMP_SGT,
		ICMP_SGE,
		ICMP_SLT,
		ICMP_SLE,
	};

	class CmpInst : public BinaryInstruction
	{
	public:
		CmpInst(CmpPredicate predicate, Value* lhs, Value* rhs, Instruction* position)
			: BinaryInstruction(ValueKind_Cmp, IntegerType::Get(lhs->GetContext(), 1), lhs, rhs, position), predicate(predicate)
		{
			OLA_ASSERT(lhs->GetType() == rhs->GetType());
		}
		CmpInst(CmpPredicate predicate, Value* lhs, Value* rhs, BasicBlock* bb = nullptr)
			: BinaryInstruction(ValueKind_Cmp, IntegerType::Get(lhs->GetContext(), 1), lhs, rhs, bb), predicate(predicate)
		{
			OLA_ASSERT(lhs->GetType() == rhs->GetType());
		}

		CmpPredicate GetPredicate() const { return predicate; }

		bool IsFPPredicate() const { return IsFPPredicate(GetPredicate()); }
		bool IsIntPredicate() const { return IsIntPredicate(GetPredicate()); }

		static bool IsFPPredicate(CmpPredicate P)
		{
			return P >= FCMP_EQ && P <= FCMP_NE;
		}
		static bool IsIntPredicate(CmpPredicate P)
		{
			return P >= ICMP_EQ && P <= ICMP_SLE;
		}

		static bool ClassOf(Value const* V) 
		{
			return isa<Instruction>(V) && cast<Instruction>(V)->GetKind() == ValueKind_Cmp;
		}

	private:
		CmpPredicate predicate;
	};

}