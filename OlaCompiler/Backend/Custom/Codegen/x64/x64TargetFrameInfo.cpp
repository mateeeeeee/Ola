#include "x64.h"
#include "x64TargetFrameInfo.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/RegisterAllocator.h"
#include "Backend/Custom/Codegen/MachineContext.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineGlobal.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/MachineModule.h"

namespace ola
{
	//Stack layout for x64 Microsoft ABI
	//Higher memory addresses
	//+ ------------------------------------ +
	//| Caller - saved registers(if spilled) | < -Saved by caller before call
	//+ ------------------------------------ +
	//| 7th argument etc					 | <- Pushed by caller before call
	//| 6th argument						 | <- Pushed by caller before call
	//| 5th argument						 | <- Pushed by caller before call
	//+ ------------------------------------ +
	//| Shadow Space(32B)					 | <- Allocated by caller before CALL
	//+ ------------------------------------ +
	//| Return Address						 | <- Pushed by CALL instruction
	//+ ------------------------------------ +
	//| Old RBP(if used)					 | <- Pushed by callee (if using frame pointer)
	//| Callee - saved registers			 | <- Saved by callee(if needed)  
	//| Local variables + register spills	 | <- Allocated by callee
	//+ ------------------------------------ +
	//Lower memory addresses(stack grows downward)
	
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
				Int32 offset = MF->GetLocalStackAllocationSize() + (MF->GetMaxCallArgCount() - idx) * 8; 
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
		if (return_type->IsVoid())
		{
			return;
		}

