#include "LLVMVisitor.h"
#include "Frontend/AST.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"

namespace wave
{

	LLVMVisitor::LLVMVisitor(AST const* ast) : builder(context)
	{
		llvm::InitializeAllTargets();
		llvm::InitializeAllTargetMCs();
		llvm::InitializeAllAsmPrinters();
		llvm::InitializeAllAsmParsers();

		module = std::make_unique<llvm::Module>("WaveModule", context);

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
		node.GetLHS()->Accept(*this);
		node.GetLHS()->Accept(*this);
		llvm::Value* right = RHS->codegen();

		if (!left || !right)
			return nullptr;

		if (Op == '+') {
			// Create an LLVM IR builder
			llvm::IRBuilder<> builder(llvm::getGlobalContext());

			// Add the left and right values
			return builder.CreateAdd(left, right, "addtmp");
		}
		else {
			// Handle other binary operators similarly
			return nullptr;
		}
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

	void LLVMVisitor::Visit(IdentifierExpr const& node, uint32 depth)
	{

	}
}


