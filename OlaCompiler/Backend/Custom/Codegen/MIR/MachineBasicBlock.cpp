#include "MachineBasicBlock.h"
#include "MachineInst.h"
#include "MachineFunction.h"
#include "Backend/Custom/IR/Values/BasicBlock.h"

namespace ola
{
	MachineBasicBlock::MachineBasicBlock(MachineFunction& mf, const BasicBlock* bb) : bb(bb), number(-1), parent(&mf)
	{
	}
	MachineBasicBlock::MachineBasicBlock() = default;
	MachineBasicBlock::~MachineBasicBlock() = default;

	uint32 MachineBasicBlock::Size() const
	{
		return (uint32)instructions.Size();
	}
}

