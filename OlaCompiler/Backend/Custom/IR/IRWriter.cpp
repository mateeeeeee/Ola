#include <ostream>
#include "IRWriter.h"
#include "IRModule.h"
#include "GlobalValue.h"

namespace ola
{

	IRWriter::IRWriter(std::ostream& os) : os(os)
	{
	}

	void IRWriter::PrintModule(IRModule const& M)
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

	void IRWriter::PrintGlobalVariable(GlobalVariable const* GV)
	{

	}

	void IRWriter::PrintFunction(Function const* F)
	{
		
	}

}

