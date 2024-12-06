#pragma once
#include "PrinterBase.h"

namespace ola
{
	class IRPrinter final : public PrinterBase
	{
	public:
		explicit IRPrinter(std::ostream& os) : os(os) {}
		void PrintModule(IRModule const& M);

	private:
		std::ostream& os;
	};
}

