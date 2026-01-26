#pragma once
#include "Backend/Custom/Codegen/Targets/Target.h"

namespace ola
{
	class X86TargetISelInfo : public TargetISelInfo
	{
	public:
		virtual Bool LowerInstruction(Instruction* I, MachineContext& ctx) const override;
		virtual void LegalizeInstruction(InstLegalizeContext& legalize_ctx, MachineContext& lowering_ctx) const override;
		virtual void PostLegalizeInstruction(InstLegalizeContext& legalize_ctx) const override;
	};
}
