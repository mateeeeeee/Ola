#pragma once
#include <vector>
#include <span>
#include <unordered_map>
#include <unordered_set>
#include "Value.h"
#include "Compiler/RTTI.h"
#include "Utility/IntrusiveList.h"
#include "Utility/IteratorRange.h"

namespace ola
{
	class BasicBlock;
	class Instruction;
	class Function;
	class IRType;
	class IRPtrType;

	enum class Opcode : uint32
	{
		None,

		TerminatorBegin,
		Ret = TerminatorBegin,
		Branch,
		Switch,
		TerminatorEnd = Switch,

		MemoryOpBegin,
		Load = MemoryOpBegin,
		Store,
		MemoryOpEnd = Store,
		
		IntegerOpBegin,
		Add = IntegerOpBegin,
		Sub,
		SMul,
		SDiv,
		SRem,
		Neg,
		// bitwise ops
		Not,
		And,
		Or,
		Xor,
		Shl,
		LShr,
		AShr,
		IntegerOpEnd = AShr,
		// floating point ops
		FloatOpBegin,
		FAdd = FloatOpBegin,
		FSub,
		FMul,
		FDiv,
		FNeg,
		FFma,
		FloatOpEnd = FFma,
		// compare ops
		CompareOpBegin,
		ICmpEQ = CompareOpBegin,
		ICmpNE,
		ICmpSLT,
		ICmpSLE,
		ICmpSGT,
		ICmpSGE,
		ICmpULT,
		ICmpULE,
		ICmpUGT,
		ICmpUGE,

		FCmpOEQ,
		FCmpONE,
		FCmpOLT,
		FCmpOLE,
		FCmpOGT,
		FCmpOGE,
		FCmpUEQ,
		FCmpUNE,
		FCmpULT,
		FCmpULE,
		FCmpUGT,
		FCmpUGE,
		CompareOpEnd = FCmpUGE,
		// cast ops
		CastOpBegin,
		ZExt = CastOpBegin,
		Bitcast,
		F2S,
		S2F,
		CastOpEnd = S2F,
		// misc
		Alloca,
		GetElementPtr,
		PtrAdd,
		Select,
		Call,
		Phi,
		Count
	};

	inline bool IsOpcodeTerminator(Opcode opcode)
	{
		return Opcode::TerminatorBegin <= opcode && opcode <= Opcode::TerminatorEnd;
	}
	inline bool IsOpcodeMemoryOp(Opcode opcode) 
	{
		return Opcode::MemoryOpBegin <= opcode && opcode <= Opcode::MemoryOpEnd;
	}
	inline bool IsOpcodeIntegerOp(Opcode opcode) 
	{
		return Opcode::IntegerOpBegin <= opcode && opcode <= Opcode::IntegerOpEnd;
	}
	inline bool IsOpcodeFloatOp(Opcode opcode) 
	{
		return Opcode::FloatOpBegin <= opcode && opcode <= Opcode::FloatOpEnd;
	}
	inline bool IsOpcodeCastOp(Opcode opcode) 
	{
		return Opcode::CastOpBegin <= opcode && opcode <= Opcode::CastOpEnd;
	}
	inline bool IsOpcodeCompareOp(Opcode opcode) 
	{
		return Opcode::CompareOpBegin <= opcode && opcode <= Opcode::CompareOpEnd;
	}
	inline bool IsOpcodeBinaryOp(Opcode opcode)
	{
		switch (opcode)
		{
		case Opcode::Add:
		case Opcode::Sub:
		case Opcode::SMul:
		case Opcode::SDiv:
		case Opcode::SRem:
		case Opcode::And:
		case Opcode::Or:
		case Opcode::Xor:
		case Opcode::Shl:
		case Opcode::LShr:
		case Opcode::AShr:
		case Opcode::FAdd:
		case Opcode::FSub:
		case Opcode::FMul:
		case Opcode::FDiv:
		case Opcode::FFma:
			return true;
		default:
			return false;
		}
	}
	inline bool IsOpcodeUnaryOp(Opcode opcode)
	{
		switch (opcode)
		{
		case Opcode::Neg:
		case Opcode::Not:
		case Opcode::FNeg:
			return true;
		default:
			return false;
		}
	}
	
	class Use 
	{
	public:
		Use() : value(nullptr), user(nullptr) {}
		Use(Value* val, Instruction* user);
		~Use();

		Value* operator=(Value* rhs)
		{
			Set(rhs);
			return rhs;
		}

		void SetValue(Value* V) { value = V; }
		Value* GetValue() const { return value; }
		Instruction* GetUser() const { return user; }

