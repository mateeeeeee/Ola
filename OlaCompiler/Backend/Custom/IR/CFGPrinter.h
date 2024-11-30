#pragma once
#include "IRModulePrinter.h"

namespace ola
{
	class CFGPrinter final : public IRModulePrinter
	{
	public:
		CFGPrinter() { }
		virtual void PrintModule(IRModule const& M) override;

	private:
		void PrintCFGPreamble(std::string_view function_name);
		void PrintFunction(Function const*);
	};
}

