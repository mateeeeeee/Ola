#include "LLVMVisitor.h"
#include "Frontend/AST.h"

namespace wave
{

	LLVMVisitor::LLVMVisitor(AST const* ast)
	{
		ast->translation_unit->Accept(*this);
	}

	void LLVMVisitor::Visit(NodeAST const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(TranslationUnit const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(Decl const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(FunctionDecl const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(VariableDecl const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(Stmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(CompoundStmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(ExprStmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(DeclStmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(NullStmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(ReturnStmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(IfStmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(Expr const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(UnaryExpr const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(BinaryExpr const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(TernaryExpr const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(IntLiteral const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(StringLiteral const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(Identifier const& node, uint32 depth)
	{

	}
}


