#include "IROptimizer.h"
#include "IRModule.h"
#include "GlobalValue.h"
#include "Passes/ArithmeticReductionPass.h"
#include "Passes/DeadCodeEliminationPass.h"
#include "Passes/CFGAnalysisPass.h"
#include "Passes/DominatorTreeAnalysisPass.h"
#include "Passes/DominanceFrontierPrinterPass.h"
#include "Passes/GlobalAttributeInferPass.h"

namespace ola
{

	IROptimizer::IROptimizer(IRModule& M) : M(M), cfg_print(false), domtree_print(false)
	{
	}

	void IROptimizer::PrintCFG()
	{
		cfg_print = true;
	}

	void IROptimizer::PrintDomTree()
	{
		domtree_print = true;
	}

	void IROptimizer::Optimize(OptimizationLevel level)
	{
		IRModulePassManager MPM;
		FunctionPassManager FPM;

		if (cfg_print)		FPM.AddPass(new CFGPrinterPass());
		if (domtree_print)  FPM.AddPass(new DominatorTreePrinterPass());
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
				FAM.RegisterPass<DominatorTreeAnalysisPass>(F);
				FAM.RegisterPass<DominanceFrontierPrinterPass>(F);
				FPM.Run(F, FAM);
			}
		}
	}

}

