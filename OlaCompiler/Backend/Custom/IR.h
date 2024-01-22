﻿#pragma once
#include <vector>
#include <unordered_set>
#include <span>
#include "IRType.h"
#include "Utility/IntrusiveList.h"

namespace ola
{
	class IRModule;
	class Value;
	class Use;
	class Function;
	class BasicBlock;
	class Instruction;
	class Argument;

	enum class ValueKind : uint32
	{
	#define HANDLE_VALUE(Name) Name,
	#include "Values.def"
	};

	class Value
	{
	public:
		OLA_NONCOPYABLE(Value)
		virtual ~Value() = default;

		ValueKind GetKind() const { return kind; }
		IRType* GetType() const { return type; }
		IRContext& GetContext() const { return type->GetContext(); }

		bool HasName() const { return !name.empty(); }
		std::string_view GetName() const { return name; }
		void SetName(std::string_view _name)
		{
			name = _name;
		}

		void AddUse(Use* u) { uses.PushBack(u); }
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
			if (value) value->AddUse(this);
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
		Instruction* user;
		Value* value;
	};

	enum class Linkage
	{
		Unknown,
		Internal,
		External
	};

	class Function : public Value, public IListNode<Function>
	{
		friend class IRModule;
	public:
		enum Attribute : uint8
		{
			Attribute_None = 0x00,
			Attribute_NoInline = 0x01,
			Attribute_ForceInline = 0x02
		};
		using Attributes = uint8;
	public:

		Function(IRModule& module, IRType* func_type, Linkage linkage, std::string_view name = "");
		OLA_NONCOPYABLE(Function)
		~Function();

		IRModule& GetModule() const { return module; }
		uint64 GetInstructionCount() const;
		FunctionType* GetFunctionType() const;
		IRType* GetReturnType() const
		{
			return GetFunctionType()->GetReturnType();
		}
		uint64 GetArgCount() const
		{
			return GetFunctionType()->GetParamCount();
		}
		IRType* GetArgType(uint32 i) const
		{
			return GetFunctionType()->GetParamType(i);
		}
		Argument* GetArg(uint32 i) const 
		{
			OLA_ASSERT_MSG(i < arguments.size(), "Parameter index out of bounds");
			return arguments[i];
		}

		void RemoveFromParent();

		BasicBlock const* GetEntryBlock() const 
		{
			if (block_list.Empty()) return nullptr; 
			return &block_list.Front();
		}
		BasicBlock* GetEntryBlock()
		{
			return const_cast<BasicBlock*>(static_cast<const Function*>(this)->GetEntryBlock());
		}

		void Insert(BasicBlock* bb)
		{
			block_list.PushBack(bb);
		}
		void InsertBefore(BasicBlock* bb, BasicBlock* before)
		{
			block_list.Insert(before, bb);
		}

		void SetFuncAttribute(Attribute attr)
		{
			attributes |= attr;
		}
		bool HasFuncAttribute(Attribute attr) const
		{
			return (attributes & attr) == attr;
		}
		bool IsInline()   const { return HasFuncAttribute(Attribute_ForceInline); }
		bool IsNoInline() const { return HasFuncAttribute(Attribute_NoInline); }

		uint64	Size() const { return block_list.Size(); }
		bool    Empty() const { return block_list.Empty(); }

		auto begin() { return block_list.begin(); }
		auto begin() const { return block_list.begin(); }
		auto end() { return block_list.end(); }
		auto end() const { return block_list.end(); }
		auto rbegin() { return block_list.rbegin(); }
		auto rbegin() const { return block_list.rbegin(); }
		auto rend() { return block_list.rend(); }
		auto rend() const { return block_list.rend(); }
		BasicBlock& front() { return *begin(); }
		BasicBlock const& front() const { return *begin(); }
		BasicBlock& back() { return *rbegin(); }
		BasicBlock const& back() const { return *rbegin(); }

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::Function;
		}

