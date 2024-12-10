#include "LLVMIRPassManager.h"
#include "LLVMUtils.h"
#include "Passes/TestPass.h"
#include "llvm/Pass.h" 
#include "llvm/IR/LegacyPassManager.h" 
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/IPO.h" 
#include <llvm/Transforms/Scalar.h>       
#include <llvm/Transforms/Vectorize.h>    
#include <llvm/Transforms/Utils.h>   
#include <llvm/Transforms/InstCombine/InstCombine.h>  


namespace ola
{
	
	LLVMIRPassManager::LLVMIRPassManager(llvm::Module& module) : module(module) {}

	void LLVMIRPassManager::Run(OptimizationLevel level)
	{
		llvm::legacy::PassManager pass_manager;

		switch (level)
		{
		case OptimizationLevel::O3:
			pass_manager.add(llvm::createDeadArgEliminationPass());
			pass_manager.add(llvm::createTailCallEliminationPass());
			pass_manager.add(llvm::createReassociatePass());
			pass_manager.add(llvm::createLoopRotatePass());
			pass_manager.add(llvm::createLICMPass());
			[[fallthrough]];
		case OptimizationLevel::O2:
			pass_manager.add(llvm::createLoopSimplifyPass());
			pass_manager.add(llvm::createLCSSAPass());
			pass_manager.add(llvm::createEarlyCSEPass());
			pass_manager.add(llvm::createLoopUnrollPass());
			[[fallthrough]];
		case OptimizationLevel::O1:
			pass_manager.add(llvm::createPromoteMemoryToRegisterPass());
			pass_manager.add(llvm::createInstructionCombiningPass());
			pass_manager.add(llvm::createCFGSimplificationPass());
			pass_manager.add(llvm::createDeadCodeEliminationPass());
			[[fallthrough]];
		case OptimizationLevel::O0:
		default:
			break;
		}
		pass_manager.run(module);
		Bool verified = VerifyLLVMModule(module);
	}
}
