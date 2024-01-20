#pragma once
#include <vector>
#include <unordered_set>
#include <span>
#include "IRType.h"
#include "Compiler/RTTI.h"
#include "Utility/IntrusiveList.h"

namespace ola
{

	class Value;
	class Use;
	class IRModule;
	class Instruction;
	class IRFunction;

	enum class ValueKind : uint32
	{
		IntegerConstant,
		FloatConstant,
		BasicBlock,
		Function,
		GlobalVariable,
		Parameter,
		Argument,
		Alloca,
		Call,
		GetElementPtr,
		GetMemberPtr,
		Load,
		Store,
		Phi,
		Branch,
		CondBranch,
		Switch,
		Select,
		Return,
		Unreachable,
		ZExt,
		SExt,
		Trunc,
		Bitcast,
		Neg,
		Copy,
		Compl,
		Add,
		FAdd,
		Sub,
		FSub,
		Mul,
		FMul,
		Div,
		FDiv,
		Rem,
		Shl,
		Sar,
		Shr,
		And,
		Or,
		Xor,
		Eq,
		FEq,
		Ne,
		FNe,
		Lt,
		FLt,
		Le,
		FLe,
		Gt,
		FGt,
		Ge,
		FGe
	};
	class Value
	{
	public:
		OLA_NONCOPYABLE(Value)
		virtual ~Value() = default;

		ValueKind GetKind() const { return kind; }
		IRType* GetType() const { return type; }

		bool HasName() const { return !name.empty(); }
		std::string_view GetName() const { return name; }
		void SetName(std::string_view _name)
		{
			name = _name;
		}

		void AddUse(Use* u) { uses.InsertAtEnd(u); }
		void RemoveUse(Use* u) { uses.Remove(u); }
		void ReplaceAllUseWith(Value* v);

		void* operator new(uint64) = delete;
		void* operator new(uint64 sz, IRModule&) { return ::operator new(sz); }

	protected:
		Value(ValueKind kind, IRType* type = nullptr) : kind(kind), type(type) {}

	private:
		ValueKind kind;
		IRType* type;
		std::string name;
		IList<Use> uses;
	};

	class Use : public IListNode<Use>
	{
		friend Value;
		friend Instruction;

	public:
		Use(Instruction* u, Value* v) : value(v), user(u)
		{
			if (v) v->AddUse(this);
		}
		OLA_NONCOPYABLE(Use)
		~Use() 
		{
			if (value) value->RemoveUse(this);
		}

		void Set(Value* v) 
		{
			if (value) value->RemoveUse(this);
			value = v;
			if (v) v->AddUse(this);
		}

	private:
		Value* value;
		Instruction* user;
	};

	class BasicBlock : public Value 
	{
	public:
		BasicBlock(std::string_view name = "",
			IRFunction* parent = nullptr,
			BasicBlock* insert_before = nullptr) : Value(ValueKind::BasicBlock), parent(parent)
		{
			SetName(name);
			if (parent) InsertInto(parent, insert_before);
			else OLA_ASSERT_MSG(!insert_before, "Cannot insert block before another block with no function!");
		}
		OLA_NONCOPYABLE(BasicBlock)
		~BasicBlock() {}


		IRFunction const* GetParent() const { return parent; }
		IRFunction* GetParent() { return parent; }

		const Instruction* GetTerminator() const;
		Instruction* getTerminator() 
		{
			return const_cast<Instruction*>(static_cast<const BasicBlock*>(this)->GetTerminator());
		}

		bool hasNPredecessors(uint32 N) const
		{
			return predecessors.size() == N;
		}
		bool hasNPredecessorsOrMore(uint32 N) const
		{
			return predecessors.size() >= N;
		}

		auto begin() { return inst_list.begin(); }
		auto begin() const { return inst_list.begin(); }
		auto end() { return inst_list.end(); }
		auto end() const { return inst_list.end(); }
		auto rbegin() { return inst_list.rbegin(); }
		auto rbegin() const { return inst_list.rbegin(); }
		auto rend() { return inst_list.rend(); }
		auto rend() const { return inst_list.rend(); }

