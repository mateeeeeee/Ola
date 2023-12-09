#pragma once
#include "ASTNode.h"
#include "ASTAliases.h"
#include "Type.h"
#include "Frontend/SourceLocation.h"

namespace ola
{
	enum class ExprKind : uint8
	{
		Unary,
		Binary,
		Ternary,
		Call,
		IntLiteral,
		FloatLiteral,
		StringLiteral,
		BoolLiteral,
		CharLiteral,
		DeclRef,
		ImplicitCast,
		InitializerList,
		ArrayAccess,
		Member,
		MemberCall,
		This,
		Super
	};
	enum class UnaryExprKind : uint8
	{
		PreIncrement, PreDecrement,
		PostIncrement, PostDecrement,
		Plus, Minus, BitNot,
		LogicalNot
	};
	enum class BinaryExprKind : uint8
	{
		Add, Subtract, Multiply, Divide, Modulo,
		ShiftLeft, ShiftRight, BitAnd, BitOr, BitXor,
		Assign,
		Comma,
		LogicalAnd, LogicalOr,
		Equal, NotEqual,
		Less, Greater,
		LessEqual, GreaterEqual,
		Invalid
	};
	enum class ExprValueCategory : bool
	{
		LValue,
		RValue
	};

	class Expr : public ASTNode
	{
	public:
		SourceLocation const& GetLocation() const { return loc; }
		ExprKind GetExprKind() const { return kind; }
		void SetLValue(bool lvalue = true) { value_category = (lvalue ? ExprValueCategory::LValue : ExprValueCategory::RValue); }
		bool IsLValue() const { return value_category == ExprValueCategory::LValue; }

		void SetType(QualType const& _type) { type = _type; }
		QualType const& GetType() const { return type; }

		virtual bool IsConstexpr() const { return false; }
		virtual int64 EvaluateConstexpr() const { return 0; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	protected:
		ExprKind const kind;
		SourceLocation loc;
		QualType type;
		ExprValueCategory value_category = ExprValueCategory::RValue;

	protected:
		Expr(ExprKind kind, SourceLocation const& loc) : kind(kind), loc(loc) {}
		void SetValueCategory(ExprValueCategory _value_category) { value_category = _value_category; }
	};

	class UnaryExpr : public Expr
	{
	public:
		UnaryExpr(UnaryExprKind op, SourceLocation const& loc) : Expr(ExprKind::Unary, loc), op(op), operand(nullptr) {}
		void SetOperand(UniqueExprPtr&& _operand)
		{
			operand = std::move(_operand);
		}
		UnaryExprKind GetUnaryKind() const { return op; }
		Expr const* GetOperand() const { return operand.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Unary; }
	private:
		UnaryExprKind op;
		UniqueExprPtr operand;
	};

	class BinaryExpr : public Expr
	{
	public:
		BinaryExpr(BinaryExprKind op, SourceLocation const& loc) : Expr(ExprKind::Binary, loc), op(op) {}
		void SetLHS(UniqueExprPtr&& _lhs) { lhs = std::move(_lhs); }
		void SetRHS(UniqueExprPtr&& _rhs) { rhs = std::move(_rhs); }

		BinaryExprKind GetBinaryKind() const { return op; }
		Expr const* GetLHS() const { return lhs.get(); }
		Expr const* GetRHS() const { return rhs.get(); }

