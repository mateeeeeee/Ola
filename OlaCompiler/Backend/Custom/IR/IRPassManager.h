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
		void Run(OptimizationLevel, IRPassOptions const&);

	private:
		IRModule& M;
		FunctionAnalysisManager& FAM;
	};
}