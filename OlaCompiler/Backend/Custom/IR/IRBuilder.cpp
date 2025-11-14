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
		insert_point = current_block->end();
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

	BasicBlock* IRBuilder::AddBlock(std::string_view name)
	{
		return AddBlock(current_function, name);
	}


	BasicBlock* IRBuilder::AddBlock(Function* F, std::string_view name)
	{
		auto& blocks = F->Blocks();
		BasicBlock* block = new BasicBlock(ctx, F, blocks.Size());
		if (name.empty())
		{
			std::string label = "BB" + std::to_string(bb_label_counter++);
			block->SetName(label);
		}
		else
		{
			block->SetName(name);
		}
		blocks.PushBack(block);
		return block;
	}


	BasicBlock* IRBuilder::AddBlock(Function* F, BasicBlock* before, std::string_view name)
	{
		OLA_ASSERT(!before || before->GetFunction() == F);
		auto& blocks = F->Blocks();
		BasicBlock* block = new BasicBlock(ctx, F, blocks.Size());
		if (name.empty())
		{
			std::string label = "BB" + std::to_string(bb_label_counter++);
			block->SetName(label);
		}
		else
		{
			block->SetName(name);
		}

		if (before)
		{
			blocks.Insert(before->GetIterator(), block);
		}
		else
		{
			blocks.PushBack(block);
		}
		return block;
	}


	BasicBlock* IRBuilder::AddBlock(BasicBlock* before, std::string_view name)
	{
		return AddBlock(before ? before->GetFunction() : current_function, before, name);
	}

}

