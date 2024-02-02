#pragma once
#include <memory>
#include <string>
#include "MIR/MachineArch.h"

namespace ola
{
	class IRModule;
	class MachineModule;

	class MachineCodeGen
	{
	public:
		MachineCodeGen(MachineArch arch, IRModule& module);
		~MachineCodeGen();

		void Generate(std::string_view output_file);

	private:
		std::unique_ptr<MachineModule> mach_module;
		MachineResult result;
	};
}