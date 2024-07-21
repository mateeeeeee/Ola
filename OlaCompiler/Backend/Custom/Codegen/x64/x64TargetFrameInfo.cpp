#include "x64.h"
#include "x64TargetFrameInfo.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/LoweringContext.h"
#include "Backend/Custom/Codegen/MIRInstruction.h"
#include "Backend/Custom/Codegen/MIRGlobal.h"

namespace ola
{

	void x64TargetFrameInfo::EmitCall(CallInst* CI, LoweringContext& ctx) const
	{
		Function* callee = CI->GetCalleeAsFunction();
		OLA_ASSERT(callee);
	}

	void x64TargetFrameInfo::EmitPrologue(MIRFunction& MF, LoweringContext& ctx) const
	{
		using enum MIROperandType;

		MIROperand rbp = MIROperand::ISAReg(x64::RBP, Int64);
		MIROperand rsp = MIROperand::ISAReg(x64::RSP, Int64);

		MIRInstruction push_rbp(InstPush);
		push_rbp.SetOp<0>(rbp);
		ctx.EmitInst(push_rbp);

		MIRInstruction set_rbp(InstStore);
		set_rbp.SetOp<0>(rbp).SetOp<1>(rsp);
		ctx.EmitInst(set_rbp);

		int32 stack_allocation = MF.GetStackAllocationSize();
		if (stack_allocation > 0)
		{
			MIRInstruction allocate_stack(InstSub);
			allocate_stack.SetOp<0>(rsp).SetOp<1>(MIROperand::Immediate(stack_allocation, Int64));
			ctx.EmitInst(allocate_stack);
		}
	}

	void x64TargetFrameInfo::EmitEpilogue(MIRFunction& MF, LoweringContext& ctx) const
	{
		using enum MIROperandType;

		MIROperand rbp = MIROperand::ISAReg(x64::RBP, Int64);
		MIROperand rsp = MIROperand::ISAReg(x64::RSP, Int64);

		MIRInstruction reset_rbp(InstStore);
		reset_rbp.SetOp<0>(rsp).SetOp<1>(rbp);
		ctx.EmitInst(reset_rbp);

		MIRInstruction pop_rbp(InstPop);
		pop_rbp.SetOp<0>(rbp);
		ctx.EmitInst(pop_rbp);
	}

	void x64TargetFrameInfo::EmitReturn(ReturnInst* RI, LoweringContext& ctx) const
	{
		if (RI->GetNumOperands() > 0)
		{
			Value const* V = RI->GetOperand(0);
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

				MIRInstruction copy_instruction(InstLoad);
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

