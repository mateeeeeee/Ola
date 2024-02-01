#include "BasicBlock.h"
#include "Instruction.h"
#include "GlobalValue.h"

namespace ola
{
	Instruction const* BasicBlock::GetTerminator() const
	{
		if (inst_list.Empty() || !inst_list.Back().IsTerminator()) return nullptr;
		return &inst_list.Back();
	}

	uint64 BasicBlock::Size() const
	{
		return inst_list.Size();
	}

	void BasicBlock::InsertInto(Function* parent, BasicBlock* insert_before)
	{
		if (insert_before) parent->InsertBefore(this, insert_before);
		else parent->Insert(this);
	}

}
