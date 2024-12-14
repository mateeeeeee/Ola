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
		FunctionAnalysisManager FAM;
		Bool changed = false;
		for (auto& G : M.Globals())
		{
			if (G->IsFunction())
			{
				Function& F = *cast<Function>(G);
				FAM.RegisterPass<CFGAnalysisPass>(F);
				FAM.RegisterPass<DominatorTreeAnalysisPass>(F);
				FAM.RegisterPass<DominanceFrontierAnalysisPass>(F);
				changed |= FPM.Run(F, FAM);
			}
		}
		return changed;
	}

}

