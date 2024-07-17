#pragma once
#include <iosfwd>

namespace ola
{
	class IRModule;
	class GlobalVariable;
	class Function;

	class IRWriter
	{
	public:
		explicit IRWriter(std::ostream& os);
		void PrintModule(IRModule const&);

	private:
		std::ostream& os;

	private:
		void PrintGlobalVariable(GlobalVariable const*);
		void PrintFunction(Function const*);
	};
}