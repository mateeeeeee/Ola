#include "x64.h"
#include "x64TargetFrameInfo.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/LoweringContext.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineGlobal.h"
#include "Backend/Custom/Codegen/MachineFunction.h"

namespace ola
{

	void x64TargetFrameInfo::EmitCall(CallInst* CI, LoweringContext& ctx) const
	{
		Function* callee = CI->GetCalleeAsFunction();
		OLA_ASSERT(callee);
		MachineGlobal const* global = ctx.GetGlobal(callee);

		static constexpr Uint32 PASS_BY_REG_OFFSET = 1 << 16;
		std::vector<Sint32> offsets;  
		Uint32 const arg_count = CI->ArgSize();
		offsets.reserve(arg_count);
		Uint32 gprs = 0;
		Uint32 current_stack_offset = 0;
		for (auto& arg : CI->Args())
		{
			if (!arg.GetValue()->GetType()->IsFloat())
			{
				if (gprs < 4)
				{
					offsets.push_back(PASS_BY_REG_OFFSET + gprs++);
					continue;
				}
			}
			else
			{
				OLA_ASSERT_MSG(false, "floating point arguments not implemented yet");
			}

			Uint32 size = arg.GetValue()->GetType()->GetSize();
			Uint32 alignment = size;

			current_stack_offset = (current_stack_offset + alignment - 1) / alignment * alignment;
			offsets.push_back(current_stack_offset);
			current_stack_offset += size;
		}

		MachineGlobal* caller_global = ctx.GetGlobal(CI->GetCaller());
		MachineFunction& caller = *static_cast<MachineFunction*>(global->GetRelocable());

		for (Sint32 idx = arg_count - 1; idx >= 0; --idx)
		{
			Sint32 offset = offsets[idx];
			Value const* arg = CI->GetArgOp(idx);
			MachineOperand arg_operand = ctx.GetOperand(arg);
			Uint32 size = arg->GetType()->GetSize();
			Uint32 alignment = size;

			Uint32 opcode = (arg_operand.IsMemoryOperand() && arg_operand.GetType() == MachineType::Ptr) ? InstLoadGlobalAddress : InstMove;
			if (offset < PASS_BY_REG_OFFSET)
			{
				MachineOperand& argument_stack = caller.AllocateStack(arg_operand.GetType());
				MachineInstruction copy_arg_to_stack(opcode);
				copy_arg_to_stack.SetOp<0>(argument_stack).SetOp<1>(arg_operand);
				ctx.EmitInst(copy_arg_to_stack);
			}
			else
			{
				Uint32 gpr = offset - PASS_BY_REG_OFFSET;
				static constexpr x64::Register arg_regs[] = {x64::RCX, x64::RDX, x64::R8, x64::R9 };
				MachineInstruction copy_arg_to_reg(opcode);
				copy_arg_to_reg.SetOp<0>(MachineOperand::ISAReg(arg_regs[gpr], arg_operand.GetType())).SetOp<1>(arg_operand);
				ctx.EmitInst(copy_arg_to_reg);
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
		ctx.AddOperand(CI, return_reg);
	}


	void x64TargetFrameInfo::EmitPrologue(MachineFunction& MF, LoweringContext& ctx) const
	{
		using enum MachineType;

		MachineOperand rbp = MachineOperand::ISAReg(x64::RBP, Int64);
		MachineOperand rsp = MachineOperand::ISAReg(x64::RSP, Int64);

		MachineInstruction push_rbp(InstPush);
		push_rbp.SetOp<0>(rbp);
		ctx.EmitInst(push_rbp);

		MachineInstruction set_rbp(InstMove);
		set_rbp.SetOp<0>(rbp).SetOp<1>(rsp);
		ctx.EmitInst(set_rbp);

		Sint32 stack_allocation = MF.GetStackAllocationSize();
		if (stack_allocation > 0)
		{
			MachineInstruction allocate_stack(InstSub);
			allocate_stack.SetOp<0>(rsp).SetOp<1>(MachineOperand::Immediate(stack_allocation, Int64));
			ctx.EmitInst(allocate_stack);
		}
		static constexpr Uint32 PASS_BY_REG_OFFSET = 1 << 16;

		std::vector<MachineOperand> const& args = MF.Args();
		std::vector<Uint32> offsets; 
		offsets.reserve(args.size());
		Uint32 gprs = 0;
		Uint32 current_offset = 0;
		for (MachineOperand const& arg : args)
		{
			if (arg.GetType() != MachineType::Float64) 
			{
				if (gprs < 4) 
				{
					offsets.push_back(PASS_BY_REG_OFFSET + gprs++);
					continue;
				}
			}
			else
			{
				OLA_ASSERT_MSG(false, "floating point arguments not implemented yet");
			}
			Uint32 size = GetOperandSize(arg.GetType());
			Uint32 alignment = size;
			current_offset = (current_offset + alignment - 1) / alignment * alignment;
			offsets.push_back(current_offset);
			current_offset += size;
		}

		for (uint32_t idx = 0; idx < args.size(); ++idx) 
		{
			Uint32 offset = offsets[idx];
			MachineOperand const& arg = args[idx];
			if (offset >= PASS_BY_REG_OFFSET)
			{
				Uint32 gpr = offset - PASS_BY_REG_OFFSET;
				static constexpr x64::Register arg_regs[] = { x64::RCX, x64::RDX, x64::R8, x64::R9 };
				MachineInstruction copy_arg_to_reg(InstMove);
				copy_arg_to_reg.SetOp<1>(MachineOperand::ISAReg(arg_regs[gpr], arg.GetType())).SetOp<0>(arg);
				ctx.EmitInst(copy_arg_to_reg);
			}
		}
		for (Uint32 idx = 0; idx < args.size(); ++idx) 
		{
			Uint32 offset = offsets[idx];
			MachineOperand const& arg = args[idx];
			Uint32 size = GetOperandSize(arg.GetType());
			Uint32 alignment = size;

			if (offset < PASS_BY_REG_OFFSET)
			{
			}
		}
	}

	void x64TargetFrameInfo::EmitEpilogue(MachineFunction& MF, LoweringContext& ctx) const
	{
		using enum MachineType;

		MachineOperand rbp = MachineOperand::ISAReg(x64::RBP, Int64);
		MachineOperand rsp = MachineOperand::ISAReg(x64::RSP, Int64);

		MachineInstruction reset_rbp(InstMove);
		reset_rbp.SetOp<0>(rsp).SetOp<1>(rbp);
		ctx.EmitInst(reset_rbp);

		MachineInstruction pop_rbp(InstPop);
		pop_rbp.SetOp<0>(rbp);
		ctx.EmitInst(pop_rbp);
	}

	void x64TargetFrameInfo::EmitReturn(ReturnInst* RI, LoweringContext& ctx) const
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

