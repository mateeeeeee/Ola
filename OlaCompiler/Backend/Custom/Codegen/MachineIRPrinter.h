#pragma once
#include <iosfwd>
#include <string>
#include <format>

namespace ola
{
	class Target;
	class MachineModule;
	class MachineGlobal;
	class MachineBasicBlock;
	class MachineInstruction;
	class MachineOperand;

	class MachineIRPrinter
	{
	public:
		explicit MachineIRPrinter(Target const& target, std::ostream& os) : target(target), os(os) {}
		void PrintModule(MachineModule const& M);

	private:
		Target const& target;
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
		void PrintOperand(MachineOperand const&);
	};

}

