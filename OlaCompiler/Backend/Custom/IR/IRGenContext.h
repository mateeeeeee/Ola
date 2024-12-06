#pragma once
#include "IRContext.h"
#include "IRModule.h"
#include "IROptimizer.h"

namespace ola
{
	struct AST;

	class IRGenContext
	{
	public:
		explicit IRGenContext(std::string_view filename);
		~IRGenContext();

		void Generate(AST const* ast);
		IRModule& GetModule() { return module; }

	private:
		IRContext context;
		IRModule  module;
	};
}