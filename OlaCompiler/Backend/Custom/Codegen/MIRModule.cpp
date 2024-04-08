#include "MIRModule.h"
#include "MIRGlobal.h"
#include "InstructionLegalizer.h"
#include "LinearScanRegisterAllocator.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	MIRModule::MIRModule(IRModule& ir_module) : lowering_pass(*this), ir_module(ir_module)
	{
	}

	void MIRModule::EmitMachineCode()
	{
		lowering_pass.RunOnModule(&ir_module);

		OLA_ASSERT(GetLegalizer());

		for (MIRGlobal& global : globals)
		{
			MIRRelocable* relocable = global.GetRelocable();
			if (relocable->IsFunction())
			{
				MIRFunction& MF = *dynamic_cast<MIRFunction*>(relocable);
				GetLegalizer()->Run(MF);

				LinearScanRegisterAllocator reg_allocator(*this);
				reg_allocator.AssignRegisters(MF);
			}
		}
	}

}