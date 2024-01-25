#include "GlobalValue.h"
#include "BasicBlock.h"
#include "Backend/Custom/IRModule.h"

namespace ola
{
	Function::Function(IRModule& module, IRType* func_type, Linkage linkage, std::string_view name) : Value(ValueKind_Function, func_type), module(module)
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

	GlobalVariable::GlobalVariable(IRModule& module, PointerType* type, std::string_view name, Linkage linkage, Value* init) : Value(ValueKind_GlobalVariable, type), module(module),
		name(name), linkage(linkage), init(init), allocated_type(type->GetPointeeType())
	{
		module.AddVariable(this);
	}
	GlobalVariable::~GlobalVariable()
	{
		module.RemoveVariable(this);
	}

}

