#include <set>
#include "DeadCodeEliminationPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	bool DeadCodeEliminationPass::RunOn(Function& F)
	{
		std::set<Instruction*> alive;
		std::vector<Instruction*> worklist;
		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB.Instructions())
			{
				if (I.IsTerminator() || isa<StoreInst>(&I))
				{
					alive.insert(&I);
					worklist.push_back(&I);
				}
			}
		}
		while (!worklist.empty())
		{
			Instruction* curr = worklist.back();
			worklist.pop_back();
			for (Use& U : curr->Operands())
			{
				if (Instruction* I = dyn_cast<Instruction>(U.GetValue()))
				{
					if (alive.insert(I).second) worklist.push_back(I);
				}
			}
		}

		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB.Instructions())
			{
				if (!alive.contains(&I))
				{
					worklist.push_back(&I);
					I.ReplaceAllUseWith(nullptr);
				}
			}
		}

		for (Instruction*& I : worklist) 
		{
			I->EraseFromParent();
		}

		return !worklist.empty();
	}

	bool DeadCodeEliminationPass::IsInstructionDead(Instruction const* I)
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

