#pragma once
#include "Instruction.h"

namespace ola
{
	class UnaryInstruction : public Instruction
	{
	public:

		static bool ClassOf(Instruction const* I) 
		{
			return I->IsUnaryOp() || I->GetKind() == ValueKind_Alloca;
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}

	protected:
		UnaryInstruction(ValueKind kind, IRType* type, Value* op, Instruction* position);
		UnaryInstruction(ValueKind kind, IRType* type, Value* op, BasicBlock* bb = nullptr);
	};

	enum UnaryOpcode
	{
		Unary_Neg,
		Unary_Not
	};


	class UnaryOperator : public UnaryInstruction
	{
		static UnaryOpcode ValueKindToOpcode(ValueKind kind)
		{
			return (UnaryOpcode)(kind - ValueKind_Neg);
		}
		static ValueKind OpcodeToValueKind(UnaryOpcode opcode)
		{
			return (ValueKind)(opcode + ValueKind_Neg);
		}

	public:

		UnaryOperator(UnaryOpcode opcode, IRType* type, Value* op, Instruction* position) 
			: UnaryInstruction(OpcodeToValueKind(opcode), type, op, position) {}
		UnaryOperator(UnaryOpcode opcode, IRType* type, Value* op, BasicBlock* bb = nullptr) 
			: UnaryInstruction(OpcodeToValueKind(opcode), type, op, bb) {}
		UnaryOperator(UnaryOpcode opcode, Value* op, Instruction* position) : UnaryOperator(opcode, op->GetType(), op, position) {}
		UnaryOperator(UnaryOpcode opcode, Value* op, BasicBlock* bb = nullptr) : UnaryOperator(opcode, op->GetType(), op, bb) {}

		UnaryOpcode GetOpcode() const { return ValueKindToOpcode(GetKind()); }

		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && cast<Instruction>(V)->IsUnaryOp();
		}
	};

	//enum CastOpcode
	//{
	//	Cast_Zext,
	//	Cast_Sext,
	//};
	//
	//
	//class CastInst : public UnaryInstruction
	//{
	//public:
	//	CastInst(
	//		CastOpcode opcode,    ///< The opcode of the cast instruction
	//		Value* S,                ///< The value to be casted (operand 0)
	//		Type* Ty,          ///< The type to which cast should be made
	//		const Twine& Name = "", ///< Name for the instruction
	//		Instruction* InsertBefore = nullptr ///< Place to insert the instruction
	//	);
	//
	//private:
	//};


	class AllocaInst : public UnaryInstruction
	{
	public:
		explicit AllocaInst(IRType* type, Value* array_size = nullptr)
			: UnaryInstruction(ValueKind_Alloca, PointerType::Get(type), array_size), allocated_type(type) {}

		AllocaInst(IRType* type, Value* array_size, Instruction* insert_before)
			: UnaryInstruction(ValueKind_Alloca, PointerType::Get(type), array_size, insert_before), allocated_type(type) {}
		AllocaInst(IRType* type, Value* array_size, BasicBlock* insert_at_end)
			: UnaryInstruction(ValueKind_Alloca, PointerType::Get(type), array_size, insert_at_end), allocated_type(type) {}
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

		static bool ClassOf(Value* V) { return V->GetKind() == ValueKind_Alloca; }

	private:
		IRType* allocated_type;
	};

}