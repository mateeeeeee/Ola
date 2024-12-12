﻿#include <set>
#include <functional>
#include "Mem2RegPass.h"
#include "CFGAnalysisPass.h"
#include "DominanceFrontierAnalysisPass.h"
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
		DF = &FAM.GetResult<DominanceFrontierAnalysisPass>(F);

		InsertPhiFunctions(Allocas, cfg, *DF);
		RenameVariables(Allocas, cfg, F);
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

	void Mem2RegPass::InsertPhiFunctions(std::vector<AllocaInst*> const& Allocas, CFG const& cfg, DominanceFrontier const& DF)
	{
		std::unordered_map<AllocaInst*, std::set<BasicBlock*>> PhiPlacement;
		for (AllocaInst* AI : Allocas)
		{
			std::set<BasicBlock*> DefBlocks; 
			for (BasicBlock* BB : cfg)
			{
				for (Instruction& I : BB->Instructions())
				{
					if (StoreInst* SI = dyn_cast<StoreInst>(&I))
					{
						if (SI->GetAddressOp() == AI)
						{
							DefBlocks.insert(BB);
							break; 
						}
					}
				}
			}

			std::set<BasicBlock*> Worklist = DefBlocks;
			while (!Worklist.empty())
			{
				BasicBlock* BB = *Worklist.begin();
				Worklist.erase(BB);
				for (BasicBlock* DFBlock : DF.GetFrontier(BB))
				{
					if (PhiPlacement[AI].insert(DFBlock).second) 
					{
						if (DefBlocks.find(DFBlock) == DefBlocks.end())
						{
							Worklist.insert(DFBlock);
						}
					}
				}
			}
		}

		for (auto& [AI, Blocks] : PhiPlacement)
		{
			for (BasicBlock* BB : Blocks)
			{
				PhiNode* Phi = new PhiNode(AI->GetAllocatedType());
				BB->AddPhiNode(Phi);
				Phi->SetAlloca(AI);
			}
		}
	}

	void Mem2RegPass::RenameVariables(std::vector<AllocaInst*> const& Allocas, CFG const& cfg, Function& F)
	{
		std::unordered_map<AllocaInst*, std::stack<Value*>> ValueStacks;
		for (AllocaInst* AI : Allocas)
		{
			ValueStacks[AI].push(nullptr);
		}

		std::function<void(BasicBlock*)> RenameBlock = [&](BasicBlock* BB)
			{
				std::unordered_map<AllocaInst*, Value*> IncomingValues;
				for (Instruction& I : BB->Instructions())
				{
					if (PhiNode* Phi = dyn_cast<PhiNode>(&I))
					{
						AllocaInst* AI = Phi->GetAlloca();
						IncomingValues[AI] = Phi;
						ValueStacks[AI].push(Phi);
					}
				}

				std::vector<Instruction*> InstructionRemoveQueue;
				for (Instruction& I : BB->Instructions())
				{
					if (LoadInst* LI = dyn_cast<LoadInst>(&I))
					{
						AllocaInst* AI = dyn_cast<AllocaInst>(LI->GetAddressOp());
						if (AI)
						{
							Value* CurrentValue = ValueStacks[AI].top();
							LI->ReplaceAllUseWith(CurrentValue);
							InstructionRemoveQueue.push_back(LI);
						}
					}
					else if (StoreInst* SI = dyn_cast<StoreInst>(&I))
					{
						AllocaInst* AI = dyn_cast<AllocaInst>(SI->GetAddressOp());
						if (AI)
						{
							ValueStacks[AI].push(SI->GetValueOp());
							InstructionRemoveQueue.push_back(SI);
						}
					}
				}
				for (Instruction* I : InstructionRemoveQueue) I->EraseFromParent();

				for (BasicBlock* Successor : cfg.GetSuccessors(BB))
				{
					for (PhiNode* Phi : Successor->PhiNodes())
					{
						AllocaInst* AI = Phi->GetAlloca();
						if (AI)
						{
							Phi->AddIncoming(ValueStacks[AI].top(), BB);
						}
					}
				}

				for (BasicBlock* Successor : cfg.GetSuccessors(BB))
				{
					RenameBlock(Successor);
				}

				for (auto& [AI, Stack] : ValueStacks)
				{
					if (!Stack.empty() && IncomingValues.count(AI))
					{
						Stack.pop();
					}
				}
			};
		RenameBlock(&F.GetEntryBlock());
	}

}

