#include <set>
#include "DeadCodeEliminationPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	bool DeadCodeEliminationPass::RunOn(Function& F)
	{
		bool changed = false;

		std::set<Instruction*> Alive;
		std::vector<Instruction*> Worklist;
		// Collect the set of "root" instructions that are known live.
		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB.Instructions())
			{
				if (I.IsTerminator() || isa<StoreInst>(&I))
				{
					Alive.insert(&I);
					Worklist.push_back(&I);
				}
			}
		}
		// Propagate liveness backwards to operands
		while (!Worklist.empty())
		{
			Instruction* Curr = Worklist.back();
			Worklist.pop_back();
			for (Use& U : Curr->Operands())
			{
				if (Instruction* I = dyn_cast<Instruction>(U.GetValue()))
				{
					if (Alive.insert(I).second) Worklist.push_back(I);
				}
			}
		}
		//the instructions which are not in live set are
		//considered dead in this pass.The instructions which do not
		//effect the control flow, return value and do not have any
		//side effects are hence deleted.
		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB.Instructions())
			{
				if (!Alive.contains(&I))
				{
					Worklist.push_back(&I);
					I.ReplaceAllUseWith(nullptr);
				}
			}
		}

		for (Instruction*& I : Worklist) 
		{
			I->EraseFromParent();
		}

		return !Worklist.empty();
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

