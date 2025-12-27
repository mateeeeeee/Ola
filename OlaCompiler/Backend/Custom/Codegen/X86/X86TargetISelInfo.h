#pragma once
#include "Backend/Custom/Codegen/Target.h"

namespace ola
{
	class x64TargetISelInfo : public TargetISelInfo
	{
	public:
		virtual Bool LowerInstruction(Instruction* I, MachineContext& ctx) const override;
		virtual void LegalizeInstruction(InstLegalizeContext& legalize_ctx, MachineContext& lowering_ctx) const override;
		virtual void PostLegalizeInstruction(InstLegalizeContext& legalize_ctx) const override;
	};
}
