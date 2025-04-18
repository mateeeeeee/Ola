#include "IRPassManager.h"
#include "IRModule.h"
#include "GlobalValue.h"
#include "Passes/Mem2RegPass.h"
#include "Passes/ConstantPropagationPass.h"
#include "Passes/ArithmeticReductionPass.h"
#include "Passes/DeadCodeEliminationPass.h"
#include "Passes/GlobalDeadCodeEliminationPass.h"
#include "Passes/CommonSubexpressionEliminationPass.h"
#include "Passes/GlobalAttributeInferPass.h"
#include "Passes/CFGAnalysisPass.h"
#include "Passes/SimplifyCFGPass.h"
#include "Passes/DominatorTreeAnalysisPass.h"
#include "Passes/DominanceFrontierAnalysisPass.h"
#include "Passes/FunctionPassManagerModuleAdaptor.h"
#include "Passes/LoopAnalysisPass.h"
#include "Passes/LoopInvariantCodeMotionPass.h"
#include "Passes/FunctionInlinerPass.h"

namespace ola
{
	IRPassManager::IRPassManager(IRModule& M, FunctionAnalysisManager& FAM) : M(M), FAM(FAM)
	{
	}

	void IRPassManager::Run(OptimizationLevel level, IRPassOptions const& opts)
	{
		for (auto& G : M.Globals())
		{
			if (Function* F = dyn_cast<Function>(G); F && !F->IsDeclaration())
			{
				FAM.RegisterPass<CFGAnalysisPass>(*F);
				FAM.RegisterPass<DominatorTreeAnalysisPass>(*F);
				FAM.RegisterPass<DominanceFrontierAnalysisPass>(*F);
				FAM.RegisterPass<LoopAnalysisPass>(*F);
			}
		}
		FunctionPassManager FPM;
		if (level >= OptimizationLevel::O1)
		{
			FPM.AddPass(CreateFunctionInlinerPass());
			FPM.AddPass(CreateMem2RegPass());
			FPM.AddPass(CreateCSEPass());
			FPM.AddPass(CreateArithmeticReductionPass());
			FPM.AddPass(CreateConstantPropagationPass());
			FPM.AddPass(CreateLICMPass());
			FPM.AddPass(CreateDCEPass());
			FPM.AddPass(CreateSimplifyCFGPass());
			FPM.AddPass(CreateDCEPass());
		}
		if (opts.cfg_print)			 FPM.AddPass(CreateCFGPrinterPass());
		if (opts.domtree_print)		 FPM.AddPass(CreateDominatorTreePrinterPass());
		if (opts.domfrontier_print)  FPM.AddPass(CreateDominanceFrontierPrinterPass());

		IRModulePassManager MPM;
		if (level >= OptimizationLevel::O1)
		{
			MPM.AddPass(CreateFunctionPassManagerModuleAdaptor(FPM, FAM));
			MPM.AddPass(CreateGlobalAttributeInferPass());
			MPM.AddPass(CreateGlobalDCEPass());
		}

		if (!MPM.IsEmpty() || !FPM.IsEmpty())
		{
			IRModuleAnalysisManager MAM;
			MPM.Run(M, MAM);
		}
	}

}

