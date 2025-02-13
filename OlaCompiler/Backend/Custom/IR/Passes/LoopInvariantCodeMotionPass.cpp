#include "LoopInvariantCodeMotionPass.h"
#include "LoopAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRBuilder.h"
#include "Backend/Custom/IR/IRContext.h"

namespace ola
{
	Bool LoopInvariantCodeMotionPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		LoopInfo const& LI = FAM.GetResult<LoopAnalysisPass>(F);
		if (LI.Empty()) 
		{
			return false;
		}
		Bool Changed = false;

		//#todo this goes only through top level loops
		for (Loop* L : LI) 
		{
			BasicBlock* LoopPreheader = L->GetLoopPreheader();
			if (!LoopPreheader) continue;

			Bool LocalChanged;
			do {
				LocalChanged = false;
				for (BasicBlock* BB : L->GetBlocks())
				{
					if (BB == L->GetHeader()) 
					{
						continue;
					}

					std::vector<Instruction*> invariant_instructions;
					for (Instruction& Inst : *BB)
					{
						if (isa<PhiInst>(&Inst) || Inst.IsTerminator()) continue;

						if (IsLoopInvariant(&Inst, L)) 
						{
							invariant_instructions.push_back(&Inst);
						}
					}

					for (Instruction* I : invariant_instructions)
					{
						I->InsertBefore(LoopPreheader, LoopPreheader->GetTerminator());
						LocalChanged = true;
						Changed = true;
					}
				}
			} while (LocalChanged);
		}

		return Changed;
	}

	Bool LoopInvariantCodeMotionPass::IsLoopInvariant(Instruction* I, Loop const* L)
	{
		if (isa<StoreInst>(I) || isa<LoadInst>(I) || isa<PhiInst>(I) || I->IsTerminator())
		{
			return false;
		}

		for (Value* Op : I->Operands()) 
		{
			if (isa<Constant>(Op)) 
			{
				continue;
			}
			if (Instruction* OpInst = dyn_cast<Instruction>(Op))
			{
				if (L->Contains(OpInst->GetBasicBlock())) 
				{
					return false;
				}
			}
		}
		return true;
	}

}