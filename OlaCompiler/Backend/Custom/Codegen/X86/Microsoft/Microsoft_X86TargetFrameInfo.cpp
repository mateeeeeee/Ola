#include "Microsoft_X86TargetFrameInfo.h"
#include "Backend/Custom/Codegen/X86/X86.h"
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
	// Stack layout for X86 Microsoft ABI
	// Higher memory addresses
	// + ------------------------------------ +
	// | Caller - saved registers(if spilled) | <- Saved by caller before call
	// + ------------------------------------ +
	// | 7th argument etc | <- Pushed by caller before call
	// | 6th argument | <- Pushed by caller before call
	// | 5th argument | <- Pushed by caller before call
	// + ------------------------------------ +
	// | Shadow Space(32B) | <- Allocated by caller before CALL
	// + ------------------------------------ +
	// | Return Address | <- Pushed by CALL instruction
	// + ------------------------------------ +
	// | Old RBP(if used) | <- Pushed by callee (if using frame pointer)
	// | Callee - saved registers | <- Saved by callee(if needed)
	// | Local variables + register spills | <- Allocated by callee
	// | Max outgoing call space | <- Pre-allocated by callee (shadow + stack args)
	// + ------------------------------------ +
	// Lower memory addresses(stack grows downward)

	static constexpr Uint32 SHADOW_SPACE_SIZE = 32;
	static constexpr Uint32 STACK_ALIGNMENT = 16;

	void Microsoft_X86TargetFrameInfo::EmitCall(CallInst* CI, MachineContext& ctx) const
	{
		Bool const is_indirect = CI->IsIndirect();
		MachineGlobal const* global = is_indirect ? nullptr : ctx.GetGlobal(CI->GetCalleeAsFunction());
		MachineFunction* MF = ctx.GetCurrentBasicBlock()->GetFunction();
		for (Int32 idx = CI->ArgSize() - 1; idx >= 0; --idx)
		{
			Value const* arg = CI->GetArgOp(idx);
			MachineOperand arg_operand = ctx.GetOperand(arg);
			Bool const is_struct_arg = arg->GetType()->IsStruct();
			Uint32 opcode = (arg_operand.IsMemoryOperand() && (arg->GetType()->IsPointer() || is_struct_arg)) ? InstLoadGlobalAddress : InstMove;
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
					static constexpr X86Register arg_regs[] = { X86_RCX, X86_RDX, X86_R8, X86_R9 };
					MachineInstruction mov(opcode);
					mov.SetOp<0>(MachineOperand::ISAReg(arg_regs[idx], arg_operand.GetType())).SetOp<1>(arg_operand);
					ctx.EmitInst(mov);
				}
				else
				{
					static constexpr X86Register arg_regs[] = { X86_XMM0, X86_XMM1, X86_XMM2, X86_XMM3 };
					MachineInstruction mov(opcode);
					mov.SetOp<0>(MachineOperand::ISAReg(arg_regs[idx], MachineType::Float64)).SetOp<1>(arg_operand);
					ctx.EmitInst(mov);
				}
			}
		}

		MachineInstruction call_inst(InstCall);
		if (is_indirect)
		{
			Value* callee_ptr = CI->GetCallee();
			MachineOperand callee_operand = ctx.GetOperand(callee_ptr);
			MachineOperand rax = MachineOperand::ISAReg(X86_RAX, MachineType::Int64);
			ctx.EmitInst(MachineInstruction(InstMove).SetOp<0>(rax).SetOp<1>(callee_operand));
			call_inst.SetOp<0>(rax);
		}
		else
		{
			call_inst.SetOp<0>(MachineOperand::Relocable(global->GetRelocable()));
		}
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
			arch_return_reg = MachineOperand::ISAReg(X86_XMM0, MachineType::Float64);
		}
		else
		{
			arch_return_reg = MachineOperand::ISAReg(X86_RAX, return_reg.GetType());
		}
		ctx.EmitInst(MachineInstruction(InstMove).SetOp<0>(return_reg).SetOp<1>(arch_return_reg));
		ctx.MapOperand(CI, return_reg);
	}

	void Microsoft_X86TargetFrameInfo::EmitPrologue(MachineFunction& MF, MachineContext& ctx) const
	{
		using enum MachineType;

		if (MF.HasCallInstructions())
		{
			MF.AllocateArgumentStack(SHADOW_SPACE_SIZE); 
		}
		if (MF.GetMaxCallArgCount() > 4)
		{
			MF.AllocateArgumentStack((MF.GetMaxCallArgCount() - 4) * 8);
		}

		MachineOperand rbp = MachineOperand::ISAReg(X86_RBP, Int64);
		MachineOperand rsp = MachineOperand::ISAReg(X86_RSP, Int64);

		Bool const needs_frame = MF.HasCallInstructions() || MF.GetLocalStackAllocationSize() > 0;
		if (needs_frame)
		{
			MachineInstruction push_rbp(InstPush);
			push_rbp.SetOp<0>(rbp);
			ctx.EmitInst(push_rbp);

			MachineInstruction set_rbp(InstMove);
			set_rbp.SetOp<0>(rbp).SetOp<1>(rsp);
			ctx.EmitInst(set_rbp);

			MachineInstruction allocate_stack(InstSub);
			allocate_stack.SetOp<0>(rsp).SetOp<1>(MachineOperand::Immediate(0, Int64));
			ctx.EmitInst(allocate_stack);
			MF.SetHasFrame(true);
		}

		Uint32 arg_idx = 0;
		for (MachineOperand const& arg : MF.Args())
		{
			if (arg_idx < 4)
			{
				if (arg.GetType() != Float64)
				{
					static constexpr X86Register arg_regs[] = { X86_RCX, X86_RDX, X86_R8, X86_R9 };
					MachineInstruction copy_arg_to_reg(InstMove);
					copy_arg_to_reg.SetOp<1>(MachineOperand::ISAReg(arg_regs[arg_idx], arg.GetType())).SetOp<0>(arg);
					ctx.EmitInst(copy_arg_to_reg);
				}
				else
				{
					static constexpr X86Register arg_regs[] = { X86_XMM0, X86_XMM1, X86_XMM2, X86_XMM3 };
					MachineInstruction copy_arg_to_reg(InstMove);
					copy_arg_to_reg.SetOp<1>(MachineOperand::ISAReg(arg_regs[arg_idx], arg.GetType())).SetOp<0>(arg);
					ctx.EmitInst(copy_arg_to_reg);
				}
			}
			else
			{
				// Offset from RBP: 16 (saved RBP + return addr) + 32 (shadow space) + (arg_idx - 4) * 8
				Int32 offset = SHADOW_SPACE_SIZE + 16 + (arg_idx - 4) * 8;
				MachineInstruction copy_arg_to_reg(InstMove);
				copy_arg_to_reg.SetOp<1>(MachineOperand::StackObject(offset, arg.GetType())).SetOp<0>(arg);
				ctx.EmitInst(copy_arg_to_reg);
			}
			++arg_idx;
		}

		for (auto const& struct_arg : MF.GetStructArgs())
		{
			MachineOperand ptr_vreg = MF.Args()[struct_arg.arg_index];
			MachineOperand dst_slot = struct_arg.local_slot;
			Uint32 size = struct_arg.size;

			MachineInstruction memcpy_inst(InstMemCpy);
			memcpy_inst.SetOp<0>(dst_slot);
			memcpy_inst.SetOp<1>(ptr_vreg);
			memcpy_inst.SetOp<2>(MachineOperand::Immediate(size, Int64));
			ctx.EmitInst(memcpy_inst);
		}
	}

	void Microsoft_X86TargetFrameInfo::EmitProloguePostRA(MachineFunction& MF, MachineContext& ctx) const
	{
		auto const& gp_regs = ctx.GetUsedRegistersInfo()->gp_used_registers;
		auto const& fp_regs = ctx.GetUsedRegistersInfo()->fp_used_registers;
		Uint32 spill_size = (gp_regs.size() + fp_regs.size()) * 8;

		Uint32 const stack_size = MF.GetStackAllocationSize();
		Uint32 const total = stack_size + spill_size;

		// After push rbp, RSP is 16-byte aligned so we need to subtract a multiple of 16
		Uint32 aligned = OLA_ALIGN_UP(total, 16);
		Uint32 padding = aligned - total;

		Bool const needs_frame = (stack_size > 0) || (spill_size > 0);
		MachineOperand rbp = MachineOperand::ISAReg(X86_RBP, MachineType::Int64);
		MachineOperand rsp = MachineOperand::ISAReg(X86_RSP, MachineType::Int64);

		auto& insts = ctx.GetCurrentBasicBlock()->Instructions();
		auto insert_it = insts.begin();
		auto sub_it = insts.end();
		if (needs_frame)
		{
			if (!MF.HasFrame())
			{
				MachineInstruction push_rbp(InstPush);
				push_rbp.SetOp<0>(rbp);
				insert_it = ctx.EmitInst(insert_it, push_rbp); ++insert_it;

				MachineInstruction set_rbp(InstMove);
				set_rbp.SetOp<0>(rbp).SetOp<1>(rsp);
				insert_it = ctx.EmitInst(insert_it, set_rbp); ++insert_it;

				MachineInstruction sub_rsp_inst(InstSub);
				sub_rsp_inst.SetOp<0>(rsp).SetOp<1>(MachineOperand::Immediate(aligned, MachineType::Int64));
				insert_it = ctx.EmitInst(insert_it, sub_rsp_inst); ++insert_it;

				sub_it = std::prev(insert_it);

				MF.SetHasFrame(true);
			}
			else
			{
				sub_it = std::find_if(insts.begin(), insts.end(),
				[](MachineInstruction& mi)
				{
					return mi.GetOpcode() == InstSub &&
						mi.GetOp<0>().IsReg() && mi.GetOp<0>().GetReg().reg == X86_RSP;
				});
			}
		}
		else
		{
			sub_it = std::find_if(insts.begin(), insts.end(),
				[](MachineInstruction& mi)
				{
					return mi.GetOpcode() == InstSub &&
						mi.GetOp<0>().IsReg() && mi.GetOp<0>().GetReg().reg == X86_RSP;
				});
		}

		if (sub_it != insts.end())
		{
			sub_it->SetOp<1>(MachineOperand::Immediate(aligned, MachineType::Int64));
		}

		// Adjust stack object offsets to account for callee-saved registers and padding
		TargetInstInfo const& target_inst_info = ctx.GetModule().GetTarget().GetInstInfo();
		if (spill_size > 0 || padding > 0)
		{
			for (auto& MBB : MF.Blocks())
			{
				for (auto& MI : MBB->Instructions())
				{
					InstInfo const& instruction_info = target_inst_info.GetInstInfo(MI);
					for (Uint32 i = 0; i < instruction_info.GetOperandCount(); ++i)
					{
						MachineOperand& MO = MI.GetOperand(i);
						if (MO.IsStackObject())
						{
							Int32 offset = MO.GetStackOffset();
							if (offset < 0)
							{
								MO = MachineOperand::StackObject(offset - spill_size - padding, MO.GetType());
							}
						}
					}
				}
			}
		}

		if (spill_size == 0)
		{
			return;
		}

		if (sub_it != insts.end())
		{
			insert_it = std::next(sub_it);
		}
		else
		{
			insert_it = insts.begin();
		}

		Int32 save_offset = 8;
		for (Uint32 reg : gp_regs)
		{
			MachineInstruction save(InstMove);
			save.SetOp<0>(MachineOperand::StackObject(-save_offset, MachineType::Int64));
			save.SetOp<1>(MachineOperand::ISAReg(reg, MachineType::Int64));
			insert_it = ctx.EmitInst(insert_it, save);
			++insert_it;
			MF.AddCalleeSavedArg(reg, save_offset, MachineType::Int64);
			save_offset += 8;
		}
		for (Uint32 reg : fp_regs)
		{
			MachineInstruction save(InstMove);
			save.SetOp<0>(MachineOperand::StackObject(-save_offset, MachineType::Float64));
			save.SetOp<1>(MachineOperand::ISAReg(reg, MachineType::Float64));
			insert_it = ctx.EmitInst(insert_it, save);
			++insert_it;
			MF.AddCalleeSavedArg(reg, save_offset, MachineType::Float64);
			save_offset += 8;
		}
	}

	void Microsoft_X86TargetFrameInfo::EmitEpilogue(MachineFunction& MF, MachineContext& ctx) const
	{
		if (MF.HasFrame())
		{
			MachineOperand rbp = MachineOperand::ISAReg(X86_RBP, MachineType::Int64);
			MachineOperand rsp = MachineOperand::ISAReg(X86_RSP, MachineType::Int64);

			MachineInstruction reset_rbp(InstMove);
			reset_rbp.SetOp<0>(rsp).SetOp<1>(rbp);
			ctx.EmitInst(reset_rbp);

			MachineInstruction pop_rbp(InstPop);
			pop_rbp.SetOp<0>(rbp);
			ctx.EmitInst(pop_rbp);
		}
		ctx.EmitInst(MachineInstruction(InstRet));
	}

	void Microsoft_X86TargetFrameInfo::EmitEpiloguePostRA(MachineFunction& MF, MachineContext& ctx) const
	{
		auto& insts = ctx.GetCurrentBasicBlock()->Instructions();

		if (MF.HasFrame())
		{
			auto mov_it = std::find_if(insts.begin(), insts.end(),
				[](MachineInstruction& mi)
				{
					return mi.GetOpcode() == InstMove &&
						mi.GetOp<0>().IsReg() && mi.GetOp<0>().GetReg().reg == X86_RSP &&
						mi.GetOp<1>().IsReg() && mi.GetOp<1>().GetReg().reg == X86_RBP;
				});

			if (mov_it == insts.end())
			{
				MachineOperand rbp = MachineOperand::ISAReg(X86_RBP, MachineType::Int64);
				MachineOperand rsp = MachineOperand::ISAReg(X86_RSP, MachineType::Int64);

				auto ret_it = std::find_if(insts.begin(), insts.end(),
					[](MachineInstruction& mi)
					{
						return mi.GetOpcode() == InstRet;
					});

				if (ret_it != insts.end())
				{
					MachineInstruction reset_stack(InstMove);
					reset_stack.SetOp<0>(rsp).SetOp<1>(rbp);
					auto mov_insert_it = ctx.EmitInst(ret_it, reset_stack); 

					MachineInstruction pop_rbp(InstPop);
					pop_rbp.SetOp<0>(rbp);
					ctx.EmitInst(std::next(mov_insert_it), pop_rbp);
					mov_it = mov_insert_it;
				}
			}

			if (!MF.GetCalleeSavedArgs().empty() && mov_it != insts.end())
			{
				auto insert_it = mov_it;
				for (auto const& [reg, offset, type] : MF.GetCalleeSavedArgs())
				{
					MachineInstruction restore(InstMove);
					restore.SetOp<0>(MachineOperand::ISAReg(reg, type));
					restore.SetOp<1>(MachineOperand::StackObject(-offset, type));
					insert_it = ctx.EmitInst(insert_it, restore);
					++insert_it;
				}
			}
		}
	}

	void Microsoft_X86TargetFrameInfo::EmitReturn(ReturnInst* RI, MachineContext& ctx) const
	{
		if (RI->GetNumOperands() == 0)
		{
			return;
		}

		Value const* V = RI->GetOperand(0);
		Uint32 const size = V->GetType()->GetSize();
		if (size > 8) 
		{ 
			OLA_ASSERT_MSG(false, "todo"); 
		}

		MachineOperand return_register;
		if (V->GetType()->IsFloat())
		{
			return_register = MachineOperand::ISAReg(X86_XMM0, MachineType::Float64);
		}
		else
		{
			MachineType const return_type = V->GetType()->IsBoolean() ? MachineType::Int8 : MachineType::Int64;
			return_register = MachineOperand::ISAReg(X86_RAX, return_type);
		}

		MachineInstruction copy(InstMove);
		copy.SetOp<0>(return_register).SetOp<1>(ctx.GetOperand(V));
		ctx.EmitInst(copy);
	}
}