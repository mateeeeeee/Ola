#include <ostream>
#include "IRPrinter.h"
#include "IRModule.h"
#include "GlobalValue.h"

namespace ola
{
	void IRPrinter::PrintModule(IRModule const& M)
	{
		std::string_view module_id = M.GetModuleId();
		EmitLn("Module ID : {}", module_id);

		std::vector<GlobalValue*> const& globals = M.Globals();
		for (GlobalValue const* global : globals)
		{
			if (GlobalVariable const* GV = dyn_cast<GlobalVariable>(global))
			{
				EmitLn("");
				PrintGlobalVariable(GV);
				EmitLn("");
			}
			else if (Function const* F = dyn_cast<Function>(global))
			{
				name_manager.ClearLocals();
				EmitLn("");
				PrintFunction(F);
				EmitLn("");
			}
		}
		os << output;
	}

}

