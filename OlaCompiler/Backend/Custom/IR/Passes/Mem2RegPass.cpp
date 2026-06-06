#include <set>
#include <functional>
#include "Mem2RegPass.h"
#include "CFGAnalysisPass.h"
#include "DominanceFrontierAnalysisPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRContext.h"
#include "Backend/Custom/IR/Constant.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/DominatorTree.h"

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
		DT = &FAM.GetResult<DominatorTreeAnalysisPass>(F);

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

						if (SI->GetValueOp()->IsConstant())
						{
							Constant const* C = cast<Constant>(SI->GetValueOp());
							if (C->GetConstantID() == ConstantID::Global)
							{
								return false;
							}
						}
					}
					else if (isa<GetElementPtrInst>(U->GetUser()))
					{
						return false;
					}
					else if (isa<PtrAddInst>(U->GetUser()))
					{
						return false;
					}
					else if (isa<CallInst>(U->GetUser()))
					{
						return false;
					}
				}
				return true;
			};

		std::vector<AllocaInst*> Allocas;
		for (BasicBlock& BB : F) 
		{
			for (Instruction& I : BB) 
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
				for (Instruction& I : *BB)
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
		std::unordered_set<AllocaInst*> AllocasSet(Allocas.begin(), Allocas.end());
		std::function<void(DominatorTreeNode const*)> RenameNode = [&](DominatorTreeNode const* Node)
			{
				BasicBlock* BB = Node->GetBasicBlock();
				std::unordered_map<AllocaInst*, size_t> StackSizes;
				for (auto& [AI, Stack] : ValueStacks)
				{
					StackSizes[AI] = Stack.size();
				}

				for (Instruction& I : *BB)
				{
					if (PhiInst* Phi = dyn_cast<PhiInst>(&I))
					{
						AllocaInst* AI = Phi->GetAlloca();
						ValueStacks[AI].push(Phi);
					}
				}

				std::vector<Instruction*> InstructionRemoveQueue;
				for (Instruction& I : *BB)
				{
					if (LoadInst* LI = dyn_cast<LoadInst>(&I))
					{
						if (AllocaInst* AI = dyn_cast<AllocaInst>(LI->GetAddressOp()); AI && AllocasSet.contains(AI))
						{
							Value* CurrentValue = ValueStacks[AI].top();
							if (!CurrentValue)
							{
								CurrentValue = LI->GetType()->GetContext().GetUndefValue(LI->GetType());
							}
							LI->ReplaceAllUsesWith(CurrentValue);
							InstructionRemoveQueue.push_back(LI);
						}
					}
					else if (StoreInst* SI = dyn_cast<StoreInst>(&I))
					{
						if (AllocaInst* AI = dyn_cast<AllocaInst>(SI->GetAddressOp()); AI && AllocasSet.contains(AI))
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
						if (AI && AllocasSet.contains(AI) && !ValueStacks[AI].empty())
						{
							if (Value* TopValue = ValueStacks[AI].top())
							{
								Phi->AddIncoming(TopValue, BB);
							}
						}
					}
				}

				for (DominatorTreeNode const* Child : *Node)
				{
					RenameNode(Child);
				}

				for (auto& [AI, Stack] : ValueStacks)
				{
					while (Stack.size() > StackSizes[AI])
					{
						Stack.pop();
					}
				}
			};

		if (DominatorTreeNode const* Root = DT->GetRoot())
		{
			RenameNode(Root);
		}
	}
}

