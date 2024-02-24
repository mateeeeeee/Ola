#include "IRModule.h"
#include "IR.h"
#include "IRType.h"
#include <fstream>

namespace ola
{

	IRModule::IRModule(IRContext& context, std::string_view module_id) : context(context), module_id(module_id)
	{
	}

	IRModule::~IRModule()
	{
	}

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
		std::ofstream ola_ir_stream(filename.data());
		for (auto const& ir_function : functions)
		{
			for (auto const& BB : ir_function)
			{
				ola_ir_stream << "BasicBlock:" << BB.GetName() << ":\n";
				for (auto inst_iterator = BB.begin(); inst_iterator != BB.end(); ++inst_iterator)
				{
					Instruction const* inst = inst_iterator;
					if (AllocaInst const* alloca_inst = dyn_cast<AllocaInst>(inst))
					{
						ola_ir_stream << "AllocaInst\n";
					}
					else if (StoreInst const* store_inst = dyn_cast<StoreInst>(inst))
					{
						ola_ir_stream << "StoreInst\n";
					}
					else if (ReturnInst const* ret_inst = dyn_cast<ReturnInst>(inst))
					{
						ola_ir_stream << "ReturnInst\n";
					}
					else if (BranchInst const* ret_inst = dyn_cast<BranchInst>(inst))
					{
						ola_ir_stream << "BranchInst\n";
					}
				}
			}
		}
	}

}

