#include <fstream>
#include "MachineCodeGen.h"
#include "MachineModule.h"
#include "x64/x64MachineModule.h"

namespace ola
{

	MachineCodeGen::MachineCodeGen(MachineArch arch, IRModule& module)
	{
		switch (arch)
		{
		case MachineArch::x64: mach_module = std::make_unique<x64MachineModule>(module); break;
		case MachineArch::x86:
		case MachineArch::Unknown:
		default:
			OLA_ASSERT_MSG(false, "Unsupported architecture!");
		}
	}

	MachineCodeGen::~MachineCodeGen()
	{

	}

	void MachineCodeGen::Generate(std::string_view output_file)
	{
		OLA_ASSERT(mach_module != nullptr);
		mach_module->Emit();
		std::ofstream output_stream(output_file.data());
		mach_module->Print(output_stream);
	}

}
