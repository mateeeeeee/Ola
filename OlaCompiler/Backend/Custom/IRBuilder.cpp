#include "IRBuilder.h"
#include "IR.h"

namespace ola
{

	IRBuilder::IRBuilder(IRContext& ctx) : ctx(ctx), insert_point(nullptr), insert_block(nullptr)
	{
	}

	IRBuilder::IRBuilder(BasicBlock* insert_block) : ctx(insert_block->GetContext()), insert_point(nullptr)
	{
		SetInsertPoint(insert_block);
	}

	IRBuilder::IRBuilder(Instruction* insert_point) : ctx(insert_point->GetContext()), insert_point(nullptr)
	{
		SetInsertPoint(insert_point);
	}

	IRBuilder::~IRBuilder() = default;

	void IRBuilder::SetInsertPoint(Instruction* _insert_point)
	{
		insert_point = _insert_point;
		insert_block = _insert_point->GetParent();
	}

	void IRBuilder::SetInsertPoint(BasicBlock* _insert_block)
	{
		insert_block = _insert_block;
		insert_point = nullptr;
	}

	void IRBuilder::Insert(Instruction* instruction)
	{
		insert_block->GetInstructions().Insert(instruction, insert_point);
	}

	void IRBuilder::Insert(Value* V)
	{
		if (Instruction* I = dyn_cast<Instruction>(V)) return Insert(I);
	}

	void IRBuilder::InsertAfter(Instruction* instruction)
	{
		insert_block->GetInstructions().InsertAfter(instruction, insert_point);
	}

	void IRBuilder::InsertAfter(Value* V)
	{
		if (Instruction* I = dyn_cast<Instruction>(V)) return InsertAfter(I);
	}

}

