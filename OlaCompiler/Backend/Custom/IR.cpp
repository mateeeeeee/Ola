#include "IR.h"
#include "IRModule.h"
#include "Compiler/RTTI.h"

namespace ola
{

	void Value::ReplaceAllUseWith(Value* v)
	{
		for (auto& use : uses) use.Set(v);
	}

	Function::Function(IRModule& module, IRType* func_type, Linkage linkage, std::string_view name) : Value(ValueKind::Function, func_type), module(module)
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
	Function const* Instruction::GetFunction() const
	{
		return GetParent()->GetParent();
	}
	FunctionType* Function::GetFunctionType() const
	{
		return cast<FunctionType>(GetType());
	}

	GlobalVariable::GlobalVariable(IRModule& module, PointerType* type, std::string_view name, Linkage linkage, Value* init) : Value(ValueKind::GlobalVariable, type), module(module),
		name(name), linkage(linkage), init(init), allocated_type(type->GetPointeeType())
	{
		module.AddVariable(this);
	}
	GlobalVariable::~GlobalVariable()
	{
		module.RemoveVariable(this);
	}

	Instruction const* BasicBlock::GetTerminator() const
	{
		if (inst_list.Empty() || !inst_list.end()->IsTerminator()) return nullptr;
		return &inst_list.Back();
	}

	void BasicBlock::InsertInto(Function* parent, BasicBlock* insert_before)
	{
		if (insert_before) parent->InsertBefore(this, insert_before);
		else parent->Insert(this);
	}

}

