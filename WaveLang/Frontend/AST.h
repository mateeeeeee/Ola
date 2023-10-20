#pragma once
#include "ASTTypeAliases.h"
#include "ASTVisitor.h"
#include "SourceLocation.h"
#include "Type.h"

namespace wave
{
	class NodeAST
	{
	public:
		virtual ~NodeAST() = default;
		virtual void Accept(ASTVisitor& visitor, uint32 depth) const {};
		virtual void Accept(ASTVisitor& visitor) const {}
	protected:
		NodeAST() = default;
	};


	class TranslationUnit final : public NodeAST
	{
	public:
		TranslationUnit() = default;

		void AddDecl(UniqueDeclPtr&& declaration)
		{
			declarations.push_back(std::move(declaration));
		}
		UniqueDeclPtrList const& GetDecls() const { return declarations; }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueDeclPtrList declarations;
	};


	enum class DeclKind : bool
	{
		Variable,
		Function
	};

	class Decl : public NodeAST
	{
	public:
		DeclKind GetDeclKind() const { return decl_kind; }
		SourceLocation GetLocation() const { return source_loc; }
		std::string_view GetName() const { return name; }

		void SetType(QualifiedType const& _type) { type = _type; }
		QualifiedType const& GetType() const { return type; }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		DeclKind const decl_kind;
		std::string name;
		SourceLocation source_loc;
		QualifiedType type;

	protected:
		Decl(DeclKind decl_kind, std::string_view name, SourceLocation const& loc)
			: decl_kind(decl_kind), name(name), source_loc(loc) {}
	};

	class VariableDecl : public Decl
	{
	public:
		VariableDecl(std::string_view name, SourceLocation const& loc) : Decl(DeclKind::Variable, name, loc) {}

		void SetInitExpr(UniqueExprPtr&& expr)
		{
			init_expr = std::move(expr);
		}
		Expr const* GetInitExpr() const { return init_expr.get(); }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueExprPtr init_expr;
	};

	class FunctionDecl : public Decl
	{
	public:
		FunctionDecl(std::string_view name, SourceLocation const& loc) : Decl(DeclKind::Function, name, loc) {}

		void SetParamDecls(UniqueVariableDeclPtrList&& param_decls)
		{
			param_declarations = std::move(param_decls);
		}
		void SetBodyStmt(UniqueCompoundStmtPtr&& _definition)
		{
			definition = std::move(_definition);
		}
		UniqueVariableDeclPtrList const& GetParamDeclarations() const { return param_declarations; }
		CompoundStmt const* GetBodyStmt() const { return definition.get(); }

		bool IsDefinition() const
		{
			return definition == nullptr;
		}

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

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

	class Stmt : public NodeAST
	{
	public:
		StmtKind GetStmtKind() const { return kind; }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	protected:
		StmtKind const kind;

	protected:
		explicit Stmt(StmtKind kind) : kind(kind) {}
	};

	class CompoundStmt final : public Stmt
	{
	public:
		CompoundStmt(UniqueStmtPtrList&& stmts) : Stmt(StmtKind::Compound), statements(std::move(stmts)) {}
		UniqueStmtPtrList const& GetStmts() const { return statements; }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueStmtPtrList statements;
	};
	
	class DeclStmt final : public Stmt
	{
	public:
		DeclStmt(UniqueDeclPtr&& decl) : Stmt(StmtKind::Decl), declaration(std::move(decl)) {}

		Decl const* GetDecl() const { return declaration.get(); }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueDeclPtr declaration;
	};

	class ExprStmt : public Stmt
	{
	public:
		ExprStmt(UniqueExprPtr&& expr) : Stmt(expr ? StmtKind::Expr : StmtKind::Null), expr(std::move(expr)) {}

		Expr const* GetExpr() const 
		{
			return expr.get(); 
		}

		Expr* ReleaseExpr()
		{
			return expr.release();
		}

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueExprPtr expr;
	};

	class NullStmt final : public ExprStmt
	{
	public:
		NullStmt() : ExprStmt(nullptr) {}

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	};

