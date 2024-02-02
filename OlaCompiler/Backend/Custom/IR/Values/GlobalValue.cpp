#include "GlobalValue.h"
#include "BasicBlock.h"
#include "Backend/Custom/IR/IRModule.h"

namespace ola
{
	Function::Function(IRFuncType* func_type, IRModule& module, Linkage linkage, std::string_view name)
		: GlobalValue(ValueKind_Function, func_type, module, linkage)
	{
		SetName(name);

		IRFuncType* function_type = GetFunctionType();
		arguments.resize(function_type->GetParamCount());
		for (uint32 i = 0; i < arguments.size(); ++i)
		{
			arguments[i] = new Argument(function_type->GetParamType(i), i);
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
	void Function::Insert(BasicBlock* bb)
	{
		block_list.PushBack(bb);
	}
	void Function::InsertBefore(BasicBlock* bb, BasicBlock* before)
	{
		block_list.Insert(before, bb);
	}
	uint64 Function::Size() const
	{
		return block_list.Size();
	}
	uint64 Function::GetInstructionCount() const
	{
		uint64 instruction_count = 0;
		for (auto const& bb : block_list) instruction_count += bb.Size();
		return instruction_count;
	}
	IRFuncType* Function::GetFunctionType() const
	{
		return cast<IRFuncType>(GetType());
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
