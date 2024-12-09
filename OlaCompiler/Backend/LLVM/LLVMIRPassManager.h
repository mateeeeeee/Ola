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
		void Run(OptimizationLevel level);

	private:
		llvm::Module& module;
	};
}