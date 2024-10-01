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
		void Optimize(OptimizationLevel);
		void EmitIR(std::string_view);
		IRModule& GetModule() { return module; }

	private:
		IRContext context;
		IRModule  module;
	};
}