	class ReturnStmt final : public Stmt
	{
	public:
		explicit ReturnStmt(std::unique_ptr<ExprStmt>&& ret_expr)
			: Stmt(StmtKind::Return), ret_expr(std::move(ret_expr)) {}

		ExprStmt const* GetExprStmt() const { return ret_expr.get(); }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueExprStmtPtr ret_expr;
	};

	class IfStmt final : public Stmt
	{
	public:
		IfStmt() : Stmt(StmtKind::If) {}

		void SetConditionExpr(UniqueExprPtr&& _condition)
		{
			condition = std::move(_condition);
		}
		void SetThenStmt(UniqueStmtPtr&& _then_stmt)
		{
			then_stmt = std::move(_then_stmt);
		}
		void SetElseStmt(UniqueStmtPtr&& _else_stmt)
		{
			else_stmt = std::move(_else_stmt);
		}

		Expr const* GetConditionExpr() const { return condition.get(); }
		Stmt const* GetThenStmt() const { return then_stmt.get(); }
		Stmt const* GetElseStmt() const { return else_stmt.get(); }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueExprPtr condition;
		UniqueStmtPtr then_stmt;
		UniqueStmtPtr else_stmt;
	};

	class BreakStmt final : public Stmt
	{
	public:
		BreakStmt() : Stmt(StmtKind::Break) {}

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;
	};

	class ContinueStmt final : public Stmt
	{
	public:
		ContinueStmt() : Stmt(StmtKind::Continue) {}

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;
	};

	class ForStmt final : public Stmt
	{
	public:
		ForStmt() : Stmt(StmtKind::For) {}

		void SetInitStmt(UniqueStmtPtr&& _init_stmt)
		{
			init_stmt = std::move(_init_stmt);
		}
		void SetCondExpr(UniqueExprPtr&& _cond_expr)
		{
			cond_expr = std::move(_cond_expr);
		}
		void SetIterExpr(UniqueExprPtr&& _iter_expr)
		{
			iter_expr = std::move(_iter_expr);
		}
		void SetBodyStmt(UniqueStmtPtr&& _body_stmt)
		{
			body_stmt = std::move(_body_stmt);
		}

		Stmt const* GetInitStmt() const { return init_stmt.get(); }
		Expr const* GetCondExpr() const { return cond_expr.get(); }
		Expr const* GetIterExpr() const { return iter_expr.get(); }
		Stmt const* GetBodyStmt() const { return body_stmt.get(); }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueStmtPtr init_stmt;
		UniqueExprPtr cond_expr;
		UniqueExprPtr iter_expr;
		UniqueStmtPtr body_stmt;
	};

	class WhileStmt final : public Stmt
	{
	public:
		WhileStmt() : Stmt(StmtKind::While) {}

		void SetCondExpr(UniqueExprPtr&& _cond_expr)
		{
			cond_expr = std::move(_cond_expr);
		}
		void SetBodyStmt(UniqueStmtPtr&& _body_stmt)
		{
			body_stmt = std::move(_body_stmt);
		}

		Expr const* GetCondExpr() const { return cond_expr.get(); }
		Stmt const* GetBodyStmt() const { return body_stmt.get(); }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueExprPtr cond_expr;
		UniqueStmtPtr body_stmt;
	};

	class DoWhileStmt final : public Stmt
	{
	public:
		DoWhileStmt() : Stmt(StmtKind::DoWhile) {}

		void SetCondExpr(UniqueExprPtr&& _cond_expr)
		{
			cond_expr = std::move(_cond_expr);
		}
		void SetBodyStmt(UniqueStmtPtr&& _body_stmt)
		{
			body_stmt = std::move(_body_stmt);
		}

		Expr const* GetCondExpr() const { return cond_expr.get(); }
		Stmt const* GetBodyStmt() const { return body_stmt.get(); }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueExprPtr cond_expr;
		UniqueStmtPtr body_stmt;
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
		BoolLiteral,
		DeclRef,
		ImplicitCast
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

