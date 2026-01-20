#include <unordered_set>
#include <functional>
#include "GlobalDeadCodeEliminationPass.h"
#include "CallGraphAnalysisPass.h"
#include "Backend/Custom/IR/CallGraph.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRModule.h"

namespace ola
{
	Bool GlobalDeadCodeEliminationPass::RunOn(IRModule& M, IRModuleAnalysisManager& MAM)
	{
		CallGraph& CG = const_cast<CallGraph&>(MAM.GetResult<CallGraphAnalysisPass>(M));
		std::unordered_set<GlobalValue const*> UsedGlobals;
		std::function<void(Function const*)> MarkFunctionAsUsed = [&](Function const* F)
		{
			if (!F || !UsedGlobals.insert(F).second)
			{
				return;
			}

			CallGraphNode* Node = CG.GetNode(F);
			if (Node)
			{
				for (CallRecord const& CR : *Node)
				{
					if (CR.callee && CR.callee->GetFunction())
					{
						MarkFunctionAsUsed(CR.callee->GetFunction());
					}
				}
			}

			if (!F->IsDeclaration())
			{
				for (BasicBlock const& BB : *F)
				{
					for (Instruction const& I : BB)
					{
						for (auto const& Op : I.Operands())
						{
							if (GlobalVariable const* GV = dyn_cast<GlobalVariable>(Op.GetValue()))
							{
								UsedGlobals.insert(GV);
							}
						}
					}
				}
			}
		};

		for (auto& G : M.Globals())
		{
			if (Function* F = dyn_cast<Function>(G); F && F->GetLinkage() != Linkage::Internal)
			{
				MarkFunctionAsUsed(F);
			}
		}

		std::vector<GlobalValue*> DeadGlobals;
		for (auto& G : M.Globals())
		{
			if (Function* F = dyn_cast<Function>(G); F && F->GetLinkage() == Linkage::Internal && !UsedGlobals.contains(F))
			{
				DeadGlobals.push_back(F);
			}
			if (GlobalVariable* GV = dyn_cast<GlobalVariable>(G); GV && GV->GetLinkage() == Linkage::Internal && !UsedGlobals.contains(GV))
			{
				DeadGlobals.push_back(GV);
			}
		}

		for (GlobalValue* DG : DeadGlobals)
		{
			if (Function* F = dyn_cast<Function>(DG))
			{
				CG.RemoveFunction(F);
			}
			M.RemoveGlobal(DG);
		}

		return !DeadGlobals.empty();
	}
}

