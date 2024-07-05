#include "MIROperand.h"


namespace ola
{
	uint64 MIROperand::GetHash() const
	{
		return std::hash<decltype(storage)>{}(storage);
	}

}
