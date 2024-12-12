#pragma once
#include "Compiler/CompilerOptions.h"


namespace ola
{
	class IRModule;

	struct IRPassOptions
	{
		Bool cfg_print;
		Bool domtree_print;
		Bool domfrontier_print;
	};

	class IRPassManager
	{
	public:
		explicit IRPassManager(IRModule& M);
		void Run(OptimizationLevel, IRPassOptions const&);

	private:
		IRModule& M;
	};
}