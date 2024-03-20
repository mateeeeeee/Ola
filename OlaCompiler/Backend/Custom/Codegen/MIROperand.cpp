#include "MIROperand.h"


namespace ola
{
	ola::uint64 MIROperand::GetHash() const
	{
		return std::hash<decltype(storage)>{}(storage);
	}

}
