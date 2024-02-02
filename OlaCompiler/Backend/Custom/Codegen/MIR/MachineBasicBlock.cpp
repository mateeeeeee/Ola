#include "MachineBasicBlock.h"
#include "MachineInst.h"

namespace ola
{

	uint32 MachineBasicBlock::Size() const
	{
		return (uint32)instructions.Size();
	}

}

