#include "LLVMIRGenContext.h"
#include "LLVMIRVisitor.h"
#include "LLVMUtils.h"
#include "Core/Log.h"
#include "llvm/Support/TargetSelect.h"

namespace ola
{

	LLVMIRGenContext::LLVMIRGenContext(std::string_view file_name) : context(), module(file_name.data(), context)
	{
		llvm::InitializeAllTargets();
		llvm::InitializeAllTargetMCs();
		llvm::InitializeAllAsmPrinters();
		llvm::InitializeAllAsmParsers();
	}
	LLVMIRGenContext::~LLVMIRGenContext() = default;

	void LLVMIRGenContext::Generate(AST const* ast)
	{
		LLVMIRVisitor llvm_visitor(context, module);
		llvm_visitor.VisitAST(ast);
		Bool verified = VerifyLLVMModule(module);
	}
}


