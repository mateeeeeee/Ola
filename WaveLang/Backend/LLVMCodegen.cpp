#include "LLVMCodegen.h"
#include "LLVMVisitorAST.h"

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
		LLVMVisitorAST llvm_visitor(ast);
	}

}


