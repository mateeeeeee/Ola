#pragma once
#include "ForwardAST.h"

namespace wave
{
	class IVisitorAST
	{
	public:
		virtual ~IVisitorAST() = default;
		virtual void Visit(NodeAST const& node, uint32 depth) {}
		virtual void Visit(TranslationUnitAST const& node, uint32 depth) {}

		virtual void Visit(DeclAST const& node, uint32 depth) {}
		virtual void Visit(FunctionDeclAST const& node, uint32 depth) {}
		virtual void Visit(VariableDeclAST const& node, uint32 depth) {}

		virtual void Visit(StmtAST const& node, uint32 depth) {}
		virtual void Visit(CompoundStmtAST const& node, uint32 depth) {}
		virtual void Visit(ExprStmtAST const& node, uint32 depth) {}
		virtual void Visit(DeclStmtAST const& node, uint32 depth) {}
		virtual void Visit(NullStmtAST const& node, uint32 depth) {}
		virtual void Visit(ReturnStmtAST const& node, uint32 depth) {}
		virtual void Visit(IfStmtAST const& node, uint32 depth) {}

		virtual void Visit(ExprAST const& node, uint32 depth) {}
		virtual void Visit(UnaryExprAST const& node, uint32 depth) {}
		virtual void Visit(BinaryExprAST const& node, uint32 depth) {}
		virtual void Visit(TernaryExprAST const& node, uint32 depth) {}
		virtual void Visit(IntLiteralAST const& node, uint32 depth) {}
		virtual void Visit(StringLiteralAST const& node, uint32 depth) {}
		virtual void Visit(IdentifierAST const& node, uint32 depth) {}
	};
}