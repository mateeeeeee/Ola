#pragma once
#include "Frontend/AST.h"

namespace wave
{
	class DebugNodeVisitorAST : public IVisitorAST
	{
	public:

		explicit DebugNodeVisitorAST(AST* ast);

		virtual void Visit(NodeAST const& node, uint32 depth) override;
		virtual void Visit(TranslationUnitAST const& node, uint32 depth) override;

		virtual void Visit(DeclAST const& node, uint32 depth) override;
		virtual void Visit(FunctionDeclAST const& node, uint32 depth) override;
		virtual void Visit(VariableDeclAST const& node, uint32 depth) override;

		virtual void Visit(StmtAST const& node, uint32 depth) override;
		virtual void Visit(CompoundStmtAST const& node, uint32 depth) override;
		virtual void Visit(ExprStmtAST const& node, uint32 depth) override;
		virtual void Visit(DeclStmtAST const& node, uint32 depth) override;
		virtual void Visit(NullStmtAST const& node, uint32 depth) override;
		virtual void Visit(ReturnStmtAST const& node, uint32 depth) override;
		virtual void Visit(IfStmtAST const& node, uint32 depth) override;

		virtual void Visit(ExprAST const& node, uint32 depth) override;
		virtual void Visit(UnaryExprAST const& node, uint32 depth) override;
		virtual void Visit(BinaryExprAST const& node, uint32 depth) override;
		virtual void Visit(TernaryExprAST const& node, uint32 depth) override;
		virtual void Visit(IntLiteralAST const& node, uint32 depth) override;
		virtual void Visit(StringLiteralAST const& node, uint32 depth) override;
		virtual void Visit(IdentifierAST const& node, uint32 depth) override;
	};
}