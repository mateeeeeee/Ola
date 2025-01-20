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

	enum class Opcode : Uint32
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

	inline Bool IsOpcodeTerminator(Opcode opcode)
	{
		return Opcode::TerminatorBegin <= opcode && opcode <= Opcode::TerminatorEnd;
	}
	inline Bool IsOpcodeMemoryOp(Opcode opcode)
	{
		return Opcode::MemoryOpBegin <= opcode && opcode <= Opcode::MemoryOpEnd;
	}
	inline Bool IsOpcodeIntegerOp(Opcode opcode)
	{
		return Opcode::IntegerOpBegin <= opcode && opcode <= Opcode::IntegerOpEnd;
	}
	inline Bool IsOpcodeFloatOp(Opcode opcode)
	{
		return Opcode::FloatOpBegin <= opcode && opcode <= Opcode::FloatOpEnd;
	}
	inline Bool IsOpcodeCastOp(Opcode opcode)
	{
		return Opcode::CastOpBegin <= opcode && opcode <= Opcode::CastOpEnd;
	}
	inline Bool IsOpcodeCompareOp(Opcode opcode)
	{
		return Opcode::CompareOpBegin <= opcode && opcode <= Opcode::CompareOpEnd;
	}
	inline Bool IsOpcodeBinaryOp(Opcode opcode)
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
	inline Bool IsOpcodeUnaryOp(Opcode opcode)
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
		using UserSet = std::unordered_set<Use*>;
	public:

		~TrackableValue();

		void AddUse(Use* u)
		{
			users.insert(u);
		}
		void RemoveUse(Use* u)
		{
			users.erase(u);
		}
		OLA_MAYBE_UNUSED Bool ReplaceAllUsesWith(Value* V);

		Bool IsUsed() const
		{
			return !users.empty();
		}
		Bool HasOneUse() const { return users.size() == 1; }
		Bool HasNUses(Uint32 N) const { return users.size() == N; }
		Bool HasNUsesOrMore(Uint32 N) const { return users.size() >= N; }

		using UserIterator = UserSet::iterator;
		using ConstUserIterator = UserSet::const_iterator;
		using UserRange = IteratorRange<UserIterator>;
		using ConstUserRange = IteratorRange<ConstUserIterator>;

		UserIterator	  UserBegin() { return users.begin(); }
		ConstUserIterator UserBegin() const { return users.begin(); }
		UserIterator      UserEnd() { return users.end(); }
		ConstUserIterator UserEnd() const { return users.end(); }
		UserRange		  Users() { return UserRange(UserBegin(), UserEnd()); }
		ConstUserRange	  Users() const { return ConstUserRange(UserBegin(), UserEnd()); }

		static Bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::Instruction || V->GetKind() == ValueKind::Constant || V->GetKind() == ValueKind::BasicBlock;
		}
	private:
		UserSet users;

	protected:
		TrackableValue(ValueKind kind, IRType* type) : Value(kind, type) {}
	};

	class Instruction : public TrackableValue, public IListNode<Instruction>
	{
	public:
		Instruction() : TrackableValue(ValueKind::Instruction, nullptr), opcode(Opcode::None), basic_block(nullptr) {}
		~Instruction();

		Opcode GetOpcode() const
		{
			return opcode;
		}
		Char const* GetOpcodeName() const;

		void SetBasicBlock(BasicBlock* BB)
		{
			basic_block = BB;
		}
		BasicBlock* GetBasicBlock() const
		{
			return basic_block;
		}

		IListIterator<Instruction> InsertBefore(BasicBlock* BB, IListIterator<Instruction> IT);
		IListIterator<Instruction> InsertBefore(BasicBlock* BB, Instruction* I);

		OLA_MAYBE_UNUSED Instruction* RemoveFromParent();
		OLA_MAYBE_UNUSED IListIterator<Instruction> EraseFromParent();

		Bool IsTerminator() const
		{
			return IsOpcodeTerminator(opcode);
		}
		Bool IsMemoryOp() const
		{
			return IsOpcodeMemoryOp(opcode);
		}
		Bool IsIntegerOp() const
		{
			return IsOpcodeIntegerOp(opcode);
		}
		Bool IsFloatOp() const
		{
			return IsOpcodeFloatOp(opcode);
		}
		Bool IsCastOp() const
		{
			return IsOpcodeCastOp(opcode);
		}
		Bool IsUnaryOp() const
		{
			return IsOpcodeUnaryOp(opcode);
		}
		Bool IsBinaryOp() const
		{
			return IsOpcodeBinaryOp(opcode);
		}
		Bool IsCompareOp() const
		{
			return IsOpcodeCompareOp(opcode);
		}

		Bool IsBranch() const
		{
			return opcode == Opcode::Branch || opcode == Opcode::Switch;
		}
		Bool CanBeOperand() const;

		Use const* GetOperandList() const
		{
			return operands.data();
		}
		Use* GetOperandList()
		{
			return operands.data();
		}
		Uint32 GetNumOperands() const
		{
			return (Uint32)operands.size();
		}
		Value* GetOperand(Uint32 i) const
		{
			return GetOperandList()[i];
		}
		void SetOperand(Uint32 i, Value* val)
		{
			GetOperandList()[i] = val;
		}
		Use const& GetOperandUse(Uint32 i) const
		{
			return GetOperandList()[i];
		}
		Use& GetOperandUse(Uint32 i)
		{
			return GetOperandList()[i];
		}
		void ClearOperands()
		{
			operands.clear();
		}
		void SwapOperands(Uint32 i, Uint32 j);

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

		OLA_NODISCARD Instruction* Clone() const;
		static Bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::Instruction;
		}

	private:
		Opcode opcode;
		std::vector<Use> operands;
		BasicBlock* basic_block;

	protected:
		Instruction(Opcode opcode, IRType* type, std::vector<Value*> const& ops = {});

		void AddOperand(Value* op)
		{
			operands.emplace_back(op, this);
		}
		void RemoveLastOperand()
		{
			operands.pop_back();
		}

		template <Uint32 Idx>
		Use& Op()
		{
			return operands[Idx];
		}
		template <Uint32 Idx>
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

		Value* GetLHS() const
		{
			return Op<0>();
		}
		Value* GetRHS() const
		{
			return Op<1>();
		}

		OLA_NODISCARD Instruction* Clone() const
		{
			return new BinaryInst(GetOpcode(), GetLHS(), GetRHS());
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->IsBinaryOp();
		}
		static Bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	class UnaryInst final : public Instruction
	{
	public:
		UnaryInst(Opcode opcode, Value* val) : Instruction(opcode, val->GetType(), { val }) {}

		Value* GetOperand() const
		{
			return Op<0>();
		}

		OLA_NODISCARD Instruction* Clone() const
		{
			return new UnaryInst(GetOpcode(), GetOperand());
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->IsUnaryOp();
		}
		static Bool ClassOf(Value const* V)
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

		Value* GetLHS() const
		{
			return Op<0>();
		}
		Value* GetRHS() const
		{
			return Op<1>();
		}

		CompareOp GetCompareOp() const { return cmp; }

		OLA_NODISCARD Instruction* Clone() const
		{
			return new CompareInst(GetOpcode(), GetLHS(), GetRHS());
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->IsCompareOp();
		}
		static Bool ClassOf(Value const* V)
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

		Value* GetSrc() const { return Op<0>(); }
		IRType* GetSrcType() const { return Op<0>()->GetType(); }
		IRType* GetDestType() const { return GetType(); }

		OLA_NODISCARD Instruction* Clone() const
		{
			return new CastInst(GetOpcode(), GetDestType(), GetSrc());
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->IsCastOp();
		}
		static Bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	class LoadInst final : public Instruction
	{
	public:
		explicit LoadInst(Value* address);
		LoadInst(Value* address, IRType* type);

		Value* GetAddressOp() const { return GetOperand(0); }

		OLA_NODISCARD Instruction* Clone() const
		{
			return new LoadInst(GetAddressOp(), GetType());
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Load;
		}
		static Bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	class StoreInst final : public Instruction
	{
	public:
		StoreInst(Value* value, Value* address);

		Value* GetValueOp() const { return GetOperand(0); }
		Value* GetAddressOp() const { return GetOperand(1); }

		OLA_NODISCARD Instruction* Clone() const
		{
			return new StoreInst(GetValueOp(), GetAddressOp());
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Store;
		}
		static Bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	class BranchInst final : public Instruction
	{
	public:
		BranchInst(IRContext& C, BasicBlock* target);
		BranchInst(Value* condition, BasicBlock* true_target, BasicBlock* false_target);

		Bool IsUnconditional() const { return !IsConditional(); }
		Bool IsConditional()   const { return is_conditional; }

		BasicBlock* GetTrueTarget() const;
		BasicBlock* GetFalseTarget() const;

		void SetTrueTarget(BasicBlock* bb);
		void SetFalseTarget(BasicBlock* bb);

		Value* GetCondition() const
		{
			return IsConditional() ? Op<2>() : nullptr;
		}
		void SetCondition(Value* C)
		{
			OLA_ASSERT(IsConditional());
			Op<2>() = C;
			is_conditional = (C != nullptr);
		}

		OLA_NODISCARD Instruction* Clone() const
		{
			return IsConditional() ? new BranchInst(GetCondition(), GetTrueTarget(), GetFalseTarget())
								   : new BranchInst(GetContext(), GetTrueTarget());
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Branch;
		}
		static Bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}

	private:
		Bool is_conditional;
	};

	class ReturnInst final : public Instruction
	{
	public:
		explicit ReturnInst(IRContext& C);
		explicit ReturnInst(Value* ret_value);

		Bool IsVoid() const { return !GetReturnValue(); }
		Value* GetReturnValue() const
		{
			return GetNumOperands() > 0 ? GetOperand(0) : nullptr;
		}

		OLA_NODISCARD Instruction* Clone() const
		{
			return IsVoid() ? new ReturnInst(GetContext())
				: new ReturnInst(GetReturnValue());
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Ret;
		}
		static Bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	class SwitchInst final : public Instruction
	{
		using Case = std::pair<Int64, BasicBlock*>;
	public:
		SwitchInst(Value* val, BasicBlock* default_block);

		void AddCase(Int64 key, BasicBlock* label)
		{
			cases.emplace_back(key, label);
		}

		using CaseIterator = std::vector<Case>::iterator;
		using ConstCaseIterator = std::vector<Case>::const_iterator;
		using CaseRange = IteratorRange<CaseIterator>;
		using ConstCaseRange = IteratorRange<ConstCaseIterator>;

		CaseIterator      CaseBegin() { return cases.begin(); }
		ConstCaseIterator CaseBegin() const { return cases.begin(); }
		CaseIterator      CaseEnd() { return cases.end(); }
		ConstCaseIterator CaseEnd()   const { return cases.end(); }
		CaseRange		  Cases() { return CaseRange(CaseBegin(), CaseEnd()); }
		ConstCaseRange	  Cases()	  const { return ConstCaseRange(CaseBegin(), CaseEnd()); }

		BasicBlock* GetDefaultCase() const
		{
			return default_block;
		}

		BasicBlock* GetCaseBlock(Uint32 case_idx) const
		{
			if (case_idx >= cases.size()) return nullptr;
			return cases[case_idx].second;
		}
		Int64 GetCaseValue(Uint32 case_idx) const
		{
			if (case_idx >= cases.size()) return INT64_MAX;
			return cases[case_idx].first;
		}

		Value* GetCondition() const { return GetOperand(0); }
		void SetCondition(Value* V) { SetOperand(0, V); }

		Uint32 GetNumCases() const
		{
			return cases.size();
		}

		OLA_NODISCARD Instruction* Clone() const
		{
			return nullptr; //#todo
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Switch;
		}
		static Bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}

	private:
		BasicBlock* default_block;
		std::vector<Case> cases;
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
		Bool ArgEmpty() const { return ArgEnd() == ArgBegin(); }
		Uint32 ArgSize() const { return ArgEnd() - ArgBegin(); }

		Value const* GetArgOp(Uint32 i) const
		{
			OLA_ASSERT_MSG(i < ArgSize(), "Out of bounds!");
			return GetOperand(i);
		}
		void SetArgOp(Uint32 i, Value* v)
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

		OLA_NODISCARD Instruction* Clone() const
		{
			Uint32 const OpCount = GetNumOperands();
			std::vector<Value*> Args; Args.reserve(OpCount - 1);
			for (Uint32 i = 0; i < OpCount - 1; ++i)
			{
				Args.push_back(GetOperand(i));
			}
			Value* Callee = GetOperand(OpCount - 1);
			return new CallInst(Callee, Args);
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Call;
		}
		static Bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}
	};

	class SelectInst final : public Instruction
	{
	public:
		SelectInst(Value* predicate, Value* lhs, Value* rhs) : Instruction(Opcode::Select, lhs->GetType(), { predicate, lhs, rhs })
		{
			OLA_ASSERT(lhs->GetType() == rhs->GetType());
		}
		Value* GetPredicate()  const { return Op<0>(); }
		Value* GetTrueValue()  const { return Op<1>(); }
		Value* GetFalseValue() const { return Op<2>(); }

		void SetCondition(Value* V) { Op<0>() = V; }
		void SetTrueValue(Value* V) { Op<1>() = V; }
		void SetFalseValue(Value* V) { Op<2>() = V; }

		OLA_NODISCARD Instruction* Clone() const
		{
			return new SelectInst(GetPredicate(), GetTrueValue(), GetFalseValue());
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Select;
		}
		static Bool ClassOf(Value const* V)
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

		OLA_NODISCARD Instruction* Clone() const
		{
			return new AllocaInst(GetAllocatedType());
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Alloca;
		}
		static Bool ClassOf(Value const* V)
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

		Uint32 GetNumIndices() const { return GetNumOperands() - 1; }
		Bool HasIndices() const { return GetNumIndices() > 0; }

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

		OLA_NODISCARD Instruction* Clone() const
		{
			return nullptr; //#todo
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::GetElementPtr;
		}
		static Bool ClassOf(Value const* V)
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

		OLA_NODISCARD Instruction* Clone() const
		{
			return new PtrAddInst(GetBase(), GetOffset(), GetResultElementType());
		}
		static Bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::PtrAdd;
		}
		static Bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}

	private:
		IRType* result_element_type;
	};

	class PhiInst final : public Instruction
	{
	public:
		explicit PhiInst(IRType* type) : Instruction(Opcode::Phi, type, {}), alloca_inst(nullptr) {}

		void SetAlloca(AllocaInst* AI)
		{
			alloca_inst = AI;
		}
		AllocaInst* GetAlloca() const { return alloca_inst; }

		void AddIncoming(Value* V, BasicBlock* BB)
		{
			AddIncomingValue(V);
			AddIncomingBlock(BB);
		}

		using ConstBlockIterator = std::vector<BasicBlock*>::const_iterator;
		using ConstBlockRange = IteratorRange<ConstBlockIterator>;

		Uint32 GetNumIncomingValues() const { return GetNumOperands() / 2; }
		Value* GetIncomingValue(Uint32 i) const { return GetOperand(GetValueOpIndex(i)); }
		void SetIncomingValue(Uint32 i, Value* V)
		{
			OLA_ASSERT_MSG(V, "PHI node got a null value!");
			OLA_ASSERT_MSG(GetType() == V->GetType(), "All operands to PHI node must be the same type as the PHI node!");
			SetOperand(GetValueOpIndex(i), V);
		}

		BasicBlock* GetIncomingBlock(Uint32 i) const;
		void SetIncomingBlock(Uint32 i, BasicBlock* BB);
		void ReplaceIncomingBlockWith(BasicBlock const* Old, BasicBlock* New)
		{
			for (Uint32 Op = 0, NumOps = GetNumIncomingValues(); Op != NumOps; ++Op)
			{
				if (GetIncomingBlock(Op) == Old) SetIncomingBlock(Op, New);
			}
		}
		Int GetBasicBlockIndex(BasicBlock const* BB) const
		{
			for (Uint32 Op = 0, NumOps = GetNumIncomingValues(); Op != NumOps; ++Op)
			{
				if (GetIncomingBlock(Op) == BB) return Op;
			}
			return -1;
		}
		Value* GetIncomingValueForBlock(BasicBlock const* BB) const
		{
			Int Idx = GetBasicBlockIndex(BB);
			return Idx >= 0 ? GetIncomingValue(Idx) : nullptr;
		}
		void SetIncomingValueForBlock(BasicBlock const* BB, Value* V)
		{
			for (Uint32 Op = 0, NumOps = GetNumIncomingValues(); Op != NumOps; ++Op)
			{
				if (GetIncomingBlock(Op) == BB) SetIncomingValue(Op, V);
			}
		}
		void RemoveIncomingValue(Uint32 i)
		{
			Uint32 lastIdx = GetNumIncomingValues() - 1;
			if (i != lastIdx)
			{
				SwapOperands(GetValueOpIndex(i), GetValueOpIndex(lastIdx));
				SwapOperands(GetBlockOpIndex(i), GetBlockOpIndex(lastIdx));
			}
			RemoveLastOperand();
			RemoveLastOperand();
		}

		OLA_NODISCARD Instruction* Clone() const;
		static Bool ClassOf(Instruction const* I)
		{
			return I->GetOpcode() == Opcode::Phi;
		}
		static Bool ClassOf(Value const* V)
		{
			return isa<Instruction>(V) && ClassOf(cast<Instruction>(V));
		}

	private:
		AllocaInst* alloca_inst;

	private:
		void AddIncomingValue(Value* V)
		{
			OLA_ASSERT(V->GetType() == GetType());
			AddOperand(V);
		}
		void AddIncomingBlock(BasicBlock* BB);

		static Uint32 GetValueOpIndex(Uint32 i)
		{
			return 2 * i;
		}
		static Uint32 GetBlockOpIndex(Uint32 i)
		{
			return 2 * i + 1;
		}
	};
}