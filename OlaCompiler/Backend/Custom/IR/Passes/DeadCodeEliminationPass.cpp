#include <unordered_set>
#include "DeadCodeEliminationPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool DeadCodeEliminationPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		std::unordered_set<Instruction*> AliveInsts;
		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB)
			{
				if (I.IsTerminator() || isa<StoreInst>(&I) || isa<CallInst>(&I))
				{
					AliveInsts.insert(&I);
				}
			}
		}

		Bool Changed = false;
		Bool KeepGoing = true;
		while (KeepGoing)
		{
			KeepGoing = false;
			for (BasicBlock& BB : F)
			{
				for (Instruction& I : BB)
				{
					if (AliveInsts.contains(&I))
					{
						for (Use& U : I.Operands())
						{
							if (Instruction* OpInst = dyn_cast<Instruction>(U.GetValue()); OpInst && AliveInsts.insert(OpInst).second) 
								KeepGoing = true;
						}
					}
				}
			}
		}

		std::vector<Instruction*> DeadInsts;
		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB)
			{
				if (!AliveInsts.contains(&I))
				{
					DeadInsts.push_back(&I);
					Changed = true;
				}
			}
		}
		for (auto it = DeadInsts.rbegin(); it != DeadInsts.rend(); ++it)
		{
			Instruction* I = *it;
			I->EraseFromParent();
		}
		return Changed;
	}
}

