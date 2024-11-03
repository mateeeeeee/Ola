#include "BasicBlock.h"
#include "GlobalValue.h"
#include "IRType.h"

namespace ola
{

	BasicBlock::BasicBlock(IRContext& C, Function* function, Uint32 idx /*= -1*/) : Value(ValueKind::BasicBlock, IRLabelType::Get(C)), function(function), block_idx(idx)
	{

	}

	Bool BasicBlock::IsEntryBlock() const
	{
		return function && &function->GetEntryBlock() == this;
	}

}

