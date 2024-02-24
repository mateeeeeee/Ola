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

	enum UnaryOpcode : uint8
	{
		Unary_Neg,
		Unary_Not
	};

	class UnaryOperator : public UnaryInstruction, public OpcodeConverter<UnaryOperator>
	{
		OPCODE_CONVERTER_IMPL(UnaryOperator, UnaryOpcode, ValueKind_Neg)
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

	enum CastOpcode
	{
		Cast_Zext,
		Cast_Sext,
	};
	
	
	class CastInst : public UnaryInstruction, public OpcodeConverter<CastInst>
	{
		OPCODE_CONVERTER_IMPL(CastInst, CastOpcode, ValueKind_Zext)
	public:
		CastInst(CastOpcode opcode, IRType* type, Value* op, Instruction* position) 
			: UnaryInstruction(OpcodeToValueKind(opcode), type, op, position)
		{}

		CastInst(CastOpcode opcode, IRType* type, Value* op, BasicBlock* bb = nullptr)
			: UnaryInstruction(OpcodeToValueKind(opcode), type, op, bb)
		{}


		IRType* GetSrcType() const { return GetOperand(0)->GetType(); }
		IRType* GetDestType() const { return GetType(); }

		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && cast<Instruction>(V)->IsCast();
		}
	
	private:
	};

	class LoadInst : public UnaryInstruction 
	{
	public:
		LoadInst(IRType* type, Value* ptr, Instruction* position) : UnaryInstruction(ValueKind_Load, type, ptr, position) {}
		LoadInst(IRType* type, Value* ptr, BasicBlock* bb = nullptr) : UnaryInstruction(ValueKind_Load, type, ptr, bb) {}

		Value* GetPointerOperand() { return GetOperand(0); }
		Value const* GetPointerOperand() const { return GetOperand(0); }
		IRType* getPointerOperandType() const { return GetPointerOperand()->GetType(); }

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind_Load;
		}
	};

	class AllocaInst : public UnaryInstruction
	{
	public:
		explicit AllocaInst(IRType* type, Value* array_size = nullptr)
			: UnaryInstruction(ValueKind_Alloca, IRPtrType::Get(type), array_size), allocated_type(type) {}

		AllocaInst(IRType* type, Value* array_size, Instruction* insert_before)
			: UnaryInstruction(ValueKind_Alloca, IRPtrType::Get(type), array_size, insert_before), allocated_type(type) {}
		AllocaInst(IRType* type, Value* array_size, BasicBlock* insert_at_end)
			: UnaryInstruction(ValueKind_Alloca, IRPtrType::Get(type), array_size, insert_at_end), allocated_type(type) {}
		AllocaInst(IRType* type, Instruction* insert_before)
			: AllocaInst(type, nullptr, insert_before) {}
		AllocaInst(IRType* type, BasicBlock* insert_at_end)
			: AllocaInst(type, nullptr, insert_at_end) {}

		bool IsArrayAllocation() const
		{
			return GetArraySize() != nullptr;
		}

		IRPtrType* GetPtrType() const
		{
			return cast<IRPtrType>(GetType());
		}
		IRType* GetAllocatedType() const { return allocated_type; }

		Value const* GetArraySize() const { return GetOperand(0); }
		Value* GetArraySize() { return GetOperand(0); }



		static bool ClassOf(Value const* V) { return V->GetKind() == ValueKind_Alloca; }

	private:
		IRType* allocated_type;
	};

}