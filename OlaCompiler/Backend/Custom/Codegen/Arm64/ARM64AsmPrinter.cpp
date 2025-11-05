#include "ARM64AsmPrinter.h"
#include "Backend/Custom/Codegen/MachineModule.h"

namespace ola
{
	void ARM64AsmPrinter::PrintModule(MachineModule const& M)
	{
		OLA_ASSERT_MSG(false, "ARM64 PrintModule not yet implemented!");
	}

	std::string ARM64AsmPrinter::GetFPConstantPoolEntry(Int64 value)
	{
		OLA_ASSERT_MSG(false, "ARM64 GetFPConstantPoolEntry not yet implemented!");
		return "";
	}

	std::string ARM64AsmPrinter::GetIntConstantPoolEntry(Int64 value)
	{
		OLA_ASSERT_MSG(false, "ARM64 GetIntConstantPoolEntry not yet implemented!");
		return "";
	}
}
