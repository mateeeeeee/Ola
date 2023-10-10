#pragma once
#include "AliasAST.h"
#include "IVisitorAST.h"
#include "SourceLocation.h"
#include "Type.h"

namespace wave
{
	class NodeAST
	{
	public:
		virtual ~NodeAST() = default;
		virtual void Accept(IVisitorAST& visitor, uint32 depth) const {};
		virtual void Accept(IVisitorAST& visitor) const {}
	protected:
		NodeAST() = default;
	};

	class TranslationUnitAST final : public NodeAST
	{
	public:
		TranslationUnitAST() = default;

		void AddDeclaration(UniqueDeclPtr&& declaration)
		{
			declarations.push_back(std::move(declaration));
		}

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UniqueDeclPtrList declarations;
	};

	enum class DeclKind : bool
	{
		Variable,
		Function
	};
	class DeclAST : public NodeAST
	{
	public:
		DeclKind GetDeclKind() const { return decl_kind; }
		SourceLocation GetLocation() const { return source_loc; }
		std::string_view GetName() const { return name; }

		void SetType(QualifiedType const& _type) { type = _type; }
		QualifiedType const& GetType() const { return type; }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		DeclKind const decl_kind;
		std::string name;
		SourceLocation source_loc;
		QualifiedType type;

	protected:
		DeclAST(DeclKind decl_kind, std::string_view name, SourceLocation const& loc)
			: decl_kind(decl_kind), name(name), source_loc(loc) {}
	};
	class VariableDeclAST : public DeclAST
	{
	public:
		VariableDeclAST(std::string_view name, SourceLocation const& loc) : DeclAST(DeclKind::Variable, name, loc) {}

		void SetInitExpr(UniqueExprPtr&& expr)
		{
			init_expr = std::move(expr);
		}
		ExprPtr GetInitExpr() const { return init_expr.get(); }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UniqueExprPtr init_expr;
	};
	class FunctionDeclAST : public DeclAST
	{
	public:
		FunctionDeclAST(std::string_view name, SourceLocation const& loc) : DeclAST(DeclKind::Function, name, loc) {}

		void SetParamDeclarations(UniqueVariableDeclPtrList&& param_decls)
		{
			param_declarations = std::move(param_decls);
		}
		void SetDefinition(UniqueCompoundStmtPtr&& _definition)
		{
			definition = std::move(_definition);
		}
		bool IsExtern() const
		{
			return definition == nullptr;
		}

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UniqueVariableDeclPtrList param_declarations;
		UniqueCompoundStmtPtr definition;
	};

	enum class StmtKind : uint8
	{
		Compound,
		Expr,
		Decl,
		Null,
		If,
		While,
		DoWhile,
		Switch,
		Case,
		For,
		Return,
		Goto,
		Label,
		Break,
		Continue
	};
	class StmtAST : public NodeAST
	{
	public:
		StmtKind GetStmtKind() const { return kind; }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	protected:
		StmtKind const kind;

	protected:
		explicit StmtAST(StmtKind kind) : kind(kind) {}
	};
	class CompoundStmtAST final : public StmtAST
	{
	public:
		CompoundStmtAST() : StmtAST(StmtKind::Compound) {}

		void AddStatement(UniqueStmtPtr&& stmt)
		{
			statements.push_back(std::move(stmt));
		}

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UniqueStmtPtrList statements;
	};
	class ExprStmtAST : public StmtAST
	{
	public:
		ExprStmtAST(UniqueExprPtr&& expr) : StmtAST(expr ? StmtKind::Expr : StmtKind::Null), expr(std::move(expr)) {}

		ExprPtr GetExpr() const { return expr.get(); }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UniqueExprPtr expr;
	};
	class NullStmtAST final : public ExprStmtAST
	{
	public:
		NullStmtAST() : ExprStmtAST(nullptr) {}

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	};
	class DeclStmtAST final : public StmtAST
	{
	public:
		DeclStmtAST(UniqueDeclPtr&& decl) : StmtAST(StmtKind::Decl), declaration(std::move(decl)) {}

		DeclPtr GetDeclaration() const { return declaration.get(); }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UniqueDeclPtr declaration;
	};
	class ReturnStmtAST final : public StmtAST
	{
	public:
		explicit ReturnStmtAST(std::unique_ptr<ExprStmtAST>&& ret_expr)
			: StmtAST(StmtKind::Return), ret_expr(std::move(ret_expr)) {}

		ExprStmtPtr GetExprStmt() const { return ret_expr.get(); }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UniqueExprStmtPtr ret_expr;
	};
	class IfStmtAST final : public StmtAST
	{
	public:
		IfStmtAST() : StmtAST(StmtKind::If) {}

		void SetCondition(UniqueExprPtr&& _condition)
		{
			condition = std::move(_condition);
		}
		void SetThenStatement(UniqueStmtPtr&& _then_stmt)
		{
			then_stmt = std::move(_then_stmt);
		}
		void SetElseStatement(UniqueStmtPtr&& _else_stmt)
		{
			else_stmt = std::move(_else_stmt);
		}

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UniqueExprPtr condition;
		UniqueStmtPtr then_stmt;
		UniqueStmtPtr else_stmt;
	};

	enum class ExprKind : uint8
	{
		Unary,
		Binary,
		Ternary,
		FunctionCall,
		IntLiteral,
		FloatLiteral,
		StringLiteral,
		DeclRef,
		Cast
	};
	enum class UnaryExprKind : uint8
	{
		PreIncrement, PreDecrement,
		PostIncrement, PostDecrement,
		Plus, Minus, BitNot,
		LogicalNot,
		Dereference, AddressOf
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
	class ExprAST : public NodeAST
	{
	public:
		SourceLocation const& GetLocation() const { return loc; }
		ExprKind GetExprKind() const { return kind; }
		bool IsLValue() const { return value_category == ExprValueCategory::LValue; }

