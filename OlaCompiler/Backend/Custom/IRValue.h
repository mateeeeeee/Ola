#pragma once
#include "IRType.h"
#include "Compiler/RTTI.h"

namespace ola::ir
{
	class IRModule;
	class Inst;

	enum class IRValueKind : uint32
	{
		IntegerConstant,
		FloatConstant,
		Block,
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
		FGe,
	};
	class IRValue
	{
	public:
		virtual ~IRValue() = default;
		IRValueKind GetKind() const { return kind; }
		IRType* GetType() const { return type; }

		void* operator new(uint64) = delete;
		void* operator new(uint64 sz, IRModule&) { return ::operator new(sz); }

	protected:
		IRValue(IRValueKind kind, IRType* type) : kind(kind), type(type) {}

	private:
		IRValueKind kind;
		IRType* type;
	};

	class UsedValue : public IRValue 
	{
		friend class Inst;
	public:

		std::vector<Inst*> const& GetUsers() const { return user_list; }

		static bool ClassOf(IRValue const* v) { return v->GetKind() == IRValueKind::Block; }

	protected:
		UsedValue(IRValueKind kind, IRType* type = nullptr) : IRValue(kind, type) {}

	private:
		std::vector<Inst*> user_list;
	};

	enum class GlobalLinkage
	{
		External,
		Internal
	};
	class GlobalVariable : public UsedValue
	{
	public:
		GlobalVariable(IRModule& ir_module, IRType* alloc_type, std::string_view name, GlobalLinkage linkage, IRValue* init_value)
			: UsedValue(IRValueKind::GlobalVariable, nullptr), name(name), linkage(linkage), init_value(init_value)
		{
		}

		IRType* GetType() { return alloc_type; }
		IRValue* GetInitValue() const { return init_value; }
		std::string_view GetName() const { return name; }
		GlobalLinkage GetLinkage() const { return linkage; }

		static bool ClassOf(IRValue* v) { return v->GetKind() == IRValueKind::GlobalVariable; }

	private:
		std::string name;
		GlobalLinkage linkage;
		IRValue* init_value;
		IRType* alloc_type;
	};

	class BasicBlock;
	class Inst : public UsedValue
	{
		friend class BasicBlock;
	public:
		Inst(IRValueKind kind, IRType* type) : UsedValue(kind, type), parent(nullptr){}

		BasicBlock* GetParent() const { return parent; }

	private:
		BasicBlock* parent;
	};

	class IRFunction;
	class BasicBlock : public UsedValue
	{
	public:
		explicit BasicBlock(std::string_view name = "") : UsedValue(IRValueKind::Block), name(name)
		{
		}

		auto begin() const { return inst_list.begin(); }
		auto end()   const { return inst_list.end();   }

		void SetFunction(IRFunction* _parent) { parent = _parent; }
		IRFunction* GetParent() const { return parent; }

		uint64 GetIndex() const { return -1; }

	private:
		std::string name;
		IRFunction* parent{};
		std::vector<Inst*> inst_list;
	};

	class IRFunction : public UsedValue
	{
	public:


	private:
	};

	template <typename V> requires std::derived_from<V, IRValue>
	inline bool isa(IRValue const* value) { return V::ClassOf(value); }

	template <typename V, typename... Vs> requires (std::derived_from<V, IRValue> && ... && std::derived_from<Vs, IRValue>)
	inline bool isoneof(IRValue const* value)
	{
		return (V::ClassOf(value) || ... || Vs::ClassOf(value));
	}

	template<typename V> requires std::derived_from<V, IRValue>
	inline V* cast(IRValue* v)
	{
		return static_cast<V*>(v);
	}
	template<typename V> requires std::derived_from<V, IRValue>
	inline V const* cast(IRValue const* v)
	{
		return static_cast<V const*>(v);
	}

	template<typename V> requires std::derived_from<V, IRValue>
	inline V* dyn_cast(IRValue* v)
	{
		return isa<V>(v) ? static_cast<V*>(v) : nullptr;
	}
	template<typename V> requires std::derived_from<V, IRValue>
	inline V const* dyn_cast(IRValue const* v)
	{
		return isa<V>(v) ? static_cast<T const*>(v) : nullptr;
	}
}

