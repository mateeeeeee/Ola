#pragma once
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"

namespace ola
{
	struct TestPass : public llvm::FunctionPass 
	{
		static Char ID;

		TestPass() : llvm::FunctionPass(ID) {}

		Bool runOnFunction(llvm::Function& F) override 
		{
			llvm::errs() << "Test: ";
			llvm::errs().write_escaped(F.getName()) << '\n';
			return false;
		}
	}; 

	Char TestPass::ID = 0;
	static llvm::RegisterPass<TestPass> X("Test", "Test Pass", false /* Only looks at CFG */,
															   false /* Analysis Pass */);
}