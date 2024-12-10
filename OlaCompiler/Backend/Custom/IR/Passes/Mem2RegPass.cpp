#include "Mem2RegPass.h"
#include "CFGAnalysisPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool Mem2RegPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		std::vector<AllocaInst*> Allocas = FindAllocaInstructions(F);
		if (Allocas.empty()) 
		{
			return false; 
		}

		CFG const& cfg = FAM.GetResult<CFGAnalysisPass>(F);
		DT = &FAM.GetResult<DominatorTreeAnalysisPass>(F);

		InsertPhiFunctions(F, cfg, Allocas);
		for (AllocaInst* AI : Allocas) 
		{
			ValueStacks[AI] = std::stack<Value*>();
			RenameVariables(AI, DT->GetRoot());
			AI->EraseFromParent(); 
		}
		return true;
	}

	std::vector<AllocaInst*> Mem2RegPass::FindAllocaInstructions(Function& F)
	{
		std::vector<AllocaInst*> Allocas;
		for (BasicBlock& BB : F) 
		{
			for (Instruction& I : BB.Instructions()) 
			{
				if (AllocaInst* AI = dyn_cast<AllocaInst>(&I))
				{
					if (!AI->GetAllocatedType()->IsArray()) 
					{
						Allocas.push_back(AI);
					}
				}
			}
		}
		return Allocas;
	}

	void Mem2RegPass::InsertPhiFunctions(Function& F, CFG const& cfg, std::vector<AllocaInst*> const& Allocas)
	{
		for (AllocaInst* AI : Allocas) 
		{
			std::unordered_set<BasicBlock const*> DefiningBlocks;
			std::unordered_set<BasicBlock const*> WorkList;

			for (Use* U : AI->Users()) 
			{
				if (StoreInst* SI = dyn_cast<StoreInst>(U->GetUser()))
				{
					DefiningBlocks.insert(SI->GetBasicBlock());
				}
			}

			for (BasicBlock const* DefBlock : DefiningBlocks) 
			{
				//#todo
			}
		}
	}

	void Mem2RegPass::RenameVariables(AllocaInst* AI, DominatorTreeNode const* Node)
	{
		BasicBlock* BB = Node->GetBasicBlock();
		//#todo
	}

}

