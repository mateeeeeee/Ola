#pragma once
#include <iosfwd>
#include <string>
#include <format>

namespace ola
{
	class MachineModule;
	class MachineGlobal;
	class MachineBasicBlock;
	class MachineInstruction;

	class MachineIRPrinter
	{
	public:
		explicit MachineIRPrinter(std::ostream& os) : os(os) {}
		void PrintModule(MachineModule const& M);

	private:
		std::ostream& os;
		std::string output;

	private:
		template<typename... Args>
		void EmitLn(Char const* fmt, Args&&... args)
		{
			output += std::vformat(fmt, std::make_format_args(args...));
			output += "\n";
		}
		template<typename... Args>
		void Emit(Char const* fmt, Args&&... args)
		{
			output += std::vformat(fmt, std::make_format_args(args...));
		}

		void PrintGlobalVariable(MachineGlobal const&);
		void PrintFunction(MachineGlobal const&);
		void PrintBlock(MachineBasicBlock const&);
		void PrintInstruction(MachineInstruction const&);
	};

}

