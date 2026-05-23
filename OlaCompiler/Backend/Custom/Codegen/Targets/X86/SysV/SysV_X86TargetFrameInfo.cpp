#include "SysV_X86TargetFrameInfo.h"
#include "Backend/Custom/Codegen/Targets/X86/X86.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/RA/RegisterAllocator.h"
#include "Backend/Custom/Codegen/MachineContext.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineGlobal.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/MachineModule.h"

namespace ola
{
	//Stack layout for X86 SysV ABI
	//Higher memory addresses
	//+ ------------------------------------ +
	//| Caller - saved registers(if spilled) | < -Saved by caller before call
	//+ ------------------------------------ +
	//| 7th argument etc					 | <- Pushed by caller before call (for integer args)
	//+ ------------------------------------ +
	//| Return Address						 | <- Pushed by CALL instruction
	//+ ------------------------------------ +
	//| Old RBP(if used)					 | <- Pushed by callee (if using frame pointer)
	//| Callee - saved registers			 | <- Saved by callee(if needed)
	//| Local variables + register spills	 | <- Allocated by callee
	//+ ------------------------------------ +
	//| Red Zone (128 bytes)				 | <- Available without explicit allocation
	//+ ------------------------------------ +
	//Lower memory addresses(stack grows downward)
	
