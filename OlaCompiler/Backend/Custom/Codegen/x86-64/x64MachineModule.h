#pragma once
#include "Backend/Custom/Codegen/MachineModule.h"

namespace ola
{
	class MachineBasicBlock;
	class MachineInst;

	class x64MachineModule : public MachineModule
	{
	public:
		explicit x64MachineModule(IRModule& ir_module);

		virtual void Emit() override;

	private:
		void EmitGlobalVariables();
		void EmitFunction(MachineFunction&);
		void EmitBasicBlock(MachineBasicBlock&);
		void EmitInstruction(MachineInst&);

		std::string GetOperandAsString(MachineOperand const&);
	};
}