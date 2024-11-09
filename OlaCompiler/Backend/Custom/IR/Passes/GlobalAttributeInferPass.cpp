#include <list>
#include "GlobalAttributeInferPass.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool GlobalAttributeInferPass::RunOn(IRModule& Module, IRModuleAnalysisManager& MAM)
	{
		std::list<GlobalVariable*> Worklist;
		for (GlobalValue* G : Module.Globals())
		{
			if (GlobalVariable* GV = dyn_cast<GlobalVariable>(G))
			{
				if (!GV->IsReadOnly() && GV->GetLinkage() == Linkage::Internal) 
				{
					Worklist.push_back(GV);
				}
			}
		}

		if (Worklist.empty())
		{
			return false;
		}

		for (GlobalValue* G : Module.Globals())
		{
			if (Function* F = dyn_cast<Function>(G))
			{
				for (BasicBlock& BB : F->Blocks())
				{
					for (Instruction& I : BB.Instructions())
					{
						if (StoreInst* SI = dyn_cast<StoreInst>(&I))
						{
							Value* AddressOperand = SI->GetAddressOp();
							Worklist.remove_if([&](GlobalVariable* GV) { return GV == AddressOperand; });
						}
					}
				}
			}
		}

		for (GlobalVariable* GV : Worklist)
		{
			GV->SetReadOnly();
		}
		return !Worklist.empty();
	}
}