		void SetType(QualifiedType const& _type) { type = _type; }
		QualifiedType const& GetType() const { return type; }

		virtual bool IsConstexpr() const { return false; }
		virtual int64 EvaluateConstexpr() const { return 0; }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	protected:
		ExprKind const kind;
		SourceLocation loc;
		QualifiedType type;
		ExprValueCategory value_category = ExprValueCategory::RValue;

	protected:
		ExprAST(ExprKind kind, SourceLocation const& loc) : kind(kind), loc(loc) {}
		void SetValueCategory(ExprValueCategory _value_category) { value_category = _value_category; }
	};
	class UnaryExprAST : public ExprAST
	{
	public:
		UnaryExprAST(UnaryExprKind op, SourceLocation const& loc) : ExprAST(ExprKind::Unary, loc), op(op), operand(nullptr) {}
		void SetOperand(UniqueExprPtr&& _operand)
		{
			operand = std::move(_operand);
		}
		UnaryExprKind GetUnaryKind() const { return op; }
		ExprPtr GetOperand() const { return operand.get(); }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UnaryExprKind op;
		UniqueExprPtr operand;
	};
	class BinaryExprAST : public ExprAST
	{
	public:
		BinaryExprAST(BinaryExprKind op, SourceLocation const& loc) : ExprAST(ExprKind::Binary, loc), op(op) {}
		void SetLHS(UniqueExprPtr&& _lhs) { lhs = std::move(_lhs); }
		void SetRHS(UniqueExprPtr&& _rhs) { rhs = std::move(_rhs); }

		BinaryExprKind GetBinaryKind() const { return op; }
		ExprPtr GetLHS() const { return lhs.get(); }
		ExprPtr GetRHS() const { return rhs.get(); }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UniqueExprPtr lhs, rhs;
		BinaryExprKind op;
	};
	class TernaryExprAST : public ExprAST
	{
	public:
		explicit TernaryExprAST(SourceLocation const& loc) : ExprAST(ExprKind::Ternary, loc),
			cond_expr(std::move(cond_expr)),
			true_expr(std::move(true_expr)),
			false_expr(std::move(false_expr))
		{}

		void SetCondition(UniqueExprPtr&& expr) { cond_expr = std::move(expr); }
		void SetTrueExpr(UniqueExprPtr&& expr) { true_expr = std::move(expr); }
		void SetFalseExpr(UniqueExprPtr&& expr) { false_expr = std::move(expr); }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UniqueExprPtr cond_expr;
		UniqueExprPtr true_expr;
		UniqueExprPtr false_expr;
	};
	class IntLiteralAST final : public ExprAST
	{
	public:
		IntLiteralAST(int64 value, SourceLocation const& loc) : ExprAST(ExprKind::IntLiteral, loc), value(value) 
		{
			SetType(builtin_types::Int);
		}
		int64 GetValue() const { return value; }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		int64 value;
	};
	class StringLiteralAST final : public ExprAST
	{
	public:
		StringLiteralAST(std::string_view str, SourceLocation const& loc) : ExprAST(ExprKind::StringLiteral, loc), str(str) 
		{
			SetType(ArrayType(builtin_types::Char, (uint32)str.size()));
		}
		std::string_view GetString() const { return str; }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		std::string str;
	};
	class IdentifierAST : public ExprAST
	{
	public:
		explicit IdentifierAST(std::string_view name, SourceLocation const& loc) : ExprAST(ExprKind::DeclRef, loc), name(name)
		{
			SetValueCategory(ExprValueCategory::LValue);
		}
		std::string_view GetName() const { return name; }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		std::string name;
	};
	class CastExprAST : public ExprAST
	{
	public:
		CastExprAST(SourceLocation const& loc, QualifiedType const& qtype)
			: ExprAST(ExprKind::Cast, loc), operand(nullptr)
		{
			SetType(qtype);
			SetValueCategory(ExprValueCategory::RValue);
		}

		void SetOperand(UniqueExprPtr&& _operand)
		{
			operand = std::move(_operand);
		}
		ExprPtr GetOperand() const { return operand.get(); }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UniqueExprPtr operand;
	};
	class FunctionCallExprAST final : public ExprAST
	{
	public:
		FunctionCallExprAST(UniqueExprPtr&& func, SourceLocation const& loc)
			: ExprAST(ExprKind::FunctionCall, loc), func_expr(std::move(func)) {}

		void AddArgument(UniqueExprPtr&& arg)
		{
			func_args.push_back(std::move(arg));
		}
		ExprPtr GetFunction() const { return func_expr.get(); }

		virtual void Accept(IVisitorAST& visitor, uint32 depth) const override;
		virtual void Accept(IVisitorAST& visitor) const override;

	private:
		UniqueExprPtr func_expr;
		UniqueExprPtrList func_args;
	};

	struct AST
	{
		AST() { translation_unit = std::make_unique<TranslationUnitAST>(); }
		std::unique_ptr<TranslationUnitAST> translation_unit;
	};

	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To>&& std::is_base_of_v<NodeAST, From>
	inline To* dynamic_ast_cast(From* from)
	{
		return dynamic_cast<To*>(from);
	}
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To>&& std::is_base_of_v<NodeAST, From>
	inline To const* dynamic_ast_cast(From const* from)
	{
		return dynamic_cast<To const*>(from);
	}
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To>&& std::is_base_of_v<NodeAST, From>
	inline To* ast_cast(From* from)
	{
		return static_cast<To*>(from);
	}
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To>&& std::is_base_of_v<NodeAST, From>
	inline To const* ast_cast(From const* from)
	{
		return static_cast<To const*>(from);
	}
}