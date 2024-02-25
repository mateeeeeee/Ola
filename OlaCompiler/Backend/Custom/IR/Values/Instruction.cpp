#include "Instruction.h"
#include "GlobalValue.h"
#include "BasicBlock.h"
#include "UnaryInstruction.h"
#include "BinaryInstruction.h"

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

	bool Instruction::IsTerminator() const
	{
		ValueKind kind = GetKind();
		return kind >= ValueKind_Call && kind <= ValueKind_Switch;
	}

	bool Instruction::IsUnaryOp() const
	{
		ValueKind kind = GetKind();
		return kind >= ValueKind_Neg && kind <= ValueKind_Not;
	}

	bool Instruction::IsBinaryOp() const
	{
		ValueKind kind = GetKind();
		return kind >= ValueKind_Add && kind <= ValueKind_Xor;
	}

	bool Instruction::IsCast() const
	{
		ValueKind kind = GetKind();
		return kind >= ValueKind_Zext && kind <= ValueKind_Sext;
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

