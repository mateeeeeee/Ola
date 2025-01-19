#include <unordered_set>
#include <functional>
#include "SimplifyCFGPass.h"
#include "CFGAnalysisPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool SimplifyCFGPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		Bool Changed = false;
		Bool LocalChanged;
		do 
		{
			cfg = const_cast<CFG*>(&FAM.GetResult<CFGAnalysisPass>(F));
			LocalChanged = false;
			//LocalChanged |= MergeBlocks(F);
			LocalChanged |= RemoveUnreachableBlocks(F);
			Changed |= LocalChanged;
		} while (LocalChanged);

		if (Changed)
		{
			FAM.InvalidateCache<CFGAnalysisPass>(F);
			FAM.InvalidateCache<DominatorTreeAnalysisPass>(F);
		}
		return Changed;
	}

	Bool SimplifyCFGPass::MergeBlocks(Function& F)
	{
		Bool Changed = false;
		for (auto& BB : F) 
		{
			if (BB.Instructions().Size() == 1)
			{
				Instruction* I = BB.GetTerminator();
				if (BranchInst* BI = dyn_cast<BranchInst>(I); BI && BI->IsUnconditional())
				{
					BasicBlock* Succ = BI->GetTrueTarget();
					OLA_ASSERT(Succ);
					BB.ReplaceAllUsesWith(Succ);
				}
			}
		}
		return Changed;
	}

	Bool SimplifyCFGPass::RemoveUnreachableBlocks(Function& F)
	{
		Bool Changed = false;
		std::unordered_set<BasicBlock*> Reachable;
		std::function<void(BasicBlock*)> MarkReachable = [&](BasicBlock* BB) 
		{
			if (!BB || !Reachable.insert(BB).second)
				return;
			for (BasicBlock* Succ : cfg->GetSuccessors(BB))
				MarkReachable(Succ);
		};
		MarkReachable(&F.GetEntryBlock());

		std::vector<BasicBlock*> ToRemove;
		for (auto& BB : F) 
		{
			if (!Reachable.contains(&BB)) 
			{
				ToRemove.push_back(&BB);
				Changed = true;
			}
		}

		for (BasicBlock* BB : ToRemove)
		{
			BB->EraseFromParent();
		}
		return Changed;
	}
}
