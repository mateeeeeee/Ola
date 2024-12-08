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
		InsertPhiFunctions(F, cfg, Allocas);

		DT = &FAM.GetResult<DominatorTreeAnalysisPass>(F);
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
				for (BasicBlock* BB : cfg.GetSuccessors(DefBlock))
				{
					if (WorkList.insert(BB).second) 
					{
						PhiNode* Phi = new PhiNode(AI->GetAllocatedType());
						BB->Instructions().Insert(BB->Instructions().begin(), Phi);
						PhiNodes[AI].push_back(Phi);
					}
				}
			}
		}
	}

	void Mem2RegPass::RenameVariables(AllocaInst* AI, DominatorTreeNode const* Node)
	{
		BasicBlock* BB = Node->GetBasicBlock();

		auto& Instructions = BB->Instructions();
		for (auto I = Instructions.begin(), E = Instructions.end(); I != E;)
		{
			Instruction* Inst = &*I++;
			if (LoadInst* LI = dyn_cast<LoadInst>(Inst))
			{
				if (LI->GetAddressOp() == AI)
				{
					if (!ValueStacks[AI].empty())
					{
						LI->ReplaceAllUseWith(ValueStacks[AI].top());
						LI->EraseFromParent();
					}
				}
			}
			else if (StoreInst* SI = dyn_cast<StoreInst>(Inst))
			{
				if (SI->GetAddressOp() == AI)
				{
					ValueStacks[AI].push(SI->GetValueOp());
					SI->EraseFromParent();
				}
			}
		}

		for (PhiNode* Phi : PhiNodes[AI]) 
		{
			Phi->AddIncoming(ValueStacks[AI].empty() ? new UndefValue(AI->GetAllocatedType()) : ValueStacks[AI].top(), BB);
		}

		for (DominatorTreeNode* Child : *Node) 
		{
			RenameVariables(AI, Child);
		}

		if (!ValueStacks[AI].empty()) 
		{
			ValueStacks[AI].pop();
		}
	}

}

