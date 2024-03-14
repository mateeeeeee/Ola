#pragma once
#include <list>
#include <vector>
#include "Instruction.h"
#include "IRType.h"
#include "Utility/Attribute.h"

namespace ola
{
	enum class Linkage
	{
		None,
		Internal,
		External
	};

	class GlobalValue : public TrackableValue 
	{
	public:
		GlobalValue(std::string_view symbol, IRType* type, Linkage linkage = Linkage::External) : TrackableValue(ValueKind::Global, IRPtrType::Get(type)), linkage(linkage), value_type(type)
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

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::Global;
		}

	protected:
		Linkage linkage = Linkage::None;
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
		~GlobalVariable();

		auto& Attributes() { return attr; }
		auto const& Attributes() const { return attr; }
		bool IsReadOnly() const { return attr.HasAttr(GlobalVariableAttribute::ReadOnly); }
		void SetReadOnly() { attr.AddAttr(GlobalVariableAttribute::ReadOnly); }

		Value* GetInitValue() const { return init; }
		std::string_view GetName() const { return name; }

		static bool ClassOf(Value const* V) { return isa<GlobalValue>(V) && ClassOf(cast<GlobalValue>(V)); }
		static bool ClassOf(GlobalValue const* GV) { return !GV->IsFunction(); }

	private:
		std::string name;
		Value* init;
		Attribute<GlobalVariableAttribute> attr;
	};

	class Argument : public Value
	{
		friend class Function;
	private:
		Argument(IRType* type, uint32 index) : Value(ValueKind::Argument, type), index(index) {}
		uint32  GetIndex() const { return index; }
		static bool ClassOf(Value* V) { return V->GetKind() == ValueKind::Argument; }

	private:
		uint32 index;
	};

	enum FunctionAttribute : uint8
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

		uint64 GetInstructionCount() const;
		IRFuncType* GetFunctionType() const;
		IRType* GetReturnType() const
		{
			return GetFunctionType()->GetReturnType();
		}

		BasicBlock const* GetEntryBlock() const
		{
			if (block_list.empty()) return nullptr;
			return block_list.front();
		}
		BasicBlock* GetEntryBlock()
		{
			return const_cast<BasicBlock*>(static_cast<const Function*>(this)->GetEntryBlock());
		}

		std::list<BasicBlock*>& Blocks()  
		{
			return block_list;
		}
		std::list<BasicBlock*> const& Blocks() const
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

		uint64	Size() const;
		bool    Empty() const { return block_list.empty(); }

		auto begin() { return block_list.begin(); }
		auto begin() const { return block_list.begin(); }
		auto end() { return block_list.end(); }
		auto end() const { return block_list.end(); }
		auto rbegin() { return block_list.rbegin(); }
		auto rbegin() const { return block_list.rbegin(); }
		auto rend() { return block_list.rend(); }
		auto rend() const { return block_list.rend(); }
		BasicBlock* front() { return *begin(); }
		BasicBlock const* front() const { return *begin(); }
		BasicBlock* back() { return *rbegin(); }
		BasicBlock const* back() const { return *rbegin(); }

		IRType* GetArgType(uint32 i) const
		{
			return GetFunctionType()->GetParamType(i);
		}
		Argument* GetArg(uint32 i) const
		{
			return i < arguments.size() ? arguments[i] : nullptr;
		}
		uint64 GetArgCount() const
		{
			return GetFunctionType()->GetParamCount();
		}

		static bool ClassOf(Value const* V) { return isa<GlobalValue>(V) && ClassOf(cast<GlobalValue>(V)); }
		static bool ClassOf(GlobalValue const* GV) { return GV->IsFunction(); }

	private:
		std::vector<Argument*> arguments;
		std::list<BasicBlock*> block_list;
		Attribute<FunctionAttribute> attr;
	};
}