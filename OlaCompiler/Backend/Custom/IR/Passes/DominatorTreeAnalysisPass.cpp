#include <functional>
#include "DominatorTreeAnalysisPass.h"
#include "CFGAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool DominatorTreeAnalysisPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		CFGAnalysisPass::Result const& cfgResult = FAM.GetResult<CFGAnalysisPass>(F);
		result = DominatorTree{};  
		return false; 
	}
}

