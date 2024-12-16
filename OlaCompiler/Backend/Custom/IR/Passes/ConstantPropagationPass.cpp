#include <unordered_set>
#include "ConstantPropagationPass.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRBuilder.h"
#include "Backend/Custom/IR/IRContext.h"

namespace ola
{
	namespace
	{
		Constant* ConstantFoldBinaryInst(BinaryInst* BI)
		{
			return nullptr;
		}
		Constant* ConstantFoldUnaryInst(UnaryInst* UI)
		{
			return nullptr;
		}
		Constant* ConstantFoldCompareInst(CompareInst* CI)
		{
			return nullptr;
		}

		Constant* ConstantFoldInstruction(Instruction* I)
		{
			return nullptr;
		}
	}

	Bool ConstantPropagationPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		std::unordered_set<Instruction*> WorkList;
		std::vector<Instruction*> WorkListVector;
		for (BasicBlock& BB : F.Blocks())
		{
			for (Instruction& I : BB.Instructions())
			{
				WorkList.insert(&I);
				WorkListVector.push_back(&I);
			}
		}
		Bool changed = false;
		while (!WorkList.empty())
		{
			std::vector<Instruction*> NewWorkListVector;
			for (Instruction* I : WorkListVector)
			{
				WorkList.erase(I);
				if (!I->HasNUsesOrMore(1)) continue;

				if (Constant* C = ConstantFoldInstruction(I))
				{
					for (Use* U : I->Users())
					{
						if (WorkList.insert(cast<Instruction>(U->GetUser())).second)
							NewWorkListVector.push_back(cast<Instruction>(U->GetUser()));
					}

					I->ReplaceAllUseWith(C);
					if (!I->HasNUsesOrMore(1))
					{
						I->EraseFromParent();
					}
					changed = true;
				}
			}
			WorkListVector = std::move(NewWorkListVector);
		}
		return changed;
	}
}