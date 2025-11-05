#pragma once
#include "Backend/Custom/Codegen/Target.h"

namespace ola
{
	class ARM64TargetFrameInfo : public TargetFrameInfo
	{
	public:
		virtual void EmitCall(CallInst* CI, MachineContext& ctx) const override;
		virtual void EmitPrologue(MachineFunction& MF, MachineContext& ctx) const override;
		virtual void EmitProloguePostRA(MachineFunction& MF, MachineContext& ctx) const override;
		virtual void EmitEpilogue(MachineFunction& MF, MachineContext& ctx) const override;
		virtual void EmitEpiloguePostRA(MachineFunction& MF, MachineContext& ctx) const override;
		virtual void EmitReturn(ReturnInst* RI, MachineContext& ctx) const override;
	};
}
