#pragma once
#include "IRType.h"
#include "Compiler/RTTI.h"

namespace ola
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
}

