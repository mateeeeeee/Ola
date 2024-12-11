#pragma once
#include "Compiler/CompilerOptions.h"

namespace llvm
{
	class Module;
}

namespace ola
{
	class LLVMIRPassManager
	{
	public:
		explicit LLVMIRPassManager(llvm::Module& module);
		void PrintDomFrontier();
		void PrintDomTree();
		void Run(OptimizationLevel level);

	private:
		llvm::Module& module;
		Bool domtree_print;
		Bool domfrontier_print;
	};
}