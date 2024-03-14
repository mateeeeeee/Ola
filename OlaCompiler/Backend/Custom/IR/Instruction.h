#pragma once
#include <vector>
#include "Value.h"
#include "Compiler/RTTI.h"
#include "Utility/IntrusiveList.h"
#include "Utility/IteratorRange.h"

namespace ola
{
	class BasicBlock;
	class Instruction;
	class IRType;

	enum class InstructionID : uint32
	{
		None,
		// control-flow
		// terminators
		TerminatorBegin,
		Ret,
		Branch,
		ConditionalBranch,
		Unreachable,
		Switch,
		TerminatorEnd,
		// memory ops
		MemoryOpBegin,
		Load,
		Store,
		MemoryOpEnd,
		// integer arithmetic ops
		IntegerOpBegin,
		Add,
		Sub,
		Mul,
		SDiv,
		UDiv,
		SRem,
		URem,
		Neg,
		Abs,
		// bitwise ops
		And,
		Or,
		Xor,
		Shl,
		LShr,
		AShr,
		SMin,
		SMax,
		IntegerOpEnd,
		// floating point ops
		FloatingPointOpBegin,
		FAdd,
		FSub,
		FMul,
		FDiv,
		FNeg,
		FAbs,
		FFma,
		FloatingPointOpEnd,
		// compare ops
		CompareOpBegin,
		ICmp,
		FCmp,
		CompareOpEnd,
		// cast ops
		CastOpBegin,
		SExt,
		ZExt,
		SignedTrunc,
		UnsignedTrunc,
		Bitcast,
		F2U,
		F2S,
		U2F,
		S2F,
		FCast,
		CastOpEnd,
		// miscellaneous
		Alloc,
		GetElementPtr,
		PtrCast,
		PtrToInt,
		IntToPtr,
		PtrAdd,
		Select,
		Call,
		Phi,
		FunctionPtr
	};

	class Use : public IListNode<Use>
	{
	public:
		Use(Value* val, Instruction* user);
		~Use();

		Value* operator=(Value* rhs)
		{
			Set(rhs);
			return rhs;
		}

		Value* GetValue() const { return value; }
		Instruction* GetUser() const { return user; }

		operator Value* () const { return value; }
		Value* Get() const { return value; }
		void Set(Value*  V);

		Value* operator->() { return value; }
		Value const* operator->() const { return value; }

	private:
		Value* value;
		Instruction* user;
	};

	class TrackableValue : public Value
	{
	public:
		bool ReplaceWith(Value* value);
		bool ReplaceWithInBlock(BasicBlock* block, Value* value);

		IList<Use>& Users()
		{
			return users;
		}
		IList<Use> const& Users() const
		{
			return users;
		}

		void AddUse(Use* u)
		{
			users.PushBack(u);
		}
		void RemoveUse(Use* u)
		{
			users.PushBack(u);
		}
		void ReplaceAllUseWith(Value* V)
		{
			for (auto& use : users) use.Set(V);
		}

		bool IsUsed() const
		{
			return users.Size() > 0;
		}
		bool HasOneUse() const { return users.Size() == 1; }
		bool HasNUses(uint32 N) const { return users.Size() == N; }
		bool HasNUsesOrMore(unsigned N) const { return users.Size() >= N; }

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::Instruction || V->GetKind() == ValueKind::Global;
		}
	private:
		IList<Use> users;

	protected:
		TrackableValue(ValueKind kind, IRType* type) : Value(kind, type) {}
	};

	class Instruction : public TrackableValue, public IListNode<Instruction>
	{
	public:

		InstructionID GetInstrID() const 
		{
			return instr_id;
		}
		BasicBlock* GetBasicBlock() const
		{
			return basic_block;
		}

		void InsertBefore(BasicBlock* block, Instruction* pos);

#define GET_INST_CATEGORY(KIND) bool Is##KIND() const { return InstructionID::KIND##Begin < instr_id && instr_id < InstructionID::KIND##End; }
		GET_INST_CATEGORY(Terminator)
		GET_INST_CATEGORY(MemoryOp)
		GET_INST_CATEGORY(IntegerOp)
		GET_INST_CATEGORY(FloatingPointOp)
		GET_INST_CATEGORY(CastOp)
		GET_INST_CATEGORY(CompareOp)
#undef GET_INST_CATEGORY

		bool IsBranch() const 
		{
			return instr_id == InstructionID::Branch || instr_id == InstructionID::ConditionalBranch ||
				instr_id == InstructionID::Switch;
		}
		bool CanBeOperand() const;

		Use const* GetOperandList() const
		{
			return operands.data();
		}
		Use* GetOperandList()
		{
			return operands.data();
		}
		uint32 GetNumOperands() const
		{
			return (uint32)operands.size();
		}
		Value* GetOperand(uint32 i) const
		{
			return GetOperandList()[i];
		}
		void SetOperand(uint32 i, Value* val)
		{
			GetOperandList()[i] = val;
		}
		Use const& GetOperandUse(uint32 i) const
		{
			return GetOperandList()[i];
		}
		Use& GetOperandUse(uint32 i)
		{
			return GetOperandList()[i];
		}

		using OpIterator = Use*;
		using ConstOpIterator = Use const*;
		using OpRange = IteratorRange<OpIterator>;
		using ConstOpRange = IteratorRange<ConstOpIterator>;

		OpIterator      OpBegin() { return GetOperandList(); }
		ConstOpIterator OpBegin()  const { return GetOperandList(); }
		OpIterator      OpEnd() { return GetOperandList() + GetNumOperands(); }
		ConstOpIterator OpEnd()    const { return GetOperandList() + GetNumOperands(); }
		OpRange			Operands() { return OpRange(OpBegin(), OpEnd()); }
		ConstOpRange	Operands() const { return ConstOpRange(OpBegin(), OpEnd()); }

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::Instruction;
		}
	private:
		InstructionID instr_id;
		std::vector<Use> operands;
		BasicBlock* basic_block;

	protected:
		Instruction(InstructionID instr_id, IRType* type, std::vector<Value*> op_values = {}) : TrackableValue(ValueKind::Instruction, type),
			instr_id(instr_id), basic_block(nullptr)
		{
			for (Value* op_value : op_values)
			{
				operands.emplace_back(op_value, this);
			}
		}

		template <uint32 Idx>
		Use& Op()
		{
			return operands[Idx];
		}
		template <uint32 Idx>
		Use const& Op() const
		{
			return operands[Idx];
		}
	};

	class BinaryInst final : public Instruction 
	{
	public:
		BinaryInst(InstructionID instID, Value* lhs, Value* rhs) : Instruction{ instID, lhs->GetType(), { lhs, rhs } } 
		{
			OLA_ASSERT(lhs->GetType() == rhs->GetType());
		}

		Value* LHS() const
		{
			return Op<0>();
		}

		Value* RHS() const
		{
			return Op<1>();
		}
		
		static bool ClassOf(Instruction const* I)
		{
			switch (I->GetInstrID())
			{
			case InstructionID::Add:
			case InstructionID::Sub:
			case InstructionID::SDiv:
			case InstructionID::UDiv:
				return true;
			}
			return false;
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};
}