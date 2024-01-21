#pragma once
#include <vector>
#include <unordered_set>
#include <span>
#include "IRType.h"
#include "Utility/IntrusiveList.h"

namespace ola
{

	class Value;
	class Use;
	class IRModule;
	class Instruction;
	class IRFunction;
	class BasicBlock;

	enum class ValueKind : uint32
	{
	#define HANDLE_VALUE(Name) Name,
	#include "Value.def"
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
		uint64 GetUseCount() const;

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


	enum class Linkage
	{
		Unknown,
		Internal,
		External
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
		OLA_NONCOPYABLE(IRFunction)
		~IRFunction() {}

		uint64 GetInstructionCount() const
		{
			uint64 instruction_count = 0;
			//while(block_list.head)
			//for (auto const& BB : block_list) instruction_count += BB->Size();
			return instruction_count;
		}
		FunctionType* GetFunctionType() const;
		IRType* GetReturnType() const
		{
			return GetFunctionType()->GetReturnType();
		}
		IRType* GetArgType(uint32 i) const
		{
			return GetFunctionType()->GetParamType(i);
		}
		uint64  GetArgCount() const
		{
			return GetFunctionType()->GetParamCount();
		}

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

		void RemoveFromParent();

		BasicBlock const* GetEntryBlock() const 
		{
			return nullptr;
			//if (block_list.empty()) return nullptr;
			//return block_list.front();
		}
		BasicBlock* GetEntryBlock()
		{
			return const_cast<BasicBlock*>(static_cast<const IRFunction*>(this)->GetEntryBlock());
		}

		void Insert(BasicBlock* bb)
		{
			block_list.InsertAtEnd(bb);
		}
		void InsertBefore(BasicBlock* bb, BasicBlock* before)
		{
			block_list.InsertBefore(bb, before);
		}

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::Function;
		}

	private:
		IList<BasicBlock> block_list;
		Linkage linkage = Linkage::Unknown;
		IRFuncAttributes attributes = IRFuncAttribute_None;
		IRModule* module = nullptr;
	};

	class GlobalVariable : public Value, public IListNode<GlobalVariable>
	{
	public:
		GlobalVariable(IRType* type) : Value(ValueKind::GlobalVariable, type) {}

	private:
	};


	class BasicBlock : public Value, public IListNode<BasicBlock>
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
		Instruction* GetTerminator()
		{
			return const_cast<Instruction*>(static_cast<const BasicBlock*>(this)->GetTerminator());
		}

		bool HasNPredecessors(uint32 N) const
		{
			return predecessors.size() == N;
		}
		bool HasNPredecessorsOrMore(uint32 N) const
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

