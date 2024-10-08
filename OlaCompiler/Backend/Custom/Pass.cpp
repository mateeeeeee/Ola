#include "Pass.h"
#include "PassRegistry.h"

namespace ola
{

	std::string_view Pass::GetPassName() const
	{
		return g_PassRegistry.GetInfo(ID)->GetName();
	}
}
