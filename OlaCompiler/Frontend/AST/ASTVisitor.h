#pragma once
#include "ASTFwd.h"

namespace ola
{
	class ASTVisitor
	{
	public:
		virtual ~ASTVisitor() = default;
		virtual void Visit(ASTNode const&, uint32) {}

		virtual void Visit(TranslationUnit const&, uint32) {}

		virtual void Visit(Decl const&, uint32) {}
		virtual void Visit(FunctionDecl const&, uint32) {}
		virtual void Visit(MethodDecl const&, uint32) {}
		virtual void Visit(VarDecl const&, uint32) {}
		virtual void Visit(ParamVarDecl const&, uint32) {}
		virtual void Visit(FieldDecl const&, uint32) {}
		virtual void Visit(TagDecl const&, uint32) {}
		virtual void Visit(EnumDecl const&, uint32) {}
		virtual void Visit(EnumMemberDecl const&, uint32) {}
		virtual void Visit(AliasDecl const&, uint32) {}
		virtual void Visit(ClassDecl const&, uint32) {}

		virtual void Visit(Stmt const&, uint32) {}
		virtual void Visit(CompoundStmt const&, uint32) {}
		virtual void Visit(DeclStmt const&, uint32) {}
		virtual void Visit(ExprStmt const&, uint32) {}
		virtual void Visit(NullStmt const&, uint32) {}
		virtual void Visit(ReturnStmt const&, uint32) {}
		virtual void Visit(IfStmt const&, uint32) {}
		virtual void Visit(BreakStmt const&, uint32) {}
		virtual void Visit(ContinueStmt const&, uint32) {}
		virtual void Visit(ForStmt const&, uint32) {}
		virtual void Visit(WhileStmt const&, uint32) {}
		virtual void Visit(DoWhileStmt const&, uint32) {}
		virtual void Visit(CaseStmt const&, uint32) {}
		virtual void Visit(SwitchStmt const&, uint32) {}
		virtual void Visit(GotoStmt const&, uint32) {}
		virtual void Visit(LabelStmt const&, uint32) {}

		virtual void Visit(Expr const&, uint32) {}
		virtual void Visit(UnaryExpr const&, uint32) {}
		virtual void Visit(BinaryExpr const&, uint32) {}
		virtual void Visit(TernaryExpr const&, uint32) {}
		virtual void Visit(IdentifierExpr const&, uint32) {}
		virtual void Visit(DeclRefExpr const&, uint32) {}
		virtual void Visit(IntLiteral const&, uint32) {}
		virtual void Visit(CharLiteral const&, uint32) {}
		virtual void Visit(StringLiteral const&, uint32) {}
		virtual void Visit(BoolLiteral const&, uint32) {}
		virtual void Visit(FloatLiteral const&, uint32) {}
		virtual void Visit(ImplicitCastExpr const&, uint32) {}
		virtual void Visit(CallExpr const&, uint32) {}
		virtual void Visit(InitializerListExpr const&, uint32) {}
		virtual void Visit(ArrayAccessExpr const&, uint32) {}
		virtual void Visit(MemberExpr const&, uint32) {}
		virtual void Visit(MethodCallExpr const&, uint32) {}
		virtual void Visit(ThisExpr const&, uint32) {}
		virtual void Visit(SuperExpr const&, uint32) {}
	};
}