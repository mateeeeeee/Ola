#include <fstream>
#include "MachineModule.h"
#include "MIR/MIR.h"
#include "Backend/Custom/IR/IRModule.h"

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
	}

	void MachineModule::Print(std::ofstream& of)
	{
		of << result;
	}

}

