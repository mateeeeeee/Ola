#include "GlobalValue.h"

namespace ola
{

	Function::Function(std::string_view name, IRFuncType* type, Linkage linkage) : GlobalValue(name, type, linkage)
	{
		IRFuncType* function_type = GetFunctionType();
		arguments.resize(function_type->GetParamCount());
		for (Uint32 i = 0; i < arguments.size(); ++i)
		{
			arguments[i] = new Argument(function_type->GetParamType(i), i);
		}
	}

	Function::~Function()
	{
		arguments.clear();
	}

	Uint64 Function::GetInstructionCount() const
	{
		Uint64 instruction_count = 0;
		for (auto const& bb : block_list) instruction_count += bb.Instructions().Size();
		return instruction_count;
	}

	IRFuncType* Function::GetFunctionType() const
	{
		return cast<IRFuncType>(GetValueType());
	}

	void Function::Insert(BasicBlock* BB)
	{
		block_list.PushBack(BB);
	}

	void Function::InsertBefore(BasicBlock* BB, BasicBlock* before)
	{
		block_list.Insert(before->GetIterator(), BB);
	}

	Uint64 Function::Size() const
	{
		return block_list.Size();
	}

	Bool Function::HasCallInstruction() const
	{
		for (BasicBlock const& bb : block_list)
		{
			for (Instruction const& I : bb)
			{
				if (I.GetOpcode() == Opcode::Call)
				{
					return true;
				}
			}
		}
		return false;
	}

}

