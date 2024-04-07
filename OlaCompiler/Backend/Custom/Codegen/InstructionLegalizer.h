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
		using MinstructionListIP = std::list<MIRInstruction>::iterator;

	public:
		explicit InstructionLegalizer(MIRModule& module) : module(module), current_block(nullptr) {}
		void Run(MIRFunction& func);

	private:
		MIRModule& module;
		MIRBasicBlock* current_block;
		MinstructionListIP current_ip;
	};
}