		operator Value* () const { return value; }
		Value* Get() const { return value; }
		void Set(Value* V);

		Value* operator->() { return value; }
		Value const* operator->() const { return value; }

	private:
		Value* value;
		Instruction* user;
	};

	class TrackableValue : public Value
	{
	public:
		void AddUse(Use* u)
		{
			users.insert(u);
		}
		void RemoveUse(Use* u)
		{
			users.erase(u);
		}
		void ReplaceAllUseWith(Value* V);

		bool IsUsed() const
		{
			return !users.empty();
		}
		bool HasOneUse() const { return users.size() == 1; }
		bool HasNUses(uint32 N) const { return users.size() == N; }
		bool HasNUsesOrMore(unsigned N) const { return users.size() >= N; }

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::Instruction || V->GetKind() == ValueKind::Constant;
		}
	private:
		std::unordered_set<Use*> users;

	protected:
		TrackableValue(ValueKind kind, IRType* type) : Value(kind, type) {}
	};

	class Instruction : public TrackableValue, public IListNode<Instruction>
	{
	public:
		Instruction() : TrackableValue(ValueKind::Instruction, nullptr), opcode(Opcode::None), basic_block(nullptr) {}

		Opcode GetOpcode() const 
		{
			return opcode;
		}
		char const* GetOpcodeName() const;

		BasicBlock* GetBasicBlock() const
		{
			return basic_block;
		}

		IListIterator<Instruction> InsertBefore(BasicBlock* BB, IListIterator<Instruction> IT);
		IListIterator<Instruction> InsertBefore(BasicBlock* BB, Instruction* I);

		void RemoveFromParent();
		IListIterator<Instruction> EraseFromParent();

		bool IsTerminator() const 
		{
			return IsOpcodeTerminator(opcode);
		}
		bool IsMemoryOp() const 
		{
			return IsOpcodeMemoryOp(opcode);
		}
		bool IsIntegerOp() const 
		{
			return IsOpcodeIntegerOp(opcode);
		}
		bool IsFloatOp() const
		{
			return IsOpcodeFloatOp(opcode);
		}
		bool IsCastOp() const 
		{
			return IsOpcodeCastOp(opcode);
		}
		bool IsUnaryOp() const
		{
			return IsOpcodeUnaryOp(opcode);
		}
		bool IsBinaryOp() const
		{
			return IsOpcodeBinaryOp(opcode);
		}
		bool IsCompareOp() const
		{
			return IsOpcodeCompareOp(opcode);
		}

		bool IsBranch() const 
		{
			return opcode == Opcode::Branch || opcode == Opcode::Switch;
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
		Opcode opcode;
		std::vector<Use> operands;
		BasicBlock* basic_block;

	protected:
		Instruction(Opcode opcode, IRType* type, std::vector<Value*> const& ops = {}) : TrackableValue(ValueKind::Instruction, type),
			opcode(opcode), basic_block(nullptr)
		{
			operands.reserve(8);
			for (Value* op : ops)
			{
				operands.emplace_back(op, this);
			}
		}

		void ClearOperands()
		{
			operands.clear();
		}

		void AddOperand(Value* op)
		{
			operands.emplace_back(op, this);
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
		BinaryInst(Opcode opcode, Value* lhs, Value* rhs) : Instruction{ opcode, lhs->GetType(), { lhs, rhs } }
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
			return I->IsBinaryOp();
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	class UnaryInst final : public Instruction 
	{
	public:
		UnaryInst(Opcode opcode, Value* val) : Instruction(opcode, val->GetType(), { val }) {}
		
		Value* Operand() const
		{
			return Op<0>();
		}

		static bool ClassOf(Instruction const* I)
		{
			return I->IsUnaryOp();
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	enum class CompareOp
	{
		ICmpEQ,
		ICmpNE,
		ICmpSLT,
		ICmpSLE,
		ICmpSGT,
		ICmpSGE,
		ICmpULT,
		ICmpULE,
		ICmpUGT,
		ICmpUGE,

		FCmpOEQ,
		FCmpONE,
		FCmpOLT,
		FCmpOLE,
		FCmpOGT,
		FCmpOGE,
		FCmpUEQ,
		FCmpUNE,
		FCmpULT,
		FCmpULE,
		FCmpUGT,
		FCmpUGE
	};

	class CompareInst final : public Instruction
	{
	public:
		CompareInst(Opcode id, Value* lhs, Value* rhs);

		Value* LHS() const
		{
			return Op<0>();
		}
		Value* RHS() const
		{
			return Op<1>();
		}

		CompareOp GetCompareOp() const { return cmp; }

		static bool ClassOf(Instruction const* I)
		{
			return I->IsCompareOp();
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}

	private:
		CompareOp cmp;
	};

	class CastInst final : public Instruction 
	{
	public:
		CastInst(Opcode opcode, IRType* cast_type, Value* src_value) 
			: Instruction(opcode, cast_type, { src_value }) {}
		
		Value*  GetSrc() const { return Op<0>(); }
		IRType* GetSrcType() const { return Op<0>()->GetType(); }
		IRType* GetDestType() const { return GetType(); }

		static bool ClassOf(Instruction const* I)
		{
			return I->IsCastOp();
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	class LoadInst final : public Instruction
	{
	public:
		explicit LoadInst(Value* address);
		LoadInst(Value* address, IRType* type);

		Value* GetAddressOp() { return GetOperand(0); }
		Value const* GetAddressOp() const { return GetOperand(0); }

		static bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Load;
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	class StoreInst final : public Instruction
	{
	public:
		StoreInst(Value* value, Value* address);

		Value* GetValueOp() { return GetOperand(0); }
		Value const* GetValueOp() const { return GetOperand(0); }

		Value* GetAddressOp() { return GetOperand(1); }
		Value const* GetAddressOp() const { return GetOperand(1); }

		static bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Store;
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	private:
	};

	class BranchInst final : public Instruction
	{
	public:
		BranchInst(IRContext& C, BasicBlock* target);
		BranchInst(Value* condition, BasicBlock* true_target, BasicBlock* false_target);

		bool IsUnconditional() const { return !IsConditional(); }
		bool IsConditional()   const { return false_target != nullptr; }

		BasicBlock* GetTrueTarget() const { return true_target; }
		BasicBlock* GetFalseTarget() const { return false_target; }

		Value* GetCondition() const
		{
			OLA_ASSERT(IsConditional());
			return Op<2>();
		}
		void SetCondition(Value* C)
		{
			OLA_ASSERT(IsConditional());
			Op<2>() = C;
		}

		static bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Branch;
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}

	private:
		BasicBlock* true_target;
		BasicBlock* false_target;
	};

	class ReturnInst final : public Instruction
	{
	public:
		explicit ReturnInst(IRContext& C);
		explicit ReturnInst(Value* ret_value);

		bool IsVoid() const { return !GetReturnValue(); }
		Value* GetReturnValue() const
		{
			return GetNumOperands() > 0 ? GetOperand(0) : nullptr;
		}

		static bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Ret;
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	class SwitchInst final : public Instruction 
	{
	public:
		SwitchInst(Value* val, BasicBlock* default_block);

		void AddCase(int64 key, BasicBlock* label)
		{
			cases.emplace_back(key, label);
		}
		auto& Cases() 
		{
			return cases;
		}
		auto const& Cases() const
		{
			return cases;
		}

		BasicBlock* GetDefaultCase() const
		{
			return default_block;
		}

		BasicBlock* GetCaseBlock(uint32 case_idx) const
		{
			if (case_idx >= cases.size()) return nullptr;
			return cases[case_idx].second;
		}
		int64 GetCaseValue(uint32 case_idx) const
		{
			if (case_idx >= cases.size()) return INT64_MAX;
			return cases[case_idx].first;
		}

		Value* GetCondition() const { return GetOperand(0); }
		void SetCondition(Value* V) { SetOperand(0, V); }

		uint32 GetNumCases() const
		{
			return cases.size();
		}

		static bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Switch;
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}

	private:
		BasicBlock* default_block;
		std::vector<std::pair<int64, BasicBlock*>> cases;
	};

	class CallInst final : public Instruction
	{
	public:
		CallInst(Value* callee, std::span<Value*> args);

		auto ArgBegin() { return OpBegin(); }
		auto ArgBegin() const { return OpBegin(); }
		auto ArgEnd() { return OpEnd() - 1; }
		auto ArgEnd() const { return OpEnd() - 1; }
		IteratorRange<OpIterator> Args() { return MakeRange(ArgBegin(), ArgEnd()); }
		IteratorRange<ConstOpIterator> Args() const { return MakeRange(ArgBegin(), ArgEnd()); }
		bool ArgEmpty() const { return ArgEnd() == ArgBegin(); }
		uint32 ArgSize() const { return ArgEnd() - ArgBegin(); }

		Value const* GetArgOp(uint32 i) const
		{
			OLA_ASSERT_MSG(i < ArgSize(), "Out of bounds!");
			return GetOperand(i);
		}
		void SetArgOp(uint32 i, Value* v)
		{
			OLA_ASSERT_MSG(i < ArgSize(), "Out of bounds!");
			SetOperand(i, v);
		}

		Use const& GetArgOpUse(unsigned i) const
		{
			OLA_ASSERT_MSG(i < ArgSize(), "Out of bounds!");
			return GetOperandUse(i);
		}
		Use& GetArgOpUse(unsigned i)
		{
			OLA_ASSERT_MSG(i < ArgSize(), "Out of bounds!");
			return GetOperandUse(i);
		}

		Value* GetCallee() const { return GetOperand(GetNumOperands() - 1); }
		Use const& GetCalleeUse() const { return GetOperandUse(GetNumOperands() - 1); }
		Use& GetCalleeUse() { return GetOperandUse(GetNumOperands() - 1); }

		Function* GetCalleeAsFunction() const;
		Function* GetCaller() const;

		static bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Call;
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	class SelectInst final : public Instruction 
	{
	public:
		SelectInst(Value* predicate, Value* lhs, Value* rhs) : Instruction( Opcode::Select, lhs->GetType(), { predicate, lhs, rhs } )
		{
			OLA_ASSERT(lhs->GetType() == rhs->GetType());
		}

		const Value* GetPredicate() const  { return Op<0>(); }
		const Value* GetTrueValue() const  { return Op<1>(); }
		const Value* GetFalseValue() const { return Op<2>(); }
		Value* GetPredicate()  { return Op<0>(); }
		Value* GetTrueValue()  { return Op<1>(); }
		Value* GetFalseValue() { return Op<2>(); }

		void SetCondition(Value* V) { Op<0>() = V; }
		void SetTrueValue(Value* V) { Op<1>() = V; }
		void SetFalseValue(Value* V) { Op<2>() = V; }

		static bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Select;
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	class AllocaInst final : public Instruction
	{
	public:
		explicit AllocaInst(IRType* type);

		IRPtrType* GetPtrType() const;
		IRType* GetAllocatedType() const { return allocated_type; }

		static bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Alloca;
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	private:
		IRType* allocated_type;
	};

	class GetElementPtrInst final : public Instruction 
	{
	public:
		static IRType* GetValueType(Value* base, std::span<Value*> indices);

		GetElementPtrInst(Value* base, std::span<Value*> indices);

		uint32 GetNumIndices() const { return GetNumOperands() - 1; }
		bool HasIndices() const { return GetNumIndices() > 0; }

		OpIterator       IdxBegin() { return OpBegin() + 1; }
		ConstOpIterator  IdxBegin() const { return OpBegin() + 1; }
		OpIterator       IdxEnd() { return OpEnd(); }
		ConstOpIterator  IdxEnd()   const { return OpEnd(); }
		IteratorRange<OpIterator> Indices()
		{
			return MakeRange(IdxBegin(), IdxEnd());
		}
		IteratorRange<ConstOpIterator> Indices()  const
		{
			return MakeRange(IdxBegin(), IdxEnd());
		}

		Value* GetBaseOperand()	       const { return GetOperand(0); }
		IRType* GetSourceElementType() const { return source_element_type; }
		IRType* GetResultElementType() const { return result_element_type; }

		static bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::GetElementPtr;
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}

	private:
		IRType* source_element_type;
		IRType* result_element_type;
	};

	class PtrAddInst final : public Instruction 
	{
	public:
		explicit PtrAddInst(Value* base, Value* offset, IRType* result_element_type);

		Value* GetBase() const { return Op<0>(); }
		Value* GetOffset() const { return Op<1>(); }
		IRType* GetResultElementType() const { return result_element_type; }

		static bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::PtrAdd;
		}
		static bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}

	private:
		IRType* result_element_type;
	};


	class PhiInst final : public Instruction 
	{
	public:
		explicit PhiInst(IRType* type) : Instruction( Opcode::Phi, type, {} ) {}

		void AddIncoming(BasicBlock* block, Value* value);

		auto& Incomings()  
		{
			return incomings;
		}
		auto const& Incomings() const
		{
			return incomings;
		}

		void Clear()
		{
			incomings.clear();
			ClearOperands();
		}
		void RemoveSource(BasicBlock* block)
		{

		}
		void ReplaceSource(BasicBlock* old_block, BasicBlock* new_block)
		{

		}
		void KeepOneIncoming(BasicBlock* block)
		{

		}

	private:
		std::unordered_map<void const*, Use> incomings;
	};
}