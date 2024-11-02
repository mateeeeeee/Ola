#include "Expr.h"
#include "ASTVisitor.h"
#include "Decl.h"

namespace ola
{
	DeclRefExpr::DeclRefExpr(Decl const* decl, SourceLocation const& loc) : IdentifierExpr(ExprKind::DeclRef, decl->GetName(), loc), decl(decl)
	{
		SetType(decl->GetType());
	}
	bool DeclRefExpr::IsConstexpr() const
	{
		return isa<EnumMemberDecl>(decl);
	}
	Sint64 DeclRefExpr::EvaluateConstexpr() const
	{
		EnumMemberDecl const* enum_member_decl = static_cast<EnumMemberDecl const*>(decl);
		return enum_member_decl->GetValue();
	}
	MethodCallExpr::MethodCallExpr(SourceLocation const& loc, MethodDecl const* method_decl) 
		: CallExpr(ExprKind::MethodCall, loc, method_decl) {}

	void Expr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		OLA_ASSERT(false);
	}
	void UnaryExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		OLA_ASSERT(operand);
		visitor.Visit(*this, depth);
		operand->Accept(visitor, depth + 1);
	}
	void BinaryExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		OLA_ASSERT(lhs && rhs);
		visitor.Visit(*this, depth);
		lhs->Accept(visitor, depth + 1);
		rhs->Accept(visitor, depth + 1);
	}
	void TernaryExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		OLA_ASSERT(cond_expr && true_expr && false_expr);
		visitor.Visit(*this, depth);
		cond_expr->Accept(visitor, depth + 1);
		true_expr->Accept(visitor, depth + 1);
		false_expr->Accept(visitor, depth + 1);
	}
	void IdentifierExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void DeclRefExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void IntLiteral::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void CharLiteral::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void StringLiteral::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void BoolLiteral::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void FloatLiteral::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void ImplicitCastExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		OLA_ASSERT(operand);
		visitor.Visit(*this, depth);
		operand->Accept(visitor, depth + 1);
	}
	void CallExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
		callee->Accept(visitor, depth + 1);
		for (auto const& arg : func_args) arg->Accept(visitor, depth + 1);
	}
	void InitializerListExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto const& init_elem : init_list) init_elem->Accept(visitor, depth + 1);
	}
	void ArrayAccessExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		OLA_ASSERT(array_expr && bracket_expr);
		visitor.Visit(*this, depth);
		array_expr->Accept(visitor, depth + 1);
		bracket_expr->Accept(visitor, depth + 1);
	}
	void MemberExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		OLA_ASSERT(class_expr && decl);
		visitor.Visit(*this, depth);
		class_expr->Accept(visitor, depth + 1);
	}
	void MethodCallExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
		callee->Accept(visitor, depth + 1);
		for (auto const& arg : func_args) arg->Accept(visitor, depth + 1);
	}
	void ThisExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void SuperExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void ConstructorExpr::Accept(ASTVisitor& visitor, Uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto const& arg : ctor_args) arg->Accept(visitor, depth + 1);
	}

	void Expr::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(false);
	}
	void UnaryExpr::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(operand);
		visitor.Visit(*this, 0);
	}
	void BinaryExpr::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(lhs && rhs);
		visitor.Visit(*this, 0);
	}
	void TernaryExpr::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(cond_expr && true_expr && false_expr);
		visitor.Visit(*this, 0);
	}
	void IdentifierExpr::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void DeclRefExpr::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}

	void IntLiteral::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void CharLiteral::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void StringLiteral::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void BoolLiteral::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void FloatLiteral::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ImplicitCastExpr::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(operand);
		visitor.Visit(*this, 0);
	}
	void CallExpr::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void InitializerListExpr::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ArrayAccessExpr::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void MemberExpr::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void MethodCallExpr::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ThisExpr::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void SuperExpr::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ConstructorExpr::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}

}