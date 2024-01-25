#include "IRGen.h"
#include "IRVisitor.h"

namespace ola
{
	IRGen::IRGen(std::string_view filename) : context(), module(context, filename)
	{
	}

	IRGen::~IRGen() = default;

	void IRGen::Generate(AST const* ast)
	{
		IRVisitor llvm_visitor(context, module);
		llvm_visitor.VisitAST(ast);
	}

	void IRGen::PrintIR(std::string_view output_file)
	{
		module.PrintIR(output_file);
	}
}

