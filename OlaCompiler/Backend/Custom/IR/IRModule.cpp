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
				ola_ir_stream << "\nBB_" << BB.GetName() << ":\n";
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
					else if (LoadInst const* load_inst = dyn_cast<LoadInst>(inst))
					{
						ola_ir_stream << "LoadInst\n";
					}
					else if (ReturnInst const* ret_inst = dyn_cast<ReturnInst>(inst))
					{
						ola_ir_stream << "ReturnInst\n";
					}
					else if (BranchInst const* branch = dyn_cast<BranchInst>(inst))
					{
						auto BB = branch->GetIfTrueDestination();
						ola_ir_stream << "BranchInst to:" << BB->GetName() << "\n";
					}
					else if (BinaryOperator const* binary_op = dyn_cast<BinaryOperator>(inst))
					{
						ola_ir_stream << "BinaryOperator" << "\n";
					}
					else if (UnaryOperator const* unary_op = dyn_cast<UnaryOperator>(inst))
					{
						ola_ir_stream << "UnaryOperator" << "\n";
					}
				}
			}
		}
	}

}

