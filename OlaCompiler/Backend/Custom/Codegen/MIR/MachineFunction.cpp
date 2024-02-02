#include "MachineFunction.h"
#include "MachineBasicBlock.h"
#include "Backend/Custom/IR/Values/GlobalValue.h"

namespace ola
{

	MachineFunction::~MachineFunction()
	{

	}
	std::string_view MachineFunction::GetName() const
	{
		return func.GetName();
	}
	uint32 MachineFunction::Size() const
	{
		return (uint32)basic_blocks.Size();
	}

}


