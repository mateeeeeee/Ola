#pragma once
#include <list>
#include <vector>
#include "Constant.h"
#include "IRType.h"
#include "BasicBlock.h"
#include "Utility/Attribute.h"

namespace ola
{
	enum class Linkage : bool
	{
		Internal,
		External
	};

	class GlobalValue : public Constant
	{
	public:
		GlobalValue(std::string_view symbol, IRType* type, Linkage linkage = Linkage::External) : Constant(ConstantID::Global, IRPtrType::Get(type)), linkage(linkage), value_type(type)
		{
			SetName(symbol);
		}
		OLA_NONCOPYABLE(GlobalValue)
			~GlobalValue() = default;

		Linkage GetLinkage() const { return linkage; }
		void SetLinkage(Linkage _linkage)
		{
			linkage = _linkage;
		}

		IRType* GetValueType() const { return value_type; }

		virtual bool IsFunction() const
		{
			return false;
		}
		virtual bool IsDeclaration() const = 0;

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::Constant && ClassOf(cast<Constant>(V));
		}
		static bool ClassOf(Constant const* C)
		{
			return C->GetConstantID() == ConstantID::Global;
		}

	protected:
		Linkage linkage;
		IRType* value_type;
	};

	enum class GlobalVariableAttribute
	{
		None = 0x0,
		ReadOnly = 0x1
	};
	class GlobalVariable : public GlobalValue
	{
	public:
		GlobalVariable(std::string_view name, IRType* type, Linkage linkage, Value* init)
			: GlobalValue(name, type, linkage), init(init)
		{
		}
		OLA_NONCOPYABLE(GlobalVariable)
		~GlobalVariable() = default;

		auto& Attributes() { return attr; }
		auto const& Attributes() const { return attr; }
		bool IsReadOnly() const { return attr.HasAttr(GlobalVariableAttribute::ReadOnly); }
		void SetReadOnly() { attr.AddAttr(GlobalVariableAttribute::ReadOnly); }

		Value* GetInitValue() const { return init; }

		virtual bool IsDeclaration() const override
		{
			return init == nullptr && linkage == Linkage::External;
		}

		static bool ClassOf(Value const* V) { return isa<GlobalValue>(V) && ClassOf(cast<GlobalValue>(V)); }
		static bool ClassOf(GlobalValue const* GV) { return !GV->IsFunction(); }

	private:
		Value* init;
		Attribute<GlobalVariableAttribute> attr;
	};

	class Argument : public Value
	{
		friend class Function;
	private:
		Argument(IRType* type, Uint32 index) : Value(ValueKind::Argument, type), index(index) {}
		Uint32  GetIndex() const { return index; }
		static bool ClassOf(Value* V) { return V->GetKind() == ValueKind::Argument; }

	private:
		Uint32 index;
	};

	enum FunctionAttribute : Uint8
	{
		Attribute_None = 0x00,
		Attribute_NoInline = 0x01,
		Attribute_ForceInline = 0x02
	};

	class BasicBlock;
	class Function : public GlobalValue
	{
	public:
		Function(std::string_view name, IRFuncType* type, Linkage linkage);
		OLA_NONCOPYABLE(Function)
		~Function();

		Uint64 GetInstructionCount() const;
		IRFuncType* GetFunctionType() const;
		IRType* GetReturnType() const
		{
			return GetFunctionType()->GetReturnType();
		}

		BasicBlock const& GetEntryBlock() const
		{
			return block_list.Front();
		}
		BasicBlock& GetEntryBlock()
		{
			return const_cast<BasicBlock&>(static_cast<const Function*>(this)->GetEntryBlock());
		}

		auto& Blocks()
		{
			return block_list;
		}
		auto const& Blocks() const
		{
			return block_list;
		}

		void Insert(BasicBlock* BB);
		void InsertBefore(BasicBlock* BB, BasicBlock* before);

		auto& Attributes() { return attr; }
		auto const& Attributes() const { return attr; }
		bool IsForceInline() const { return attr.HasAttr(Attribute_ForceInline); }
		void SetForceInline() { attr.AddAttr(Attribute_ForceInline); }
		bool IsNoInline() const { return attr.HasAttr(Attribute_NoInline); }
		void SetNoInline() { attr.AddAttr(Attribute_NoInline); }

		Uint64	Size() const;
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

		auto ArgBegin()			{ return arguments.begin(); }
		auto ArgBegin()  const	{ return arguments.begin(); }
		auto ArgEnd()			{ return arguments.end(); }
		auto ArgEnd()    const	{ return arguments.end(); }
		auto Arguments()		{ return IteratorRange(ArgBegin(), ArgEnd()); }
		auto Arguments() const	{ return IteratorRange(ArgBegin(), ArgEnd()); }

		IRType* GetArgType(Uint32 i) const
		{
			return GetFunctionType()->GetParamType(i);
		}
		Argument* GetArg(Uint32 i) const
		{
			return i < arguments.size() ? arguments[i] : nullptr;
		}
		Uint64 GetArgCount() const
		{
			return GetFunctionType()->GetParamCount();
		}

		virtual bool IsFunction() const override
		{
			return true;
		}
		virtual bool IsDeclaration() const override
		{
			return Empty();
		}

		static bool ClassOf(Value const* V) { return isa<GlobalValue>(V) && ClassOf(cast<GlobalValue>(V)); }
		static bool ClassOf(GlobalValue const* GV) { return GV->IsFunction(); }

	private:
		std::vector<Argument*> arguments;
		IList<BasicBlock> block_list;
		Attribute<FunctionAttribute> attr;
	};
}