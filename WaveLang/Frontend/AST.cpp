#include "AST.h"

namespace wave
{
	void TranslationUnitAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& decl : declarations) decl->Accept(visitor, depth + 1);
	}

	void DeclAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(false);
	}
	void VariableDeclAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (init_expr) init_expr->Accept(visitor, depth + 1);
	}
	void FunctionDeclAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& param : param_declarations) param->Accept(visitor, depth + 1);
		if (definition) definition->Accept(visitor, depth + 1);
	}

	void StmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(false);
	}
	void CompoundStmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& stmt : statements) stmt->Accept(visitor, depth + 1);
	}
	void ExprStmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (expr) expr->Accept(visitor, depth + 1);
	}
	void NullStmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void DeclStmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (declaration) declaration->Accept(visitor, depth + 1);
	}
	void ReturnStmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (ret_expr) ret_expr->Accept(visitor, depth + 1);
	}
	void IfStmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(condition && then_stmt);
		visitor.Visit(*this, depth);
		condition->Accept(visitor, depth + 1);
		then_stmt->Accept(visitor, depth + 1);
		if (else_stmt) else_stmt->Accept(visitor, depth + 1);
	}

	void ExprAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(false);
	}
	void UnaryExprAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(operand);
		visitor.Visit(*this, depth);
		operand->Accept(visitor, depth + 1);
	}
	void BinaryExprAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(lhs && rhs);
		visitor.Visit(*this, depth);
		lhs->Accept(visitor, depth + 1);
		rhs->Accept(visitor, depth + 1);
	}
	void TernaryExprAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(cond_expr && true_expr && false_expr);
		visitor.Visit(*this, depth);
		cond_expr->Accept(visitor, depth + 1);
		true_expr->Accept(visitor, depth + 1);
		false_expr->Accept(visitor, depth + 1);
	}
	void IntLiteralAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void StringLiteralAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void CastExprAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(operand);
		visitor.Visit(*this, depth);
		operand->Accept(visitor, depth + 1);
	}
	void FunctionCallExprAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(func_expr);
		visitor.Visit(*this, depth);
		func_expr->Accept(visitor, depth + 1);
		for (auto const& arg : func_args) arg->Accept(visitor, depth + 1);
	}
	void IdentifierAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}

}

