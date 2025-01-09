#include "BasicBlock.h"
#include "GlobalValue.h"
#include "IRType.h"
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

	std::vector<ola::BasicBlock*> const& BasicBlock::GetSuccessors() const
	{
		OLA_ASSERT(current_cfg);
		return current_cfg->GetSuccessors(this);
	}

}

