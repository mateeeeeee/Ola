#pragma once
#include "Compiler/CompilerOptions.h"


namespace ola
{
	class IRModule;

	class IROptimizer
	{
		friend class IRGenContext;
	private:
		explicit IROptimizer(IRModule& M);
		void Optimize(OptimizationLevel);

	private:
		IRModule& M;
	};
}