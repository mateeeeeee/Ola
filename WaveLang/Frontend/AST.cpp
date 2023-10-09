#include "AST.h"

namespace wave
{
	void TranslationUnitAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& decl : declarations) decl->Accept(visitor, depth + 1);
	}
	void DeclAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(false);
	}
	void VariableDeclAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (init_expr) init_expr->Accept(visitor, depth + 1);
	}
	void FunctionDeclAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& param : param_declarations) param->Accept(visitor, depth + 1);
		if (definition) definition->Accept(visitor, depth + 1);
	}

	void StmtAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(false);
	}
	void CompoundStmtAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& stmt : statements) stmt->Accept(visitor, depth + 1);
	}
	void ExprStmtAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (expr) expr->Accept(visitor, depth + 1);
	}
	void NullStmtAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void DeclStmtAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (declaration) declaration->Accept(visitor, depth + 1);
	}
	void ReturnStmtAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (ret_expr) ret_expr->Accept(visitor, depth + 1);
	}
	void IfStmtAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(condition && then_stmt);
		visitor.Visit(*this, depth);
		condition->Accept(visitor, depth + 1);
		then_stmt->Accept(visitor, depth + 1);
		if (else_stmt) else_stmt->Accept(visitor, depth + 1);
	}

	void ExprAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(false);
	}
	void UnaryExprAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(operand);
		visitor.Visit(*this, depth);
		operand->Accept(visitor, depth + 1);
	}
	void BinaryExprAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(lhs && rhs);
		visitor.Visit(*this, depth);
		lhs->Accept(visitor, depth + 1);
		rhs->Accept(visitor, depth + 1);
	}
	void TernaryExprAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(cond_expr && true_expr && false_expr);
		visitor.Visit(*this, depth);
		cond_expr->Accept(visitor, depth + 1);
		true_expr->Accept(visitor, depth + 1);
		false_expr->Accept(visitor, depth + 1);
	}
	void IntLiteralAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void StringLiteralAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void CastExprAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(operand);
		visitor.Visit(*this, depth);
		operand->Accept(visitor, depth + 1);
	}
	void FunctionCallExprAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(func_expr);
		visitor.Visit(*this, depth);
		func_expr->Accept(visitor, depth + 1);
		for (auto const& arg : func_args) arg->Accept(visitor, depth + 1);
	}
	void IdentifierAST::Accept(IVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}

	void TranslationUnitAST::Accept(IVisitorAST& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void DeclAST::Accept(IVisitorAST& visitor) const
	{
		WAVE_ASSERT(false);
	}
	void VariableDeclAST::Accept(IVisitorAST& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void FunctionDeclAST::Accept(IVisitorAST& visitor) const
	{
		visitor.Visit(*this, 0);
	}

	void StmtAST::Accept(IVisitorAST& visitor) const
	{
		WAVE_ASSERT(false);
	}
	void CompoundStmtAST::Accept(IVisitorAST& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ExprStmtAST::Accept(IVisitorAST& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void NullStmtAST::Accept(IVisitorAST& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void DeclStmtAST::Accept(IVisitorAST& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ReturnStmtAST::Accept(IVisitorAST& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void IfStmtAST::Accept(IVisitorAST& visitor) const
	{
		WAVE_ASSERT(condition && then_stmt);
		visitor.Visit(*this, 0);
	}

	void ExprAST::Accept(IVisitorAST& visitor) const
	{
		WAVE_ASSERT(false);
	}
	void UnaryExprAST::Accept(IVisitorAST& visitor) const
	{
		WAVE_ASSERT(operand);
		visitor.Visit(*this, 0);
	}
	void BinaryExprAST::Accept(IVisitorAST& visitor) const
	{
		WAVE_ASSERT(lhs && rhs);
		visitor.Visit(*this, 0);
	}
	void TernaryExprAST::Accept(IVisitorAST& visitor) const
	{
		WAVE_ASSERT(cond_expr && true_expr && false_expr);
		visitor.Visit(*this, 0);
	}
	void IntLiteralAST::Accept(IVisitorAST& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void StringLiteralAST::Accept(IVisitorAST& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void CastExprAST::Accept(IVisitorAST& visitor) const
	{
		WAVE_ASSERT(operand);
		visitor.Visit(*this, 0);
	}
	void FunctionCallExprAST::Accept(IVisitorAST& visitor) const
	{
		WAVE_ASSERT(func_expr);
		visitor.Visit(*this, 0);
	}
	void IdentifierAST::Accept(IVisitorAST& visitor) const
	{
		visitor.Visit(*this, 0);
	}

}

