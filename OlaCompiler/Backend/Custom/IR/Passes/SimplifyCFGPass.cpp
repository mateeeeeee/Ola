#include <unordered_set>
#include <functional>
#include "SimplifyCFGPass.h"
#include "CFGAnalysisPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "DominanceFrontierAnalysisPass.h"
#include "LoopAnalysisPass.h"
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
			LocalChanged |= MergeBlocks(F);
			ResetCFG(F, FAM);
			LocalChanged |= RemoveUnreachableBlocks(F);
			Changed |= LocalChanged;
		} while (LocalChanged);
		if (Changed)
		{
			FAM.InvalidateCache<CFGAnalysisPass>(F);
			FAM.InvalidateCache<DominatorTreeAnalysisPass>(F);
			FAM.InvalidateCache<DominanceFrontierAnalysisPass>(F);
			FAM.InvalidateCache<LoopAnalysisPass>(F);
		}
		Changed |= SimplifyPHIs(F);
		return Changed;
	}

	void SimplifyCFGPass::ResetCFG(Function& F, FunctionAnalysisManager& FAM)
	{
		FAM.InvalidateCache<CFGAnalysisPass>(F);
		cfg = &FAM.GetResult<CFGAnalysisPass>(F);
	}

	Bool SimplifyCFGPass::MergeBlocks(Function& F)
	{
		Bool Changed = false;
		for (auto& BB : F) 
		{
			if (BB.Instructions().Size() == 1)
			{
				Instruction* I = BB.GetTerminator();
				if (BranchInst* BI = dyn_cast<BranchInst>(I); BI && BI->IsUnconditional() && BI->GetTrueTarget())
				{
					BasicBlock* Succ = BI->GetTrueTarget();
					if (!Succ->HasPhiInsts())
					{
						BB.ReplaceAllUsesWith(Succ);
					}
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

	Bool SimplifyCFGPass::SimplifyPHIs(Function& F)
	{
		Bool Changed = false;
		for (auto& BB : F)
		{
			for (auto& I : BB)
			{
				if (PhiInst* Phi = dyn_cast<PhiInst>(&I))
				{
					for (Int i = Phi->GetNumIncomingValues() - 1; i >= 0; --i) 
					{
						if (Phi->GetIncomingBlock(i) == nullptr) 
						{
							Phi->RemoveIncomingValue(i);
							Changed = true;
						}
					}

					if (Phi->GetNumIncomingValues() == 1)
					{
						Phi->ReplaceAllUsesWith(Phi->GetIncomingValue(0));
						Changed = true;
					}
				}
			}
		}
		return Changed;
	}

}
