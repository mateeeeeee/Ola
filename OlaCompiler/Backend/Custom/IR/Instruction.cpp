#include "Instruction.h"
#include "GlobalValue.h"
#include "BasicBlock.h"

namespace ola
{

	Function const* Instruction::GetFunction() const
	{
		return GetParent()->GetParent();
	}

	IRModule& Instruction::GetModule() const
	{
		return GetFunction()->GetModule();
	}

	void Instruction::RemoveFromParent()
	{
		if (parent) parent->GetInstructions().Remove(this);
	}

	void Instruction::Insert(BasicBlock* bb)
	{
		bb->GetInstructions().PushBack(this);
		SetParent(bb);
	}

	void Instruction::Insert(BasicBlock* bb, Instruction* position)
	{
		bb->GetInstructions().Insert(position, this);
		SetParent(bb);
	}

	void Instruction::Insert(Instruction* position)
	{
		position->GetParent()->GetInstructions().Insert(position, this);
		SetParent(position->GetParent());
	}

	void Instruction::InsertAfter(BasicBlock* bb, Instruction* position)
	{
		bb->GetInstructions().InsertAfter(position, this);
		SetParent(bb);
	}

	void Instruction::InsertAfter(Instruction* position)
	{
		position->GetParent()->GetInstructions().InsertAfter(position, this);
		SetParent(position->GetParent());
	}

	void Instruction::SetParent(BasicBlock* bb)
	{
		if (parent) parent->GetInstructions().Remove(this);
		parent = bb;
	}

}

