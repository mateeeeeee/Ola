#pragma once
#include "PrinterBase.h"

namespace ola
{
	class CFG;

	class CFGPrinter final : public PrinterBase
	{
	public:
		CFGPrinter() { }
		void Print(Function const*, CFG const&);

	private:
		void PrintFunction(Function const*, CFG const&);
	};
}