	class Expr : public NodeAST
	{
	public:
		SourceLocation const& GetLocation() const { return loc; }
		ExprKind GetExprKind() const { return kind; }
		bool IsLValue() const { return value_category == ExprValueCategory::LValue; }

		void SetType(QualifiedType const& _type) { type = _type; }
		QualifiedType const& GetType() const { return type; }

		virtual bool IsConstexpr() const { return false; }
		virtual int64 EvaluateConstexpr() const { return 0; }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	protected:
		ExprKind const kind;
		SourceLocation loc;
		QualifiedType type;
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

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

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

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueExprPtr lhs, rhs;
		BinaryExprKind op;
	};

	class TernaryExpr : public Expr
	{
	public:
		explicit TernaryExpr(SourceLocation const& loc) : Expr(ExprKind::Ternary, loc),
			cond_expr(std::move(cond_expr)),
			true_expr(std::move(true_expr)),
			false_expr(std::move(false_expr))
		{}

		void SetCondExpr(UniqueExprPtr&& expr) { cond_expr = std::move(expr); }
		void SetTrueExpr(UniqueExprPtr&& expr) { true_expr = std::move(expr); }
		void SetFalseExpr(UniqueExprPtr&& expr) { false_expr = std::move(expr); }

		Expr const* GetCondExpr() const { return cond_expr.get(); }
		Expr const* GetTrueExpr() const { return true_expr.get(); }
		Expr const* GetFalseExpr() const { return false_expr.get(); }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueExprPtr cond_expr;
		UniqueExprPtr true_expr;
		UniqueExprPtr false_expr;
	};

	class IdentifierExpr : public Expr
	{
	protected:
		explicit IdentifierExpr(ExprKind kind, std::string_view name, SourceLocation const& loc) : Expr(kind, loc), name(name)
		{
			SetValueCategory(ExprValueCategory::LValue);
		}
		std::string_view GetName() const { return name; }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		std::string name;
	};

	class DeclRefExpr : public IdentifierExpr
	{
	public:
		DeclRefExpr(Decl* decl, SourceLocation const& loc) : IdentifierExpr(ExprKind::DeclRef, decl->GetName(), loc), decl(decl)
		{
			SetType(decl->GetType());
		}

		Decl const* GetDecl() const { return decl; }
		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

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

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		int64 value;
	};

	class ConstantString final : public Expr
	{
	public:
		ConstantString(std::string_view str, SourceLocation const& loc) : Expr(ExprKind::StringLiteral, loc), str(str) 
		{
			SetType(ArrayType(builtin_types::Char, (uint32)str.size()));
		}
		std::string_view GetString() const { return str; }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

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

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

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

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		double value;
	};

	class ImplicitCastExpr : public Expr
	{
	public:
		ImplicitCastExpr(SourceLocation const& loc, QualifiedType const& qtype) : Expr(ExprKind::ImplicitCast, loc), operand(nullptr)
		{
			SetType(qtype);
			SetValueCategory(ExprValueCategory::RValue);
		}

		void SetOperand(UniqueExprPtr&& _operand)
		{
			operand = std::move(_operand);
		}
		Expr const* GetOperand() const { return operand.get(); }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueExprPtr operand;
	};

	class FunctionCallExpr final : public Expr
	{
	public:
		FunctionCallExpr(SourceLocation const& loc, UniqueExprPtr&& func)
			: Expr(ExprKind::FunctionCall, loc), func_expr(std::move(func)) {}

		void SetArgs(UniqueExprPtrList&& args)
		{
			func_args = std::move(args);
		}
		Expr const* GetFunction() const { return func_expr.get(); }

		virtual void Accept(ASTVisitor& visitor, uint32 depth) const override;
		virtual void Accept(ASTVisitor& visitor) const override;

	private:
		UniqueExprPtr func_expr;
		UniqueExprPtrList func_args;
	};

	struct AST
	{
		AST() { translation_unit = std::make_unique<TranslationUnit>(); }
		std::unique_ptr<TranslationUnit> translation_unit;
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