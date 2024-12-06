#pragma once
#include "Compiler/CompilerOptions.h"

namespace llvm
{
	class Module;
}

namespace ola
{
	class LLVMOptimizer
	{
	public:
		explicit LLVMOptimizer(llvm::Module& module);
		void Optimize(OptimizationLevel level);

	private:
		llvm::Module& module;
	};
}