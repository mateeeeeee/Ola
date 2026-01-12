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
		if (SelectInst* SI = dyn_cast<SelectInst>(I))
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
			if (src.IsImmediate())
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
		else if (MI.GetOpcode() == InstMove && MI.GetOperand(0).IsMemoryOperand() && MI.GetOperand(1).IsMemoryOperand())
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
