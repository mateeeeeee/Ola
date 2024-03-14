#include "GlobalValue.h"
#include "BasicBlock.h"

namespace ola
{

	Function::Function(std::string_view name, IRFuncType* type, Linkage linkage) : GlobalValue(name, type, linkage)
	{
		IRFuncType* function_type = GetFunctionType();
		arguments.resize(function_type->GetParamCount());
		for (uint32 i = 0; i < arguments.size(); ++i)
		{
			arguments[i] = new Argument(function_type->GetParamType(i), i);
		}
	}

	Function::~Function()
	{
		for (uint32 i = 0; i < arguments.size(); ++i)
		{
			delete arguments[i];
		}
	}

	uint64 Function::GetInstructionCount() const
	{
		uint64 instruction_count = 0;
		for (auto const& bb : block_list) instruction_count += bb->Instructions().Size();
		return instruction_count;
	}

	IRFuncType* Function::GetFunctionType() const
	{
		return cast<IRFuncType>(GetValueType());
	}

	void Function::Insert(BasicBlock* BB)
	{
		block_list.push_back(BB);
	}

	void Function::InsertBefore(BasicBlock* BB, BasicBlock* before)
	{
		for (auto it = block_list.begin(); it != block_list.end(); ++it)
		{
			if (*it = before)
			{
				block_list.insert(it, BB);
				return;
			}
		}
		Insert(BB);
	}

	uint64 Function::Size() const
	{
		return block_list.size();
	}

}

