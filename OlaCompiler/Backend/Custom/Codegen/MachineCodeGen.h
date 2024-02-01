#pragma once
#include <memory>
#include <string>

namespace ola
{
	class IRModule;
	class MachineModule;

	enum class MachineArch
	{
		x86,
		x64,
		Unknown
	};
	class MachineCodeGen
	{
	public:
		MachineCodeGen(MachineArch arch, IRModule& module);
		~MachineCodeGen();

		void Generate(std::string_view output_file);

	private:
		std::unique_ptr<MachineModule> mach_module;
	};
}