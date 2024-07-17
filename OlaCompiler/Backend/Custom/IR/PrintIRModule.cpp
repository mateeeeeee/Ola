#include <ostream>
#include "PrintIRModule.h"
#include "IRModule.h"
#include "GlobalValue.h"

namespace ola
{
	namespace
	{
		void PrintGlobalVariable(GlobalVariable const* GV)
		{

		}

		void PrintFunction(Function const* F)
		{

		}
	}

	void PrintIRModule(std::ostream& os, IRModule const& M)
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

}

