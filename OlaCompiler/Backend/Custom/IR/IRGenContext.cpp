#include "IRGenContext.h"
#include "IRVisitor.h"

namespace ola
{
	IRGenContext::IRGenContext(std::string_view filename) : context(), module(context, filename)
	{
	}

	IRGenContext::~IRGenContext() = default;

	void IRGenContext::Generate(AST const* ast)
	{
		IRVisitor ir_visitor(context, module);
		ir_visitor.VisitAST(ast);
	}
}

