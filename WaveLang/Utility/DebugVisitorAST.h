#pragma once
#include "Frontend/ASTVisitor.h"

namespace wave
{
	class DebugVisitorAST : public ASTVisitor
	{
	public:
		explicit DebugVisitorAST(AST const* ast);

		virtual void Visit(NodeAST const& node, uint32 depth) override;
		virtual void Visit(TranslationUnit const& node, uint32 depth) override;

		virtual void Visit(Decl const& node, uint32 depth) override;
		virtual void Visit(FunctionDecl const& node, uint32 depth) override;
		virtual void Visit(VariableDecl const& node, uint32 depth) override;

		virtual void Visit(Stmt const& node, uint32 depth) override;
		virtual void Visit(CompoundStmt const& node, uint32 depth) override;
		virtual void Visit(ExprStmt const& node, uint32 depth) override;
		virtual void Visit(DeclStmt const& node, uint32 depth) override;
		virtual void Visit(NullStmt const& node, uint32 depth) override;
		virtual void Visit(ReturnStmt const& node, uint32 depth) override;
		virtual void Visit(IfStmt const& node, uint32 depth) override;

		virtual void Visit(Expr const& node, uint32 depth) override;
		virtual void Visit(UnaryExpr const& node, uint32 depth) override;
		virtual void Visit(BinaryExpr const& node, uint32 depth) override;
		virtual void Visit(TernaryExpr const& node, uint32 depth) override;
		virtual void Visit(IntLiteral const& node, uint32 depth) override;
		virtual void Visit(StringLiteral const& node, uint32 depth) override;
		virtual void Visit(Identifier const& node, uint32 depth) override;
	};
}