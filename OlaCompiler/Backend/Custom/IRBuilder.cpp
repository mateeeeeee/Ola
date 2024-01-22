#include "IRBuilder.h"
#include "IR.h"

namespace ola
{

	IRBuilder::IRBuilder(IRContext& ctx) : ctx(ctx), insert_point(nullptr)
	{

	}

	IRBuilder::IRBuilder(BasicBlock* insert_block) : ctx(insert_block->GetContext())
	{
		SetInsertPoint(insert_block);
	}

	IRBuilder::~IRBuilder() = default;

}

