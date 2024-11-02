#include "MachineOperand.h"


namespace ola
{
	Uint64 MachineOperand::GetHash() const
	{
		return std::hash<decltype(storage)>{}(storage);
	}

}
