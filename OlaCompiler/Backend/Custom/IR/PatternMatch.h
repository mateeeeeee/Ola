#pragma once
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRType.h"

namespace ola
{
	template<typename ValueT> requires std::is_base_of_v<Value, ValueT>
	struct PatternMatchContext
	{
		explicit PatternMatchContext(ValueT* V) : value(V) {}

		OLA_NODISCARD PatternMatchContext<Value> GetOperandContext(Uint32 idx) const
		{
			if constexpr (std::is_base_of_v<Instruction, ValueT>)
			{
				Value* V = value->GetOperand(idx);
				return PatternMatchContext<Value>(V);
			}
			else return PatternMatchContext<Value>(nullptr);
		}
		ValueT* value;
	};

	class AnyMatch 
	{
	public:
		explicit AnyMatch(Value*& value) : V(value) {}

		OLA_NODISCARD Bool operator()(PatternMatchContext<Value> const& ctx) const
		{
			V = ctx.value;
			return true;
		}

	private:
		Value*& V;
	};
	inline auto Any_(Value*& V) 
	{
		return AnyMatch(V);
	}

	class ExactMatch
	{
	public:
		explicit ExactMatch(Value*& value) : V(value) {}

		bool operator()(PatternMatchContext<Value> const& ctx) const
		{
			return ctx.value == V;
		}


	private:
		Value*& V;
	};

	inline auto Exact_(Value*& V)
	{
		return ExactMatch(V);
	}

	class BoolMatch
	{
	public:
		explicit BoolMatch(Value*& value) : V(value) {}

		OLA_NODISCARD Bool operator()(PatternMatchContext<Value> const& ctx) const
		{
			V = ctx.value;
			return V->GetType()->IsBoolean();
		}

	private:
		Value*& V;
	};
	inline auto Bool_(Value*& V) 
	{
		return BoolMatch(V);
	}

	class Int64Match
	{
	public:
		explicit Int64Match(Value*& value) : V(value) {}

		OLA_NODISCARD Bool operator()(PatternMatchContext<Value> const& ctx) const
		{
			V = ctx.value;
			return V->GetType()->IsInteger() && V->GetType()->GetSize() == 8;
		}

	private:
		Value*& V;
	};
	inline auto Int64_(Value*& V)
	{
		return Int64Match(V);
	}

	template <typename ValueT, typename Derived>
	class GenericMatch 
	{
	public:
		OLA_NODISCARD Bool operator()(PatternMatchContext<Value> const& ctx) const
		{
			if (ValueT* V = dyn_cast<ValueT>(ctx.value))
			{
				return (static_cast<Derived const*>(this))->TryMatch(PatternMatchContext<ValueT>(V));
			}
			return false;
		}
	};

	class ConstantIntMatch : public GenericMatch<ConstantInt, ConstantIntMatch>
	{
	public:
		explicit ConstantIntMatch(Int64& value) : V(value) {}

		OLA_NODISCARD Bool TryMatch(PatternMatchContext<ConstantInt> const& ctx) const
		{
			V = ctx.value->GetValue();
			return true;
		}

	private:
		Int64& V;
	};
	inline auto Int_(Int64& V)
	{
		return ConstantIntMatch(V);
	}

	class ConstantIntValueMatch : public GenericMatch<ConstantInt, ConstantIntValueMatch>
	{
	public:
		explicit ConstantIntValueMatch(Int64 value) : V(value) {}

		OLA_NODISCARD Bool TryMatch(PatternMatchContext<ConstantInt> const& ctx) const
		{
			return V == ctx.value->GetValue();
		}

	private:
		Int64 V;
	};
	inline auto CInt_(Int64 V)
	{
		return ConstantIntValueMatch(V);
	}

	class ConstantFloatMatch : public GenericMatch<ConstantFloat, ConstantFloatMatch>
	{
	public:
		explicit ConstantFloatMatch(Float64& value) : V(value) {}

		OLA_NODISCARD Bool TryMatch(PatternMatchContext<ConstantFloat> const& ctx) const
		{
			V = ctx.value->GetValue();
			return true;
		}

	private:
		Float64& V;
	};
	inline auto Float_(Float64& V)
	{
		return ConstantFloatMatch(V);
	}

	class ConstantFloatValueMatch : public GenericMatch<ConstantFloat, ConstantFloatValueMatch>
	{
	public:
		explicit ConstantFloatValueMatch(Float64 value) : V(value) {}

		OLA_NODISCARD Bool TryMatch(PatternMatchContext<ConstantFloat> const& ctx) const
		{
			return V == ctx.value->GetValue();
		}

	private:
		Float64 V;
	};
	inline auto CFloat_(Float64 V)
	{
		return ConstantFloatValueMatch(V);
	}

	template <typename OperandMatchT>
	class UnaryOpMatch : public GenericMatch<UnaryInst, UnaryOpMatch<OperandMatchT>>
	{
	public:
		UnaryOpMatch(Opcode inst_opcode, OperandMatchT&& operand_matcher) : inst_opcode(inst_opcode), operand_matcher(std::forward<OperandMatchT>(operand_matcher)) {}

		OLA_NODISCARD Bool TryMatch(PatternMatchContext<UnaryInst> const& ctx) const
		{
			return ctx.value->GetOpcode() == inst_opcode && operand_matcher(ctx.GetOperandContext(0));
		}

	private:
		Opcode inst_opcode;
		OperandMatchT operand_matcher;
	};

