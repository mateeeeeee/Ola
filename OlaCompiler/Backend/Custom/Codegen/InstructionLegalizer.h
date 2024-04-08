#pragma once
#include <unordered_map>
#include <unordered_set>
#include <list>
#include "MIROperand.h"

namespace ola
{
	class MIRModule;
	class MIRFunction;
    class MIRInstruction;
	class MIRBasicBlock;

	class InstructionLegalizer
	{
	public:
		explicit InstructionLegalizer(MIRModule& module) : module(module), current_block(nullptr) {}
		virtual void Run(MIRFunction& func) = 0;

	protected:
		MIRModule& module;
		MIRBasicBlock* current_block;
	};
}