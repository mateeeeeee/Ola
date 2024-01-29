#pragma once
#include "Value.h"

namespace ola
{


	enum class Linkage
	{
		Unknown,
		Internal,
		External
	};

	class GlobalValue : public Value
	{
	public:
		OLA_NONCOPYABLE(GlobalValue)
			~GlobalValue() = default;

		Linkage GetLinkage() const { return linkage; }
		void SetLinkage(Linkage _linkage)
		{
			linkage = _linkage;
		}
		IRModule& GetModule() const { return module; }
		IRType* GetValueType() const { return value_type; }

		static bool ClassOf(Value const* V)
		{
			return  V->GetKind() == ValueKind_Function ||
				V->GetKind() == ValueKind_GlobalVariable;
		}

	protected:
		IRModule& module;
		Linkage linkage = Linkage::Unknown;
		IRType* value_type;

	protected:
		GlobalValue(ValueKind kind, IRType* type, IRModule& module, Linkage linkage = Linkage::Unknown) : Value(kind, PointerType::Get(type)), module(module), linkage(linkage), value_type(type)
		{}
	};

	class Function : public GlobalValue, public IListNode<Function>
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

		Function(FunctionType* type, IRModule& module, Linkage linkage, std::string_view name = "");
		OLA_NONCOPYABLE(Function)
			~Function();

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
			return V->GetKind() == ValueKind_Function;
		}

	private:
		IList<BasicBlock> block_list;
		Attributes attributes = Attribute_None;
		std::vector<Argument*> arguments;
	};

	class Argument : public Value
	{
		friend Function;
	public:
		uint32  GetIndex() const { return index; }
		static bool ClassOf(Value* V) { return V->GetKind() == ValueKind_Argument; }

	private:
		uint32 index;

	private:
		Argument(IRType* type, uint32 index) : Value(ValueKind_Argument, type), index(index) {}
	};

	class GlobalVariable : public GlobalValue, public IListNode<GlobalVariable>
	{
	public:
		GlobalVariable(IRType* type, IRModule& module, Linkage linkage, Value* init, std::string_view name = "");
		OLA_NONCOPYABLE(GlobalVariable)
			~GlobalVariable();

		Value* GetInitValue() const { return init; }
		std::string_view GetName() const { return name; }

		static bool ClassOf(Value const* V) { return V->GetKind() == ValueKind_GlobalVariable; }

	private:
		std::string name;
		Value* init;
	};

}