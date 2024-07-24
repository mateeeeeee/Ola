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
		MIRGlobal const* global = ctx.GetGlobal(callee);

		static constexpr uint32 PASS_BY_REG_OFFSET = 1 << 16;
		std::vector<int32> offsets;  
		uint32 const arg_count = CI->ArgSize();
		offsets.reserve(arg_count);
		uint32 gprs = 0;
		uint32 current_stack_offset = 0;
		for (auto& arg : CI->Args())
		{
			if (!arg.GetValue()->GetType()->IsFloat())
			{
				if (gprs < 4)
				{
					offsets.push_back(PASS_BY_REG_OFFSET + gprs++);
				}
			}
			else
			{
				OLA_ASSERT_MSG(false, "floating point arguments not implemented yet");
			}

			uint32 size = arg.GetValue()->GetType()->GetSize();
			uint32 alignment = size;

			current_stack_offset = (current_stack_offset + alignment - 1) / alignment * alignment;
			offsets.push_back(current_stack_offset);
			current_stack_offset += size;
		}

		MIRGlobal* caller_global = ctx.GetGlobal(CI->GetCaller());
		MIRFunction& caller = *static_cast<MIRFunction*>(global->GetRelocable());

		for (uint32 idx = 0; idx < arg_count; ++idx)
		{
			int32 offset = offsets[idx];
			Value const* arg = CI->GetArgOp(idx);
			MIROperand arg_operand = ctx.GetOperand(arg);
			uint32 size = arg->GetType()->GetSize();
			uint32 alignment = size;
			if (offset < PASS_BY_REG_OFFSET)
			{
			}
			else
			{
			}
		}
		MIRInstruction call_inst(InstCall);
		call_inst.SetOp<0>(MIROperand::Relocable(global->GetRelocable()));
		ctx.EmitInst(call_inst);
		IRType const* return_type = CI->GetType();
		if (return_type->IsVoid()) return;

		const auto return_reg = ctx.VirtualReg(return_type);
		MIROperand arch_return_reg;
		if (return_type->IsFloat()) 
		{
			arch_return_reg = MIROperand::ISAReg(x64::XMM0, MIROperandType::Float64);
		}
		else 
		{
			arch_return_reg = MIROperand::ISAReg(x64::RAX, MIROperandType::Int64);
		}
		ctx.EmitInst(MIRInstruction(InstLoad).SetOp<0>(return_reg).SetOp<1>(arch_return_reg));
		ctx.AddOperand(CI, return_reg);
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
				if (V->GetType()->IsFloat())
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

