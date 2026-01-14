#include <vector>
#include "CriticalEdgeSplittingPass.h"
#include "CFGAnalysisPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "DominanceFrontierAnalysisPass.h"
#include "LoopAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/CFG.h"

namespace ola
{
	Bool CriticalEdgeSplittingPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		cfg = &FAM.GetResult<CFGAnalysisPass>(F);
		edge_block_counter = 0;

		Bool Changed = SplitCriticalEdges(F);

		if (Changed)
		{
			FAM.InvalidateCache<CFGAnalysisPass>(F);
			FAM.InvalidateCache<DominatorTreeAnalysisPass>(F);
			FAM.InvalidateCache<DominanceFrontierAnalysisPass>(F);
			FAM.InvalidateCache<LoopAnalysisPass>(F);
		}
		return Changed;
	}

	Bool CriticalEdgeSplittingPass::SplitCriticalEdges(Function& F)
	{
		Bool Changed = false;

		std::vector<std::pair<BasicBlock*, BasicBlock*>> EdgesToSplit;
		for (BasicBlock& BB : F)
		{
			auto const& Successors = cfg->GetSuccessors(&BB);
			if (Successors.size() <= 1)
				continue;

			for (BasicBlock* Succ : Successors)
			{
				auto const& Preds = cfg->GetPredecessors(Succ);
				if (Preds.size() > 1)
				{
					EdgesToSplit.emplace_back(&BB, Succ);
				}
			}
		}

		for (auto& [Src, Dst] : EdgesToSplit)
		{
			SplitEdge(Src, Dst, F);
			Changed = true;
		}

		if (Changed)
		{
			Uint32 idx = 0;
			for (BasicBlock& BB : F)
			{
				BB.SetIndex(idx++);
			}
		}
		return Changed;
	}

	BasicBlock* CriticalEdgeSplittingPass::SplitEdge(BasicBlock* Src, BasicBlock* Dst, Function& F)
	{
		IRContext& Ctx = F.GetEntryBlock().front().GetContext();

		std::string EdgeBlockName = "edge." + std::to_string(edge_block_counter++);
		BasicBlock* EdgeBlock = new BasicBlock(Ctx, &F, F.Blocks().Size());
		EdgeBlock->SetName(EdgeBlockName);

		auto it = Src->GetIterator();
		++it;
		if (it != F.Blocks().end())
		{
			F.InsertBefore(EdgeBlock, &*it);
		}
		else
		{
			F.Insert(EdgeBlock);
		}

		BranchInst* EdgeBranch = new BranchInst(Ctx, Dst);
		EdgeBranch->InsertBefore(EdgeBlock, EdgeBlock->end());

		Instruction* Term = Src->GetTerminator();
		if (BranchInst* BI = dyn_cast<BranchInst>(Term))
		{
			if (BI->IsConditional())
			{
				if (BI->GetTrueTarget() == Dst)
					BI->SetTrueTarget(EdgeBlock);
				if (BI->GetFalseTarget() == Dst)
					BI->SetFalseTarget(EdgeBlock);
			}
			else
			{
				if (BI->GetTrueTarget() == Dst)
					BI->SetTrueTarget(EdgeBlock);
			}
		}
		else if (SwitchInst* SI = dyn_cast<SwitchInst>(Term))
		{
			if (SI->GetDefaultCase() == Dst)
				SI->SetDefaultCase(EdgeBlock);

			for (Uint32 i = 0; i < SI->GetNumCases(); ++i)
			{
				if (SI->GetCaseBlock(i) == Dst)
					SI->SetCaseBlock(i, EdgeBlock);
			}
		}

		for (PhiInst* Phi : Dst->PhiInsts())
		{
			Phi->ReplaceIncomingBlockWith(Src, EdgeBlock);
		}

		return EdgeBlock;
	}
}
