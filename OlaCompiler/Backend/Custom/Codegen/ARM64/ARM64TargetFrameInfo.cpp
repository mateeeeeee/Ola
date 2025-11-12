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
    static constexpr Uint32 STACK_ALIGNMENT = 16;

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
                    static constexpr Uint32 arg_regs[] = { ARM64_X0, ARM64_X1, ARM64_X2, ARM64_X3, ARM64_X4, ARM64_X5, ARM64_X6, ARM64_X7 };
                    MachineInstruction mov(opcode);
                    mov.SetOp<0>(MachineOperand::ISAReg(arg_regs[idx], arg_operand.GetType())).SetOp<1>(arg_operand);
                    ctx.EmitInst(mov);
                }
            }
            else
            {
                // Floating args go in v0-v7 (use MachineType::Float64)
                if (idx >= 8)
                {
                    Int32 offset = MF->GetLocalStackAllocationSize() + (MF->GetMaxCallArgCount() - idx) * 8;
                    MachineInstruction copy_arg_to_stack(opcode);
                    copy_arg_to_stack.SetOp<0>(MachineOperand::StackObject(-offset, arg_operand.GetType())).SetOp<1>(arg_operand);
                    ctx.EmitInst(copy_arg_to_stack);
                }
                else
                {
                    static constexpr Uint32 arg_regs[] = { ARM64_V0, ARM64_V1, ARM64_V2, ARM64_V3, ARM64_V4, ARM64_V5, ARM64_V6, ARM64_V7 };
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

        Bool const needs_frame = MF.HasCallInstructions() || MF.GetLocalStackAllocationSize() > 0;
        if (needs_frame)
        {
            MachineInstruction push_fp(InstPush);
            push_fp.SetOp<0>(fp);
            ctx.EmitInst(push_fp);

            MachineInstruction push_lr(InstPush);
            push_lr.SetOp<0>(lr);
            ctx.EmitInst(push_lr);

            MachineInstruction set_fp(InstMove);
            set_fp.SetOp<0>(fp).SetOp<1>(sp);
            ctx.EmitInst(set_fp);

            MachineInstruction allocate_stack(InstSub);
            allocate_stack.SetOp<0>(sp).SetOp<1>(MachineOperand::Immediate(0, Int64));
            ctx.EmitInst(allocate_stack);

            MF.SetHasFrame(true);
        }

        Uint32 arg_idx = 0;
        for (MachineOperand const& arg : MF.Args())
        {
            if (arg.GetType() != Float64)
            {
                if (arg_idx < 8)
                {
                    static constexpr Uint32 arg_regs[] = { ARM64_X0, ARM64_X1, ARM64_X2, ARM64_X3, ARM64_X4, ARM64_X5, ARM64_X6, ARM64_X7 };
                    MachineInstruction copy_arg_to_reg(InstMove);
                    copy_arg_to_reg.SetOp<1>(MachineOperand::ISAReg(arg_regs[arg_idx], arg.GetType())).SetOp<0>(arg);
                    ctx.EmitInst(copy_arg_to_reg);
                }
                else
                {
                    Int32 offset = 16 + (arg_idx - 8) * 8; 
                    MachineInstruction copy_arg_to_reg(InstMove);
                    copy_arg_to_reg.SetOp<1>(MachineOperand::StackObject(offset, arg.GetType())).SetOp<0>(arg);
                    ctx.EmitInst(copy_arg_to_reg);
                }
            }
            else
            {
                if (arg_idx < 8)
                {
                    static constexpr Uint32 arg_regs[] = { ARM64_V0, ARM64_V1, ARM64_V2, ARM64_V3, ARM64_V4, ARM64_V5, ARM64_V6, ARM64_V7 };
                    MachineInstruction copy_arg_to_reg(InstMove);
                    copy_arg_to_reg.SetOp<1>(MachineOperand::ISAReg(arg_regs[arg_idx], arg.GetType())).SetOp<0>(arg);
                    ctx.EmitInst(copy_arg_to_reg);
                }
                else
                {
                    Int32 offset = 16 + (arg_idx - 8) * 8;
                    MachineInstruction copy_arg_to_reg(InstMove);
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
        Uint32 spill_size = (gp_regs.size() + fp_regs.size()) * 8;

        Uint32 const stack_size = MF.GetStackAllocationSize();
        Uint32 const total = stack_size + spill_size;

        Uint32 aligned = OLA_ALIGN_UP(total, STACK_ALIGNMENT);
        Uint32 padding = aligned - total;

        Bool const needs_frame = (stack_size > 0) || (spill_size > 0);
        MachineOperand fp = MachineOperand::ISAReg(ARM64_X29, MachineType::Int64);
        MachineOperand sp = MachineOperand::ISAReg(ARM64_SP, MachineType::Int64);

        auto& insts = ctx.GetCurrentBasicBlock()->Instructions();
        auto insert_it = insts.begin();
        auto sub_it = insts.end();
        if (needs_frame)
        {
            if (!MF.HasFrame())
            {
                MachineInstruction push_fp(InstPush);
                push_fp.SetOp<0>(fp);
                insert_it = ctx.EmitInst(insert_it, push_fp); ++insert_it;

                MachineInstruction push_lr(InstPush);
                push_lr.SetOp<0>(MachineOperand::ISAReg(ARM64_X30, MachineType::Int64));
                insert_it = ctx.EmitInst(insert_it, push_lr); ++insert_it;

                MachineInstruction set_fp(InstMove);
                set_fp.SetOp<0>(fp).SetOp<1>(sp);
                insert_it = ctx.EmitInst(insert_it, set_fp); ++insert_it;

                MachineInstruction sub_sp_inst(InstSub);
                sub_sp_inst.SetOp<0>(sp).SetOp<1>(MachineOperand::Immediate(aligned, MachineType::Int64));
                insert_it = ctx.EmitInst(insert_it, sub_sp_inst); ++insert_it;
                sub_it = std::prev(insert_it);

                MF.SetHasFrame(true);
            }
            else
            {
                sub_it = std::find_if(insts.begin(), insts.end(),
                    [](MachineInstruction& mi)
                    {
                        return mi.GetOpcode() == InstSub &&
                            mi.GetOp<0>().IsReg() && mi.GetOp<0>().GetReg().reg == ARM64_SP;
                    });
            }
        }
        else
        {
            sub_it = std::find_if(insts.begin(), insts.end(),
                [](MachineInstruction& mi)
                {
                    return mi.GetOpcode() == InstSub &&
                        mi.GetOp<0>().IsReg() && mi.GetOp<0>().GetReg().reg == ARM64_SP;
                });
        }

        if (sub_it != insts.end())
        {
            sub_it->SetOp<1>(MachineOperand::Immediate(aligned, MachineType::Int64));
        }

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

    void ARM64TargetFrameInfo::EmitEpilogue(MachineFunction& MF, MachineContext& ctx) const
    {
        if (MF.HasFrame())
        {
            MachineOperand fp = MachineOperand::ISAReg(ARM64_X29, MachineType::Int64);
            MachineOperand sp = MachineOperand::ISAReg(ARM64_SP, MachineType::Int64);

            MachineInstruction reset_sp(InstMove);
            reset_sp.SetOp<0>(sp).SetOp<1>(fp);
            ctx.EmitInst(reset_sp);

            // pop lr ; pop fp
            MachineInstruction pop_lr(InstPop);
            pop_lr.SetOp<0>(MachineOperand::ISAReg(ARM64_X30, MachineType::Int64));
            ctx.EmitInst(pop_lr);

            MachineInstruction pop_fp(InstPop);
            pop_fp.SetOp<0>(fp);
            ctx.EmitInst(pop_fp);
        }
        ctx.EmitInst(MachineInstruction(InstRet));
    }

    void ARM64TargetFrameInfo::EmitEpiloguePostRA(MachineFunction& MF, MachineContext& ctx) const
    {
        auto& insts = ctx.GetCurrentBasicBlock()->Instructions();

        if (MF.HasFrame())
        {
            auto mov_it = std::find_if(insts.begin(), insts.end(),
                [](MachineInstruction& mi)
                {
                    return mi.GetOpcode() == InstMove &&
                        mi.GetOp<0>().IsReg() && mi.GetOp<0>().GetReg().reg == ARM64_SP &&
                        mi.GetOp<1>().IsReg() && mi.GetOp<1>().GetReg().reg == ARM64_X29;
                });

            if (mov_it == insts.end())
            {
                MachineOperand fp = MachineOperand::ISAReg(ARM64_X29, MachineType::Int64);

                auto ret_it = std::find_if(insts.begin(), insts.end(),
                    [](MachineInstruction& mi)
                    {
                        return mi.GetOpcode() == InstRet;
                    });

                if (ret_it != insts.end())
                {
                    MachineInstruction reset_stack(InstMove);
                    reset_stack.SetOp<0>(MachineOperand::ISAReg(ARM64_SP, MachineType::Int64)).SetOp<1>(fp);
                    auto mov_insert_it = ctx.EmitInst(ret_it, reset_stack);

                    MachineInstruction pop_lr(InstPop);
                    pop_lr.SetOp<0>(MachineOperand::ISAReg(ARM64_X30, MachineType::Int64));
                    ctx.EmitInst(std::next(mov_insert_it), pop_lr);

                    MachineInstruction pop_fp(InstPop);
                    pop_fp.SetOp<0>(fp);
                    ctx.EmitInst(std::next(mov_insert_it, 2), pop_fp);
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

    void ARM64TargetFrameInfo::EmitReturn(ReturnInst* RI, MachineContext& ctx) const
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
            return_register = MachineOperand::ISAReg(ARM64_V0, MachineType::Float64);
        }
        else
        {
            MachineType const return_type = V->GetType()->IsBoolean() ? MachineType::Int8 : MachineType::Int64;
            return_register = MachineOperand::ISAReg(ARM64_X0, return_type);
        }

        MachineInstruction copy(InstMove);
        copy.SetOp<0>(return_register).SetOp<1>(ctx.GetOperand(V));
        ctx.EmitInst(copy);
    }
}
