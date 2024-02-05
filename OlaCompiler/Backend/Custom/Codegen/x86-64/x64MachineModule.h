#pragma once
#include "Backend/Custom/Codegen/MachineModule.h"

namespace ola
{

	class IRModule;
	class x64MachineModule : public MachineModule
	{
	public:
		explicit x64MachineModule(IRModule& ir_module);

		virtual void Emit() override;

	private:
		void EmitGlobalVariables();
	};
}