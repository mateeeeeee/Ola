#pragma once
#include "Frontend/ASTVisitor.h"

namespace wave
{
	class DebugVisitor : public ASTVisitor
	{
	public:
		explicit DebugVisitor(AST const* ast);

		virtual void Visit(NodeAST const&, uint32 depth) override;
		virtual void Visit(TranslationUnit const&, uint32 depth) override;

		virtual void Visit(Decl const&, uint32 depth) override;
		virtual void Visit(FunctionDecl const&, uint32 depth) override;
		virtual void Visit(VariableDecl const&, uint32 depth) override;

		virtual void Visit(Stmt const&, uint32 depth) override;
		virtual void Visit(CompoundStmt const&, uint32 depth) override;
		virtual void Visit(DeclStmt const&, uint32 depth) override;
		virtual void Visit(ExprStmt const&, uint32 depth) override;
		virtual void Visit(NullStmt const&, uint32 depth) override;
		virtual void Visit(ReturnStmt const&, uint32 depth) override;
		virtual void Visit(IfStmt const&, uint32 depth) override;

		virtual void Visit(Expr const&, uint32 depth) override;
		virtual void Visit(UnaryExpr const&, uint32 depth) override;
		virtual void Visit(BinaryExpr const&, uint32 depth) override;
		virtual void Visit(TernaryExpr const&, uint32 depth) override;
		virtual void Visit(IdentifierExpr const&, uint32 depth) override;
		virtual void Visit(DeclRefExpr const&, uint32 depth) override;
		virtual void Visit(ConstantInt const&, uint32 depth) override;
		virtual void Visit(ConstantString const&, uint32 depth) override;
		virtual void Visit(ConstantBool const&, uint32 depth) override;
		virtual void Visit(CastExpr const&, uint32 depth) override;
		virtual void Visit(FunctionCallExpr const&, uint32 depth) override;
	};
}