		uint64	Size() const { return inst_list.size(); }
		bool    Empty() const { return inst_list.empty(); }

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::BasicBlock;
		}

	private:
		IRFunction* parent;
		std::vector<Instruction*> inst_list;

		uint32 block_index = -1;
		std::unordered_set<BasicBlock*> predecessors;
		std::unordered_set<BasicBlock*> successors;

	private:  

		void SetParent(IRFunction* _parent)
		{
			parent = _parent;
		}

		void InsertInto(IRFunction* parent, BasicBlock* insert_before = nullptr);
	};

	enum class Linkage
	{
		Unknown,
		Internal,
		External
	};

	class GlobalVariable : public Value, public IListNode<GlobalVariable>
	{
	public:
		GlobalVariable(IRType* type) : Value(ValueKind::GlobalVariable, type) {}

	private:
	};

	enum IRFuncAttribute : uint8
	{
		IRFuncAttribute_None = 0x00,
		IRFuncAttribute_NoInline = 0x01,
		IRFuncAttribute_Inline = 0x02
	};
	using IRFuncAttributes = uint8;

	class IRFunction : public Value, public IListNode<IRFunction>
	{
		friend class IRModule;
	public:

		IRFunction(IRType* func_type, Linkage linkage, std::string_view name = "", IRModule* module = nullptr) 
			: Value(ValueKind::Function, func_type), module(module)
		{
			SetName(name);
		}
		~IRFunction() {}

		uint64 GetInstructionCount() const
		{
			uint64 instruction_count = 0;
			for (auto const& BB : block_list) instruction_count += BB->Size();
			return instruction_count;
		}

		FunctionType* GetFunctionType() const
		{
			return nullptr; // cast<FunctionType>(GetType());
		}
		IRType* GetReturnType() const
		{
			return GetFunctionType()->GetReturnType();
		}
		IRType* GetParamType(uint32 arg_index) const
		{
			return GetFunctionType()->GetParamType(arg_index);
		}
		uint64 GetParamCount() const
		{
			return GetFunctionType()->GetParamCount();
		}

		void RemoveFromParent();

		void SetFuncAttribute(IRFuncAttribute attr)
		{
			attributes |= attr;
		}
		bool HasFuncAttribute(IRFuncAttribute attr) const
		{
			return (attributes & attr) == attr;
		}
		bool IsInline()   const { return HasFuncAttribute(IRFuncAttribute_Inline); }
		bool IsNoInline() const { return HasFuncAttribute(IRFuncAttribute_NoInline); }

		auto begin() { return block_list.begin(); }
		auto begin() const { return block_list.begin(); }
		auto end() { return block_list.end(); }
		auto end() const { return block_list.end(); }
		auto rbegin() { return block_list.rbegin(); }
		auto rbegin() const { return block_list.rbegin(); }
		auto rend() { return block_list.rend(); }
		auto rend() const { return block_list.rend(); }

		uint64	Size() const { return block_list.size(); }
		bool    Empty() const { return block_list.empty(); }

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::Function;
		}
	private:
		std::vector<BasicBlock*> block_list;
		Linkage linkage = Linkage::Unknown;
		IRFuncAttributes attributes = IRFuncAttribute_None;
		IRModule* module = nullptr;
	};

	class Instruction : public Value, public IListNode<Instruction>
	{
	public:

		BasicBlock const* GetParent() const { return parent; }
		BasicBlock* GetParent() { return parent; }

		IRFunction const* GetFunction() const;
		IRFunction* GetFunction() { return const_cast<IRFunction*>(static_cast<const Instruction*>(this)->GetFunction());}

		bool IsTerminator() const { return false; }
		bool IsUnaryOp()	const { return false; }
		bool IsBinaryOp()	const { return false; }
		bool IsModulo()		const { return false; }
		bool IsShift()		const { return false; }
		bool IsCast()		const { return false; }

		static bool ClassOf(Value const* V)
		{
			switch (V->GetKind())
			{
			default:
				return false;
			}
			return false;
		}

	protected:
		Instruction(ValueKind kind, IRType* type) : Value(kind, type)
		{

		}

	private:
		BasicBlock* parent;
	};
}

