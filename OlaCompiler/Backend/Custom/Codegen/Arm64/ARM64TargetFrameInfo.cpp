#include "ARM64TargetFrameInfo.h"

namespace ola
{
	void ARM64TargetFrameInfo::EmitCall(CallInst* CI, MachineContext& ctx) const
	{
		OLA_ASSERT_MSG(false, "ARM64 EmitCall not yet implemented!");
	}

	void ARM64TargetFrameInfo::EmitPrologue(MachineFunction& MF, MachineContext& ctx) const
	{
		OLA_ASSERT_MSG(false, "ARM64 EmitPrologue not yet implemented!");
	}

	void ARM64TargetFrameInfo::EmitProloguePostRA(MachineFunction& MF, MachineContext& ctx) const
	{
		OLA_ASSERT_MSG(false, "ARM64 EmitProloguePostRA not yet implemented!");
	}

	void ARM64TargetFrameInfo::EmitEpilogue(MachineFunction& MF, MachineContext& ctx) const
	{
		OLA_ASSERT_MSG(false, "ARM64 EmitEpilogue not yet implemented!");
	}

	void ARM64TargetFrameInfo::EmitEpiloguePostRA(MachineFunction& MF, MachineContext& ctx) const
	{
		OLA_ASSERT_MSG(false, "ARM64 EmitEpiloguePostRA not yet implemented!");
	}

	void ARM64TargetFrameInfo::EmitReturn(ReturnInst* RI, MachineContext& ctx) const
	{
		OLA_ASSERT_MSG(false, "ARM64 EmitReturn not yet implemented!");
	}
}
