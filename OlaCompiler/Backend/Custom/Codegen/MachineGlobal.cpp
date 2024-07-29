#include "MachineGlobal.h"
#include "MachineBasicBlock.h"

namespace ola
{

	MachineFunction::MachineFunction(std::string_view symbol, bool is_declaration) : MachineRelocable(symbol), is_declaration(is_declaration)
	{
		stack_objects.reserve(32);
	}

	MachineFunction::~MachineFunction() = default;
}

