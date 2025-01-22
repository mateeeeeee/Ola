#include "x64.h"
#include "x64TargetFrameInfo.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/MachineContext.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineGlobal.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"

namespace ola
{

	void x64TargetFrameInfo::EmitCall(CallInst* CI, MachineContext& ctx) const
	{
		Function* callee = CI->GetCalleeAsFunction();
		OLA_ASSERT(callee);
		MachineGlobal const* global = ctx.GetGlobal(callee);

		MachineFunction* MF = ctx.GetCurrentBasicBlock()->GetFunction();
		for (Int32 idx = CI->ArgSize() - 1; idx >= 0; --idx)
		{
			Value const* arg = CI->GetArgOp(idx);
			MachineOperand arg_operand = ctx.GetOperand(arg);
			Uint32 opcode = (arg_operand.IsMemoryOperand() && arg->GetType()->IsPointer()) ? InstLoadGlobalAddress : InstMove;
			if (idx >= 4) 
			{
				Int32 offset = 8 + MF->GetLocalStackAllocationSize() + (CI->ArgSize() - 1 - idx) * 8; //this is wrong, 6th goes 
				MachineInstruction copy_arg_to_stack(opcode);
				copy_arg_to_stack.SetOp<0>(MachineOperand::StackObject(-offset, arg_operand.GetType())).SetOp<1>(arg_operand);
				ctx.EmitInst(copy_arg_to_stack);
			}
			else 
			{
				if (arg_operand.GetType() != MachineType::Float64)
				{
					static constexpr x64::Register arg_regs[] = { x64::RCX, x64::RDX, x64::R8, x64::R9 };
					MachineInstruction mov(opcode);
					mov.SetOp<0>(MachineOperand::ISAReg(arg_regs[idx], arg_operand.GetType())).SetOp<1>(arg_operand);
					ctx.EmitInst(mov);
				}
				else
				{
					static constexpr x64::Register arg_regs[] = { x64::XMM0, x64::XMM1, x64::XMM2, x64::XMM3 };
					MachineInstruction mov(opcode);
					mov.SetOp<0>(MachineOperand::ISAReg(arg_regs[idx], MachineType::Float64)).SetOp<1>(arg_operand);
					ctx.EmitInst(mov);
				}
			}
		}

		MachineInstruction call_inst(InstCall);
		call_inst.SetOp<0>(MachineOperand::Relocable(global->GetRelocable()));
		ctx.EmitInst(call_inst);
		IRType const* return_type = CI->GetType();
		if (return_type->IsVoid()) return;

		const auto return_reg = ctx.VirtualReg(return_type);
		MachineOperand arch_return_reg;
		if (return_type->IsFloat()) 
		{
			arch_return_reg = MachineOperand::ISAReg(x64::XMM0, MachineType::Float64);
		}
		else 
		{
			arch_return_reg = MachineOperand::ISAReg(x64::RAX, MachineType::Int64);
		}
		ctx.EmitInst(MachineInstruction(InstMove).SetOp<0>(return_reg).SetOp<1>(arch_return_reg));
		ctx.MapOperand(CI, return_reg);
	}

	void x64TargetFrameInfo::EmitPrologue(MachineFunction& MF, MachineContext& ctx) const
	{
		using enum MachineType;

		if (MF.HasCallInstructions()) MF.AllocateArgumentStack(32);
		if (MF.GetMaxCallArgCount() > 4) MF.AllocateArgumentStack(8 * (MF.GetMaxCallArgCount() - 4));

		MachineOperand rbp = MachineOperand::ISAReg(x64::RBP, Int64);
		MachineOperand rsp = MachineOperand::ISAReg(x64::RSP, Int64);

		if (MF.GetStackAllocationSize() > 0)
		{
			MachineInstruction push_rbp(InstPush);
			push_rbp.SetOp<0>(rbp);
			ctx.EmitInst(push_rbp);

			MachineInstruction set_rbp(InstMove);
			set_rbp.SetOp<0>(rbp).SetOp<1>(rsp);
			ctx.EmitInst(set_rbp);
		}

		Int32 stack_allocation = MF.GetStackAllocationSize();
		if (stack_allocation > 0)
		{
			MachineInstruction allocate_stack(InstSub);
			allocate_stack.SetOp<0>(rsp).SetOp<1>(MachineOperand::Immediate(stack_allocation, Int64));
			ctx.EmitInst(allocate_stack);
		}

		Uint32 arg_idx = 0;
		for (MachineOperand const& arg : MF.Args())
		{
			if (arg_idx < 4)
			{
				if (arg.GetType() != Float64)
				{
					static constexpr x64::Register arg_regs[] = { x64::RCX, x64::RDX, x64::R8, x64::R9 };
					MachineInstruction copy_arg_to_reg(InstMove);
					copy_arg_to_reg.SetOp<1>(MachineOperand::ISAReg(arg_regs[arg_idx], arg.GetType())).SetOp<0>(arg);
					ctx.EmitInst(copy_arg_to_reg);
				}
				else
				{
					static constexpr x64::Register arg_regs[] = { x64::XMM0, x64::XMM1, x64::XMM2, x64::XMM3 };
					MachineInstruction copy_arg_to_reg(InstMove);
					copy_arg_to_reg.SetOp<1>(MachineOperand::ISAReg(arg_regs[arg_idx], arg.GetType())).SetOp<0>(arg);
					ctx.EmitInst(copy_arg_to_reg);
				}
			}
			else
			{
				MachineInstruction copy_arg_to_reg(InstMove);
				Int32 offset = 8 + 40 + (arg_idx - 4) * 8;
				copy_arg_to_reg.SetOp<1>(MachineOperand::StackObject(offset, arg.GetType())).SetOp<0>(arg);
				ctx.EmitInst(copy_arg_to_reg);
			}
			++arg_idx;
		}
	}

	void x64TargetFrameInfo::EmitProloguePostRA(MachineFunction& MF, MachineContext& ctx) const
	{

	}

	void x64TargetFrameInfo::EmitEpilogue(MachineFunction& MF, MachineContext& ctx) const
	{
		using enum MachineType;

		if (MF.GetStackAllocationSize() > 0)
		{
			MachineOperand rbp = MachineOperand::ISAReg(x64::RBP, Int64);
			MachineOperand rsp = MachineOperand::ISAReg(x64::RSP, Int64);

			MachineInstruction reset_rbp(InstMove);
			reset_rbp.SetOp<0>(rsp).SetOp<1>(rbp);
			ctx.EmitInst(reset_rbp);

			MachineInstruction pop_rbp(InstPop);
			pop_rbp.SetOp<0>(rbp);
			ctx.EmitInst(pop_rbp);
		}
		ctx.EmitInst(MachineInstruction(InstRet));
	}

	void x64TargetFrameInfo::EmitEpiloguePostRA(MachineFunction& MF, MachineContext& ctx) const
	{

	}

	void x64TargetFrameInfo::EmitReturn(ReturnInst* RI, MachineContext& ctx) const
	{
		if (RI->GetNumOperands() > 0)
		{
			Value const* V = RI->GetOperand(0);
			Uint32 const size = V->GetType()->GetSize();
			if (size <= 8)
			{
				MachineOperand return_register;
				if (V->GetType()->IsFloat())
				{
					return_register = MachineOperand::ISAReg(x64::XMM0, MachineType::Float64);
				}
				else 
				{
					return_register = MachineOperand::ISAReg(x64::RAX, MachineType::Int64);
				}

				MachineInstruction copy_instruction(InstMove);
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

