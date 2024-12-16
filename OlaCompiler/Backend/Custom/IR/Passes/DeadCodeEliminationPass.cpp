#include <set>
#include "DeadCodeEliminationPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool DeadCodeEliminationPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		return false; //temporary, causes issues on ifelse test with --O3
	}
}

