#include "MIRGlobal.h"
#include "MIRBasicBlock.h"

namespace ola
{

	MIRFunction::MIRFunction(std::string_view symbol, bool is_declaration) : MIRRelocable(symbol), is_declaration(is_declaration)
	{
		stack_objects.reserve(32);
	}

	MIRFunction::~MIRFunction() = default;
}

