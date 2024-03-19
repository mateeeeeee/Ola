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

	BasicBlock* IRBuilder::AddBlock()
	{
		auto& blocks = current_function->Blocks();
		BasicBlock* block = new BasicBlock(current_function, blocks.Size());
		std::string label = "BB" + std::to_string(bb_label_counter++);
		block->SetLabel(label);
		blocks.PushBack(block);
		return block;
	}


	BasicBlock* IRBuilder::AddBlock(Function* F)
	{
		auto& blocks = F->Blocks();
		BasicBlock* block = new BasicBlock(F, blocks.Size());
		std::string label = "BB" + std::to_string(bb_label_counter++);
		block->SetLabel(label);
		blocks.PushBack(block);
		return block;
	}


	BasicBlock* IRBuilder::AddBlock(Function* F, BasicBlock* before)
	{
		OLA_ASSERT(before->GetFunction() == F);
		auto& blocks = F->Blocks();
		BasicBlock* block = new BasicBlock(F, blocks.Size());
		std::string label = "BB" + std::to_string(bb_label_counter++);
		block->SetLabel(label);
		blocks.Insert(before->GetIterator(), block);
		return block;
	}


	BasicBlock* IRBuilder::AddBlock(BasicBlock* before)
	{
		Function* F = before->GetFunction();
		auto& blocks = F->Blocks();
		BasicBlock* block = new BasicBlock(F, blocks.Size());
		std::string label = "BB" + std::to_string(bb_label_counter++);
		block->SetLabel(label);
		blocks.Insert(before->GetIterator(), block);
		return block;
	}

}

