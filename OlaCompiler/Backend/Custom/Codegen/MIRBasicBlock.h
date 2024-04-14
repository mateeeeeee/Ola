#pragma once
#include <list>
#include "MIRInstruction.h"
#include "MIRGlobal.h"

namespace ola
{
	class MIRFunction;
	class MIRBasicBlock : public MIRRelocable
	{
	public:
		MIRBasicBlock(MIRFunction* function, std::string_view label) : MIRRelocable(label), function(function)
		{}

		MIRFunction* GetFunction() const 
		{
			return function;
		}
		std::list<MIRInstruction>& Instructions()
		{
			return instructions;
		}
		std::list<MIRInstruction> const& Instructions() const
		{
			return instructions;
		}

		void AddSuccessor(MIRBasicBlock* MBB)
		{
			successors.push_back(MBB);
		}
		void AddPredecessor(MIRBasicBlock* MBB)
		{
			predecessors.push_back(MBB);
		}
		std::vector<MIRBasicBlock*> const& Predecessors() const { return predecessors; }
		std::vector<MIRBasicBlock*> const& Successors() const { return successors; }

	private:
		MIRFunction* function;
		std::list<MIRInstruction> instructions;
		std::vector<MIRBasicBlock*> successors;
		std::vector<MIRBasicBlock*> predecessors;
	};
}