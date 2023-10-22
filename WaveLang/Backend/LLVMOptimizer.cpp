#include "LLVMOptimizer.h"
#include "llvm/Pass.h" 
#include "llvm/IR/LegacyPassManager.h" 
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/IPO.h" 
#include <llvm/Transforms/Scalar.h>       
#include <llvm/Transforms/Vectorize.h>    
#include <llvm/Transforms/Utils.h>   
#include <llvm/Transforms/InstCombine/InstCombine.h>  


namespace wave
{
	
	LLVMOptimizer::LLVMOptimizer(llvm::Module& module) : module(module) {}

	void LLVMOptimizer::Optimize(OptimizationLevel level)
	{
		if (level == OptimizationLevel::O0) return;

		llvm::legacy::PassManager pass_manager;

		pass_manager.add(llvm::createPromoteMemoryToRegisterPass());
		pass_manager.add(llvm::createDeadCodeEliminationPass());
		pass_manager.add(llvm::createLoopUnrollPass());
		pass_manager.add(llvm::createInstructionCombiningPass());

		pass_manager.run(module);
	}

}
