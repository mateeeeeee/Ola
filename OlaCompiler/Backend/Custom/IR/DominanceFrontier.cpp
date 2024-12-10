#include "DominanceFrontier.h"
#include "DominatorTree.h"
#include "CFG.h"

namespace ola
{
	//Efficiently Computing Static Single Assignment Form and the Control Dependence Graph, Cytron et al
	//(Section 4.2) Dominance Frontiers
	//for each X in a bottom - up traversal of the dominator tree do
	//
	//	DF(X) <- null
	//	for each Y in Succ(X) do
	//		if (idom(Y) != X) then DF(X) <- DF(X) U {Y}
	//	end
    //	for each Z in {idom(Z) = X} do
    //		for each Y in DF(Z) do
    //			if (idom(Y) != X) then DF(X) <- DF(X) U {Y}
    //	end
	void DominanceFrontier::Initialize(DominatorTree const& DT, CFG const& cfg)
	{
		dominance_frontier_map.clear();
		dominance_frontier_map[cfg.GetEntryBlock()] = {};
		DT.VisitPostOrder([this, &DT, &cfg](DominatorTreeNode const* node) -> Bool
			{
				BasicBlock* X = node->GetBasicBlock();
				for (BasicBlock* Y : cfg.GetSuccessors(X)) 
				{
					if (!DT.StrictlyDominates(X, Y)) 
					{
						dominance_frontier_map[X].insert(Y);
					}
				}

				for (DominatorTreeNode const* child : *node)
				{
					BasicBlock* Z = child->GetBasicBlock();
					for (BasicBlock* Y : dominance_frontier_map[Z])
					{
						if (!DT.StrictlyDominates(X, Y)) 
						{
							dominance_frontier_map[X].insert(Y);
						}
					}
				}
				return true;
			});
	}

}