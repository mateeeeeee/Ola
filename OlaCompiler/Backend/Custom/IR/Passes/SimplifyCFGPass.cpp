#include "SimplifyCFGPass.h"
#include "CFGAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool SimplifyCFGPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		Bool Changed = false;
		Bool LocalChanged;
		do 
		{
			LocalChanged = false;

			Changed |= LocalChanged;
		} while (LocalChanged);

		if (Changed)
		{
			FAM.InvalidateCache<CFGAnalysisPass>(F);
		}
		return Changed;
	}
}
