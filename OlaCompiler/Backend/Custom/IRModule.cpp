#include "IRModule.h"
#include "IR.h"
#include "IRType.h"

namespace ola
{

	void IRModule::AddVariable(GlobalVariable* gvar)
	{
		variables.InsertAtEnd(gvar);
	}

	void IRModule::RemoveVariable(GlobalVariable* gvar)
	{
		variables.Remove(gvar);
	}

	void IRModule::AddFunction(IRFunction* func)
	{
		functions.InsertAtEnd(func);
	}

	void IRModule::RemoveFunction(IRFunction* func)
	{
		functions.Remove(func);
	}

	IList<GlobalVariable> const& IRModule::GetVariableList() const
	{
		return variables;
	}

	IList<IRFunction> const& IRModule::GetFunctionList() const
	{
		return functions;
	}

	void IRModule::PrintIR(std::string_view filename)
	{

	}

}

