#include <ostream>
#include "IRPrinter.h"
#include "IRModule.h"
#include "GlobalValue.h"

namespace ola
{
	void IRPrinter::PrintModule(IRModule const& M)
	{
		std::vector<GlobalValue*> const& globals = M.Globals();

		for (GlobalValue const* global : globals)
		{
			if (GlobalVariable const* GV = dyn_cast<GlobalVariable>(global))
			{
				os << "\n";
				PrintGlobalVariable(GV);
				os << "\n";
			}
			else if (Function const* F = dyn_cast<Function>(global))
			{
				os << "\n";
				PrintFunction(F);
				os << "\n";
			}
		}
	}

	void IRPrinter::PrintGlobalVariable(GlobalVariable const* GV)
	{

	}

	void IRPrinter::PrintFunction(Function const* F)
	{
		if (F->IsDeclaration())
		{

		}
	}

}

