#include "IR.h"
#include "IRModule.h"
#include "Compiler/RTTI.h"

namespace ola
{

	void Value::ReplaceAllUseWith(Value* v)
	{
		//while (uses.head) uses.head->Set(v);
	}

	uint64 Value::GetUseCount() const
	{
		uint64 use_count = 0;
		//while (uses.head) ++use_count;
		return use_count;
	}

	const Instruction* BasicBlock::GetTerminator() const
	{
		if (inst_list.empty() || !inst_list.back()->IsTerminator())
			return nullptr;
		return inst_list.back();
	}

	void BasicBlock::InsertInto(IRFunction* parent, BasicBlock* insert_before)
	{
		if (insert_before)
		{
			parent->InsertBefore(this, insert_before);
		}
		else
		{
			parent->Insert(this);
		}
	}

	IRFunction const* Instruction::GetFunction() const
	{
		return GetParent()->GetParent();
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

