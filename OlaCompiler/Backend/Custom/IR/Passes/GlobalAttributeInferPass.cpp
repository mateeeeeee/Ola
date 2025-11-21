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
				for (BasicBlock& BB : *F)
				{
					for (Instruction& I : BB)
					{
						// Direct store to global
						if (StoreInst* SI = dyn_cast<StoreInst>(&I))
						{
							Value* AddressOperand = SI->GetAddressOp();
							Worklist.remove_if([&](GlobalVariable* GV) { return GV == AddressOperand; });
						}

						// Check all operands - if a global is used as a value (not just store destination),
						// its address has escaped and could be modified indirectly
						for (Use& U : I.Operands())
						{
							if (GlobalVariable* GV = dyn_cast<GlobalVariable>(U.Get()))
							{
								// Special case: StoreInst uses the address operand, but that's OK
								// We only care if it's used in other ways (address-taken)
								if (StoreInst* SI = dyn_cast<StoreInst>(&I))
								{
									if (&U == &SI->GetOperandUse(1))  // Address operand
									{
										continue;  // This is the store destination, not address-taken
									}
								}

								// Global is used as a value - its address escapes
								Worklist.remove_if([&](GlobalVariable* GV2) { return GV2 == GV; });
							}
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