	template <typename OperandMatchT>
	inline auto Neg_(OperandMatchT&& operand_matcher)
	{
		return UnaryOpMatch(Opcode::Neg, std::forward<OperandMatchT>(operand_matcher));
	}
	template <typename OperandMatchT>
	inline auto Not_(OperandMatchT&& operand_matcher)
	{
		return UnaryOpMatch(Opcode::Not, std::forward<OperandMatchT>(operand_matcher));
	}
	template <typename OperandMatchT>
	inline auto FNeg_(OperandMatchT&& operand_matcher)
	{
		return UnaryOpMatch(Opcode::FNeg, std::forward<OperandMatchT>(operand_matcher));
	}

	template <Bool Commutative, typename LeftOperandMatchT, typename RightOperandMatchT>
	class BinaryOpMatch : public GenericMatch<BinaryInst, BinaryOpMatch<Commutative, LeftOperandMatchT, RightOperandMatchT>>
	{
	public:
		BinaryOpMatch(Opcode inst_opcode, LeftOperandMatchT&& left_operand_matcher, RightOperandMatchT&& right_operand_matcher)
			: inst_opcode(inst_opcode), 
			left_operand_matcher(std::forward<LeftOperandMatchT>(left_operand_matcher)),
			right_operand_matcher(std::forward<RightOperandMatchT>(right_operand_matcher)) {}

		OLA_NODISCARD Bool TryMatch(PatternMatchContext<BinaryInst> const& ctx) const
		{
			if (inst_opcode != ctx.value->GetOpcode()) return false;
			if (left_operand_matcher(ctx.GetOperandContext(0)) && right_operand_matcher(ctx.GetOperandContext(1))) return true;
			if constexpr (Commutative) return left_operand_matcher(ctx.GetOperandContext(1)) && right_operand_matcher(ctx.GetOperandContext(0));
			return false;
		}

	private:
		Opcode inst_opcode;
		LeftOperandMatchT left_operand_matcher;
		RightOperandMatchT right_operand_matcher;
	};

	template <typename LeftOperandMatchT, typename RightOperandMatchT>
	inline auto Add_(LeftOperandMatchT&& lhs, RightOperandMatchT&& rhs)
	{
		return BinaryOpMatch<true, LeftOperandMatchT, RightOperandMatchT>( Opcode::Add, std::forward<LeftOperandMatchT>(lhs), std::forward<RightOperandMatchT>(rhs) );
	}
	template <typename LeftOperandMatchT, typename RightOperandMatchT>
	inline auto Sub_(LeftOperandMatchT&& lhs, RightOperandMatchT&& rhs)
	{
		return BinaryOpMatch<false, LeftOperandMatchT, RightOperandMatchT>(Opcode::Sub, std::forward<LeftOperandMatchT>(lhs), std::forward<RightOperandMatchT>(rhs));
	}
	template <typename LeftOperandMatchT, typename RightOperandMatchT>
	inline auto Mul_(LeftOperandMatchT&& lhs, RightOperandMatchT&& rhs)
	{
		return BinaryOpMatch<true, LeftOperandMatchT, RightOperandMatchT>(Opcode::SMul, std::forward<LeftOperandMatchT>(lhs), std::forward<RightOperandMatchT>(rhs));
	}
	template <typename LeftOperandMatchT, typename RightOperandMatchT>
	inline auto SDiv_(LeftOperandMatchT&& lhs, RightOperandMatchT&& rhs)
	{
		return BinaryOpMatch<false, LeftOperandMatchT, RightOperandMatchT>(Opcode::SDiv, std::forward<LeftOperandMatchT>(lhs), std::forward<RightOperandMatchT>(rhs));
	}
	template <typename LeftOperandMatchT, typename RightOperandMatchT>
	inline auto SRem_(LeftOperandMatchT&& lhs, RightOperandMatchT&& rhs)
	{
		return BinaryOpMatch<false, LeftOperandMatchT, RightOperandMatchT>(Opcode::SRem, std::forward<LeftOperandMatchT>(lhs), std::forward<RightOperandMatchT>(rhs));
	}

	template <typename LeftOperandMatchT, typename RightOperandMatchT>
	inline auto FAdd_(LeftOperandMatchT&& lhs, RightOperandMatchT&& rhs)
	{
		return BinaryOpMatch<true, LeftOperandMatchT, RightOperandMatchT>(Opcode::FAdd, std::forward<LeftOperandMatchT>(lhs), std::forward<RightOperandMatchT>(rhs));
	}
	template <typename LeftOperandMatchT, typename RightOperandMatchT>
	inline auto FSub_(LeftOperandMatchT&& lhs, RightOperandMatchT&& rhs)
	{
		return BinaryOpMatch<false, LeftOperandMatchT, RightOperandMatchT>(Opcode::FSub, std::forward<LeftOperandMatchT>(lhs), std::forward<RightOperandMatchT>(rhs));
	}
	template <typename LeftOperandMatchT, typename RightOperandMatchT>
	inline auto FMul_(LeftOperandMatchT&& lhs, RightOperandMatchT&& rhs)
	{
		return BinaryOpMatch<true, LeftOperandMatchT, RightOperandMatchT>(Opcode::FMul, std::forward<LeftOperandMatchT>(lhs), std::forward<RightOperandMatchT>(rhs));
	}
	template <typename LeftOperandMatchT, typename RightOperandMatchT>
	inline auto FDiv_(LeftOperandMatchT&& lhs, RightOperandMatchT&& rhs)
	{
		return BinaryOpMatch<false, LeftOperandMatchT, RightOperandMatchT>(Opcode::FDiv, std::forward<LeftOperandMatchT>(lhs), std::forward<RightOperandMatchT>(rhs));
	}
}