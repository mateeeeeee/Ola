#pragma once
#include <list>
#include <unordered_set>
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
			successors.insert(MBB);
			MBB->predecessors.insert(this);
		}
		void AddPredecessor(MachineBasicBlock* MBB)
		{
			predecessors.insert(MBB);
			MBB->successors.insert(this);
		}
		std::unordered_set<MachineBasicBlock*> const& Predecessors() const { return predecessors; }
		std::unordered_set<MachineBasicBlock*> const& Successors() const { return successors; }

		virtual RelocableKind GetRelocableKind() const override
		{
			return RelocableKind::Block;
		}

	private:
		MachineFunction* function;
		std::list<MachineInstruction> instructions;
		std::unordered_set<MachineBasicBlock*> successors;
		std::unordered_set<MachineBasicBlock*> predecessors;
	};
}