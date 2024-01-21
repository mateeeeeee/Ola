#include "IR.h"
#include "IRModule.h"
#include "Compiler/RTTI.h"

namespace ola
{

	void Value::ReplaceAllUseWith(Value* v)
	{
		for (auto& use : uses) use.Set(v);
	}

	uint64 Value::GetUseCount() const
	{
		return uses.size();
	}

	Instruction const* BasicBlock::GetTerminator() const
	{
		if (inst_list.empty() || !inst_list.end()->IsTerminator()) return nullptr;
		return &inst_list.back();
	}

	void BasicBlock::InsertInto(IRFunction* parent, BasicBlock* insert_before)
	{
		if (insert_before) parent->InsertBefore(this, insert_before);
		else parent->Insert(this);
	}

	IRFunction const* Instruction::GetFunction() const
	{
		return GetParent()->GetParent();
	}

	uint64 IRFunction::GetInstructionCount() const
	{
		uint64 instruction_count = 0;
		for (auto const& bb : block_list) instruction_count += bb.Size();
		return instruction_count;
	}

	FunctionType* IRFunction::GetFunctionType() const
	{
		return nullptr; // cast<FunctionType>(GetType());
	}

	void IRFunction::RemoveFromParent()
	{
		OLA_ASSERT(module);
		module->RemoveFunction(this);
	}

}

