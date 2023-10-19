#pragma once
#include "ASTForwardDeclarations.h"

namespace wave
{
	class ASTVisitor
	{
	public:
		virtual ~ASTVisitor() = default;
		virtual void Visit(NodeAST const&, uint32 depth) {}

		virtual void Visit(TranslationUnit const&, uint32 depth) {}

		virtual void Visit(Decl const&, uint32 depth) {}
		virtual void Visit(FunctionDecl const&, uint32 depth) {}
		virtual void Visit(VariableDecl const&, uint32 depth) {}

		virtual void Visit(Stmt const&, uint32 depth) {}
		virtual void Visit(CompoundStmt const&, uint32 depth) {}
		virtual void Visit(DeclStmt const&, uint32 depth) {}
		virtual void Visit(ExprStmt const&, uint32 depth) {}
		virtual void Visit(NullStmt const&, uint32 depth) {}
		virtual void Visit(ReturnStmt const&, uint32 depth) {}
		virtual void Visit(IfStmt const&, uint32 depth) {}

		virtual void Visit(Expr const&, uint32 depth) {}
		virtual void Visit(UnaryExpr const&, uint32 depth) {}
		virtual void Visit(BinaryExpr const&, uint32 depth) {}
		virtual void Visit(TernaryExpr const&, uint32 depth) {}
		virtual void Visit(IdentifierExpr const&, uint32 depth) {}
		virtual void Visit(DeclRefExpr const&, uint32 depth) {}
		virtual void Visit(ConstantInt const&, uint32 depth) {}
		virtual void Visit(ConstantString const&, uint32 depth) {}
		virtual void Visit(ConstantBool const&, uint32 depth) {}
		virtual void Visit(ConstantFloat const&, uint32 depth) {}
		virtual void Visit(ImplicitCastExpr const&, uint32 depth) {}
		virtual void Visit(FunctionCallExpr const&, uint32 depth) {}

	};
}