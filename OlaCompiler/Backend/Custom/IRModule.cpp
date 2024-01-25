#include "IRModule.h"
#include "IR.h"
#include "IRType.h"

namespace ola
{

	void IRModule::AddVariable(GlobalVariable* gvar)
	{
		variables.PushBack(gvar);
	}

	void IRModule::RemoveVariable(GlobalVariable* gvar)
	{
		variables.Remove(gvar);
	}

	void IRModule::AddFunction(Function* func)
	{
		functions.PushBack(func);
	}

	void IRModule::RemoveFunction(Function* func)
	{
		functions.Remove(func);
	}

	IList<GlobalVariable> const& IRModule::GetVariableList() const
	{
		return variables;
	}

	IList<Function> const& IRModule::GetFunctionList() const
	{
		return functions;
	}

	void IRModule::PrintIR(std::string_view filename)
	{

	}

}

