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
#include "Passes/CriticalEdgeSplittingPass.h"
#include "Passes/DominatorTreeAnalysisPass.h"
#include "Passes/DominanceFrontierAnalysisPass.h"
#include "Passes/FunctionPassManagerModuleAdaptor.h"
#include "Passes/LoopAnalysisPass.h"
#include "Passes/LoopInvariantCodeMotionPass.h"
#include "Passes/LoopUnrollPass.h"
#include "Passes/FunctionInlinerPass.h"
#include "Passes/IPConstantPropagationPass.h"
#include "Passes/CallGraphAnalysisPass.h"

namespace ola
{
	IRPassManager::IRPassManager(IRModule& M) : M(M)
	{}

	void IRPassManager::Run(OptimizationLevel level, IRPassOptions const& opts)
	{
		RegisterAnalysisPasses();

		if (level >= OptimizationLevel::O1)
		{
			Uint32 const max_iterations = level >= OptimizationLevel::O2 ? 5 : 2;
			RunEarlyOptimizationPipeline();
			RunMainOptimizationLoop(max_iterations);
			RunLateOptimizationPipeline();
		}
		RunDebugPasses(opts);

		if (level >= OptimizationLevel::O1)
		{
			IRModulePassManager MPM;
			MPM.AddPass(CreateGlobalAttributeInferPass());
			MPM.AddPass(CreateGlobalDCEPass());

			IRModuleAnalysisManager MAM;
			MAM.RegisterPass<CallGraphAnalysisPass>(M);
			MPM.Run(M, MAM);
		}
	}

	void IRPassManager::RunEarlyOptimizationPipeline()
	{
		{
			IRModulePassManager MPM;
			MPM.AddPass(CreateIPConstantPropagationPass());
			IRModuleAnalysisManager MAM;
			MAM.RegisterPass<CallGraphAnalysisPass>(M);
			MPM.Run(M, MAM);
		}

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
			FPM.AddPass(CreateLoopUnrollPass());
			FPM.AddPass(CreateSimplifyCFGPass());
			FPM.AddPass(CreateGVNPass());
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
		FPM.AddPass(CreateCriticalEdgeSplittingPass());

		IRModulePassManager MPM;
		MPM.AddPass(CreateFunctionPassManagerModuleAdaptor(FPM, FAM));

		IRModuleAnalysisManager MAM;
		MPM.Run(M, MAM);
	}

	void IRPassManager::RunDebugPasses(IRPassOptions const& opts)
	{
		FunctionPassManager FPM;
		if (opts.cfg_print) 
		{
			FPM.AddPass(CreateCFGPrinterPass());
		}
		if (opts.domtree_print) 
		{
			FPM.AddPass(CreateDominatorTreePrinterPass());
		}
		if (opts.domfrontier_print) 
		{
			FPM.AddPass(CreateDominanceFrontierPrinterPass());
		}

		if (!FPM.IsEmpty())
		{
			IRModulePassManager MPM;
			MPM.AddPass(CreateFunctionPassManagerModuleAdaptor(FPM, FAM));

			IRModuleAnalysisManager MAM;
			MPM.Run(M, MAM);
		}
	}

	void IRPassManager::RegisterAnalysisPasses() 
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
	}
} 