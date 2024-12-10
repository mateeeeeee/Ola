#pragma once
#include "Compiler/CompilerOptions.h"


namespace ola
{
	class IRModule;

	class IRPassManager
	{
	public:
		explicit IRPassManager(IRModule& M);
		void PrintCFG();
		void PrintDomTree();
		void PrintDomFrontier();
		void Run(OptimizationLevel);

	private:
		IRModule& M;
		Bool cfg_print;
		Bool domtree_print;
		Bool domfrontier_print;
	};
}