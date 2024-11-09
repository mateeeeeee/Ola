#include "IROptimizer.h"
#include "IRModule.h"
#include "GlobalValue.h"
#include "Passes/ArithmeticReductionPass.h"
#include "Passes/DeadCodeEliminationPass.h"
#include "Passes/CFGAnalysisPass.h"
#include "Passes/GlobalAttributeInferPass.h"

namespace ola
{

	IROptimizer::IROptimizer(IRModule& M) : M(M)
	{
	}

	void IROptimizer::Optimize(OptimizationLevel level)
	{
		IRModulePassManager MPM;
		FunctionPassManager FPM;
		switch (level)
		{
		case OptimizationLevel::O3:
			[[fallthrough]];
		case OptimizationLevel::O2:
			[[fallthrough]];
		case OptimizationLevel::O1:
			FPM.AddPass(new ArithmeticReductionPass());
			FPM.AddPass(new DeadCodeEliminationPass());
			MPM.AddPass(new GlobalAttributeInferPass());
		}
		if (FPM.IsEmpty() && MPM.IsEmpty()) return;

		IRModuleAnalysisManager MAM;
		MPM.Run(M, MAM);

		FunctionAnalysisManager FAM;
		for (auto& G : M.Globals())
		{
			if (G->IsFunction())
			{
				Function& F = *cast<Function>(G);
				FAM.RegisterPass<CFGAnalysisPass>(F);
				FPM.Run(F, FAM);
			}
		}
	}

}

