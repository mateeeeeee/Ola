#include "LLVMVisitorAST.h"
#include "Frontend/AST.h"

namespace wave
{

	LLVMVisitorAST::LLVMVisitorAST(AST const* ast)
	{
		ast->translation_unit->Accept(*this);
	}

	void LLVMVisitorAST::Visit(NodeAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(TranslationUnitAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(DeclAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(FunctionDeclAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(VariableDeclAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(StmtAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(CompoundStmtAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(ExprStmtAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(DeclStmtAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(NullStmtAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(ReturnStmtAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(IfStmtAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(ExprAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(UnaryExprAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(BinaryExprAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(TernaryExprAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(IntLiteralAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(StringLiteralAST const& node, uint32 depth)
	{

	}

	void LLVMVisitorAST::Visit(IdentifierAST const& node, uint32 depth)
	{

	}
}


