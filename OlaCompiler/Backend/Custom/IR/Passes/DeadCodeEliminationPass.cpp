#include <set>
#include "DeadCodeEliminationPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool DeadCodeEliminationPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		return false;
#if 0
		std::set<Instruction*> AliveSet;
		std::vector<Instruction*> WorkList;
		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB.Instructions())
			{
				if (I.IsTerminator() || isa<StoreInst>(&I) || isa<CallInst>(&I))
				{
					AliveSet.insert(&I);
					WorkList.push_back(&I);
				}
			}
		}
		while (!WorkList.empty())
		{
			Instruction* curr = WorkList.back();
			WorkList.pop_back();
			for (Use& U : curr->Operands())
			{
				if (Instruction* I = dyn_cast<Instruction>(U.GetValue()))
				{
					if (AliveSet.insert(I).second) WorkList.push_back(I);
				}
			}
		}

		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB.Instructions())
			{
				if (!AliveSet.contains(&I))
				{
					WorkList.push_back(&I);
					I.ReplaceAllUseWith(nullptr);
				}
			}
		}

		for (Instruction*& I : WorkList)
		{
			I->EraseFromParent();
		}

		return !WorkList.empty();
#endif
	}
}