		virtual bool IsConstexpr() const
		{
			return lhs->IsConstexpr() && rhs->IsConstexpr();
		}
		virtual int64 EvaluateConstexpr() const
		{
			switch (op)
			{
			case BinaryExprKind::Add:			return lhs->EvaluateConstexpr() + rhs->EvaluateConstexpr();
			case BinaryExprKind::Subtract:		return lhs->EvaluateConstexpr() - rhs->EvaluateConstexpr();
			case BinaryExprKind::Multiply:		return lhs->EvaluateConstexpr() * rhs->EvaluateConstexpr();
			case BinaryExprKind::Divide:		return lhs->EvaluateConstexpr() / rhs->EvaluateConstexpr();
			case BinaryExprKind::Modulo:		return lhs->EvaluateConstexpr() % rhs->EvaluateConstexpr();
			case BinaryExprKind::ShiftLeft:		return lhs->EvaluateConstexpr() << rhs->EvaluateConstexpr();
			case BinaryExprKind::ShiftRight:	return lhs->EvaluateConstexpr() >> rhs->EvaluateConstexpr();
			case BinaryExprKind::BitAnd:		return lhs->EvaluateConstexpr() & rhs->EvaluateConstexpr();
			case BinaryExprKind::BitOr:			return lhs->EvaluateConstexpr() | rhs->EvaluateConstexpr();
			case BinaryExprKind::BitXor:		return lhs->EvaluateConstexpr() ^ rhs->EvaluateConstexpr();
			case BinaryExprKind::Assign:		return lhs->EvaluateConstexpr();
			case BinaryExprKind::Comma:			return rhs->EvaluateConstexpr();
			case BinaryExprKind::LogicalAnd:	return lhs->EvaluateConstexpr() && rhs->EvaluateConstexpr();
			case BinaryExprKind::LogicalOr:		return lhs->EvaluateConstexpr() || rhs->EvaluateConstexpr();
			case BinaryExprKind::Equal:			return lhs->EvaluateConstexpr() == rhs->EvaluateConstexpr();
			case BinaryExprKind::NotEqual:		return lhs->EvaluateConstexpr() != rhs->EvaluateConstexpr();
			case BinaryExprKind::Less:			return lhs->EvaluateConstexpr() < rhs->EvaluateConstexpr();
			case BinaryExprKind::Greater:		return lhs->EvaluateConstexpr() > rhs->EvaluateConstexpr();
			case BinaryExprKind::LessEqual:		return lhs->EvaluateConstexpr() <= rhs->EvaluateConstexpr();
			case BinaryExprKind::GreaterEqual:	return lhs->EvaluateConstexpr() >= rhs->EvaluateConstexpr();
			default:
				OLA_UNREACHABLE();
			}
			return 0;
		}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Binary; }
	private:
		UniqueExprPtr lhs, rhs;
		BinaryExprKind op;
	};

	class TernaryExpr : public Expr
	{
	public:
		explicit TernaryExpr(SourceLocation const& loc) : Expr(ExprKind::Ternary, loc)
		{}

		void SetCondExpr(UniqueExprPtr&& expr) { cond_expr = std::move(expr); }
		void SetTrueExpr(UniqueExprPtr&& expr) { true_expr = std::move(expr); }
		void SetFalseExpr(UniqueExprPtr&& expr) { false_expr = std::move(expr); }

		Expr const* GetCondExpr() const { return cond_expr.get(); }
		Expr const* GetTrueExpr() const { return true_expr.get(); }
		Expr const* GetFalseExpr() const { return false_expr.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Ternary; }
	private:
		UniqueExprPtr cond_expr;
		UniqueExprPtr true_expr;
		UniqueExprPtr false_expr;
	};

	class IdentifierExpr : public Expr
	{
	public:
		std::string_view GetName() const { return name; }

	protected:
		explicit IdentifierExpr(ExprKind kind, std::string_view name, SourceLocation const& loc) : Expr(kind, loc), name(name)
		{
			SetValueCategory(ExprValueCategory::LValue);
		}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		std::string name;
	};

	class DeclRefExpr : public IdentifierExpr
	{
	public:
		DeclRefExpr(Decl* decl, SourceLocation const& loc);

