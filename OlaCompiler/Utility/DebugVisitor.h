#pragma once
#include "Frontend/AST/ASTVisitor.h"

namespace ola
{
	class DebugVisitor : public ASTVisitor
	{
	public:
		explicit DebugVisitor(AST const* ast);

		virtual void Visit(ASTNode const&, uint32) override;
		virtual void Visit(TranslationUnit const&, uint32) override;

		virtual void Visit(Decl const&, uint32) override;
		virtual void Visit(FunctionDecl const&, uint32) override;
		virtual void Visit(MethodDecl const&, uint32) override;
		virtual void Visit(VarDecl const&, uint32) override;
		virtual void Visit(ParamVarDecl const&, uint32) override;
		virtual void Visit(FieldDecl const&, uint32) override;
		virtual void Visit(TagDecl const&, uint32) override;
		virtual void Visit(EnumDecl const&, uint32) override;
		virtual void Visit(EnumMemberDecl const&, uint32) override;
		virtual void Visit(AliasDecl const&, uint32) override;
		virtual void Visit(ClassDecl const&, uint32) override;

		virtual void Visit(Stmt const&, uint32) override;
		virtual void Visit(CompoundStmt const&, uint32) override;
		virtual void Visit(DeclStmt const&, uint32) override;
		virtual void Visit(ExprStmt const&, uint32) override;
		virtual void Visit(NullStmt const&, uint32) override;
		virtual void Visit(ReturnStmt const&, uint32) override;
		virtual void Visit(IfStmt const&, uint32) override;
		virtual void Visit(BreakStmt const&, uint32) override;
		virtual void Visit(ContinueStmt const&, uint32) override;
		virtual void Visit(ForStmt const&, uint32) override;
		virtual void Visit(WhileStmt const&, uint32) override;
		virtual void Visit(DoWhileStmt const&, uint32) override;
		virtual void Visit(CaseStmt const&, uint32) override;
		virtual void Visit(SwitchStmt const&, uint32) override;
		virtual void Visit(GotoStmt const&, uint32) override;
		virtual void Visit(LabelStmt const&, uint32) override;

		virtual void Visit(Expr const&, uint32) override;
		virtual void Visit(UnaryExpr const&, uint32) override;
		virtual void Visit(BinaryExpr const&, uint32) override;
		virtual void Visit(TernaryExpr const&, uint32) override;
		virtual void Visit(IdentifierExpr const&, uint32) override;
		virtual void Visit(DeclRefExpr const&, uint32) override;
		virtual void Visit(ConstantInt const&, uint32) override;
		virtual void Visit(ConstantChar const&, uint32) override;
		virtual void Visit(ConstantString const&, uint32) override;
		virtual void Visit(ConstantBool const&, uint32) override;
		virtual void Visit(ConstantFloat const&, uint32) override;
		virtual void Visit(ImplicitCastExpr const&, uint32) override;
		virtual void Visit(CallExpr const&, uint32) override;
		virtual void Visit(InitializerListExpr const&, uint32) override;
		virtual void Visit(ArrayAccessExpr const&, uint32) override;
		virtual void Visit(MemberExpr const&, uint32) override;
		virtual void Visit(MemberCallExpr const&, uint32) override;
		virtual void Visit(ThisExpr const&, uint32) override;
	};
}