#include "X86TargetISelInfo.h"
#include "X86.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/MachineContext.h"

namespace ola
{
	Bool X86TargetISelInfo::LowerInstruction(Instruction* I, MachineContext& ctx) const
	{
		if (BinaryInst* BI = dyn_cast<BinaryInst>(I))
		{
			Opcode opcode = I->GetOpcode();
			if (opcode == Opcode::SDiv || opcode == Opcode::SRem)
			{
				MachineOperand dst = ctx.VirtualReg(BI->GetType());
				MachineOperand op1 = ctx.GetOperand(BI->GetLHS());
				MachineOperand op2 = ctx.GetOperand(BI->GetRHS());

				MachineInstruction move_to_rax(InstMove);
				move_to_rax.SetOp<0>(MachineOperand::ISAReg(X86_RAX, MachineType::Int64));
				move_to_rax.SetOp<1>(op1);
				ctx.EmitInst(move_to_rax);

				MachineInstruction cqo(X86_InstCqo);
				ctx.EmitInst(cqo);

				if (op2.IsImmediate())
				{
					MachineOperand op2_reg = ctx.VirtualReg(BI->GetType());
					MachineInstruction move_to_reg(InstMove);
					move_to_reg.SetOp<0>(op2_reg);
					move_to_reg.SetOp<1>(op2);
					ctx.EmitInst(move_to_reg);
					MachineInstruction idiv(InstSDiv);
					idiv.SetOp<0>(op2_reg);
					ctx.EmitInst(idiv);
				}
				else
				{
					MachineInstruction idiv(InstSDiv);
					idiv.SetOp<0>(op2);
					ctx.EmitInst(idiv);
				}

				if (opcode == Opcode::SDiv)
				{
					MachineInstruction move_quotient(InstMove);
					move_quotient.SetOp<0>(dst);
					move_quotient.SetOp<1>(MachineOperand::ISAReg(X86_RAX, MachineType::Int64));
					ctx.EmitInst(move_quotient);
				}
				else if (opcode == Opcode::SRem)
				{
					MachineInstruction move_remainder(InstMove);
					move_remainder.SetOp<0>(dst);
					move_remainder.SetOp<1>(MachineOperand::ISAReg(X86_RDX, MachineType::Int64));
					ctx.EmitInst(move_remainder);
				}
				ctx.MapOperand(BI, dst);
				return true;
			}
		}
		else if (SelectInst* SI = dyn_cast<SelectInst>(I))
		{
			if (SI->GetType()->IsFloat())
			{
				Value* predicate = SI->GetPredicate();
				Value* true_value = SI->GetTrueValue();
				Value* false_value = SI->GetFalseValue();
				MachineOperand result_reg = ctx.VirtualReg(SI->GetType());
				MachineOperand true_op = ctx.GetOperand(true_value);
				MachineOperand false_op = ctx.GetOperand(false_value);
				MachineOperand predicate_op = ctx.GetOperand(predicate);

				ctx.EmitInst(MachineInstruction(InstMove)
					.SetOp<0>(result_reg)
					.SetOp<1>(false_op));

				MachineInstruction testMI(InstTest);
				testMI.SetOp<0>(predicate_op);
				testMI.SetOp<1>(predicate_op);
				ctx.EmitInst(testMI);

				MachineBasicBlock* MBB = ctx.GetCurrentBasicBlock();
				MachineFunction* MF = MBB->GetFunction();
				auto Where = std::find_if(MF->Blocks().begin(), MF->Blocks().end(),
					[MBB](const auto& block) { return block.get() == MBB; });
				++Where;
				auto& inserted = *MF->Blocks().insert(Where, std::make_unique<MachineBasicBlock>(MF, ctx.GetLabel()));
				MachineBasicBlock* SkipBlock = inserted.get();

				ctx.EmitInst(MachineInstruction(InstJE).SetOp<0>(MachineOperand::Relocable(SkipBlock)));
				ctx.EmitInst(MachineInstruction(InstMove)
					.SetOp<0>(result_reg)
					.SetOp<1>(true_op));
				ctx.MapOperand(SI, result_reg);
				ctx.SetCurrentBasicBlock(SkipBlock);
				return true;
			}
		}
		return false;
	}

