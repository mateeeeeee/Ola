#pragma once
#include <list>
#include "MIRInstruction.h"

namespace ola
{
	class MIRFunction;
	class MIRBasicBlock
	{
	public:
		MIRBasicBlock(MIRFunction* function, std::string_view label) : function(function), label(label)
		{}

		MIRFunction* GetFunction() const 
		{
			return function;
		}
		std::string_view GetLabel() const
		{
			return label;
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
		std::string label;
		std::vector<MIRBasicBlock*> successors;
		std::vector<MIRBasicBlock*> predecessors;
	};
}