	void SysV_X86TargetFrameInfo::EmitCall(CallInst* CI, MachineContext& ctx) const
	{
		Bool const is_indirect = CI->IsIndirect();
		MachineGlobal const* global = is_indirect ? nullptr : ctx.GetGlobal(CI->GetCalleeAsFunction());

		MachineFunction* MF = ctx.GetCurrentBasicBlock()->GetFunction();
		for (Int32 idx = CI->ArgSize() - 1; idx >= 0; --idx)
		{
			Value const* arg = CI->GetArgOp(idx);
			MachineOperand arg_operand = ctx.GetOperand(arg);
			Bool const is_aggregate_arg = arg->GetType()->IsAggregate();
			Uint32 opcode = (arg_operand.IsMemoryOperand() && (arg->GetType()->IsPointer() || is_aggregate_arg)) ? InstLoadGlobalAddress : InstMove;

			if (arg_operand.GetType() != MachineType::Float64)
			{
				// SysV X86 ABI: Integer arguments go in RDI, RSI, RDX, RCX, R8, R9 (6 registers)
				if (idx >= 6)
				{
					Int32 offset = (MF->GetMaxCallArgCount() - idx) * 8;
					MachineInstruction copy_arg_to_stack(opcode);
					copy_arg_to_stack.SetOp<0>(MachineOperand::ArgSlot(-offset, arg_operand.GetType())).SetOp<1>(arg_operand);
					ctx.EmitInst(copy_arg_to_stack);
				}
				else
				{
					static constexpr X86Register arg_regs[] = { X86_RDI, X86_RSI, X86_RDX, X86_RCX, X86_R8, X86_R9 };
					MachineInstruction mov(opcode);
					mov.SetOp<0>(MachineOperand::ISAReg(arg_regs[idx], arg_operand.GetType())).SetOp<1>(arg_operand);
					ctx.EmitInst(mov);
				}
			}
			else
			{
				// SysV X86 ABI: Float arguments go in XMM0-XMM7 (8 registers)
				if (idx >= 8)
				{
					Int32 offset = (MF->GetMaxCallArgCount() - idx) * 8;
					MachineInstruction copy_arg_to_stack(opcode);
					copy_arg_to_stack.SetOp<0>(MachineOperand::ArgSlot(-offset, arg_operand.GetType())).SetOp<1>(arg_operand);
				 ctx.EmitInst(copy_arg_to_stack);
				}
				else
				{
					static constexpr X86Register arg_regs[] = { X86_XMM0, X86_XMM1, X86_XMM2, X86_XMM3, X86_XMM4, X86_XMM5, X86_XMM6, X86_XMM7 };
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

	void SysV_X86TargetFrameInfo::EmitPrologue(MachineFunction& MF, MachineContext& ctx) const
	{
		using enum MachineType;

		// SysV X86 ABI: No shadow space allocation (unlike Microsoft X86)
		// Only allocate stack space for arguments beyond the 6 integer registers
		if (MF.GetMaxCallArgCount() > 6)
		{
			MF.AllocateArgumentStack((MF.GetMaxCallArgCount() - 6) * 8);
		}

		MachineOperand rbp = MachineOperand::ISAReg(X86_RBP, Int64);
		MachineOperand rsp = MachineOperand::ISAReg(X86_RSP, Int64);

		// Always emit a frame when there are calls or local stack. Stack size
		// may grow further during register allocation (spills) — the actual
		// `sub rsp, N` immediate is patched in EmitProloguePostRA.
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
			if (arg.GetType() != Float64)
			{
				// SysV X86 ABI: First 6 integer arguments in RDI, RSI, RDX, RCX, R8, R9
				if (arg_idx < 6)
				{
					static constexpr X86Register arg_regs[] = { X86_RDI, X86_RSI, X86_RDX, X86_RCX, X86_R8, X86_R9 };
					MachineInstruction copy_arg_to_reg(InstMove);
					copy_arg_to_reg.SetOp<1>(MachineOperand::ISAReg(arg_regs[arg_idx], arg.GetType())).SetOp<0>(arg);
					ctx.EmitInst(copy_arg_to_reg);
				}
				else
				{
					// Arguments 7+ are on the stack
					// Stack layout: [return addr (8)] + [old RBP (8)] = 16 bytes base
					MachineInstruction copy_arg_to_reg(InstMove);
					Int32 offset = 16 + (arg_idx - 6) * 8;
					copy_arg_to_reg.SetOp<1>(MachineOperand::StackObject(offset, arg.GetType())).SetOp<0>(arg);
					ctx.EmitInst(copy_arg_to_reg);
				}
			}
			else
			{
				// SysV X86 ABI: First 8 float arguments in XMM0-XMM7
				if (arg_idx < 8)
				{
					static constexpr X86Register arg_regs[] = { X86_XMM0, X86_XMM1, X86_XMM2, X86_XMM3, X86_XMM4, X86_XMM5, X86_XMM6, X86_XMM7 };
					MachineInstruction copy_arg_to_reg(InstMove);
					copy_arg_to_reg.SetOp<1>(MachineOperand::ISAReg(arg_regs[arg_idx], arg.GetType())).SetOp<0>(arg);
					ctx.EmitInst(copy_arg_to_reg);
				}
				else
				{
					// Arguments 9+ are on the stack
					MachineInstruction copy_arg_to_reg(InstMove);
					Int32 offset = 16 + (arg_idx - 8) * 8;
					copy_arg_to_reg.SetOp<1>(MachineOperand::StackObject(offset, arg.GetType())).SetOp<0>(arg);
					ctx.EmitInst(copy_arg_to_reg);
				}
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

	void SysV_X86TargetFrameInfo::EmitProloguePostRA(MachineFunction& MF, MachineContext& ctx) const
	{
		auto const& gp_regs = ctx.GetUsedRegistersInfo()->gp_used_registers;
		auto const& fp_regs = ctx.GetUsedRegistersInfo()->fp_used_registers;
		Uint32 const spill_size = (gp_regs.size() + fp_regs.size()) * 8;
		Uint32 const stack_size = MF.GetStackAllocationSize();
		Uint32 const total = stack_size + spill_size;

		// Keep RSP 16-byte aligned. After `push rbp`, RSP is 16-byte aligned;
		// we then `sub rsp, N` where N is a multiple of 16.
		Uint32 const aligned = OLA_ALIGN_UP(total, 16);
		Uint32 const padding = aligned - total;

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
				// Prologue didn't emit a frame (no calls + no local stack at
				// prologue-emit time), but RA introduced spills. Emit one now.
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

		// Adjust negative stack-object offsets to account for the callee-saved
		// register save area (placed below RBP first) and any alignment padding.
		// Outgoing-call argument slots additionally need the post-RA local-stack
		// size folded in — they were emitted with offset = -(MaxCall-idx)*8 in
		// EmitCall, before RA could grow the local stack with spills.
		Int32 const local_stack = MF.GetLocalStackAllocationSize();
		Int32 const arg_shift = -static_cast<Int32>(spill_size + padding) - local_stack;
		Int32 const local_shift = -static_cast<Int32>(spill_size + padding);
		TargetInstInfo const& target_inst_info = ctx.GetModule().GetTarget().GetInstInfo();
		if (spill_size > 0 || padding > 0 || local_stack > 0)
		{
			for (auto const& MBB : MF.Blocks())
			{
				for (auto& MI : MBB->Instructions())
				{
					InstInfo const& inst_info = target_inst_info.GetInstInfo(MI);
					for (Uint32 i = 0; i < inst_info.GetOperandCount(); ++i)
					{
						MachineOperand& MO = MI.GetOperand(i);
						if (!MO.IsStackObject()) continue;
						Int32 operand_offset = MO.GetStackOffset();
						if (MO.IsArgSlot())
						{
							MI.SetOperand(i, MachineOperand::StackObject(operand_offset + arg_shift, MO.GetType()));
						}
						else if (operand_offset < 0 && (spill_size > 0 || padding > 0))
						{
							MI.SetOperand(i, MachineOperand::StackObject(operand_offset + local_shift, MO.GetType()));
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

	void SysV_X86TargetFrameInfo::EmitEpilogue(MachineFunction& MF, MachineContext& ctx) const
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

	void SysV_X86TargetFrameInfo::EmitEpiloguePostRA(MachineFunction& MF, MachineContext& ctx) const
	{
		auto& insts = ctx.GetCurrentBasicBlock()->Instructions();

		if (!MF.HasFrame()) return;

		auto mov_it = std::find_if(insts.begin(), insts.end(),
			[](MachineInstruction& mi)
			{
				return mi.GetOpcode() == InstMove &&
					mi.GetOp<0>().IsReg() && mi.GetOp<0>().GetReg().reg == X86_RSP &&
					mi.GetOp<1>().IsReg() && mi.GetOp<1>().GetReg().reg == X86_RBP;
			});

		if (mov_it == insts.end())
		{
			// Prologue created the frame post-RA, so no epilogue marker exists yet.
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

	void SysV_X86TargetFrameInfo::EmitReturn(ReturnInst* RI, MachineContext& ctx) const
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
					return_register = MachineOperand::ISAReg(X86_XMM0, MachineType::Float64);
				}
				else 
				{
					MachineType const return_type = V->GetType()->IsBoolean() ? MachineType::Int8 : MachineType::Int64;
					return_register = MachineOperand::ISAReg(X86_RAX, return_type);
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

