#pragma once

namespace llvm
{
	class Module;
}

namespace ola
{
	enum class OptimizationLevel : uint8
	{
		Od,
		O0 = Od,
		O1,
		O2,
		O3
	};

	class LLVMOptimizer
	{
		friend class LLVMIRGenerator;

	private:
		explicit LLVMOptimizer(llvm::Module& module);
		void Optimize(OptimizationLevel level);

	private:
		llvm::Module& module;
	};
}