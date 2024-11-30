#pragma once
#include "IRModulePrinter.h"

namespace ola
{
	class IRPrinter final : public IRModulePrinter
	{
	public:
		explicit IRPrinter(std::ostream& os) : os(os) {}
		virtual void PrintModule(IRModule const& M) override;

	private:
		std::ostream& os;
	};
}

