#pragma once
#include "Symbol.h"
#include "AST.h"

namespace wave
{
	struct AST;
	class Sema 
	{
		struct Context
		{
			std::unique_ptr<SymbolTable<Symbol>> sym_table;
		};

	public:
		explicit Sema(AST* ast);
		~Sema() = default;


	private:
		Context ctx;
	};
}