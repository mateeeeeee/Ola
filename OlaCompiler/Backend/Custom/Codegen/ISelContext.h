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

	class ISelContext
	{
		using MinstructionListIP = std::list<MIRInstruction>::iterator;

	public:
		explicit ISelContext(MIRModule& module) : module(module), current_block(nullptr) {}
		void Run(MIRFunction& func);

		std::unordered_map<MIROperand, uint32> GetDefCount(MIRFunction& func);

	private:
		MIRModule& module;
		MIRBasicBlock* current_block;
		MinstructionListIP current_ip;

		std::unordered_map<MIROperand, MIRInstruction*> instruction_mapping, constant_mapping;
		std::unordered_map<MIROperand, MIROperand> replace_list;
        std::unordered_set<MIRInstruction*> replace_block_list;
        std::unordered_map<MIROperand, uint32> use_count;

	private:
		MIROperand& GetInstDef(MIRInstruction& inst) const;
	};
}