		Decl const* GetDecl() const { return decl; }
		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual bool IsConstexpr() const;
		virtual int64 EvaluateConstexpr() const;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::DeclRef; }
	private:
		Decl* decl;
	};

	class ConstantInt final : public Expr
	{
	public:
		ConstantInt(int64 value, SourceLocation const& loc) : Expr(ExprKind::IntLiteral, loc), value(value)
		{
			SetType(builtin_types::Int);
		}
		int64 GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual bool IsConstexpr() const { return true; }
		virtual int64 EvaluateConstexpr() const { return value; }

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::IntLiteral; }
	private:
		int64 value;
	};

	class ConstantChar final : public Expr
	{
	public:
		ConstantChar(char c, SourceLocation const& loc) : Expr(ExprKind::CharLiteral, loc), c(c)
		{
			SetValueCategory(ExprValueCategory::RValue);
			SetType(builtin_types::Char);
		}
		char GetChar() const { return c; }

		virtual bool IsConstexpr() const { return true; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::CharLiteral; }
	private:
		char c;
	};

	class ConstantString final : public Expr
	{
	public:
		ConstantString(std::string_view str, SourceLocation const& loc) : Expr(ExprKind::StringLiteral, loc), str(str)
		{
			SetValueCategory(ExprValueCategory::RValue);
			SetType(QualType(ArrayType(builtin_types::Char, (uint32)str.size() + 1), Qualifier_Const));
		}
		std::string_view GetString() const { return str; }

		virtual bool IsConstexpr() const { return true; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::StringLiteral; }
	private:
		std::string str;
	};

	class ConstantBool final : public Expr
	{
	public:
		ConstantBool(bool value, SourceLocation const& loc) : Expr(ExprKind::BoolLiteral, loc), value(value)
		{
			SetType(builtin_types::Bool);
		}
		bool GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual bool IsConstexpr() const { return true; }

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::BoolLiteral; }
	private:
		bool value;
	};

	class ConstantFloat final : public Expr
	{
	public:
		ConstantFloat(double value, SourceLocation const& loc) : Expr(ExprKind::FloatLiteral, loc), value(value)
		{
			SetType(builtin_types::Float);
		}
		double GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual bool IsConstexpr() const { return true; }

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::FloatLiteral; }
	private:
		double value;
	};

	class ImplicitCastExpr : public Expr
	{
	public:
		ImplicitCastExpr(SourceLocation const& loc, QualType const& qtype) : Expr(ExprKind::ImplicitCast, loc), operand(nullptr)
		{
			SetType(qtype);
			SetValueCategory(ExprValueCategory::RValue);
		}

		void SetOperand(UniqueExprPtr&& _operand)
		{
			operand = std::move(_operand);
		}
		Expr const* GetOperand() const { return operand.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::ImplicitCast; }
	private:
		UniqueExprPtr operand;
	};

	class CallExpr : public Expr
	{
	public:
		CallExpr(SourceLocation const& loc, std::string_view function_name)
			: Expr(ExprKind::Call, loc), function_name(function_name) {}

		void SetArgs(UniqueExprPtrList&& args)
		{
			func_args = std::move(args);
		}
		UniqueExprPtrList const& GetArgs() const { return func_args; }
		void SetCallee(UniqueExprPtr&& _callee)
		{
			callee = std::move(_callee);
		}
		Expr const* GetCallee() const { return callee.get(); }

		FuncType const& GetCalleeType() const
		{
			OLA_ASSERT(isa<FuncType>(GetCallee()->GetType()));
			return type_cast<FuncType>(GetCallee()->GetType());
		}

		std::string_view GetFunctionName() const { return function_name; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Call; }
	protected:
		std::string function_name;
		UniqueExprPtr callee;
		UniqueExprPtrList func_args;

	protected:
		CallExpr(ExprKind kind, SourceLocation const& loc, std::string_view function_name)
			: Expr(kind, loc), function_name(function_name) {}
	};

	class InitializerListExpr final : public Expr
	{
	public:
		explicit InitializerListExpr(SourceLocation const& loc) : Expr(ExprKind::InitializerList, loc) {}

		void SetInitList(UniqueExprPtrList&& _init_list)
		{
			init_list = std::move(_init_list);
		}
		UniqueExprPtrList const& GetInitList() const { return init_list; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual bool IsConstexpr() const
		{
			bool is_constexpr = true;
			for (auto const& init_elem : init_list) if (!init_elem->IsConstexpr()) return false;
			return true;
		}

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::InitializerList; }
	private:
		UniqueExprPtrList init_list;
	};

	class ArrayAccessExpr final : public Expr
	{
	public:
		explicit ArrayAccessExpr(SourceLocation const& loc) : Expr(ExprKind::ArrayAccess, loc)
		{
			SetValueCategory(ExprValueCategory::LValue);
		}

		void SetArrayExpr(UniqueExprPtr&& _array_expr)
		{
			array_expr = std::move(_array_expr);
		}
		void SetIndexExpr(UniqueExprPtr&& _bracket_expr)
		{
			bracket_expr = std::move(_bracket_expr);
		}

		Expr const* GetArrayExpr() const { return array_expr.get(); }
		Expr const* GetIndexExpr() const { return bracket_expr.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::ArrayAccess; }
	private:
		UniqueExprPtr array_expr;
		UniqueExprPtr bracket_expr;
	};

	class MemberExpr final : public Expr
	{
	public:
		explicit MemberExpr(SourceLocation const& loc) : Expr(ExprKind::Member, loc), decl(nullptr)
		{
			SetValueCategory(ExprValueCategory::LValue);
		}

		void SetClassExpr(UniqueExprPtr&& _class_expr)
		{
			class_expr = std::move(_class_expr);
		}
		Expr const* GetClassExpr() const { return class_expr.get(); }

		void SetMemberDecl(Decl const* _decl)
		{
			decl = _decl;
		}
		Decl const* GetMemberDecl() const { return decl; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Member; }
	private:
		UniqueExprPtr class_expr;
		Decl const* decl;
	};

	class MemberCallExpr final : public CallExpr
	{
	public:
		MemberCallExpr(SourceLocation const& loc, std::string_view function_name)
			: CallExpr(ExprKind::MemberCall, loc, function_name) {}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::MemberCall; }
	};

	class ThisExpr final : public Expr
	{
	public:
		explicit ThisExpr(SourceLocation const& loc) : Expr(ExprKind::This, loc) {}

		void SetImplicit(bool _implicit)
		{
			implicit = _implicit;
		}
		bool IsImplicit() const { return implicit; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::This; }
	private:
		bool implicit = false;
	};

	class SuperExpr final : public Expr
	{
	public:
		explicit SuperExpr(SourceLocation const& loc) : Expr(ExprKind::Super, loc) {}

		void SetImplicit(bool _implicit)
		{
			implicit = _implicit;
		}
		bool IsImplicit() const { return implicit; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Super; }
	private:
		bool implicit = false;
	};


	template <typename T> requires std::derived_from<T, Expr>
	inline bool isa(Expr const* expr) { return T::ClassOf(expr); }

	template <typename T, typename... Ts> requires (std::derived_from<T, Expr> && ... && std::derived_from<Ts, Expr>)
	inline bool isoneof(Expr const* expr)
	{
		return (T::ClassOf(expr) || ... || Ts::ClassOf(expr));
	}

	template<typename T> requires std::derived_from<T, Expr>
	inline T* cast(Expr* expr)
	{
		return static_cast<T*>(expr);
	}
	template<typename T> requires std::derived_from<T, Expr>
	inline T const* cast(Expr const* expr)
	{
		return static_cast<T const*>(expr);
	}

	template<typename T> requires std::derived_from<T, Expr>
	inline T* dyn_cast(Expr* expr)
	{
		return isa<T>(expr) ? static_cast<T*>(expr) : nullptr;
	}
	template<typename T> requires std::derived_from<T, Expr>
	inline T const* dyn_cast(Expr const* expr)
	{
		return isa<T>(expr) ? static_cast<T const*>(expr) : nullptr;
	}
}