#include "MachineInst.h"
#include "MachineOperand.h"
#include "MachineBasicBlock.h"

namespace ola
{

	MachineInst::MachineInst(MachineOpCode opcode) : opcode(opcode)
	{

	}

	MachineInst::~MachineInst()
	{

	}

	MachineFunction const* MachineInst::GetFunction() const
	{
		return parent->GetParent();
	}

	MachineFunction* MachineInst::GetFunction()
	{
		return parent->GetParent();
	}

	uint32 MachineInst::GetOpCount() const
	{
		return operands.size();
	}

	MachineOperand const& MachineInst::GetOperand(uint32 i) const
	{
		return operands[i];
	}

	MachineOperand& MachineInst::GetOperand(uint32 i)
	{
		return operands[i];
	}

	void MachineInst::AddOperand(MachineOperand const& op)
	{
		operands.push_back(op);
	}

}

