#include "GlobalValue.h"
#include "BasicBlock.h"
#include "Backend/Custom/IRModule.h"

namespace ola
{
	Function::Function(FunctionType* func_type, IRModule& module, Linkage linkage, std::string_view name)
		: GlobalValue(ValueKind_Function, func_type, module, linkage)
	{
		SetName(name);

		FunctionType* function_type = GetFunctionType();
		arguments.resize(function_type->GetParamCount());
		for (uint32 i = 0; i < arguments.size(); ++i)
		{
			arguments[i] = new (module) Argument(function_type->GetParamType(i), i);
		}
		module.AddFunction(this);
	}
	Function::~Function()
	{
		for (uint32 i = 0; i < arguments.size(); ++i) delete arguments[i];
		RemoveFromParent();
	}
	void Function::RemoveFromParent()
	{
		module.RemoveFunction(this);
	}
	uint64 Function::GetInstructionCount() const
	{
		uint64 instruction_count = 0;
		for (auto const& bb : block_list) instruction_count += bb.Size();
		return instruction_count;
	}

	FunctionType* Function::GetFunctionType() const
	{
		return cast<FunctionType>(GetType());
	}

	GlobalVariable::GlobalVariable(IRType* type, IRModule& module, Linkage linkage, Value* init, std::string_view name)
		: GlobalValue(ValueKind_GlobalVariable, type, module, linkage), name(name), init(init)
	{
		module.AddVariable(this);
	}
	GlobalVariable::~GlobalVariable()
	{
		module.RemoveVariable(this);
	}
}
