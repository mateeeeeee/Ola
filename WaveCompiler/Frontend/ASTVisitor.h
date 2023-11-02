#pragma once
#include "ASTForwardDeclarations.h"

namespace wave
{
	class ASTVisitor
	{
	public:
		virtual ~ASTVisitor() = default;
		virtual void Visit(NodeAST const&, uint32) {}

		virtual void Visit(TranslationUnit const&, uint32) {}

		virtual void Visit(Decl const&, uint32) {}
		virtual void Visit(FunctionDecl const&, uint32) {}
		virtual void Visit(VariableDecl const&, uint32) {}
		virtual void Visit(TagDecl const&, uint32) {}
		virtual void Visit(EnumDecl const&, uint32) {}
		virtual void Visit(EnumMemberDecl const&, uint32) {}
		virtual void Visit(AliasDecl const&, uint32) {}

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
		virtual void Visit(ConstantInt const&, uint32) {}
		virtual void Visit(ConstantString const&, uint32) {}
		virtual void Visit(ConstantBool const&, uint32) {}
		virtual void Visit(ConstantFloat const&, uint32) {}
		virtual void Visit(ImplicitCastExpr const&, uint32) {}
		virtual void Visit(FunctionCallExpr const&, uint32) {}
		virtual void Visit(InitializerListExpr const&, uint32) {}
		virtual void Visit(ArrayAccessExpr const&, uint32) {}
	};
}