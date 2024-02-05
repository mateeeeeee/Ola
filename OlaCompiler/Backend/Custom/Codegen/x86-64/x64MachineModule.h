#pragma once
#include "Backend/Custom/Codegen/MachineModule.h"

namespace ola
{
	class IRModule;
	class x64MachineModule : public MachineModule
	{
	public:
		explicit x64MachineModule(IRModule& ir_module) : MachineModule(ir_module)
		{
			EmitLn<MachineSegment::Text>(".text");
			EmitLn<MachineSegment::Data>(".data");
			EmitLn<MachineSegment::Const>(".rodata");
			EmitLn<MachineSegment::BSS>(".bss");
		}

		virtual void Emit() override
		{

		}
	};
}