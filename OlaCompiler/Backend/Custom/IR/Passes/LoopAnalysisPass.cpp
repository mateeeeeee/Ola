#include <unordered_set>
#include "LoopAnalysisPass.h"
#include "DominatorTreeAnalysisPass.h"


namespace ola
{

	Bool LoopAnalysisPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		LI.Clear();  // Clear old loop info before recomputing
		DominatorTree const& DT = FAM.GetResult<DominatorTreeAnalysisPass>(F);
		DT.VisitPostOrder([&](DominatorTreeNode const* DTNode) -> Bool 
		{
			BasicBlock* Header = DTNode->GetBasicBlock();
			std::vector<BasicBlock*> BackEdges;

			for (BasicBlock* Pred : Header->GetPredecessors()) 
			{
				DominatorTreeNode const* PredNode = DT.GetTreeNode(Pred);
				if (PredNode && DT.Dominates(DTNode, PredNode)) 
				{
					BackEdges.push_back(Pred);
				}
			}

			if (!BackEdges.empty())
			{
				Loop* L = new Loop(Header);
				DiscoverLoop(L, BackEdges, DT, LI);
				if (!LI.GetLoopFor(Header)) 
				{
					LI.AddTopLevelLoop(L);
				}
			}

			return true;  
		});
		return false;
	}

	void LoopAnalysisPass::DiscoverLoop(Loop* L, std::span<BasicBlock*> BackEdges, DominatorTree const& DT, LoopInfo& LI)
	{
		std::unordered_set<BasicBlock*> Visited;
		std::vector<BasicBlock*> WorkList;

		BasicBlock* Header = L->GetHeader();

		for (BasicBlock* BB : BackEdges) 
		{
			if (Visited.insert(BB).second) WorkList.push_back(BB);
		}

		Visited.insert(Header);
		while (!WorkList.empty()) 
		{
			BasicBlock* BB = WorkList.back();
			WorkList.pop_back();

			Loop* ContainingLoop = LI.GetLoopFor(BB);
			if (ContainingLoop) 
			{
				if (ContainingLoop->GetHeader() != Header) 
				{
					L->AddChildLoop(ContainingLoop);
					if (ContainingLoop->IsOutermost()) 
					{
						LI.ChangeTopLevelLoop(ContainingLoop, L);
					}
				}
			}
			else 
			{
				L->AddBlockToLoop(BB);
				LI.ChangeLoopFor(BB, L);
			}

			for (BasicBlock* Pred : BB->GetPredecessors())
			{
				if (DT.Dominates(Header, Pred) && Visited.insert(Pred).second) WorkList.push_back(Pred);
			}
		}
	}
}