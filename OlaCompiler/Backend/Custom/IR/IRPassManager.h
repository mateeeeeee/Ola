#pragma once
#include "Compiler/CompilerOptions.h"


namespace ola
{
	class IRModule;

	struct IRPassOptions
	{
		Bool cfg_print;
		Bool domtree_print;
		Bool domfrontier_print;
	};

	class Function;
	template<typename UnitT>
	class AnalysisManager;
	using FunctionAnalysisManager = AnalysisManager<Function>;

	class IRPassManager
	{
	public:
		IRPassManager(IRModule& M, FunctionAnalysisManager& FAM);
		void Run(OptimizationLevel level, IRPassOptions const& opts);

	private:
		IRModule& M;
		FunctionAnalysisManager& FAM;

	private:
		void RunEarlyOptimizationPipeline();
		void RunMainOptimizationLoop(Uint32 max_iterations);
		void RunLateOptimizationPipeline();
		void RunDebugPasses(IRPassOptions const& opts);
	};
}