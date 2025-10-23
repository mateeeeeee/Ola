#include "IRPassManager.h"
#include "IRModule.h"
#include "GlobalValue.h"
#include "Passes/Mem2RegPass.h"
#include "Passes/ConstantPropagationPass.h"
#include "Passes/ArithmeticReductionPass.h"
#include "Passes/DeadCodeEliminationPass.h"
#include "Passes/GlobalDeadCodeEliminationPass.h"
#include "Passes/CommonSubexpressionEliminationPass.h"
#include "Passes/GlobalValueNumberingPass.h"
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
	{}

	void IRPassManager::Run(OptimizationLevel level, IRPassOptions const& opts)
	{
		for (GlobalValue* G : M.Globals())
		{
			if (Function* F = dyn_cast<Function>(G); F && !F->IsDeclaration())
			{
				FAM.RegisterPass<CFGAnalysisPass>(*F);
				FAM.RegisterPass<DominatorTreeAnalysisPass>(*F);
				FAM.RegisterPass<DominanceFrontierAnalysisPass>(*F);
				FAM.RegisterPass<LoopAnalysisPass>(*F);
			}
		}

		if (level >= OptimizationLevel::O1)
		{
			RunEarlyOptimizationPipeline();
			if (level >= OptimizationLevel::O2)
			{
				RunMainOptimizationLoop(5);
			}
			else
			{
				RunMainOptimizationLoop(2);
			}
			RunLateOptimizationPipeline();
		}

		if (opts.cfg_print || opts.domtree_print || opts.domfrontier_print)
		{
			RunDebugPasses(opts);
		}

		if (level >= OptimizationLevel::O1)
		{
			IRModulePassManager MPM;
			MPM.AddPass(CreateGlobalAttributeInferPass());
			MPM.AddPass(CreateGlobalDCEPass());

			IRModuleAnalysisManager MAM;
			MPM.Run(M, MAM);
		}
	}

	void IRPassManager::RunEarlyOptimizationPipeline()
	{
		FunctionPassManager FPM;

		FPM.AddPass(CreateFunctionInlinerPass());
		FPM.AddPass(CreateMem2RegPass());
		FPM.AddPass(CreateDCEPass());
		FPM.AddPass(CreateSimplifyCFGPass());

		IRModulePassManager MPM;
		MPM.AddPass(CreateFunctionPassManagerModuleAdaptor(FPM, FAM));
		IRModuleAnalysisManager MAM;
		MPM.Run(M, MAM);
	}

	void IRPassManager::RunMainOptimizationLoop(Uint32 max_iterations)
	{
		for (Uint32 iteration = 0; iteration < max_iterations; ++iteration)
		{
			FunctionPassManager FPM;
			FPM.AddPass(CreateConstantPropagationPass());
			FPM.AddPass(CreateArithmeticReductionPass());

			FPM.AddPass(CreateCSEPass());
			FPM.AddPass(CreateDCEPass());
			FPM.AddPass(CreateLICMPass());
			FPM.AddPass(CreateSimplifyCFGPass());
			//FPM.AddPass(CreateGVNPass());
			FPM.AddPass(CreateDCEPass());

			IRModulePassManager MPM;
			MPM.AddPass(CreateFunctionPassManagerModuleAdaptor(FPM, FAM));

			IRModuleAnalysisManager MAM;
			Bool changed = MPM.Run(M, MAM);

			if (!changed)
			{
				break;
			}
		}
	}

	void IRPassManager::RunLateOptimizationPipeline()
	{
		FunctionPassManager FPM;

		FPM.AddPass(CreateDCEPass());
		FPM.AddPass(CreateSimplifyCFGPass());
		FPM.AddPass(CreateDCEPass());

		IRModulePassManager MPM;
		MPM.AddPass(CreateFunctionPassManagerModuleAdaptor(FPM, FAM));

		IRModuleAnalysisManager MAM;
		MPM.Run(M, MAM);
	}

	void IRPassManager::RunDebugPasses(IRPassOptions const& opts)
	{
		FunctionPassManager FPM;
		if (opts.cfg_print) FPM.AddPass(CreateCFGPrinterPass());
		if (opts.domtree_print) FPM.AddPass(CreateDominatorTreePrinterPass());
		if (opts.domfrontier_print) FPM.AddPass(CreateDominanceFrontierPrinterPass());

		if (!FPM.IsEmpty())
		{
			IRModulePassManager MPM;
			MPM.AddPass(CreateFunctionPassManagerModuleAdaptor(FPM, FAM));

			IRModuleAnalysisManager MAM;
			MPM.Run(M, MAM);
		}
	}
}