#include "Stmt.h"
#include "ASTVisitor.h"
#include "Decl.h"
#include "Expr.h"

namespace ola
{
	void Stmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		OLA_ASSERT(false);
	}
	void CompoundStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& stmt : statements) stmt->Accept(visitor, depth + 1);
	}
	void ExprStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (expr) expr->Accept(visitor, depth + 1);
	}
	void NullStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void DeclStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto const& decl : declarations) decl->Accept(visitor, depth + 1);
	}
	void ReturnStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (ret_expr) ret_expr->Accept(visitor, depth + 1);
	}
	void IfStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		OLA_ASSERT(cond_expr && then_stmt);
		visitor.Visit(*this, depth);
		cond_expr->Accept(visitor, depth + 1);
		then_stmt->Accept(visitor, depth + 1);
		if (else_stmt) else_stmt->Accept(visitor, depth + 1);
	}
	void BreakStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void ContinueStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void ForStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		OLA_ASSERT(body_stmt);
		visitor.Visit(*this, depth);
		if (init_stmt) init_stmt->Accept(visitor, depth + 1);
		if (cond_expr) cond_expr->Accept(visitor, depth + 1);
		if (iter_expr) iter_expr->Accept(visitor, depth + 1);
		body_stmt->Accept(visitor, depth + 1);
	}
	void WhileStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		OLA_ASSERT(cond_expr && body_stmt);
		visitor.Visit(*this, depth);
		cond_expr->Accept(visitor, depth + 1);
		body_stmt->Accept(visitor, depth + 1);
	}
	void DoWhileStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		OLA_ASSERT(cond_expr && body_stmt);
		visitor.Visit(*this, depth);
		cond_expr->Accept(visitor, depth + 1);
		body_stmt->Accept(visitor, depth + 1);
	}
	void CaseStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void SwitchStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		OLA_ASSERT(cond_expr && body_stmt);
		visitor.Visit(*this, depth);
		cond_expr->Accept(visitor, depth + 1);
		body_stmt->Accept(visitor, depth + 1);
	}
	void LabelStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void GotoStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}

	void Stmt::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(false);
	}
	void CompoundStmt::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ExprStmt::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void NullStmt::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void DeclStmt::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ReturnStmt::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void IfStmt::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(cond_expr && then_stmt);
		visitor.Visit(*this, 0);
	}
	void BreakStmt::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ContinueStmt::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ForStmt::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(body_stmt);
		visitor.Visit(*this, 0);
	}
	void WhileStmt::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(cond_expr && body_stmt);
		visitor.Visit(*this, 0);
	}
	void DoWhileStmt::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(cond_expr && body_stmt);
		visitor.Visit(*this, 0);
	}
	void CaseStmt::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void SwitchStmt::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(cond_expr && body_stmt);
		visitor.Visit(*this, 0);
	}
	void LabelStmt::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void GotoStmt::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
}