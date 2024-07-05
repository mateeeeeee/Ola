#include "MIRGlobal.h"
#include "MIRBasicBlock.h"

namespace ola
{

	MIRFunction::MIRFunction(std::string_view symbol) : MIRRelocable(symbol)
	{
	}

	MIRFunction::~MIRFunction() = default;
}

