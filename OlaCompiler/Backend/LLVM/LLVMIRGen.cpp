#include "LLVMIRGen.h"
#include "LLVMIRVisitor.h"
#include "LLVMOptimizer.h"
#include "Core/Logger.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Verifier.h"

namespace ola
{

	LLVMIRGen::LLVMIRGen(std::string_view file_name) : context(), module(file_name.data(), context)
	{
		llvm::InitializeAllTargets();
		llvm::InitializeAllTargetMCs();
		llvm::InitializeAllAsmPrinters();
		llvm::InitializeAllAsmParsers();
	}
	LLVMIRGen::~LLVMIRGen() = default;

	void LLVMIRGen::Generate(AST const* ast)
	{
		LLVMIRVisitor llvm_visitor(context, module);
		llvm_visitor.VisitAST(ast);
		bool verified = VerifyModule(module);
	}

	void LLVMIRGen::Optimize(OptimizationLevel level)
	{
		LLVMOptimizer optimizer(module);
		optimizer.Optimize(level);
		bool verified = VerifyModule(module);
	}

	void LLVMIRGen::PrintIR(std::string_view output_file)
	{
		std::error_code error;
		llvm::raw_fd_ostream llvm_ir_file(output_file, error, llvm::sys::fs::OF_None);
		if (error)
		{
			OLA_ERROR("Error when creating llvm::raw_fd_ostream: {}", error.message());
			return;
		}  
		module.print(llvm_ir_file, nullptr);
	}

	bool LLVMIRGen::VerifyModule(llvm::Module& module)
	{
		std::string error_msg;
		llvm::raw_string_ostream error_stream(error_msg);
		if (llvm::verifyModule(module, &error_stream))
		{
			error_stream.flush();
			OLA_ERROR("Module verification failed: {}", error_msg);
			return false;
		}
		return true;
	}

}


