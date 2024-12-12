#pragma once
#include "Compiler/CompilerOptions.h"

namespace llvm
{
	class Module;
}

namespace ola
{
	struct LLVMIRPassOptions
	{
		Bool domfrontier_print;
	};
	class LLVMIRPassManager
	{
	public:
		explicit LLVMIRPassManager(llvm::Module& module);
		void Run(OptimizationLevel level, LLVMIRPassOptions const& opts);

	private:
		llvm::Module& module;
	};
}