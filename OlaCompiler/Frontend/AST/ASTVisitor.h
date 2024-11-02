#pragma once
#include "ASTFwd.h"

namespace ola
{
	class ASTVisitor
	{
	public:
		virtual ~ASTVisitor() = default;
		virtual void Visit(ASTNode const&, Uint32) {}

		virtual void Visit(TranslationUnit const&, Uint32) {}

		virtual void Visit(Decl const&, Uint32) {}
		virtual void Visit(FunctionDecl const&, Uint32) {}
		virtual void Visit(MethodDecl const&, Uint32) {}
		virtual void Visit(ConstructorDecl const&, Uint32) {}
		virtual void Visit(VarDecl const&, Uint32) {}
		virtual void Visit(ParamVarDecl const&, Uint32) {}
		virtual void Visit(FieldDecl const&, Uint32) {}
		virtual void Visit(TagDecl const&, Uint32) {}
		virtual void Visit(EnumDecl const&, Uint32) {}
		virtual void Visit(EnumMemberDecl const&, Uint32) {}
		virtual void Visit(AliasDecl const&, Uint32) {}
		virtual void Visit(ClassDecl const&, Uint32) {}

		virtual void Visit(Stmt const&, Uint32) {}
		virtual void Visit(CompoundStmt const&, Uint32) {}
		virtual void Visit(DeclStmt const&, Uint32) {}
		virtual void Visit(ExprStmt const&, Uint32) {}
		virtual void Visit(NullStmt const&, Uint32) {}
		virtual void Visit(ReturnStmt const&, Uint32) {}
		virtual void Visit(IfStmt const&, Uint32) {}
		virtual void Visit(BreakStmt const&, Uint32) {}
		virtual void Visit(ContinueStmt const&, Uint32) {}
		virtual void Visit(ForStmt const&, Uint32) {}
		virtual void Visit(WhileStmt const&, Uint32) {}
		virtual void Visit(DoWhileStmt const&, Uint32) {}
		virtual void Visit(CaseStmt const&, Uint32) {}
		virtual void Visit(SwitchStmt const&, Uint32) {}
		virtual void Visit(GotoStmt const&, Uint32) {}
		virtual void Visit(LabelStmt const&, Uint32) {}

		virtual void Visit(Expr const&, Uint32) {}
		virtual void Visit(UnaryExpr const&, Uint32) {}
		virtual void Visit(BinaryExpr const&, Uint32) {}
		virtual void Visit(TernaryExpr const&, Uint32) {}
		virtual void Visit(IdentifierExpr const&, Uint32) {}
		virtual void Visit(DeclRefExpr const&, Uint32) {}
		virtual void Visit(IntLiteral const&, Uint32) {}
		virtual void Visit(CharLiteral const&, Uint32) {}
		virtual void Visit(StringLiteral const&, Uint32) {}
		virtual void Visit(BoolLiteral const&, Uint32) {}
		virtual void Visit(FloatLiteral const&, Uint32) {}
		virtual void Visit(ImplicitCastExpr const&, Uint32) {}
		virtual void Visit(CallExpr const&, Uint32) {}
		virtual void Visit(InitializerListExpr const&, Uint32) {}
		virtual void Visit(ArrayAccessExpr const&, Uint32) {}
		virtual void Visit(MemberExpr const&, Uint32) {}
		virtual void Visit(MethodCallExpr const&, Uint32) {}
		virtual void Visit(ThisExpr const&, Uint32) {}
		virtual void Visit(SuperExpr const&, Uint32) {}
		virtual void Visit(ConstructorExpr const&, Uint32) {}
	};
}