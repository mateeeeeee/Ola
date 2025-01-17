#include "BasicBlock.h"
#include "GlobalValue.h"
#include "IRType.h"
#include "IRBuilder.h"
#include "CFG.h"

namespace ola
{

	BasicBlock::BasicBlock(IRContext& C, Function* function, Uint32 idx) : Value(ValueKind::BasicBlock, IRLabelType::Get(C)), function(function), block_idx(idx), current_cfg(nullptr)
	{
	}

	Bool BasicBlock::IsEntryBlock() const
	{
		return function && &function->GetEntryBlock() == this;
	}

	std::vector<BasicBlock*> const& BasicBlock::GetPredecessors() const
	{
		OLA_ASSERT(current_cfg);
		return current_cfg->GetPredecessors(this);
	}

	std::vector<BasicBlock*> const& BasicBlock::GetSuccessors() const
	{
		OLA_ASSERT(current_cfg);
		return current_cfg->GetSuccessors(this);
	}

	BasicBlock* BasicBlock::SplitBasicBlock(Instruction* SplitBefore)
	{
		IRBuilder builder(GetContext());
		builder.SetCurrentFunction(GetParent());

		std::string NewBlockName(GetName()); NewBlockName += ".split";
		BasicBlock* NewBlock = builder.AddBlock(GetNextNode(), NewBlockName);

		auto& CurrentInstructions = Instructions();
		auto& NewBlockInstructions = NewBlock->Instructions();

		auto SplitIter = std::find_if(CurrentInstructions.begin(), CurrentInstructions.end(), [SplitBefore](const Instruction& I) { return &I == SplitBefore; });
		NewBlockInstructions.Splice(NewBlockInstructions.begin(), CurrentInstructions, SplitIter, CurrentInstructions.end());

		builder.SetCurrentBlock(this);
		builder.MakeInst<BranchInst>(GetContext(), NewBlock);
		return NewBlock;
	}

}

