#pragma once
#include <vector>
#include <unordered_set>
#include "IRType.h"
#include "Utility/IntrusiveList.h"
#include "Utility/IteratorRange.h"

namespace ola
{
	class IRModule;
	class Value;
	class Use;
	class User;
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

		auto UseBegin() { return uses.begin(); }
		auto UseBegin() const { return uses.begin(); }
		auto UseEnd() { return uses.end(); }
		auto UseEnd() const { return uses.end(); }
		auto UseRBegin() { return uses.rbegin(); }
		auto UseRBegin() const { return uses.rbegin(); }
		auto UseREnd() { return uses.rend(); }
		auto UseREnd() const { return uses.rend(); }
		bool UseEmpty() const { return UseBegin() == UseEnd(); }
		uint64 UseSize() const { return uses.Size(); }

		void AddUse(Use* u) { uses.PushBack(u); }
		void RemoveUse(Use* u) { uses.Remove(u); }
		void ReplaceAllUseWith(Value* v);

		bool HasOneUse() const { return UseSize() == 1; }
		bool hasNUses(uint32 N) const { return UseSize() == N; }
		bool hasNUsesOrMore(unsigned N) const { return UseSize() >= N; }

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
		friend User;

	public:
		Use(User* u, Value* v = nullptr) : value(v), user(u)
		{
			if (value) value->AddUse(this);
		}
		Use const& operator=(Use const& rhs)
		{
			Set(rhs.value);
			return *this;
		}
		~Use()
		{
			if (value) value->RemoveUse(this);
		}

		operator Value* () const { return value; }
		Value* Get() const { return value; }
		void Set(Value* v)
		{
			if (value) value->RemoveUse(this);
			value = v;
			if (v) v->AddUse(this);
		}

		Value* operator=(Value* rhs)
		{
			Set(rhs);
			return rhs;
		}
		Value* operator->() { return value; }
		Value const* operator->() const { return value; }

	private:
		User* user;
		Value* value;
	};

	class User : public Value
	{
	public:
		~User()
		{
			for (Use* op : operands) delete op;
		}
		Use *const* GetOperandList() const
		{
			return operands.data();
		}
		Use** GetOperandList()
		{
			return const_cast<Use**>(static_cast<const User*>(this)->GetOperandList());
		}
		uint32 GetNumOperands() const { return (uint32)operands.size(); }

		Value* GetOperand(uint32 i) const 
		{
			return *GetOperandList()[i];
		}
		void SetOperand(uint32 i, Value* val) 
		{
			*GetOperandList()[i] = val;
		}

		Use const& GetOperandUse(uint32 i) const
		{
			return *GetOperandList()[i];
		}
		Use& GetOperandUse(uint32 i)
		{
			return *GetOperandList()[i];
		}

		using OpIterator = Use**;
		using ConstOpIterator = Use *const*;
		using OpRange = IteratorRange<OpIterator>;
		using ConstOpRange = IteratorRange<ConstOpIterator>;

		OpIterator      OpBegin()	 	 { return GetOperandList(); }
		ConstOpIterator OpBegin()  const { return GetOperandList(); }
		OpIterator      OpEnd()			 { return GetOperandList() + GetNumOperands(); }
		ConstOpIterator OpEnd()    const { return GetOperandList() + GetNumOperands(); }
		OpRange			Operands() 		 { return OpRange(OpBegin(), OpEnd()); }
		ConstOpRange	Operands() const { return ConstOpRange(OpBegin(), OpEnd()); }

		void DropAllReferences() 
		{
			for (Use* U : Operands()) U->Set(nullptr);
		}

		bool ReplaceUsesOfWith(Value* from, Value* to)
		{
			bool changed = false;
			if (from == to) return changed;  
			for (uint32 i = 0, N = GetNumOperands(); i != N; ++i)
			{
				if (GetOperand(i) == from)
				{
					SetOperand(i, to);
					changed = true;
				}
			}
			return changed;
		}

	private:
		std::vector<Use*> operands;

	protected:

		User(ValueKind kind, IRType* type, uint32 num_operands) : Value(kind, type)
		{
			operands.resize(num_operands);
			for (Use* op : operands) op = new Use(this);
		}

		template <uint32 Idx, typename U> 
		static Use& OpFrom(U const* that)
		{
			return *that->operands[Idx];
		}
		template <uint32 Idx>
		Use& Op() 
		{
			return OpFrom<Idx>(this);
		}
		template <uint32 Idx>
		Use const& Op() const 
		{
			return OpFrom<Idx>(this);
		}
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

	class Instruction : public User, public IListNode<Instruction>
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
			case ValueKind::Call:
				return true;
			default:
				return false;
			}
			return false;
		}

	protected:
		Instruction(ValueKind kind, IRType* type, uint32 num_operands, BasicBlock* parent = nullptr) : User(kind, type, num_operands), parent(parent)
		{
			if (parent) Insert(parent);
		}
		Instruction(ValueKind kind, IRType* type, uint32 num_operands, Instruction* position) : User(kind, type, num_operands), parent(nullptr)
		{
			if (position) Insert(position);
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

	class UnaryInstruction : public Instruction
	{
	public:

		static bool ClassOf(Value const* V)
		{
			switch (V->GetKind())
			{
			case ValueKind::Alloca:
			case ValueKind::Call:
				return true;
			default:
				return false;
			}
			return false;
		}

	protected:
		UnaryInstruction(ValueKind kind, IRType* type, Value* op, Instruction* position) : Instruction(kind, type, 1, position)
		{
			Op<0>() = op;
		}
		UnaryInstruction(ValueKind kind, IRType* type, Value* op, BasicBlock* bb = nullptr) : Instruction(kind, type, 1, bb)
		{
			Op<0>() = op;
		}
	};

	class BinaryInstruction : public Instruction
	{
	public:

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
		BinaryInstruction(ValueKind kind, IRType* type) : Instruction(kind, type, 2)
		{
		}
	};

	class AllocaInst : public UnaryInstruction
	{
	public:
		explicit AllocaInst(IRType* type, Value* array_size = nullptr) 
			: UnaryInstruction(ValueKind::Alloca, PointerType::Get(type), array_size), array_size(array_size) {}

		AllocaInst(IRType* type, Value* array_size, Instruction* insert_before)
			: UnaryInstruction(ValueKind::Alloca, PointerType::Get(type), array_size, insert_before), allocated_type(type), array_size(array_size) {}
		AllocaInst(IRType* type, Value* array_size, BasicBlock* insert_at_end)
			: UnaryInstruction(ValueKind::Alloca, PointerType::Get(type), array_size, insert_at_end), allocated_type(type), array_size(array_size) {}
		AllocaInst(IRType* type, Instruction* insert_before)
			: AllocaInst(type, nullptr, insert_before) {}
		AllocaInst(IRType* type, BasicBlock* insert_at_end)
			: AllocaInst(type, nullptr, insert_at_end) {}


		bool IsArrayAllocation() const
		{
			return array_size != nullptr;
		}
		PointerType* GetPtrType() const
		{
			return cast<PointerType>(GetType());
		}
		IRType* GetAllocatedType() const { return allocated_type; }

		Value const* GetArraySize() const { return array_size; }
		Value* GetArraySize() { return array_size; }

		static bool ClassOf(Value* V) { return V->GetKind() == ValueKind::Alloca; }

	private:
		IRType* allocated_type;
		Value*  array_size;
	};

	class CallInst : public UnaryInstruction
	{
	};
}

