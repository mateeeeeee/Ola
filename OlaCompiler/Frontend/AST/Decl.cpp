#include "Decl.h"
#include "ASTVisitor.h"
#include "Expr.h"

namespace ola
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
		OLA_ASSERT(body_stmt);
		if (!labels.empty()) return labels;

		LabelVisitor label_visitor(labels);
		body_stmt->Accept(label_visitor, 0);
		return labels;
	}

	void Decl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		OLA_ASSERT(false);
	}
	void VarDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		if (init_expr) init_expr->Accept(visitor, depth + 1);
	}
	void ParamVarDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void FieldDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void FunctionDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& param : param_declarations) param->Accept(visitor, depth + 1);
		if (body_stmt) body_stmt->Accept(visitor, depth + 1);
	}
	void MethodDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& param : param_declarations) param->Accept(visitor, depth + 1);
		if (body_stmt) body_stmt->Accept(visitor, depth + 1);
	}
	void EnumMemberDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void EnumDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& enum_member : enum_members) enum_member->Accept(visitor, depth + 1);
	}
	void AliasDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
	}
	void ClassDecl::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto const& member_variable : member_variables) member_variable->Accept(visitor, depth + 1);
		for (auto const& member_function : member_functions) member_function->Accept(visitor, depth + 1);
	}

	void Decl::Accept(ASTVisitor& visitor) const
	{
		OLA_ASSERT(false);
	}
	void VarDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ParamVarDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void FieldDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void FunctionDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}

	void MethodDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void EnumMemberDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void EnumDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void AliasDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
	void ClassDecl::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}

}

