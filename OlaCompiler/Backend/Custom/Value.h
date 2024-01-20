#pragma once
#include <vector>
#include <span>
#include "IRType.h"
#include "Compiler/RTTI.h"

namespace ola
{
	class IRModule;

	class Value;
	class User;

	class Use
	{
		friend class Value;
		friend class User;
	public:
		OLA_NONCOPYABLE(Use)

		operator Value* () const { return value; }
		Value* Get() const { return value; }
		void Set(Value* _value) { value = _value; }

		User* GetUser() const { return user; };

	private:
		Value* value = nullptr;
		User*  user = nullptr;

	private:

		explicit Use(User* user) : user(user) {}

		~Use()
		{

		}
	};

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
	class Value
	{
	public:
		OLA_NONCOPYABLE(Value)
		virtual ~Value() = default;

		IRValueKind GetKind() const { return kind; }
		IRType* GetType() const { return type; }

		bool HasName() const { return !name.empty(); }
		std::string_view GetName() const { return name; }
		void SetName(std::string_view _name)
		{
			name = _name;
		}

		std::span<Use* const> Uses() const { return use_list; }
		bool HasOneUse() const { return use_list.size() == 1; }
		bool HasNUses(uint32 n) const { return use_list.size() == n; }
		bool HasNUsesOrMore(uint32 n) const { return use_list.size() >= n; }
		uint64 GetNumUses() const { return use_list.size(); }
		void AddUse(Use& U)
		{
			use_list.push_back(&U);
		}

		void* operator new(uint64) = delete;
		void* operator new(uint64 sz, IRModule&) { return ::operator new(sz); }

	protected:
		Value(IRValueKind kind, IRType* type) : kind(kind), type(type) {}

	private:
		IRValueKind kind;
		IRType* type;
		std::string name;
		std::vector<Use*> use_list;
	};

	class User : public Value
	{

	};
}

