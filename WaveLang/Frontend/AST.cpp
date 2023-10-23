#include "AST.h"

namespace wave
{
	class LabelVisitor : public ASTVisitor
	{
	public:
		explicit LabelVisitor(ConstLabelStmtPtrList& labels) : labels(labels) {}
		virtual void Visit(LabelStmt const& label, uint32) override
		{
			labels.push_back(&label);
		}

	private:
		ConstLabelStmtPtrList& labels;
	};

	ConstLabelStmtPtrList FunctionDecl::GetLabels() const
	{
		WAVE_ASSERT(body_stmt);
		if (!labels.empty()) return labels;

		LabelVisitor label_visitor(labels);
		body_stmt->Accept(label_visitor, 0);
		return labels;
	}



	void TranslationUnit::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& decl : declarations) decl->Accept(visitor, depth + 1);
	}

	void Decl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		WAVE_ASSERT(false);
	}
	void VariableDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (init_expr) init_expr->Accept(visitor, depth + 1);
	}
	void FunctionDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& param : param_declarations) param->Accept(visitor, depth + 1);
		if (body_stmt) body_stmt->Accept(visitor, depth + 1);
	}

	void Stmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		WAVE_ASSERT(false);
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
		for(auto const& decl : declarations) decl->Accept(visitor, depth + 1);
	}
	void ReturnStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (ret_expr) ret_expr->Accept(visitor, depth + 1);
	}
	void IfStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		WAVE_ASSERT(cond_expr && then_stmt);
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
		WAVE_ASSERT(body_stmt);
		visitor.Visit(*this, depth);
		if (init_stmt) init_stmt->Accept(visitor, depth + 1);
		if (cond_expr) cond_expr->Accept(visitor, depth + 1);
		if (iter_expr) iter_expr->Accept(visitor, depth + 1);
		body_stmt->Accept(visitor, depth + 1);
	}
	void WhileStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		WAVE_ASSERT(cond_expr && body_stmt);
		visitor.Visit(*this, depth);
		cond_expr->Accept(visitor, depth + 1);
		body_stmt->Accept(visitor, depth + 1);
	}
	void DoWhileStmt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		WAVE_ASSERT(cond_expr && body_stmt);
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
		WAVE_ASSERT(cond_expr && body_stmt);
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

	void Expr::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		WAVE_ASSERT(false);
	}
	void UnaryExpr::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		WAVE_ASSERT(operand);
		visitor.Visit(*this, depth);
		operand->Accept(visitor, depth + 1);
	}
	void BinaryExpr::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		WAVE_ASSERT(lhs && rhs);
		visitor.Visit(*this, depth);
		lhs->Accept(visitor, depth + 1);
		rhs->Accept(visitor, depth + 1);
	}
	void TernaryExpr::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		WAVE_ASSERT(cond_expr && true_expr && false_expr);
		visitor.Visit(*this, depth);
		cond_expr->Accept(visitor, depth + 1);
		true_expr->Accept(visitor, depth + 1);
		false_expr->Accept(visitor, depth + 1);
	}
	void IdentifierExpr::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		WAVE_ASSERT(false);
	}
	void DeclRefExpr::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void ConstantInt::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void ConstantString::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void ConstantBool::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void ConstantFloat::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void ImplicitCastExpr::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		WAVE_ASSERT(operand);
		visitor.Visit(*this, depth);
		operand->Accept(visitor, depth + 1);
	}
	void FunctionCallExpr::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto const& arg : func_args) arg->Accept(visitor, depth + 1);
	}

	void TranslationUnit::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void Decl::Accept(ASTVisitor& visitor) const
	{
		WAVE_ASSERT(false);
	}
	void VariableDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void FunctionDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}

	void Stmt::Accept(ASTVisitor& visitor) const
	{
		WAVE_ASSERT(false);
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
		WAVE_ASSERT(cond_expr && then_stmt);
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
		WAVE_ASSERT(body_stmt);
		visitor.Visit(*this, 0);
	}
	void WhileStmt::Accept(ASTVisitor& visitor) const
	{
		WAVE_ASSERT(cond_expr && body_stmt);
		visitor.Visit(*this, 0);
	}
	void DoWhileStmt::Accept(ASTVisitor& visitor) const
	{
		WAVE_ASSERT(cond_expr && body_stmt);
		visitor.Visit(*this, 0);
	}
	void CaseStmt::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void SwitchStmt::Accept(ASTVisitor& visitor) const
	{
		WAVE_ASSERT(cond_expr && body_stmt);
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

	void Expr::Accept(ASTVisitor& visitor) const
	{
		WAVE_ASSERT(false);
	}
	void UnaryExpr::Accept(ASTVisitor& visitor) const
	{
		WAVE_ASSERT(operand);
		visitor.Visit(*this, 0);
	}
	void BinaryExpr::Accept(ASTVisitor& visitor) const
	{
		WAVE_ASSERT(lhs && rhs);
		visitor.Visit(*this, 0);
	}
	void TernaryExpr::Accept(ASTVisitor& visitor) const
	{
		WAVE_ASSERT(cond_expr && true_expr && false_expr);
		visitor.Visit(*this, 0);
	}
	void IdentifierExpr::Accept(ASTVisitor& visitor) const
	{
		WAVE_ASSERT(false);
	}
	void DeclRefExpr::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ConstantInt::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ConstantString::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ConstantBool::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ConstantFloat::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ImplicitCastExpr::Accept(ASTVisitor& visitor) const
	{
		WAVE_ASSERT(operand);
		visitor.Visit(*this, 0);
	}
	void FunctionCallExpr::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
}

