#pragma once
#include <list>
#include <vector>
#include "Constant.h"
#include "IRType.h"
#include "BasicBlock.h"
#include "Utility/Attribute.h"

namespace ola
{
	enum class Linkage : Bool
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

		virtual Bool IsFunction() const
		{
			return false;
		}
		virtual Bool IsDeclaration() const = 0;

		static Bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::Constant && ClassOf(cast<Constant>(V));
		}
		static Bool ClassOf(Constant const* C)
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
		Bool IsReadOnly() const { return attr.HasAttr(GlobalVariableAttribute::ReadOnly); }
		void SetReadOnly() { attr.AddAttr(GlobalVariableAttribute::ReadOnly); }

		Value* GetInitValue() const { return init; }

		virtual Bool IsDeclaration() const override
		{
			return init == nullptr && linkage == Linkage::External;
		}

		static Bool ClassOf(Value const* V) { return isa<GlobalValue>(V) && ClassOf(cast<GlobalValue>(V)); }
		static Bool ClassOf(GlobalValue const* GV) { return !GV->IsFunction(); }

	private:
		Value* init;
		Attribute<GlobalVariableAttribute> attr;
	};

	class Argument : public Value
	{
		friend class Function;
	public:
		static Bool ClassOf(Value* V) { return V->GetKind() == ValueKind::Argument; }

	private:
		Argument(IRType* type, Uint32 index) : Value(ValueKind::Argument, type), index(index) {}
		Uint32  GetIndex() const { return index; }
	private:
		Uint32 index;
	};

	enum FunctionAttribute : Uint8
	{
		Attribute_None = 0x00,
		Attribute_NoInline = 0x01,
		Attribute_ForceInline = 0x02,
		Attribute_NoOptimizations = 0x04
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
			return block_list.Front();
		}
		BasicBlock const& GetLastBlock() const
		{
			return block_list.Back();
		}
		BasicBlock& GetLastBlock()
		{
			return block_list.Back();
		}

		auto& Blocks()
		{
			return block_list;
		}
		auto const& Blocks() const
		{
			return block_list;
		}
		Bool HasPhiInsts() const
		{
			for (auto const& BB : block_list) 
			{
				if (BB.PhiInsts().size() > 0) 
				{
					return true;
				}
			}
			return false;
		}

		void Insert(BasicBlock* BB);
		void InsertBefore(BasicBlock* BB, BasicBlock* before);

		auto& Attributes() { return attr; }
		auto const& Attributes() const { return attr; }
		Bool IsForceInline() const { return attr.HasAttr(Attribute_ForceInline); }
		void SetForceInline() { attr.AddAttr(Attribute_ForceInline); }
		Bool IsNoInline() const { return attr.HasAttr(Attribute_NoInline); }
		void SetNoInline() { attr.AddAttr(Attribute_NoInline); }
		Bool IsNoOptimizations() const { return attr.HasAttr(Attribute_NoOptimizations); }
		void SetNoOptimizations() { attr.AddAttr(Attribute_NoOptimizations); }

		Uint64	Size() const;
		Bool    Empty() const { return block_list.Empty(); }

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
		Bool HasCallInstruction() const;

		virtual Bool IsFunction() const override
		{
			return true;
		}
		virtual Bool IsDeclaration() const override
		{
			return Empty();
		}

		static Bool ClassOf(Value const* V) { return isa<GlobalValue>(V) && ClassOf(cast<GlobalValue>(V)); }
		static Bool ClassOf(GlobalValue const* GV) { return GV->IsFunction(); }

	private:
		std::vector<Argument*> arguments;
		IList<BasicBlock> block_list;
		Attribute<FunctionAttribute> attr;
	};
}