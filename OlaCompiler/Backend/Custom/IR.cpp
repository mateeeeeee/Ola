#include "IR.h"
#include "IRModule.h"

namespace ola
{

	void Value::ReplaceAllUseWith(Value* v)
	{
		while (uses.head) uses.head->Set(v);
	}

	const Instruction* BasicBlock::GetTerminator() const
	{
		if (inst_list.empty() || !inst_list.back()->IsTerminator())
			return nullptr;
		return inst_list.back();
	}

	void BasicBlock::InsertInto(IRFunction* parent, BasicBlock* insert_before)
	{
		
	}

	IRFunction const* Instruction::GetFunction() const
	{
		return GetParent()->GetParent();
	}

	void IRFunction::RemoveFromParent()
	{
		OLA_ASSERT(module);
		module->RemoveFunction(this);
	}

}

