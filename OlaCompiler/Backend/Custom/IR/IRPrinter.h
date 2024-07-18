#pragma once
#include <iosfwd>

namespace ola
{
	class IRModule;
	class Function;
	class GlobalVariable;
	class IRPrinter
	{
	public:
		explicit IRPrinter(std::ostream& os) : os(os) {}
		void PrintModule(IRModule const& M);

	private:
		std::ostream& os;

	private:
		void PrintGlobalVariable(GlobalVariable const* GV);
		void PrintFunction(Function const* F);
	};
}