#include "LLVMCodegen.h"
#include "LLVMVisitor.h"

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
	}

}


