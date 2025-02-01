#include "FunctionPassManagerModuleAdaptor.h"
#include "CFGAnalysisPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "DominanceFrontierAnalysisPass.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool FunctionPassManagerModuleAdaptor::RunOn(IRModule& M, IRModuleAnalysisManager& MAM)
	{
		Bool changed = false;
		for (auto& G : M.Globals())
		{
			if (Function* F = dyn_cast<Function>(G); F && !F->IsDeclaration() && !F->IsNoOptimizations())
			{
				changed |= FPM.Run(*F, FAM);
			}
		}
		return changed;
	}
}

