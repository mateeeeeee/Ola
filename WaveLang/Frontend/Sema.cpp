#include "Sema.h"

namespace wave
{

	Sema::Sema(AST* ast)
	{
		ctx.sym_table = std::make_unique<SymbolTable<Symbol>>();
		//ast->translation_unit->Accept(*this, 0);
	}

}

