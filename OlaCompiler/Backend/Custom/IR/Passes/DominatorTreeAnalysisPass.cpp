#include <functional>
#include "DominatorTreeAnalysisPass.h"
#include "CFGAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool DominatorTreeAnalysisPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		CFG const& cfg = FAM.GetResult<CFGAnalysisPass>(F);
		dom_tree.Initialize(cfg);
		return false; 
	}

	Bool DominatorTreePrinterPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		return false;
	}

}

