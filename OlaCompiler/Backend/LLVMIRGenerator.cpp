#include "LLVMIRGenerator.h"
#include "LLVMVisitor.h"
#include "LLVMOptimizer.h"
#include "Core/Logger.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Verifier.h"

namespace ola
{

	LLVMIRGenerator::LLVMIRGenerator(std::string_view file_name) : context(), module(file_name.data(), context)
	{
		llvm::InitializeAllTargets();
		llvm::InitializeAllTargetMCs();
		llvm::InitializeAllAsmPrinters();
		llvm::InitializeAllAsmParsers();
	}
	LLVMIRGenerator::~LLVMIRGenerator() = default;

	void LLVMIRGenerator::Generate(AST const* ast)
	{
		LLVMVisitor llvm_visitor(context, module);
		llvm_visitor.VisitAST(ast);
		bool verified = VerifyModule(module);
		//OLA_ASSERT(verified);
	}

	void LLVMIRGenerator::Optimize(OptimizationLevel level)
	{
		LLVMOptimizer optimizer(module);
		optimizer.Optimize(level);
		bool verified = VerifyModule(module);
		//OLA_ASSERT(verified);
	}

	void LLVMIRGenerator::PrintIR(std::string_view output_file)
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

	bool LLVMIRGenerator::VerifyModule(llvm::Module& module)
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


