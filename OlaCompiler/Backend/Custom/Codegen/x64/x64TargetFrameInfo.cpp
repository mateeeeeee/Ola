#include "x64.h"
#include "x64TargetFrameInfo.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/LoweringContext.h"
#include "Backend/Custom/Codegen/MIRInstruction.h"

namespace ola
{

	void x64TargetFrameInfo::EmitCall(CallInst* inst, LoweringContext& ctx) const
	{
		Function* callee = inst->GetCalleeAsFunction();
		OLA_ASSERT(callee);
	}

	void x64TargetFrameInfo::EmitPrologue(MIRFunction& func, LoweringContext& ctx) const
	{

	}

	void x64TargetFrameInfo::EmitReturn(ReturnInst* inst, LoweringContext& ctx) const
	{
		if (inst->GetNumOperands() > 0)
		{
			Value const* V = inst->GetOperand(0);
			uint32 const size = V->GetType()->GetSize();
			if (size <= 8)
			{
				MIROperand return_register;
				if (V->GetType()->IsFloatType())
				{
					return_register = MIROperand::ISAReg(x64::XMM0, MIROperandType::Float64);
				}
				else 
				{
					return_register = MIROperand::ISAReg(x64::RAX, MIROperandType::Int64);
				}

				MIRInstruction copy_instruction(InstMove);
				copy_instruction.SetOp<0>(return_register).SetOp<1>(ctx.GetOperand(V));
				ctx.EmitInst(copy_instruction);
			}
			else
			{
				OLA_ASSERT_MSG(false, "todo");
			}
		}
	}

}

