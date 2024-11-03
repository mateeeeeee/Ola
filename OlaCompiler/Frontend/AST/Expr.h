#pragma once
#include "ASTNode.h"
#include "ASTAliases.h"
#include "Type.h"
#include "Frontend/SourceLocation.h"
#include "Compiler/RTTI.h"

namespace ola
{
	enum class ExprKind : Uint8
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
		Identifier,
		DeclRef,
		ImplicitCast,
		InitializerList,
		Ctor,
		ArrayAccess,
		Member,
		MethodCall,
		This,
		Super
	};
	enum class UnaryExprKind : Uint8
	{
		PreIncrement, PreDecrement,
		PostIncrement, PostDecrement,
		Plus, Minus, BitNot,
		LogicalNot
	};
	enum class BinaryExprKind : Uint8
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
	enum class ExprValueCategory : Bool
	{
		LValue,
		RValue
	};

	class Expr : public ASTNode
	{
	public:
		SourceLocation const& GetLocation() const { return loc; }
		ExprKind GetExprKind() const { return kind; }
		void SetLValue(Bool lvalue = true) { value_category = (lvalue ? ExprValueCategory::LValue : ExprValueCategory::RValue); }
		Bool IsLValue() const { return value_category == ExprValueCategory::LValue; }

		void SetType(QualType const& _type) { type = _type; }
		QualType const& GetType() const { return type; }

		virtual Bool IsConstexpr() const { return false; }
		virtual Sint64 EvaluateConstexpr() const { return 0; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return true; }

	protected:
		ExprKind const kind;
		SourceLocation loc;
		QualType type;
		ExprValueCategory value_category = ExprValueCategory::RValue;

	protected:
		Expr(ExprKind kind, SourceLocation const& loc) : kind(kind), loc(loc) {}
		void SetValueCategory(ExprValueCategory _value_category) { value_category = _value_category; }
	};

	class UnaryExpr final : public Expr
	{
	public:
		UnaryExpr(UnaryExprKind op, SourceLocation const& loc) : Expr(ExprKind::Unary, loc), op(op), operand(nullptr) {}
		void SetOperand(UniqueExprPtr&& _operand)
		{
			operand = std::move(_operand);
		}
		UnaryExprKind GetUnaryKind() const { return op; }
		Expr const* GetOperand() const { return operand.get(); }

		virtual Bool IsConstexpr() const override
		{ 
			return operand->IsConstexpr(); 
		}

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Unary; }
	private:
		UnaryExprKind op;
		UniqueExprPtr operand;
	};

	class BinaryExpr final : public Expr
	{
	public:
		BinaryExpr(BinaryExprKind op, SourceLocation const& loc) : Expr(ExprKind::Binary, loc), op(op) {}
		void SetLHS(UniqueExprPtr&& _lhs) { lhs = std::move(_lhs); }
		void SetRHS(UniqueExprPtr&& _rhs) { rhs = std::move(_rhs); }

		BinaryExprKind GetBinaryKind() const { return op; }
		Expr const* GetLHS() const { return lhs.get(); }
		Expr const* GetRHS() const { return rhs.get(); }

		virtual Bool IsConstexpr() const
		{
			return lhs->IsConstexpr() && rhs->IsConstexpr();
		}
		virtual Sint64 EvaluateConstexpr() const
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

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Binary; }
	private:
		UniqueExprPtr lhs, rhs;
		BinaryExprKind op;
	};

	class TernaryExpr final : public Expr
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

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Ternary; }
	private:
		UniqueExprPtr cond_expr;
		UniqueExprPtr true_expr;
		UniqueExprPtr false_expr;
	};

	class IdentifierExpr : public Expr
	{
	public:
		IdentifierExpr(std::string_view name, SourceLocation const& loc) : Expr(ExprKind::Identifier, loc), name(name)
		{
			SetValueCategory(ExprValueCategory::LValue);
		}
		std::string_view GetName() const { return name; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Identifier || expr->GetExprKind() == ExprKind::DeclRef; }
	private:
		std::string name;

	protected:
		IdentifierExpr(ExprKind kind, std::string_view name, SourceLocation const& loc) : Expr(kind, loc), name(name)
		{
			OLA_ASSERT(kind == ExprKind::DeclRef);
			SetValueCategory(ExprValueCategory::LValue);
		}
	};

	class DeclRefExpr final : public IdentifierExpr
	{
	public:
		DeclRefExpr(Decl const* decl, SourceLocation const& loc);

		Decl const* GetDecl() const { return decl; }
		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual Bool IsConstexpr() const;
		virtual Sint64 EvaluateConstexpr() const;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::DeclRef; }
	private:
		Decl const* decl;
	};

	class IntLiteral final : public Expr
	{
	public:
		IntLiteral(Sint64 value, SourceLocation const& loc) : Expr(ExprKind::IntLiteral, loc), value(value) 
		{
			SetValueCategory(ExprValueCategory::RValue);
		}
		Sint64 GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual Bool IsConstexpr() const { return true; }
		virtual Sint64 EvaluateConstexpr() const { return value; }

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::IntLiteral; }
	private:
		Sint64 value;
	};

	class CharLiteral final : public Expr
	{
	public:
		CharLiteral(Char c, SourceLocation const& loc) : Expr(ExprKind::CharLiteral, loc), c(c)
		{
			SetValueCategory(ExprValueCategory::RValue);
		}
		Char GetChar() const { return c; }

		virtual Bool IsConstexpr() const { return true; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::CharLiteral; }
	private:
		Char c;
	};

	class StringLiteral final : public Expr
	{
	public:
		StringLiteral(std::string_view str, SourceLocation const& loc) : Expr(ExprKind::StringLiteral, loc), str(str)
		{
			SetValueCategory(ExprValueCategory::RValue);
		}
		std::string_view GetString() const { return str; }

		virtual Bool IsConstexpr() const { return true; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::StringLiteral; }
	private:
		std::string str;
	};

	class BoolLiteral final : public Expr
	{
	public:
		BoolLiteral(Bool value, SourceLocation const& loc) : Expr(ExprKind::BoolLiteral, loc), value(value) 
		{
			SetValueCategory(ExprValueCategory::RValue);
		}
		Bool GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual Bool IsConstexpr() const { return true; }

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::BoolLiteral; }
	private:
		Bool value;
	};

	class FloatLiteral final : public Expr
	{
	public:
		FloatLiteral(Float64 value, SourceLocation const& loc) : Expr(ExprKind::FloatLiteral, loc), value(value) {}
		Float64 GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual Bool IsConstexpr() const { return true; }

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::FloatLiteral; }
	private:
		Float64 value;
	};

	class ImplicitCastExpr final : public Expr
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

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::ImplicitCast; }
	private:
		UniqueExprPtr operand;
	};

	class CallExpr : public Expr
	{
	public:
		CallExpr(SourceLocation const& loc, FunctionDecl const* func_decl)
			: Expr(ExprKind::Call, loc), func_decl(func_decl) {}

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
		FuncType const* GetCalleeType() const
		{
			OLA_ASSERT(isa<FuncType>(GetCallee()->GetType()));
			return cast<FuncType>(GetCallee()->GetType());
		}
		FunctionDecl const* GetFunctionDecl() const { return func_decl; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Call || expr->GetExprKind() == ExprKind::MethodCall; }
	protected:
		FunctionDecl const* func_decl;
		UniqueExprPtr callee;
		UniqueExprPtrList func_args;

	protected:
		CallExpr(ExprKind kind, SourceLocation const& loc, FunctionDecl const* func_decl)
			: Expr(kind, loc), func_decl(func_decl) {}
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
		virtual Bool IsConstexpr() const
		{
			Bool is_constexpr = true;
			for (auto const& init_elem : init_list) if (!init_elem->IsConstexpr()) return false;
			return true;
		}

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::InitializerList; }
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

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::ArrayAccess; }
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

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Member; }
	private:
		UniqueExprPtr class_expr;
		Decl const* decl;
	};

	class MethodCallExpr final : public CallExpr
	{
	public:
		MethodCallExpr(SourceLocation const& loc, MethodDecl const* method_decl);

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::MethodCall; }
	};

	class ThisExpr final : public Expr
	{
	public:
		explicit ThisExpr(SourceLocation const& loc) : Expr(ExprKind::This, loc) {}

		void SetImplicit(Bool _implicit)
		{
			implicit = _implicit;
		}
		Bool IsImplicit() const { return implicit; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::This; }
	private:
		Bool implicit = false;
	};

	class SuperExpr final : public Expr
	{
	public:
		explicit SuperExpr(SourceLocation const& loc) : Expr(ExprKind::Super, loc) {}

		void SetImplicit(Bool _implicit)
		{
			implicit = _implicit;
		}
		Bool IsImplicit() const { return implicit; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Super; }
	private:
		Bool implicit = false;
	};

	class ConstructorExpr final : public Expr
	{
	public:
		ConstructorExpr(SourceLocation const& loc, ConstructorDecl const* ctor_decl) : Expr(ExprKind::Ctor, loc), ctor_decl(ctor_decl) {}

		void SetArgs(UniqueExprPtrList&& args)
		{
			ctor_args = std::move(args);
		}
		UniqueExprPtrList const& GetArgs() const { return ctor_args; }
		ConstructorDecl const* GetCtorDecl() const { return ctor_decl; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static Bool ClassOf(Expr const* expr) { return expr->GetExprKind() == ExprKind::Ctor; }

	private:
		ConstructorDecl const* ctor_decl;
		UniqueExprPtrList ctor_args;
	};
}