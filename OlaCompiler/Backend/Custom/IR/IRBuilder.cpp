#include "IRBuilder.h"
#include "IRContext.h"
#include "BasicBlock.h"
#include "Instruction.h"
#include "GlobalValue.h"

namespace ola
{
	void IRBuilder::SetCurrentBlock(BasicBlock* BB)
	{
		OLA_ASSERT(BB != nullptr);
		current_block = BB;
		current_function = BB->GetFunction();
		insert_point = current_block->Instructions().end();
	}


	void IRBuilder::SetInsertPoint(BasicBlock* BB, IListIterator<Instruction> IP)
	{
		SetCurrentBlock(BB);
		insert_point = IP;
	}


	void IRBuilder::SetInsertPoint(BasicBlock* BB, Instruction* I)
	{
		OLA_ASSERT(BB == I->GetBasicBlock());
		SetInsertPoint(BB, I->GetIterator());
	}


	void IRBuilder::NextInsertPoint()
	{
		++insert_point;
	}


	BasicBlock* IRBuilder::AddBlock(char const* label)
	{
		auto& blocks = current_function->Blocks();
		BasicBlock* block = new BasicBlock(current_function, blocks.size());
		block->SetLabel(label);
		blocks.push_back(block);
		return block;
	}

}

