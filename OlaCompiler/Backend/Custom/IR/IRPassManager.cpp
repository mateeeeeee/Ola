#include "IRPassManager.h"
#include "IRModule.h"
#include "GlobalValue.h"
#include "Passes/Mem2RegPass.h"
#include "Passes/ArithmeticReductionPass.h"
#include "Passes/DeadCodeEliminationPass.h"
#include "Passes/CFGAnalysisPass.h"
#include "Passes/DominatorTreeAnalysisPass.h"
#include "Passes/DominanceFrontierAnalysisPass.h"
#include "Passes/GlobalAttributeInferPass.h"

namespace ola
{

	IRPassManager::IRPassManager(IRModule& M) : M(M)
	{}

	void IRPassManager::Run(OptimizationLevel level, IRPassOptions const& opts)
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
			FPM.AddPass(new Mem2RegPass());
			FPM.AddPass(new ArithmeticReductionPass());
			FPM.AddPass(new DeadCodeEliminationPass());
			MPM.AddPass(new GlobalAttributeInferPass());
		}
		if (opts.cfg_print)			 FPM.AddPass(new CFGPrinterPass());
		if (opts.domtree_print)		 FPM.AddPass(new DominatorTreePrinterPass());
		if (opts.domfrontier_print)  FPM.AddPass(new DominanceFrontierPrinterPass());

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
				FAM.RegisterPass<DominanceFrontierAnalysisPass>(F);
				FPM.Run(F, FAM);
			}
		}
	}

}

