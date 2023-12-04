#pragma once
#include "ASTNode.h"
#include "ASTTypeAliases.h"
#include "Expr.h"
#include "Type.h"
#include "Frontend/SourceLocation.h"

namespace ola
{
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

	class Stmt : public ASTNode
	{
	public:
		StmtKind GetStmtKind() const { return kind; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

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

		void AddBeginStmt(UniqueStmtPtr&& stmt)
		{
			statements.insert(std::begin(statements), std::move(stmt));
		}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::Compound; }
	private:
		UniqueStmtPtrList statements;
	};

	class DeclStmt final : public Stmt
	{
	public:
		DeclStmt(UniqueDeclPtr&& decl) : Stmt(StmtKind::Decl), declarations{}
		{
			declarations.push_back(std::move(decl));
		}
		DeclStmt(UniqueDeclPtrList&& decls) : Stmt(StmtKind::Decl), declarations(std::move(decls)) {}

		UniqueDeclPtrList const& GetDecls() const { return declarations; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::Decl; }

	private:
		UniqueDeclPtrList declarations;
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

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::Expr; }
	private:
		UniqueExprPtr expr;
	};

	class NullStmt final : public ExprStmt
	{
	public:
		NullStmt() : ExprStmt(nullptr) {}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::Null; }
	};

	class ReturnStmt final : public Stmt
	{
	public:
		explicit ReturnStmt(std::unique_ptr<ExprStmt>&& ret_expr)
			: Stmt(StmtKind::Return), ret_expr(std::move(ret_expr)) {}

		ExprStmt const* GetExprStmt() const { return ret_expr.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::Return; }
	private:
		UniqueExprStmtPtr ret_expr;
	};

	class IfStmt final : public Stmt
	{
	public:
		IfStmt() : Stmt(StmtKind::If) {}

		void SetConditionExpr(UniqueExprPtr&& _condition)
		{
			cond_expr = std::move(_condition);
		}
		void SetThenStmt(UniqueStmtPtr&& _then_stmt)
		{
			then_stmt = std::move(_then_stmt);
		}
		void SetElseStmt(UniqueStmtPtr&& _else_stmt)
		{
			else_stmt = std::move(_else_stmt);
		}

		Expr const* GetCondExpr() const { return cond_expr.get(); }
		Stmt const* GetThenStmt() const { return then_stmt.get(); }
		Stmt const* GetElseStmt() const { return else_stmt.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::If; }
	private:
		UniqueExprPtr cond_expr;
		UniqueStmtPtr then_stmt;
		UniqueStmtPtr else_stmt;
	};

	class BreakStmt final : public Stmt
	{
	public:
		BreakStmt() : Stmt(StmtKind::Break) {}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::Break; }
	};

	class ContinueStmt final : public Stmt
	{
	public:
		ContinueStmt() : Stmt(StmtKind::Continue) {}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::Continue; }
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

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::For; }
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

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::While; }
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

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::DoWhile; }
	private:
		UniqueExprPtr cond_expr;
		UniqueStmtPtr body_stmt;
	};

	class CaseStmt final : public Stmt
	{
	public:
		CaseStmt() : Stmt(StmtKind::Case), is_default(true), value(0) {}
		explicit CaseStmt(int64 value) : Stmt(StmtKind::Case), is_default(false), value(value) {}

		bool IsDefault() const { return is_default; }
		int64 GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::Case; }
	private:
		int64 value;
		bool is_default;
	};

	class SwitchStmt final : public Stmt
	{
	public:
		SwitchStmt() : Stmt(StmtKind::Switch) {}

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

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::Switch; }
	private:
		UniqueExprPtr cond_expr;
		UniqueStmtPtr body_stmt;
	};

	class LabelStmt final : public Stmt
	{
	public:
		LabelStmt(std::string_view label) : Stmt(StmtKind::Label), label_name(label) {}
		std::string_view GetName() const { return label_name; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::Label; }
	private:
		std::string label_name;
	};

	class GotoStmt final : public Stmt
	{
	public:
		explicit GotoStmt(std::string_view label) : Stmt(StmtKind::Label), label_name(label) {}
		std::string_view GetLabelName() const { return label_name; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		static bool ClassOf(Stmt const* stmt) { return stmt->GetStmtKind() == StmtKind::Goto; }
	private:
		std::string label_name;
	};

	template <typename T> requires std::derived_from<T, Stmt>
	inline bool isa(Stmt const* stmt) { return T::ClassOf(stmt); }

	template<typename T> requires std::derived_from<T, Stmt>
	inline T* cast(Stmt* stmt)
	{
		return static_cast<T*>(stmt);
	}
	template<typename T> requires std::derived_from<T, Stmt>
	inline T const* cast(Stmt const* stmt)
	{
		return static_cast<T const*>(stmt);
	}

	template<typename T> requires std::derived_from<T, Stmt>
	inline T* dyn_cast(Stmt* stmt)
	{
		return isa<T>(stmt) ? static_cast<T*>(stmt) : nullptr;
	}
	template<typename T> requires std::derived_from<T, Stmt>
	inline T const* dyn_cast(Stmt const* stmt)
	{
		return isa<T>(stmt) ? static_cast<T const*>(stmt) : nullptr;
	}
}