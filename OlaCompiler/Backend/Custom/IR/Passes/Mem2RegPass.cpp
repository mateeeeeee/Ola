#include <set>
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
		std::vector<AllocaInst*> Allocas = FindPromotableAllocaInstructions(F);
		if (Allocas.empty()) 
		{
			return false; 
		}

		CFG const& cfg = FAM.GetResult<CFGAnalysisPass>(F);
		DF = &FAM.GetResult<DominanceFrontierAnalysisPass>(F);

		InsertPhiFunctions(Allocas, cfg);
		RenameVariables(Allocas, cfg);
		return true;
	}

	std::vector<AllocaInst*> Mem2RegPass::FindPromotableAllocaInstructions(Function& F)
	{
		auto IsAllocaPromotable = [](AllocaInst const* AI)
			{
				if (AI->GetAllocatedType()->IsArray())
				{
					return false;
				}
				for (Use const* U : AI->Users())
				{
					if (LoadInst const* LI = dyn_cast<LoadInst>(U->GetUser()))
					{
						if (LI->GetType() != AI->GetAllocatedType()) return false;
					}
					else if (StoreInst const* SI = dyn_cast<StoreInst>(U->GetUser()))
					{
						if (SI->GetValueOp() == AI ||
							SI->GetValueOp()->GetType() != AI->GetAllocatedType())
							return false; 
					}
					else if (const GetElementPtrInst* GEPI = dyn_cast<GetElementPtrInst>(U->GetUser()))
					{
						return false;
					}
					else if (CallInst* CI = dyn_cast<CallInst>(U->GetUser()))
					{
						return false;
					}
				}
				return true;
			};

		std::vector<AllocaInst*> Allocas;
		for (BasicBlock& BB : F) 
		{
			for (Instruction& I : BB.Instructions()) 
			{
				if (AllocaInst* AI = dyn_cast<AllocaInst>(&I))
				{
					if (IsAllocaPromotable(AI))
					{
						Allocas.push_back(AI);
					}
				}
			}
		}
		return Allocas;
	}

	void Mem2RegPass::InsertPhiFunctions(std::vector<AllocaInst*> const& Allocas, CFG const& cfg)
	{
		OLA_ASSERT(DF);
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
				for (BasicBlock* DFBlock : DF->GetFrontier(BB))
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

	void Mem2RegPass::RenameVariables(std::vector<AllocaInst*> const& Allocas, CFG const& cfg)
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
		RenameBlock(cfg.GetEntryBlock());
	}

}

