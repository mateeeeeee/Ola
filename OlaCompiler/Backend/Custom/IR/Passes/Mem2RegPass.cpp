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
				PhiInst* Phi = new PhiInst(AI->GetAllocatedType());
				BB->AddPhiInst(Phi);
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

		std::unordered_set<BasicBlock*> Visited;
		std::function<void(BasicBlock*)> RenameBlock = [&](BasicBlock* BB)
			{
				std::unordered_map<AllocaInst*, size_t> StackSizes;
				for (auto& [AI, Stack] : ValueStacks)
				{
					StackSizes[AI] = Stack.size();
				}

				for (Instruction& I : BB->Instructions())
				{
					if (PhiInst* Phi = dyn_cast<PhiInst>(&I))
					{
						AllocaInst* AI = Phi->GetAlloca();
						ValueStacks[AI].push(Phi);
					}
				}

				std::vector<Instruction*> InstructionRemoveQueue;
				for (Instruction& I : BB->Instructions())
				{
					if (LoadInst* LI = dyn_cast<LoadInst>(&I))
					{
						if (AllocaInst* AI = dyn_cast<AllocaInst>(LI->GetAddressOp()))
						{
							Value* CurrentValue = ValueStacks[AI].top();
							OLA_ASSERT(CurrentValue);
							LI->ReplaceAllUsesWith(CurrentValue);
							InstructionRemoveQueue.push_back(LI);
						}
					}
					else if (StoreInst* SI = dyn_cast<StoreInst>(&I))
					{
						if (AllocaInst* AI = dyn_cast<AllocaInst>(SI->GetAddressOp()))
						{
							ValueStacks[AI].push(SI->GetValueOp());
							InstructionRemoveQueue.push_back(SI);
						}
					}
				}

				for (Instruction* I : InstructionRemoveQueue)
				{
					I->EraseFromParent();
				}

				for (BasicBlock* Successor : cfg.GetSuccessors(BB))
				{
					for (PhiInst* Phi : Successor->PhiInsts())
					{
						AllocaInst* AI = Phi->GetAlloca();
						if (AI && !ValueStacks[AI].empty())
						{
							if (Value* TopValue = ValueStacks[AI].top())
							{
								Phi->AddIncoming(TopValue, BB);
							}
						}
					}
				}

				for (BasicBlock* Successor : cfg.GetSuccessors(BB))
				{
					if (Visited.insert(Successor).second)
					{
						RenameBlock(Successor);
					}
				}

				for (auto& [AI, Stack] : ValueStacks)
				{
					while (Stack.size() > StackSizes[AI])
					{
						Stack.pop();
					}
				}
			};

		RenameBlock(cfg.GetEntryBlock());
	}
}

