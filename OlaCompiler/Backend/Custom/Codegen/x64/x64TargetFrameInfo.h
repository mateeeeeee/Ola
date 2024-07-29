#include "Backend/Custom/Codegen/Target.h"

namespace ola
{
	class x64TargetFrameInfo : public TargetFrameInfo
	{
	public:
		virtual void EmitCall(CallInst* CI, LoweringContext& ctx) const override;
		virtual void EmitPrologue(MachineFunction& MF, LoweringContext& ctx) const override;
		virtual void EmitEpilogue(MachineFunction& MF, LoweringContext& ctx) const override;
		virtual void EmitReturn(ReturnInst* RI, LoweringContext& ctx) const override;
	};
}