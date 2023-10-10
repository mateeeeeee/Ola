#pragma once
#include "ASTForwardDeclarations.h"

namespace wave
{
	class ASTVisitor
	{
	public:
		virtual ~ASTVisitor() = default;
		virtual void Visit(NodeAST const& node, uint32 depth) {}
		virtual void Visit(TranslationUnit const& node, uint32 depth) {}

		virtual void Visit(Decl const& node, uint32 depth) {}
		virtual void Visit(FunctionDecl const& node, uint32 depth) {}
		virtual void Visit(VariableDecl const& node, uint32 depth) {}

		virtual void Visit(Stmt const& node, uint32 depth) {}
		virtual void Visit(CompoundStmt const& node, uint32 depth) {}
		virtual void Visit(ExprStmt const& node, uint32 depth) {}
		virtual void Visit(DeclStmt const& node, uint32 depth) {}
		virtual void Visit(NullStmt const& node, uint32 depth) {}
		virtual void Visit(ReturnStmt const& node, uint32 depth) {}
		virtual void Visit(IfStmt const& node, uint32 depth) {}

		virtual void Visit(Expr const& node, uint32 depth) {}
		virtual void Visit(UnaryExpr const& node, uint32 depth) {}
		virtual void Visit(BinaryExpr const& node, uint32 depth) {}
		virtual void Visit(TernaryExpr const& node, uint32 depth) {}
		virtual void Visit(IntLiteral const& node, uint32 depth) {}
		virtual void Visit(StringLiteral const& node, uint32 depth) {}
		virtual void Visit(IdentifierExpr const& node, uint32 depth) {}
		virtual void Visit(DeclRefExpr const& node, uint32 depth) {}
	};
}