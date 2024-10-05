#include "IROptimizer.h"
#include "IRModule.h"
#include "GlobalValue.h"
#include "Passes/ArithmeticStrengthReductionPass.h"
#include "Passes/DeadCodeEliminationPass.h"
#include "Passes/CFGAnalysisPass.h"

namespace ola
{

	IROptimizer::IROptimizer(IRModule& M) : M(M)
	{
	}

	void IROptimizer::Optimize(OptimizationLevel level)
	{
		FunctionPassManager FPM;
		switch (level)
		{
		case OptimizationLevel::O3:
			[[fallthrough]];
		case OptimizationLevel::O2:
			[[fallthrough]];
		case OptimizationLevel::O1:
			FPM.AddPass(new ArithmeticStrengthReductionPass());
			FPM.AddPass(new DeadCodeEliminationPass());
		}
		if (FPM.IsEmpty()) return;

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

