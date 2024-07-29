#pragma once
#include <list>
#include "MachineInstruction.h"
#include "MachineGlobal.h"

namespace ola
{
	class MachineFunction;
	class MachineBasicBlock : public MachineRelocable
	{
	public:
		MachineBasicBlock(MachineFunction* function, std::string_view label) : MachineRelocable(label), function(function)
		{}

		MachineFunction* GetFunction() const 
		{
			return function;
		}
		std::list<MachineInstruction>& Instructions()
		{
			return instructions;
		}
		std::list<MachineInstruction> const& Instructions() const
		{
			return instructions;
		}

		void AddSuccessor(MachineBasicBlock* MBB)
		{
			successors.push_back(MBB);
		}
		void AddPredecessor(MachineBasicBlock* MBB)
		{
			predecessors.push_back(MBB);
		}
		std::vector<MachineBasicBlock*> const& Predecessors() const { return predecessors; }
		std::vector<MachineBasicBlock*> const& Successors() const { return successors; }

		virtual RelocableKind GetRelocableKind() const override
		{
			return RelocableKind::Block;
		}

	private:
		MachineFunction* function;
		std::list<MachineInstruction> instructions;
		std::vector<MachineBasicBlock*> successors;
		std::vector<MachineBasicBlock*> predecessors;
	};
}