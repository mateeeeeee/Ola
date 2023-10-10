#include "LLVMCodegen.h"
#include "LLVMVisitor.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"

namespace wave
{
	LLVMCodegen::LLVMCodegen(std::string_view output_file)
	{
	}

	LLVMCodegen::~LLVMCodegen()
	{
	}

	void LLVMCodegen::Generate(AST const* ast)
	{
		LLVMVisitor llvm_visitor(ast);
		std::error_code error;
		llvm::raw_fd_ostream llvm_ir_file(output_file, error, llvm::sys::fs::OF_None);
		WAVE_ASSERT(!error);
		llvm_visitor.module->print(llvm_ir_file, nullptr);
	}

}


