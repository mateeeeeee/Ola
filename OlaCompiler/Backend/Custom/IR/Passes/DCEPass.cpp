#include "DCEPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	bool DCEPass::RunOn(Function& F)
	{
		bool changed = false;

		// Iterate over all basic blocks in the function
		for (auto& BB : F)
		{
			auto& instructions = BB.Instructions();
			// Iterate over instructions in the basic block in reverse order
			// to safely remove them if found dead
			for (auto it = instructions.rbegin(); it != instructions.rend();)
			{
				Instruction& Inst = *it++;
				if (IsInstructionDead(&Inst))
				{
					
				}
			}
		}
		return changed;
	}

	bool DCEPass::IsInstructionDead(Instruction const* I)
	{
		if (I->IsUsed())
			return false;
		if (I->IsTerminator())
			return false;
		if (isa<StoreInst>(I))
			return false;
		return true;
	}

}

