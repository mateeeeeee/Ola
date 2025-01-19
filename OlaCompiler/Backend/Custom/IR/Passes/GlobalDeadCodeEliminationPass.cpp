#include <unordered_set>
#include <functional>
#include "GlobalDeadCodeEliminationPass.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRModule.h"

namespace ola
{
	Bool GlobalDeadCodeEliminationPass::RunOn(IRModule& M, IRModuleAnalysisManager& FAM)
	{
		std::unordered_set<GlobalValue const*> UsedGlobals;
		std::function<void(Function const*)> MarkFunctionAsUsed = [&](Function const* F) 
		{
			if (!F || !UsedGlobals.insert(F).second) 
			{
				return; 
			}

			for (BasicBlock const& BB : *F) 
			{
				for (Instruction const& I : BB) 
				{
					if (CallInst const* Call = dyn_cast<CallInst>(&I))
					{
						if (Function const* Callee = Call->GetCalleeAsFunction())
						{
							MarkFunctionAsUsed(Callee);
						}
					}

					for (auto const& Op : I.Operands())
					{
						if (GlobalVariable const* GV = dyn_cast<GlobalVariable>(Op.GetValue()))
						{
							UsedGlobals.insert(GV);
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
			M.RemoveGlobal(DG);
		}
		return !DeadGlobals.empty();
	}
}

