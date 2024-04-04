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
		friend class LLVMIRGenContext;

	private:
		explicit LLVMOptimizer(llvm::Module& module);
		void Optimize(OptimizationLevel level);

	private:
		llvm::Module& module;
	};
}