		MachineOperand const return_reg = ctx.VirtualReg(return_type);
		MachineOperand arch_return_reg;
		if (return_type->IsFloat()) 
		{
			arch_return_reg = MachineOperand::ISAReg(x64::XMM0, MachineType::Float64);
		}
		else 
		{
			arch_return_reg = MachineOperand::ISAReg(x64::RAX, return_reg.GetType());
		}
		ctx.EmitInst(MachineInstruction(InstMove).SetOp<0>(return_reg).SetOp<1>(arch_return_reg));
		ctx.MapOperand(CI, return_reg);
	}

	void x64TargetFrameInfo::EmitPrologue(MachineFunction& MF, MachineContext& ctx) const
	{
		using enum MachineType;

		if (MF.HasCallInstructions()) MF.AllocateArgumentStack(32);
		if (MF.GetMaxCallArgCount() > 4)
		{
			MF.AllocateArgumentStack((MF.GetMaxCallArgCount() - 4) * 8);
		}

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

			MachineInstruction allocate_stack(InstSub);
			allocate_stack.SetOp<0>(rsp).SetOp<1>(MachineOperand::Immediate(MF.GetStackAllocationSize(), Int64));
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
		auto const& gp_regs = ctx.GetUsedRegistersInfo()->gp_used_registers;
		auto const& fp_regs = ctx.GetUsedRegistersInfo()->fp_used_registers;
		Uint32 const stack_adjustment = (gp_regs.size() + fp_regs.size()) * 8;

		std::list<MachineInstruction>& insert_list = ctx.GetCurrentBasicBlock()->Instructions();
		std::list<MachineInstruction>::iterator insert_point = insert_list.begin();
		//try to find stack allocation
		insert_point = std::find_if(insert_list.begin(), insert_list.end(), [](MachineInstruction& MI)
			{
				if (MI.GetOpcode() == InstSub && MI.GetOp<0>().IsReg() && MI.GetOp<0>().GetReg().reg == x64::RSP) return true;
				return false;
			});
		if (insert_point != insert_list.end())
		{
			MachineInstruction& MI = *insert_point;
			OLA_ASSERT(MI.GetOp<1>().IsImmediate());
			Int64 stack_alloc = MI.GetOp<1>().GetImmediate();
			MI.SetOp<1>(MachineOperand::Immediate(MF.GetStackAllocationSize() + stack_adjustment, MachineType::Int64));
			++insert_point;
		}
		else
		{
			OLA_ASSERT(MF.GetStackAllocationSize() == 0);
			Uint32 new_stack_allocation = MF.GetStackAllocationSize() + stack_adjustment;
			if (new_stack_allocation > 0)
			{
				MachineOperand rbp = MachineOperand::ISAReg(x64::RBP, MachineType::Int64);
				MachineOperand rsp = MachineOperand::ISAReg(x64::RSP, MachineType::Int64);

				MachineInstruction push_rbp(InstPush);
				push_rbp.SetOp<0>(rbp);
				insert_point = ctx.EmitInst(insert_list.begin(), push_rbp); ++insert_point;

				MachineInstruction set_rbp(InstMove);
				set_rbp.SetOp<0>(rbp).SetOp<1>(rsp);
				insert_point = ctx.EmitInst(insert_point, set_rbp); ++insert_point;

				MachineInstruction allocate_stack(InstSub);
				allocate_stack.SetOp<0>(rsp).SetOp<1>(MachineOperand::Immediate(MF.GetStackAllocationSize() + stack_adjustment, MachineType::Int64));
				insert_point = ctx.EmitInst(insert_point, allocate_stack); ++insert_point;
			}
		}
		if (stack_adjustment == 0) return;

		TargetInstInfo const& target_inst_info = ctx.GetModule().GetTarget().GetInstInfo();
		for (auto const& MBB : MF.Blocks())
		{
			for (auto& MI : MBB->Instructions())
			{
				InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);
				for (Uint32 i = 0; i < inst_info.GetOperandCount(); ++i)
				{
					MachineOperand& MO = MI.GetOperand(i);
					if (MO.IsStackObject())
					{
						Int32 operand_offset = MO.GetStackOffset();
						if (operand_offset < 0)
						{
							MI.SetOperand(i, MachineOperand::StackObject(operand_offset - stack_adjustment, MO.GetType()));
						}
					}
				}
			}
		}

		Uint32 stack_offset = 0;
		for (Uint32 gp_reg : gp_regs)
		{
			stack_offset += 8;
			MachineInstruction MI(InstMove);
			MI.SetOp<0>(MachineOperand::StackObject(-stack_offset, MachineType::Int64));
			MI.SetOp<1>(MachineOperand::ISAReg(gp_reg, MachineType::Int64));
			ctx.EmitInst(insert_point, MI);
			MF.AddCalleeSavedArg(gp_reg, stack_offset, MachineType::Int64);
		}
		for (Uint32 fp_reg : fp_regs)
		{
			stack_offset += 8;
			MachineInstruction MI(InstMove);
			MI.SetOp<0>(MachineOperand::StackObject(-stack_offset, MachineType::Float64));
			MI.SetOp<1>(MachineOperand::ISAReg(fp_reg, MachineType::Float64));
			ctx.EmitInst(insert_point, MI);
			MF.AddCalleeSavedArg(fp_reg, stack_offset, MachineType::Float64);
		}
		OLA_ASSERT(stack_offset == stack_adjustment);

	}

	void x64TargetFrameInfo::EmitEpilogue(MachineFunction& MF, MachineContext& ctx) const
	{
		if (MF.GetStackAllocationSize() > 0)
		{
			MachineOperand rbp = MachineOperand::ISAReg(x64::RBP, MachineType::Int64);
			MachineOperand rsp = MachineOperand::ISAReg(x64::RSP, MachineType::Int64);

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
		if (!MF.GetCalleeSavedArgs().empty())
		{
			std::list<MachineInstruction>& insert_list = ctx.GetCurrentBasicBlock()->Instructions();
			std::list<MachineInstruction>::iterator insert_point = insert_list.end();
			insert_point = std::find_if(insert_list.begin(), insert_list.end(), [](MachineInstruction& MI)
				{
					if (MI.GetOpcode() == InstMove && MI.GetOp<0>().IsReg() && MI.GetOp<0>().GetReg().reg == x64::RSP
						&& MI.GetOp<1>().IsReg() && MI.GetOp<1>().GetReg().reg == x64::RBP)
					{
						return true;
					}
					return false;
				});
			Bool missing_epilogue = (insert_point == insert_list.end());
			if(missing_epilogue) --insert_point;

			for (auto const& [reg, offset, type] : MF.GetCalleeSavedArgs())
			{
				MachineInstruction MI(InstMove);
				MI.SetOp<0>(MachineOperand::ISAReg(reg, type));
				MI.SetOp<1>(MachineOperand::StackObject(-offset, type));
				insert_point = ctx.EmitInst(insert_point, MI);
				++insert_point;
			}
			if (missing_epilogue)
			{
				MachineOperand rbp = MachineOperand::ISAReg(x64::RBP, MachineType::Int64);
				MachineOperand rsp = MachineOperand::ISAReg(x64::RSP, MachineType::Int64);

				MachineInstruction set_rbp(InstMove);
				set_rbp.SetOp<0>(rsp).SetOp<1>(rbp);
				insert_point = ctx.EmitInst(insert_point, set_rbp); ++insert_point;

				MachineInstruction allocate_stack(InstPop);
				allocate_stack.SetOp<0>(rbp);
				insert_point = ctx.EmitInst(insert_point, allocate_stack); ++insert_point;
			}
		}
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
					MachineType const return_type = V->GetType()->IsBoolean() ? MachineType::Int8 : MachineType::Int64;
					return_register = MachineOperand::ISAReg(x64::RAX, return_type);
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

