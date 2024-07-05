#pragma once

namespace ola
{
	class MIRModule;
	class MIRFunction;
    class MIRInstruction;
	class MIRBasicBlock;

	class LegalizeContext
	{
	public:
		explicit LegalizeContext(MIRModule& module) : module(module), current_block(nullptr) {}

	protected:
		MIRModule& module;
		MIRBasicBlock* current_block;
	};
}