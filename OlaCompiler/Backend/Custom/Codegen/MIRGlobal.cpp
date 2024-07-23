#include "MIRGlobal.h"
#include "MIRBasicBlock.h"

namespace ola
{

	MIRFunction::MIRFunction(std::string_view symbol, bool is_declaration) : MIRRelocable(symbol), is_declaration(is_declaration)
	{
	}

	MIRFunction::~MIRFunction() = default;
}

