#include "MachineOperand.h"


namespace ola
{
	uint64 MachineOperand::GetHash() const
	{
		return std::hash<decltype(storage)>{}(storage);
	}

}