	private:
		IRModule& module;
		IList<BasicBlock> block_list;
		Linkage linkage = Linkage::Unknown;
		Attributes attributes = Attribute_None;
		std::vector<Argument*> arguments;
	};

	class GlobalVariable : public Value, public IListNode<GlobalVariable>
	{
	public:
		GlobalVariable(IRModule& module, PointerType* type, std::string_view name, Linkage linkage, Value* init);
		OLA_NONCOPYABLE(GlobalVariable)
		~GlobalVariable();

		IRModule& GetModule() const { return module; }
		IRType* GetAllocatedType() const { return allocated_type; }
		Value* GetInitValue() const { return init; }
		std::string_view GetName() const { return name; }
		Linkage GetLinkage() const { return linkage; }

		static bool ClassOf(Value const* V) { return V->GetKind() >= ValueKind::GlobalVariable; }

	private:
		IRModule& module;
		std::string name;
		Linkage linkage;
		Value* init;
		IRType* allocated_type;
	};

	class BasicBlock : public Value, public IListNode<BasicBlock>
	{
		friend class IRBuilder;

	public:
		BasicBlock(IRContext& ctx, std::string_view name = "",
			Function* parent = nullptr,
			BasicBlock* insert_before = nullptr) : Value(ValueKind::BasicBlock, LabelType::Get(ctx)), parent(parent)
		{
			SetName(name);
			if (parent) InsertInto(parent, insert_before);
			else OLA_ASSERT_MSG(!insert_before, "Cannot insert block before another block with no function!");
		}

		OLA_NONCOPYABLE(BasicBlock)
		~BasicBlock() {}

		void SetParent(Function* _parent)
		{
			InsertInto(parent, nullptr);
		}
		Function const* GetParent() const { return parent; }
		Function* GetParent() { return parent; }

		IList<Instruction>& GetInstructions() { return inst_list; }
		IList<Instruction> const& GetInstructions() const { return inst_list; }
		Instruction const* GetTerminator() const;
		Instruction* GetTerminator()
		{
			return const_cast<Instruction*>(static_cast<const BasicBlock*>(this)->GetTerminator());
		}

		uint32 GetID() const { return block_index; }

		bool HasNPredecessors(uint32 N) const
		{
			return predecessors.size() == N;
		}
		bool HasNPredecessorsOrMore(uint32 N) const
		{
			return predecessors.size() >= N;
		}
		bool HasPredecessor(BasicBlock* bb) const
		{
			for (auto& predecessor : predecessors)
			{
				if (bb == predecessor) return true;
			}
			return false;
		}
		uint32 GetPredecessorCount() const { return (uint32)predecessors.size(); }
		uint32 GetSucessorCount() const { return (uint32)successors.size(); }

		auto begin() { return inst_list.begin(); }
		auto begin() const { return inst_list.begin(); }
		auto end() { return inst_list.end(); }
		auto end() const { return inst_list.end(); }
		auto rbegin() { return inst_list.rbegin(); }
		auto rbegin() const { return inst_list.rbegin(); }
		auto rend() { return inst_list.rend(); }
		auto rend() const { return inst_list.rend(); }

		uint64	Size() const { return inst_list.Size(); }
		bool    Empty() const { return inst_list.Empty(); }

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::BasicBlock;
		}

	private:
		Function* parent;
		IList<Instruction> inst_list;

		uint32 block_index = -1;
		std::unordered_set<BasicBlock*> predecessors;
		std::unordered_set<BasicBlock*> successors;

	private:
		void InsertInto(Function* parent, BasicBlock* insert_before = nullptr);
	};

	class Instruction : public Value, public IListNode<Instruction>
	{
	public:

		OLA_NONCOPYABLE(Instruction)
		~Instruction()
		{
			RemoveFromParent();
		}

		BasicBlock const* GetParent() const { return parent; }
		BasicBlock* GetParent() { return parent; }
		Function const* GetFunction() const;
		Function* GetFunction() { return const_cast<Function*>(static_cast<const Instruction*>(this)->GetFunction());}
		IRModule& GetModule() const { return GetFunction()->GetModule(); }

		void RemoveFromParent()
		{
			if (parent) parent->GetInstructions().Remove(this);
		}

		void Insert(Instruction* position)
		{
			position->GetParent()->GetInstructions().Insert(position, this);
			SetParent(position->GetParent());
		}
		void InsertAfter(Instruction* position)
		{
			position->GetParent()->GetInstructions().InsertAfter(position, this);
			SetParent(position->GetParent());
		}
		void Insert(BasicBlock* bb, Instruction* position)
		{
			bb->GetInstructions().Insert(position, this);
			SetParent(bb);
		}
		void InsertAfter(BasicBlock* bb, Instruction* position)
		{
			bb->GetInstructions().InsertAfter(position, this);
			SetParent(bb);
		}
		void Insert(BasicBlock* bb)
		{
			bb->GetInstructions().PushBack(this);
			SetParent(bb);
		}

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
			case ValueKind::Alloca:
				return true;
			default:
				return false;
			}
			return false;
		}

	protected:
		Instruction(ValueKind kind, IRType* type, BasicBlock* parent = nullptr) : Value(kind, type), parent(parent)
		{
			if (parent) Insert(parent);
		}
		Instruction(ValueKind kind, IRType* type, Instruction* position) : Value(kind, type), parent(position->GetParent())
		{
			if (parent) Insert(position);
		}

	private:
		BasicBlock* parent;

	private:

		void SetParent(BasicBlock* bb)
		{
			if (parent) parent->GetInstructions().Remove(this);
			parent = bb;
		}
	};

	class Argument : public Value
	{
		friend Function;
	public:
		uint32  GetIndex() const { return index; }
		static bool ClassOf(Value* V) { return V->GetKind() == ValueKind::Argument; }

	private:
		uint32 index;

	private:
		Argument(IRType* type, uint32 index) : Value(ValueKind::Argument, type), index(index) {}
	};

	class AllocaInst : public Instruction
	{
		friend Instruction;
	public:
		explicit AllocaInst(PointerType* type) : Instruction(ValueKind::Alloca, type), allocated_type(type->GetPointeeType()) {}
		IRType* GetAllocatedType() { return allocated_type; }
		static bool ClassOf(Value* V) { return V->GetKind() == ValueKind::Alloca; }

	private:
		IRType* allocated_type;
	};
}

