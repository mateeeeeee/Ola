#include <fstream>
#include "MachineModule.h"
#include "MIR/MIR.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/Values/GlobalValue.h"

namespace ola
{
	void operator<<(std::ostream& os, MachineResult const& res)
	{
		os << res.no_segment << "\n";
		os << res.rodata_segment << "\n";
		os << res.bss_segment << "\n";
		os << res.data_segment << "\n";
		os << res.text_segment << "\nend\n";
	}

	MachineModule::MachineModule(IRModule& ir_module) : global_variables(ir_module.GetVariableList())
	{
		for (auto const& ir_function : ir_module.GetFunctionList())
		{
			functions.PushBack(new MachineFunction(ir_function, functions.Size()));
		}
	}

	void MachineModule::Print(std::ofstream& of)
	{
		of << result;
	}

}

