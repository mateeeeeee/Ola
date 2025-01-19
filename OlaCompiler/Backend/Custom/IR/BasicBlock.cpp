#include "BasicBlock.h"
#include "GlobalValue.h"
#include "IRType.h"
#include "IRBuilder.h"
#include "CFG.h"

namespace ola
{

	BasicBlock::BasicBlock(IRContext& C, Function* function, Uint32 idx) : TrackableValue(ValueKind::BasicBlock, IRLabelType::Get(C)), function(function), block_idx(idx), current_cfg(nullptr)
	{
	}

	BasicBlock::~BasicBlock()
	{
	}

	BasicBlock* BasicBlock::RemoveFromParent()
	{
		return function->Blocks().Remove(this);
	}

	IListIterator<BasicBlock> BasicBlock::EraseFromParent()
	{
		return function->Blocks().Erase(this);
	}

	Bool BasicBlock::IsEntryBlock() const
	{
		return function && &function->GetEntryBlock() == this;
	}

	void BasicBlock::AddPredecessor(BasicBlock* pred)
	{
		OLA_ASSERT(current_cfg);
		return current_cfg->AddPredecessor(this, pred);
	}
	void BasicBlock::AddSuccessor(BasicBlock* succ)
	{
		OLA_ASSERT(current_cfg);
		return current_cfg->AddSuccessor(this, succ);
	}
	void BasicBlock::RemovePredecessor(BasicBlock* pred)
	{
		OLA_ASSERT(current_cfg);
		return current_cfg->RemovePredecessor(this, pred);
	}
	void BasicBlock::RemoveSuccessor(BasicBlock* succ)
	{
		OLA_ASSERT(current_cfg);
		return current_cfg->RemovePredecessor(this, succ);
	}

	std::unordered_set<BasicBlock*> const& BasicBlock::GetPredecessors() const
	{
		OLA_ASSERT(current_cfg);
		return current_cfg->GetPredecessors(this);
	}
	std::unordered_set<BasicBlock*> const& BasicBlock::GetSuccessors() const
	{
		OLA_ASSERT(current_cfg);
		return current_cfg->GetSuccessors(this);
	}
	BasicBlock* BasicBlock::GetUniquePredecessor() const
	{
		return current_cfg->GetUniquePredecessor(this);
	}
	BasicBlock* BasicBlock::GetUniqueSuccessor() const
	{
		return current_cfg->GetUniqueSuccessor(this);
	}

	BasicBlock* BasicBlock::SplitBasicBlock(Instruction* SplitBefore)
	{
		IRBuilder builder(GetContext());
		builder.SetCurrentFunction(GetParent());

		std::string NewBlockName(GetName()); NewBlockName += ".split";
		BasicBlock* NewBlock = builder.AddBlock(GetNextNode(), NewBlockName);

		auto& CurrentInstructions = Instructions();
		auto& NewBlockInstructions = NewBlock->Instructions();

		auto SplitIter = std::find_if(CurrentInstructions.begin(), CurrentInstructions.end(), [SplitBefore](Instruction const& I) { return &I == SplitBefore; });
		if (SplitIter == CurrentInstructions.end()) return NewBlock;

		NewBlockInstructions.Splice(NewBlockInstructions.begin(), CurrentInstructions, SplitIter, CurrentInstructions.end());
		for (Instruction& NewInstruction : NewBlockInstructions)
		{
			NewInstruction.SetBasicBlock(NewBlock);
		}

		builder.SetCurrentBlock(this);
		builder.MakeInst<BranchInst>(GetContext(), NewBlock);
		return NewBlock;
	}

}

