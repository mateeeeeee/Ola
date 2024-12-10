#include <functional>
#include "DominatorTreeAnalysisPass.h"
#include "CFGAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool DominatorTreeAnalysisPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		CFG const& cfg = FAM.GetResult<CFGAnalysisPass>(F);
		DT.Initialize(cfg);
		return false; 
	}

	Bool DominatorTreePrinterPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		DominatorTree const& DT = FAM.GetResult<DominatorTreeAnalysisPass>(F);
		std::string function_name(F.GetName());
		DT.Print(function_name);
		return false;
	}

}

