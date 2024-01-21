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

	IRFunction::IRFunction(IRModule& module, IRType* func_type, Linkage linkage, std::string_view name /*= ""*/) : Value(ValueKind::Function, func_type), module(module)
	{
		SetName(name);
		module.AddFunction(this);
	}
	IRFunction::~IRFunction()
	{
		RemoveFromParent();
	}
	void IRFunction::RemoveFromParent()
	{
		module.RemoveFunction(this);
	}
	uint64 IRFunction::GetInstructionCount() const
	{
		uint64 instruction_count = 0;
		for (auto const& bb : block_list) instruction_count += bb.Size();
		return instruction_count;
	}
	IRFunction const* Instruction::GetFunction() const
	{
		return GetParent()->GetParent();
	}
	FunctionType* IRFunction::GetFunctionType() const
	{
		return nullptr; // cast<FunctionType>(GetType());
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
		if (inst_list.empty() || !inst_list.end()->IsTerminator()) return nullptr;
		return &inst_list.back();
	}

	void BasicBlock::InsertInto(IRFunction* parent, BasicBlock* insert_before)
	{
		if (insert_before) parent->InsertBefore(this, insert_before);
		else parent->Insert(this);
	}

}

