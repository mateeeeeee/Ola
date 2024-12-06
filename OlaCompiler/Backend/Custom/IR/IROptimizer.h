#pragma once
#include "Compiler/CompilerOptions.h"


namespace ola
{
	class IRModule;

	class IROptimizer
	{
	public:
		explicit IROptimizer(IRModule& M);
		void PrintCFG();
		void PrintDomTree();
		void Optimize(OptimizationLevel);

	private:
		IRModule& M;
		Bool cfg_print;
		Bool domtree_print;
	};
}