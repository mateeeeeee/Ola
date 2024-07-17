#include "Backend/Custom/Codegen/Target.h"

namespace ola
{
	class x64TargetFrameInfo : public TargetFrameInfo
	{
	public:
		virtual void EmitCall(CallInst* inst, LoweringContext& ctx) const override;
		virtual void EmitPrologue(MIRFunction& func, LoweringContext& ctx) const override;
		virtual void EmitReturn(ReturnInst* inst, LoweringContext& ctx) const override;
	};
}