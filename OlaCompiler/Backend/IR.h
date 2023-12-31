#pragma once

namespace ola::ir 
{
	enum class ValueKind
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
		Value()
		{

		}

		virtual ~Value() = default;

		ValueKind GetKind() const { return kind; }

	private:
		ValueKind kind;
	};
}

