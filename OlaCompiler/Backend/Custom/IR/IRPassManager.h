#pragma once
#include "Compiler/CompilerOptions.h"
#include "AnalysisManager.h"
#include "FunctionPass.h"
#include "IRModulePass.h"

namespace ola
{
	class IRModule;

	struct IRPassOptions
	{
		Bool cfg_print;
		Bool domtree_print;
		Bool domfrontier_print;
	};

	class IRPassManager
	{
	public:
		explicit IRPassManager(IRModule& M);
		void Run(OptimizationLevel level, IRPassOptions const& opts);

		FunctionAnalysisManager& GetFAM() { return FAM; }

	private:
		IRModule& M;
		FunctionAnalysisManager FAM;

	private:
		void RunEarlyOptimizationPipeline();
		void RunMainOptimizationLoop(Uint32 max_iterations);
		void RunLateOptimizationPipeline();
		void RunDebugPasses(IRPassOptions const& opts);
		void RegisterAnalysisPasses();
	};
}