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


	private:
		MIRFunction* function;
		std::list<MIRInstruction> instructions;
		std::string label;
	};
}