	void X86TargetISelInfo::LegalizeInstruction(InstLegalizeContext& legalize_ctx, MachineContext& lowering_ctx) const
	{
		MachineInstruction& MI = legalize_ctx.instruction;
		auto& instructions = legalize_ctx.instructions;
		auto& instruction_iter = legalize_ctx.instruction_iterator;

		switch (MI.GetOpcode())
		{
		case InstMove:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand src = MI.GetOperand(1);
			if (src.IsMemoryOperand() && dst.IsMemoryOperand())
			{
				MachineOperand tmp = lowering_ctx.VirtualReg(src.GetType());
				MI.SetOp<0>(tmp);

				MachineInstruction MI2(InstMove);
				MI2.SetOp<0>(dst);
				MI2.SetOp<1>(tmp);
				instructions.insert(++instruction_iter, MI2);
			}
		}
		break;
		case InstStore:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand src = MI.GetOperand(1);
			if (src.IsImmediate() && (dst.GetType() == MachineType::Float64 || src.GetType() == MachineType::Float64))
			{
				MachineOperand tmp = lowering_ctx.VirtualReg(src.GetType());
				MI.SetOp<0>(tmp);
				MI.SetOpcode(X86_InstMoveFP);

				MachineInstruction MI2(InstStore);
				MI2.SetOp<0>(dst);
				MI2.SetOp<1>(tmp);
				instructions.insert(++instruction_iter, MI2);
			}
			else if (dst.GetType() == MachineType::Ptr && src.IsMemoryOperand())
			{
				MachineOperand tmp = lowering_ctx.VirtualReg(dst.GetType());
				MI.SetOp<0>(tmp);
				MI.SetOp<1>(src);
				MI.SetOpcode(InstLoadGlobalAddress);

				MachineInstruction MI2(InstStore);
				MI2.SetOp<0>(dst);
				MI2.SetOp<1>(tmp);

				++instruction_iter;
				instructions.insert(instruction_iter, MI2);
			}
			else if (src.IsRelocable())
			{
				MachineOperand tmp = lowering_ctx.VirtualReg(dst.GetType());
				MI.SetOp<0>(tmp);
				MI.SetOp<1>(src);
				MI.SetOpcode(InstLoad);

				MachineInstruction MI2(InstStore);
				MI2.SetOp<0>(dst);
				MI2.SetOp<1>(tmp);

				++instruction_iter;
				instructions.insert(instruction_iter, MI2);
			}
		}
		break;
		case InstAdd:
		case InstSub:
		case InstAnd:
		case InstOr:
		case InstXor:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand op1 = MI.GetOperand(1);
			MachineOperand op2 = MI.GetOperand(2);
			if (!op2.IsUndefined())
			{
				MI.SetOp<1>(op2);
				MachineInstruction MI2(InstMove);
				MI2.SetOp<0>(dst);
				MI2.SetOp<1>(op1);
				instructions.insert(instruction_iter, MI2);
			}
		}
		break;
		case InstShl:
		case InstAShr:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand op1 = MI.GetOperand(1);
			MachineOperand op2 = MI.GetOperand(2);

			MI.SetOp<1>(op2);
			MachineInstruction MI2(InstMove);
			MI2.SetOp<0>(dst);
			MI2.SetOp<1>(op1);
			instructions.insert(instruction_iter, MI2);

			if (!op2.IsImmediate())
			{
				MachineInstruction MI3(InstMove);
				MI3.SetOp<0>(MachineOperand::ISAReg(X86_RCX, op2.GetType()));
				MI3.SetOp<1>(op2);
				instructions.insert(instruction_iter, MI3);
				MI.SetOp<1>(MachineOperand::ISAReg(X86_RCX, MachineType::Int8));
			}
		}
		break;
		case InstNeg:
		case InstNot:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand op = MI.GetOperand(1);

			MachineInstruction MI2(InstMove);
			MI2.SetOp<0>(dst);
			MI2.SetOp<1>(op);
			instructions.insert(instruction_iter, MI2);
		}
		break;
		case InstSMul:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand op1 = MI.GetOperand(1);
			MachineOperand op2 = MI.GetOperand(2);

			MI.SetOp<1>(op2);
			MachineInstruction MI2(InstMove);
			MI2.SetOp<0>(dst);
			MI2.SetOp<1>(op1);
			instructions.insert(instruction_iter, MI2);
		}
		break;
		case InstICmp:
		{
			if (!MI.GetOperand(2).IsUndefined())
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand op1 = MI.GetOperand(1);
				MachineOperand op2 = MI.GetOperand(2);
				MachineOperand compare_op = MI.GetOperand(3);

				auto GetOppositeCondition = [](MachineOperand compare_op) -> CompareOp
					{
						OLA_ASSERT(compare_op.IsImmediate());
						CompareOp cmp_op = (CompareOp)compare_op.GetImmediate();
						switch (cmp_op)
						{
						case CompareOp::ICmpEQ:  return CompareOp::ICmpEQ;
						case CompareOp::ICmpNE:  return CompareOp::ICmpNE;
						case CompareOp::ICmpSGT: return CompareOp::ICmpSLE;
						case CompareOp::ICmpSGE: return CompareOp::ICmpSLT;
						case CompareOp::ICmpSLT: return CompareOp::ICmpSGE;
						case CompareOp::ICmpSLE: return CompareOp::ICmpSGT;
						}
						OLA_ASSERT_MSG(false, "opcode has to be compare instruction!");
						return CompareOp::ICmpEQ;
					};
				MI.SetOp<0>(op1).SetOp<1>(op2);
				if (op1.IsImmediate())
				{
					OLA_ASSERT(!op2.IsImmediate());
					MI.SetOp<0>(op2);
					MI.SetOp<1>(op1);
					compare_op = MachineOperand::Immediate((Uint32)GetOppositeCondition(compare_op), MachineType::Int64);
				}

				auto GetSetCondition = [](MachineOperand compare_op) -> Uint32
					{
						OLA_ASSERT(compare_op.IsImmediate());
						CompareOp cmp_op = (CompareOp)compare_op.GetImmediate();
						switch (cmp_op)
						{
						case CompareOp::ICmpEQ:  return X86_InstSetE;
						case CompareOp::ICmpNE:  return X86_InstSetNE;
						case CompareOp::ICmpSGT: return X86_InstSetGT;
						case CompareOp::ICmpSGE: return X86_InstSetGE;
						case CompareOp::ICmpSLT: return X86_InstSetLT;
						case CompareOp::ICmpSLE: return X86_InstSetLE;
						}
						OLA_ASSERT_MSG(false, "opcode has to be compare instruction!");
						return InstUnknown;
					};

				MachineInstruction MI2(GetSetCondition(compare_op));
				MI2.SetOp<0>(dst);
				instructions.insert(++instruction_iter, MI2);

				MachineInstruction MI3(InstAnd);
				MI3.SetOp<0>(dst);
				MI3.SetOp<1>(MachineOperand::Immediate(1, MachineType::Int8));
				instructions.insert(instruction_iter++, MI3);
			}
		}
		break;
		case InstCMoveEQ:
		case InstCMoveNE:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand src = MI.GetOperand(1);

			if (dst.GetType() == MachineType::Float64)
			{
				MachineBasicBlock* MBB = lowering_ctx.GetCurrentBasicBlock();
				MachineFunction* MF = MBB->GetFunction();

				auto Where = std::find_if(MF->Blocks().begin(), MF->Blocks().end(),
					[MBB](const auto& block) { return block.get() == MBB; });
				++Where;

				auto& inserted = *MF->Blocks().insert(Where, std::make_unique<MachineBasicBlock>(MF, lowering_ctx.GetLabel()));
				MachineBasicBlock* ContinuationBlock = inserted.get();

				Uint32 jump_opcode = (MI.GetOpcode() == InstCMoveNE) ? InstJE : InstJNE;
				MI.SetOpcode(jump_opcode);
				MI.SetOp<0>(MachineOperand::Relocable(ContinuationBlock));
				MI.SetOp<1>(MachineOperand::Undefined());

				MachineInstruction mov(X86_InstMoveFP);
				mov.SetOp<0>(dst);
				mov.SetOp<1>(src);
				++instruction_iter;
				instruction_iter = instructions.insert(instruction_iter, mov);

				MachineInstruction jmp(InstJump);
				jmp.SetOp<0>(MachineOperand::Relocable(ContinuationBlock));
				++instruction_iter;
				instruction_iter = instructions.insert(instruction_iter, jmp);

				auto& cont_instructions = ContinuationBlock->Instructions();
				auto move_start = instruction_iter;
				++move_start;
				while (move_start != instructions.end())
				{
					cont_instructions.push_back(std::move(*move_start));
					move_start = instructions.erase(move_start);
				}
			}
			else if (src.IsImmediate())
			{
				MachineOperand tmp = lowering_ctx.VirtualReg(src.GetType());
				MachineInstruction MI2(InstMove);
				MI2.SetOp<0>(tmp);
				MI2.SetOp<1>(src);
				MI.SetOp<1>(tmp);
				instructions.insert(instruction_iter, MI2);
			}
		}
		break;
		case InstFAdd:
		case InstFSub:
		case InstFMul:
		case InstFDiv:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand op1 = MI.GetOperand(1);
			MachineOperand op2 = MI.GetOperand(2);

			MI.SetOp<1>(op2);
			MachineInstruction MI2(X86_InstMoveFP);
			MI2.SetOp<0>(dst);
			MI2.SetOp<1>(op1);

			instructions.insert(instruction_iter, MI2);

			if (op2.IsImmediate())
			{
				MachineOperand tmp = lowering_ctx.VirtualReg(MachineType::Float64);

				MachineInstruction MI3(X86_InstMoveFP);
				MI3.SetOp<0>(tmp);
				MI3.SetOp<1>(op2);
				instructions.insert(instruction_iter, MI3);

				MI.SetOp<1>(tmp);
			}
		}
		break;
		case InstFNeg:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand src = MI.GetOperand(1);

			MachineInstruction MI2(X86_InstMoveFP);
			MI2.SetOp<0>(dst);
			MI2.SetOp<1>(src);
			instructions.insert(instruction_iter, MI2);

			MachineInstruction MI3(X86_InstMoveFP);
			MachineOperand neg_mask = lowering_ctx.VirtualReg(MachineType::Float64);
			MI3.SetOp<0>(neg_mask);
			MI3.SetOp<1>(MachineOperand::Immediate(0x8000000000000000, MachineType::Float64));
			instructions.insert(instruction_iter, MI3);

			MI.SetOpcode(X86_InstXorFP);
			MI.SetOp<0>(dst);
			MI.SetOp<1>(neg_mask);
		}
		break;
		case InstFCmp:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand op1 = MI.GetOperand(1);
			MachineOperand op2 = MI.GetOperand(2);
			MachineOperand compare_op = MI.GetOperand(3);

			MI.SetOp<0>(op1).SetOp<1>(op2);
			auto GetOppositeCondition = [](MachineOperand compare_op) -> CompareOp
				{
					OLA_ASSERT(compare_op.IsImmediate());
					CompareOp cmp_op = (CompareOp)compare_op.GetImmediate();
					switch (cmp_op)
					{
					case CompareOp::FCmpOEQ:  return CompareOp::FCmpOEQ;
					case CompareOp::FCmpONE:  return CompareOp::FCmpONE;
					case CompareOp::FCmpOGT:  return CompareOp::FCmpOLE;
					case CompareOp::FCmpOGE:  return CompareOp::FCmpOLT;
					case CompareOp::FCmpOLT:  return CompareOp::FCmpOGE;
					case CompareOp::FCmpOLE:  return CompareOp::FCmpOGT;
					}
					OLA_ASSERT_MSG(false, "opcode has to be compare instruction!");
					return CompareOp::FCmpOEQ;
				};
			if (op1.IsImmediate())
			{
				OLA_ASSERT(!op2.IsImmediate());
				MI.SetOp<0>(op2);
				MI.SetOp<1>(op1);
				compare_op = MachineOperand::Immediate((Uint32)GetOppositeCondition(compare_op), MachineType::Int64);
			}

			auto GetSetCondition = [](MachineOperand compare_op) -> Uint32
				{
					OLA_ASSERT(compare_op.IsImmediate());
					CompareOp cmp_op = (CompareOp)compare_op.GetImmediate();
					switch (cmp_op)
					{
					case CompareOp::FCmpOEQ: return X86_InstSetE;
					case CompareOp::FCmpONE: return X86_InstSetNE;
					case CompareOp::FCmpOGT: return X86_InstSetA;
					case CompareOp::FCmpOGE: return X86_InstSetAE;
					case CompareOp::FCmpOLT: return X86_InstSetB;
					case CompareOp::FCmpOLE: return X86_InstSetBE;
					}
					OLA_ASSERT_MSG(false, "opcode has to be compare instruction!");
					return InstUnknown;
				};

			MachineInstruction MI2(GetSetCondition(compare_op));
			MI2.SetOp<0>(dst);
			instructions.insert(++instruction_iter, MI2);

			MachineInstruction MI3(InstAnd);
			MI3.SetOp<0>(dst);
			MI3.SetOp<1>(MachineOperand::Immediate(1, MachineType::Int8));
			instructions.insert(instruction_iter++, MI3);
		}
		break;
		case InstS2F:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand src = MI.GetOperand(1);
			OLA_ASSERT(dst.GetType() == MachineType::Float64);

			if (src.GetType() == MachineType::Int8)
			{
				MachineOperand tmp = lowering_ctx.VirtualReg(MachineType::Int64);
				// If source is immediate, use Move instead of ZExt
				if (src.IsImmediate())
				{
					src.SetType(MachineType::Int64);
					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp).SetOp<1>(src);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<1>(tmp);
				}
				else
				{
					MachineInstruction MI2(InstZExt);
					MI2.SetOp<0>(tmp).SetOp<1>(src);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<1>(tmp);
				}
			}
		}
		break;
		case InstZExt:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand op1 = MI.GetOperand(1);
			if (op1.IsImmediate())
			{
				MI.SetOpcode(InstMove);
			}
		}
		break;
		case InstMemCpy:
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand src = MI.GetOperand(1);
			MachineOperand size_op = MI.GetOperand(2);

			OLA_ASSERT(size_op.IsImmediate());
			Int64 size = size_op.GetImmediate();

			MachineOperand src_base = src;
			MachineOperand dst_base = dst;
			Bool first = true;

			if (src.IsStackObject() || src.IsMemoryOperand())
			{
				src_base = lowering_ctx.VirtualReg(MachineType::Ptr);
				MachineInstruction lea_src(InstLoadGlobalAddress);
				lea_src.SetOp<0>(src_base).SetOp<1>(src);
				MI.SetOpcode(InstLoadGlobalAddress);
				MI.SetOp<0>(src_base).SetOp<1>(src).SetOp<2>(MachineOperand::Undefined());
				first = false;
			}

			if (dst.IsStackObject() || dst.IsMemoryOperand())
			{
				dst_base = lowering_ctx.VirtualReg(MachineType::Ptr);
				MachineInstruction lea_dst(InstLoadGlobalAddress);
				lea_dst.SetOp<0>(dst_base).SetOp<1>(dst);
				if (first)
				{
					MI.SetOpcode(InstLoadGlobalAddress);
					MI.SetOp<0>(dst_base).SetOp<1>(dst).SetOp<2>(MachineOperand::Undefined());
					first = false;
				}
				else
				{
					instructions.insert(instruction_iter, lea_dst);
				}
			}

			Int64 offset = 0;
			while (size >= 8)
			{
				MachineOperand tmp = lowering_ctx.VirtualReg(MachineType::Int64);
				MachineOperand current_src = src_base;
				MachineOperand current_dst = dst_base;

				if (offset > 0)
				{
					MachineOperand src_ptr = lowering_ctx.VirtualReg(MachineType::Ptr);
					MachineInstruction add_src(InstAdd);
					add_src.SetOp<0>(src_ptr).SetOp<1>(src_base).SetOp<2>(MachineOperand::Immediate(offset, MachineType::Int64));
					if (first)
					{
						MI.SetOpcode(InstAdd);
						MI.SetOp<0>(src_ptr).SetOp<1>(src_base).SetOp<2>(MachineOperand::Immediate(offset, MachineType::Int64));
						first = false;
					}
					else
					{
						instructions.insert(instruction_iter, add_src);
					}
					current_src = src_ptr;
				}

				MachineInstruction load(InstLoad);
				load.SetOp<0>(tmp).SetOp<1>(current_src);
				if (first)
				{
					MI.SetOpcode(InstLoad);
					MI.SetOp<0>(tmp).SetOp<1>(current_src).SetOp<2>(MachineOperand::Undefined());
					first = false;
				}
				else
				{
					instructions.insert(instruction_iter, load);
				}

				if (offset > 0)
				{
					MachineOperand dst_ptr = lowering_ctx.VirtualReg(MachineType::Ptr);
					MachineInstruction add_dst(InstAdd);
					add_dst.SetOp<0>(dst_ptr).SetOp<1>(dst_base).SetOp<2>(MachineOperand::Immediate(offset, MachineType::Int64));
					instructions.insert(instruction_iter, add_dst);
					current_dst = dst_ptr;
				}

				MachineInstruction store(InstStore);
				store.SetOp<0>(current_dst).SetOp<1>(tmp);

				++instruction_iter;
				instruction_iter = instructions.insert(instruction_iter, store);

				offset += 8;
				size -= 8;
			}

			while (size > 0)
			{
				MachineOperand tmp = lowering_ctx.VirtualReg(MachineType::Int8);
				MachineOperand current_src = src_base;
				MachineOperand current_dst = dst_base;

				MachineOperand src_ptr = lowering_ctx.VirtualReg(MachineType::Ptr);
				MachineInstruction add_src(InstAdd);
				add_src.SetOp<0>(src_ptr).SetOp<1>(src_base).SetOp<2>(MachineOperand::Immediate(offset, MachineType::Int64));
				if (first)
				{
					MI.SetOpcode(InstAdd);
					MI.SetOp<0>(src_ptr).SetOp<1>(src_base).SetOp<2>(MachineOperand::Immediate(offset, MachineType::Int64));
					first = false;
				}
				else
				{
					instructions.insert(instruction_iter, add_src);
				}
				current_src = src_ptr;

				MachineInstruction load(InstLoad);
				load.SetOp<0>(tmp).SetOp<1>(current_src);
				instructions.insert(instruction_iter, load);

				MachineOperand dst_ptr = lowering_ctx.VirtualReg(MachineType::Ptr);
				MachineInstruction add_dst(InstAdd);
				add_dst.SetOp<0>(dst_ptr).SetOp<1>(dst_base).SetOp<2>(MachineOperand::Immediate(offset, MachineType::Int64));
				instructions.insert(instruction_iter, add_dst);
				current_dst = dst_ptr;

				MachineInstruction store(InstStore);
				store.SetOp<0>(current_dst).SetOp<1>(tmp);

				++instruction_iter;
				instruction_iter = instructions.insert(instruction_iter, store);

				offset += 1;
				size -= 1;
			}

			if (first)
			{
				MI.SetDead();
			}
		}
		break;
		}
	}

	void X86TargetISelInfo::PostLegalizeInstruction(InstLegalizeContext& legalize_ctx) const
	{
		MachineInstruction& MI = legalize_ctx.instruction;
		auto& instructions = legalize_ctx.instructions;
		auto& instruction_iter = legalize_ctx.instruction_iterator;
		auto GetScratchReg = [&legalize_ctx](MachineType type)
			{
				if (type == MachineType::Float64)
				{
					return MachineOperand::ISAReg(legalize_ctx.target_reg_info.GetFPScratchRegister(), type);
				}
				else
				{
					return MachineOperand::ISAReg(legalize_ctx.target_reg_info.GetGPScratchRegister(), type);
				}
			};

		if (MI.GetOpcode() == InstMove)
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand src = MI.GetOperand(1);
			if (dst.IsMemoryOperand())
			{
				MI.SetOpcode(InstStore);
			}
			else if (src.IsMemoryOperand())
			{
				MI.SetOpcode(InstLoad);
			}
		}

		// LEA format: lea dst, [base + index*scale + disp]
		// Op 0: dst, Op 1: base, Op 2: index, Op 3: scale, Op 4: disp
		if (MI.GetOpcode() == X86_InstLea)
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand base = MI.GetOperand(1);
			MachineOperand index = MI.GetOperand(2);
			MachineOperand scale = MI.GetOperand(3);
			MachineOperand disp = MI.GetOperand(4);
			Bool base_is_mem = base.IsMemoryOperand();
			Bool index_is_mem = !index.IsUndefined() && index.IsMemoryOperand();
			if (base_is_mem && index_is_mem)
			{
				auto scratch = GetScratchReg(MachineType::Int64);
				Int64 scale_val = scale.GetImmediate();
				Int64 disp_val = disp.GetImmediate();

				// mov scratch, [base]
				MachineInstruction load_base(InstLoad);
				load_base.SetOp<0>(scratch).SetOp<1>(base);
				instructions.insert(instruction_iter, load_base);
				if (scale_val == 1)
				{
					// add scratch, [index] - x86 supports mem source
					MachineInstruction add_index(InstAdd);
					add_index.SetOp<0>(scratch).SetOp<1>(index);
					instructions.insert(instruction_iter, add_index);
				}
				else
				{
					// For scale > 1, use dst as temp if available
					if (!dst.IsMemoryOperand())
					{
						MachineInstruction load_index(InstLoad);
						load_index.SetOp<0>(dst).SetOp<1>(index);
						instructions.insert(instruction_iter, load_index);

						MachineInstruction mul_scale(InstSMul);
						mul_scale.SetOp<0>(dst).SetOp<1>(MachineOperand::Immediate(scale_val, MachineType::Int64));
						instructions.insert(instruction_iter, mul_scale);

						MachineInstruction add_result(InstAdd);
						add_result.SetOp<0>(scratch).SetOp<1>(dst);
						instructions.insert(instruction_iter, add_result);
					}
				}

				if (disp_val != 0)
				{
					MachineInstruction add_disp(InstAdd);
					add_disp.SetOp<0>(scratch).SetOp<1>(MachineOperand::Immediate(disp_val, MachineType::Int64));
					instructions.insert(instruction_iter, add_disp);
				}

				if (dst.IsMemoryOperand())
				{
					MI.SetOpcode(InstStore);
					MI.SetOp<0>(dst);
					MI.SetOp<1>(scratch);
				}
				else
				{
					MI.SetOpcode(InstMove);
					MI.SetOp<0>(dst);
					MI.SetOp<1>(scratch);
				}
			}
			else if (base_is_mem)
			{
				auto scratch = GetScratchReg(MachineType::Int64);
				MachineInstruction load_base(InstLoad);
				load_base.SetOp<0>(scratch).SetOp<1>(base);
				instructions.insert(instruction_iter, load_base);
				MI.SetOp<1>(scratch);
			}
			else if (index_is_mem)
			{
				auto scratch = GetScratchReg(MachineType::Int64);
				MachineInstruction load_index(InstLoad);
				load_index.SetOp<0>(scratch).SetOp<1>(index);
				instructions.insert(instruction_iter, load_index);
				MI.SetOp<2>(scratch);
			}

			if (MI.GetOpcode() == X86_InstLea && dst.IsMemoryOperand())
			{
				auto scratch = GetScratchReg(MachineType::Int64);
				MI.SetOp<0>(scratch);
				MachineInstruction store_result(InstStore);
				store_result.SetOp<0>(dst).SetOp<1>(scratch);
				instructions.insert(++instruction_iter, store_result);
			}
		}

		if (MI.GetOpcode() == InstLoad && MI.GetOperand(0).IsMemoryOperand())
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand src = MI.GetOperand(1);
			auto scratch = GetScratchReg(dst.GetType());
			Uint32 load_opcode = (dst.GetType() == MachineType::Float64) ? X86_InstLoadFP : InstLoad;
			Uint32 store_opcode = (dst.GetType() == MachineType::Float64) ? X86_InstStoreFP : InstStore;
			MI.SetOp<0>(scratch);
			MI.SetOpcode(load_opcode);
			MachineInstruction MI2(store_opcode);
			MI2.SetOp<0>(dst).SetOp<1>(scratch);
			instructions.insert(++instruction_iter, MI2);
		}
		else if (MI.GetOpcode() == InstStore && MI.GetOperand(1).IsMemoryOperand())
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand src = MI.GetOperand(1);
			auto scratch = GetScratchReg(src.GetType());
			Uint32 load_opcode = (src.GetType() == MachineType::Float64) ? X86_InstLoadFP : InstLoad;
			Uint32 store_opcode = (src.GetType() == MachineType::Float64) ? X86_InstStoreFP : InstStore;
			MachineInstruction MI2(load_opcode);
			MI2.SetOp<0>(scratch).SetOp<1>(src);
			instructions.insert(instruction_iter, MI2);
			MI.SetOp<1>(scratch);
			MI.SetOpcode(store_opcode);
		}
		else if ((MI.GetOpcode() == InstMove || MI.GetOpcode() == InstLoadGlobalAddress) 
			   && MI.GetOperand(0).IsMemoryOperand() && MI.GetOperand(1).IsMemoryOperand())
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand src = MI.GetOperand(1);
			auto scratch = GetScratchReg(dst.GetType());
			Uint32 load_opcode = (dst.GetType() == MachineType::Float64) ? X86_InstLoadFP : InstLoad;
			Uint32 store_opcode = (dst.GetType() == MachineType::Float64) ? X86_InstStoreFP : InstStore;
			MachineInstruction MI2(load_opcode);
			MI2.SetOp<0>(scratch).SetOp<1>(src);
			instructions.insert(instruction_iter, MI2);
			MI.SetOp<1>(scratch);
			MI.SetOpcode(store_opcode);
		}

		if (MI.GetOpcode() == X86_InstMoveFP)
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand src = MI.GetOperand(1);
			if (dst.IsMemoryOperand() && src.IsMemoryOperand())
			{
				auto scratch = GetScratchReg(MachineType::Float64);
				MachineInstruction MI2(X86_InstLoadFP);
				MI2.SetOp<0>(scratch).SetOp<1>(src);
				instructions.insert(instruction_iter, MI2);
				MI.SetOp<1>(scratch);
				MI.SetOpcode(X86_InstStoreFP);
			}
		}

		if (MI.GetOpcode() == X86_InstLoadFP && MI.GetOperand(0).IsMemoryOperand())
		{
			MachineOperand dst = MI.GetOperand(0);
			auto scratch = GetScratchReg(MachineType::Float64);
			MI.SetOp<0>(scratch);
			MachineInstruction MI2(X86_InstStoreFP);
			MI2.SetOp<0>(dst).SetOp<1>(scratch);
			instructions.insert(++instruction_iter, MI2);
		}
		if (MI.GetOpcode() == X86_InstStoreFP && MI.GetOperand(1).IsMemoryOperand())
		{
			MachineOperand src = MI.GetOperand(1);
			auto scratch = GetScratchReg(MachineType::Float64);
			MachineInstruction MI2(X86_InstLoadFP);
			MI2.SetOp<0>(scratch).SetOp<1>(src);
			instructions.insert(instruction_iter, MI2);
			MI.SetOp<1>(scratch);
		}

		if (MI.GetOpcode() >= InstMove && MI.GetOpcode() <= InstStore)
		{
			MachineOperand dst = MI.GetOperand(0);
			MachineOperand src = MI.GetOperand(1);
			if (src.GetType() == MachineType::Float64 && MI.GetOpcode() == InstStore)
			{
				MI.SetOpcode(X86_InstStoreFP);
				if (src.IsImmediate())
				{
					auto scratch = GetScratchReg(MachineType::Float64);
					MachineInstruction load_imm(X86_InstMoveFP);
					load_imm.SetOp<0>(scratch).SetOp<1>(src);
					instructions.insert(instruction_iter, load_imm);
					MI.SetOp<1>(scratch);
				}
			}
			else if (dst.GetType() == MachineType::Float64 && MI.GetOpcode() == InstLoad)
			{
				MI.SetOpcode(X86_InstLoadFP);
			}
			else if (dst.GetType() == MachineType::Float64 || src.GetType() == MachineType::Float64)
			{
				if (MI.GetOpcode() == InstMove)
				{
					MI.SetOpcode(X86_InstMoveFP);
				}
			}
		}
	}
}