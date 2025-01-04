#include "IRPassManager.h"
#include "IRModule.h"
#include "GlobalValue.h"
#include "Passes/Mem2RegPass.h"
#include "Passes/ConstantPropagationPass.h"
#include "Passes/ArithmeticReductionPass.h"
#include "Passes/DeadCodeEliminationPass.h"
#include "Passes/GlobalAttributeInferPass.h"
#include "Passes/CFGAnalysisPass.h"
#include "Passes/DominatorTreeAnalysisPass.h"
#include "Passes/DominanceFrontierAnalysisPass.h"
#include "Passes/FunctionPassManagerModuleAdaptor.h"

namespace ola
{

	IRPassManager::IRPassManager(IRModule& M, FunctionAnalysisManager& FAM) : M(M), FAM(FAM)
	{
	}

	void IRPassManager::Run(OptimizationLevel level, IRPassOptions const& opts)
	{
		for (auto& G : M.Globals())
		{
			if (G->IsFunction())
			{
				Function& F = *cast<Function>(G);
				FAM.RegisterPass<CFGAnalysisPass>(F);
				FAM.RegisterPass<DominatorTreeAnalysisPass>(F);
				FAM.RegisterPass<DominanceFrontierAnalysisPass>(F);
			}
		}

		IRModulePassManager MPM;
		FunctionPassManager FPM;
		switch (level)
		{
		case OptimizationLevel::O3:
			[[fallthrough]];
		case OptimizationLevel::O2:
			[[fallthrough]];
		case OptimizationLevel::O1:
			FPM.AddPass(CreateMem2RegPass());
			FPM.AddPass(CreateDeadCodeEliminationPass());
			FPM.AddPass(CreateArithmeticReductionPass());
			FPM.AddPass(CreateConstantPropagationPass());
			MPM.AddPass(CreateGlobalAttributeInferPass());
		}
		if (opts.cfg_print)			 FPM.AddPass(CreateCFGPrinterPass());
		if (opts.domtree_print)		 FPM.AddPass(CreateDominatorTreePrinterPass());
		if (opts.domfrontier_print)  FPM.AddPass(CreateDominanceFrontierPrinterPass());

		if (FPM.IsEmpty() && MPM.IsEmpty()) return;

		MPM.AddPass(CreateFunctionPassManagerModuleAdaptor(FPM, FAM));
		IRModuleAnalysisManager MAM;
		MPM.Run(M, MAM);
	}

}

