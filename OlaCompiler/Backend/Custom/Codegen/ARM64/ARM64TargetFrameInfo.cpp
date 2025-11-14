#include "ARM64TargetFrameInfo.h"
#include "Backend/Custom/Codegen/ARM64/ARM64.h"
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
	// ARM64 AAPCS (ARM Architecture Procedure Call Standard)
	// Integer arguments: X0-X7 (8 registers)
	// Float arguments: V0-V7 (8 registers)
	// Return values: X0 (integer), V0 (float)
	// FP = X29, LR = X30, SP = stack pointer
	// Stack must be 16-byte aligned

	void ARM64TargetFrameInfo::EmitCall(CallInst* CI, MachineContext& ctx) const
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

			if (arg_operand.GetType() != MachineType::Float64)
			{
				if (idx >= 8)
				{
					Int32 offset = MF->GetLocalStackAllocationSize() + (MF->GetMaxCallArgCount() - idx) * 8;
					MachineInstruction copy_arg_to_stack(opcode);
					copy_arg_to_stack.SetOp<0>(MachineOperand::StackObject(-offset, arg_operand.GetType())).SetOp<1>(arg_operand);
					ctx.EmitInst(copy_arg_to_stack);
				}
				else
				{
					static constexpr ARM64Register arg_regs[] = { ARM64_X0, ARM64_X1, ARM64_X2, ARM64_X3, ARM64_X4, ARM64_X5, ARM64_X6, ARM64_X7 };
					MachineInstruction mov(opcode);
					mov.SetOp<0>(MachineOperand::ISAReg(arg_regs[idx], arg_operand.GetType())).SetOp<1>(arg_operand);
					ctx.EmitInst(mov);
				}
			}
			else
			{
				if (idx >= 8)
				{
					Int32 offset = MF->GetLocalStackAllocationSize() + (MF->GetMaxCallArgCount() - idx) * 8;
					MachineInstruction copy_arg_to_stack(opcode);
					copy_arg_to_stack.SetOp<0>(MachineOperand::StackObject(-offset, arg_operand.GetType())).SetOp<1>(arg_operand);
					ctx.EmitInst(copy_arg_to_stack);
				}
				else
				{
					static constexpr ARM64Register arg_regs[] = { ARM64_V0, ARM64_V1, ARM64_V2, ARM64_V3, ARM64_V4, ARM64_V5, ARM64_V6, ARM64_V7 };
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
			arch_return_reg = MachineOperand::ISAReg(ARM64_V0, MachineType::Float64);
		}
		else
		{
			arch_return_reg = MachineOperand::ISAReg(ARM64_X0, return_reg.GetType());
		}
		ctx.EmitInst(MachineInstruction(InstMove).SetOp<0>(return_reg).SetOp<1>(arch_return_reg));
		ctx.MapOperand(CI, return_reg);
	}

	void ARM64TargetFrameInfo::EmitPrologue(MachineFunction& MF, MachineContext& ctx) const
	{
		using enum MachineType;

		if (MF.GetMaxCallArgCount() > 8)
		{
			MF.AllocateArgumentStack((MF.GetMaxCallArgCount() - 8) * 8);
		}

		MachineOperand fp = MachineOperand::ISAReg(ARM64_X29, Int64);
		MachineOperand lr = MachineOperand::ISAReg(ARM64_X30, Int64);
		MachineOperand sp = MachineOperand::ISAReg(ARM64_SP, Int64);

		if (MF.GetStackAllocationSize() > 0)
		{
			MachineInstruction stp_fp_lr(ARM64_InstStp);
			stp_fp_lr.SetOp<0>(fp);
			stp_fp_lr.SetOp<1>(lr);
			stp_fp_lr.SetOp<2>(MachineOperand::StackObject(-16, Ptr));
			ctx.EmitInst(stp_fp_lr);

			MachineInstruction set_fp(InstMove);
			set_fp.SetOp<0>(fp).SetOp<1>(sp);
			ctx.EmitInst(set_fp);

			MachineInstruction allocate_stack(InstSub);
			allocate_stack.SetOp<0>(sp).SetOp<1>(MachineOperand::Immediate(MF.GetStackAllocationSize(), Int64));
			ctx.EmitInst(allocate_stack);
		}

		Uint32 arg_idx = 0;
		for (MachineOperand const& arg : MF.Args())
		{
			if (arg.GetType() != Float64)
			{
				if (arg_idx < 8)
				{
					static constexpr ARM64Register arg_regs[] = { ARM64_X0, ARM64_X1, ARM64_X2, ARM64_X3, ARM64_X4, ARM64_X5, ARM64_X6, ARM64_X7 };
					MachineInstruction copy_arg_to_reg(InstMove);
					copy_arg_to_reg.SetOp<1>(MachineOperand::ISAReg(arg_regs[arg_idx], arg.GetType())).SetOp<0>(arg);
					ctx.EmitInst(copy_arg_to_reg);
				}
				else
				{
					MachineInstruction copy_arg_to_reg(InstMove);
					Int32 offset = 16 + (arg_idx - 8) * 8;
					copy_arg_to_reg.SetOp<1>(MachineOperand::StackObject(offset, arg.GetType())).SetOp<0>(arg);
					ctx.EmitInst(copy_arg_to_reg);
				}
			}
			else
			{
				if (arg_idx < 8)
				{
					static constexpr ARM64Register arg_regs[] = { ARM64_V0, ARM64_V1, ARM64_V2, ARM64_V3, ARM64_V4, ARM64_V5, ARM64_V6, ARM64_V7 };
					MachineInstruction copy_arg_to_reg(InstMove);
					copy_arg_to_reg.SetOp<1>(MachineOperand::ISAReg(arg_regs[arg_idx], arg.GetType())).SetOp<0>(arg);
					ctx.EmitInst(copy_arg_to_reg);
				}
				else
				{
					MachineInstruction copy_arg_to_reg(InstMove);
					Int32 offset = 16 + (arg_idx - 8) * 8;
					copy_arg_to_reg.SetOp<1>(MachineOperand::StackObject(offset, arg.GetType())).SetOp<0>(arg);
					ctx.EmitInst(copy_arg_to_reg);
				}
			}
			++arg_idx;
		}
	}

	void ARM64TargetFrameInfo::EmitProloguePostRA(MachineFunction& MF, MachineContext& ctx) const
	{
		auto const& gp_regs = ctx.GetUsedRegistersInfo()->gp_used_registers;
		auto const& fp_regs = ctx.GetUsedRegistersInfo()->fp_used_registers;
		Uint32 const stack_adjustment = (gp_regs.size() + fp_regs.size()) * 8;
		Uint32 const aligned_stack_adjustment = OLA_ALIGN_UP(stack_adjustment, 16);

		std::list<MachineInstruction>& insert_list = ctx.GetCurrentBasicBlock()->Instructions();
		std::list<MachineInstruction>::iterator insert_point = insert_list.begin();

		insert_point = std::find_if(insert_list.begin(), insert_list.end(), [](MachineInstruction& MI)
			{
				if (MI.GetOpcode() == InstSub && MI.GetOp<0>().IsReg() && MI.GetOp<0>().GetReg().reg == ARM64_SP) return true;
				return false;
			});

		if (insert_point != insert_list.end())
		{
			MachineInstruction& MI = *insert_point;
			OLA_ASSERT(MI.GetOp<1>().IsImmediate());
			MI.SetOp<1>(MachineOperand::Immediate(MF.GetStackAllocationSize() + aligned_stack_adjustment, MachineType::Int64));
			++insert_point;
		}
		else
		{
			OLA_ASSERT(MF.GetStackAllocationSize() == 0);
			Uint32 new_stack_allocation = MF.GetStackAllocationSize() + aligned_stack_adjustment;
			if (new_stack_allocation > 0)
			{
				MachineOperand fp = MachineOperand::ISAReg(ARM64_X29, MachineType::Int64);
				MachineOperand lr = MachineOperand::ISAReg(ARM64_X30, MachineType::Int64);
				MachineOperand sp = MachineOperand::ISAReg(ARM64_SP, MachineType::Int64);

				MachineInstruction stp_fp_lr(ARM64_InstStp);
				stp_fp_lr.SetOp<0>(fp).SetOp<1>(lr).SetOp<2>(MachineOperand::StackObject(-16, MachineType::Ptr));
				insert_point = ctx.EmitInst(insert_list.begin(), stp_fp_lr); ++insert_point;

				MachineInstruction set_fp(InstMove);
				set_fp.SetOp<0>(fp).SetOp<1>(sp);
				insert_point = ctx.EmitInst(insert_point, set_fp); ++insert_point;

				MachineInstruction allocate_stack(InstSub);
				allocate_stack.SetOp<0>(sp).SetOp<1>(MachineOperand::Immediate(new_stack_allocation, MachineType::Int64));
				insert_point = ctx.EmitInst(insert_point, allocate_stack); ++insert_point;
			}
		}

		if (aligned_stack_adjustment == 0) 
		{
			return;
		}

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
							MI.SetOperand(i, MachineOperand::StackObject(operand_offset - aligned_stack_adjustment, MO.GetType()));
						}
					}
				}
			}
		}

		Uint32 stack_offset = 0;
		for (Uint32 gp_reg : gp_regs)
		{
			stack_offset += 8;
			MachineInstruction MI(InstStore);
			MI.SetOp<0>(MachineOperand::StackObject(-stack_offset, MachineType::Int64));
			MI.SetOp<1>(MachineOperand::ISAReg(gp_reg, MachineType::Int64));
			ctx.EmitInst(insert_point, MI);
			MF.AddCalleeSavedArg(gp_reg, stack_offset, MachineType::Int64);
		}
		for (Uint32 fp_reg : fp_regs)
		{
			stack_offset += 8;
			MachineInstruction MI(InstStore);
			MI.SetOp<0>(MachineOperand::StackObject(-stack_offset, MachineType::Float64));
			MI.SetOp<1>(MachineOperand::ISAReg(fp_reg, MachineType::Float64));
			ctx.EmitInst(insert_point, MI);
			MF.AddCalleeSavedArg(fp_reg, stack_offset, MachineType::Float64);
		}
	}

	void ARM64TargetFrameInfo::EmitEpilogue(MachineFunction& MF, MachineContext& ctx) const
	{
		if (MF.GetStackAllocationSize() > 0)
		{
			MachineOperand fp = MachineOperand::ISAReg(ARM64_X29, MachineType::Int64);
			MachineOperand lr = MachineOperand::ISAReg(ARM64_X30, MachineType::Int64);
			MachineOperand sp = MachineOperand::ISAReg(ARM64_SP, MachineType::Int64);

			MachineInstruction reset_sp(InstMove);
			reset_sp.SetOp<0>(sp).SetOp<1>(fp);
			ctx.EmitInst(reset_sp);

			MachineInstruction ldp_fp_lr(ARM64_InstLdp);
			ldp_fp_lr.SetOp<0>(fp);
			ldp_fp_lr.SetOp<1>(lr);
			ldp_fp_lr.SetOp<2>(MachineOperand::StackObject(16, MachineType::Ptr));
			ctx.EmitInst(ldp_fp_lr);
		}
		ctx.EmitInst(MachineInstruction(InstRet));
	}

	void ARM64TargetFrameInfo::EmitEpiloguePostRA(MachineFunction& MF, MachineContext& ctx) const
	{
		if (!MF.GetCalleeSavedArgs().empty())
		{
			std::list<MachineInstruction>& insert_list = ctx.GetCurrentBasicBlock()->Instructions();
			std::list<MachineInstruction>::iterator insert_point = insert_list.end();

			insert_point = std::find_if(insert_list.begin(), insert_list.end(), [](MachineInstruction& MI)
				{
					if (MI.GetOpcode() == InstMove && MI.GetOp<0>().IsReg() && MI.GetOp<0>().GetReg().reg == ARM64_SP
						&& MI.GetOp<1>().IsReg() && MI.GetOp<1>().GetReg().reg == ARM64_X29)
					{
						return true;
					}
					return false;
				});

			Bool missing_epilogue = (insert_point == insert_list.end());
			if (missing_epilogue) 
			{
				--insert_point;
			}

			for (auto const& [reg, offset, type] : MF.GetCalleeSavedArgs())
			{
				MachineInstruction MI(InstLoad);
				MI.SetOp<0>(MachineOperand::ISAReg(reg, type));
				MI.SetOp<1>(MachineOperand::StackObject(-offset, type));
				insert_point = ctx.EmitInst(insert_point, MI);
				++insert_point;
			}

			if (missing_epilogue)
			{
				MachineOperand fp = MachineOperand::ISAReg(ARM64_X29, MachineType::Int64);
				MachineOperand lr = MachineOperand::ISAReg(ARM64_X30, MachineType::Int64);
				MachineOperand sp = MachineOperand::ISAReg(ARM64_SP, MachineType::Int64);

				MachineInstruction set_sp(InstMove);
				set_sp.SetOp<0>(sp).SetOp<1>(fp);
				insert_point = ctx.EmitInst(insert_point, set_sp); ++insert_point;

				MachineInstruction ldp_fp_lr(ARM64_InstLdp);
				ldp_fp_lr.SetOp<0>(fp).SetOp<1>(lr).SetOp<2>(MachineOperand::StackObject(16, MachineType::Ptr));
				insert_point = ctx.EmitInst(insert_point, ldp_fp_lr); ++insert_point;
			}
		}
	}

	void ARM64TargetFrameInfo::EmitReturn(ReturnInst* RI, MachineContext& ctx) const
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
					return_register = MachineOperand::ISAReg(ARM64_V0, MachineType::Float64);
				}
				else
				{
					MachineType const return_type = V->GetType()->IsBoolean() ? MachineType::Int8 : MachineType::Int64;
					return_register = MachineOperand::ISAReg(ARM64_X0, return_type);
				}

				MachineInstruction copy_instruction(InstMove);
				copy_instruction.SetOp<0>(return_register).SetOp<1>(ctx.GetOperand(V));
				ctx.EmitInst(copy_instruction);
			}
			else
			{
				OLA_ASSERT_MSG(false, "Return values larger than 8 bytes not yet supported");
			}
		}
	}
}
