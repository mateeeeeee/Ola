#include <fstream>
#include "ARMTarget.h"
#include "Backend/Custom/Codegen/ARM/ARM.h"
#include "ARMTargetFrameInfo.h"
#include "ARMTargetInstInfo.h"
#include "ARMAsmPrinter.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/MachineContext.h"

namespace ola
{
	class ARMTargetDataLayout : public TargetDataLayout
	{
	public:
		virtual Bool   IsLittleEndian() const override { return true; }
		virtual Uint64 GetBuiltinAlignment(IRType const* type) const override
		{
			return type->GetSize();
		}
		virtual Uint64 GetPointerSize() const override
		{
			return 8u;
		}
		virtual Uint64 GetCodeAlignment() const override
		{
			return 8u;
		}
		virtual Uint64 GetStorageAlignment() const override
		{
			return 8u;
		}
	};

	class ARMTargetISelInfo : public TargetISelInfo
	{
	public:
		virtual Bool LowerInstruction(Instruction* I, MachineContext& ctx) const override
		{
			return false;
		}

		virtual void LegalizeInstruction(InstLegalizeContext& legalize_ctx, MachineContext& lowering_ctx) const override
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

				if ((dst.GetType() == MachineType::Float64 || src.GetType() == MachineType::Float64) && src.IsImmediate())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(MachineType::Int64);
					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp);
					MI2.SetOp<1>(src);  
					instructions.insert(instruction_iter, MI2);

					MI.SetOpcode(ARM_InstFMov);
					MI.SetOp<1>(tmp);  
					break;
				}

				if (dst.GetType() == MachineType::Float64 || src.GetType() == MachineType::Float64)
				{
					MI.SetOpcode(ARM_InstFMov);
				}

				if (src.IsImmediate() && dst.IsMemoryOperand())
				{
					if (src.GetType() == MachineType::Float64)
					{
						MachineOperand tmp_int = lowering_ctx.VirtualReg(MachineType::Int64);
						MachineOperand tmp_fp = lowering_ctx.VirtualReg(MachineType::Float64);

						MachineInstruction MI2(InstMove);
						MI2.SetOp<0>(tmp_int);
						MI2.SetOp<1>(src);
						instructions.insert(instruction_iter, MI2);

						MachineInstruction MI3(ARM_InstFMov);
						MI3.SetOp<0>(tmp_fp);
						MI3.SetOp<1>(tmp_int);
						instructions.insert(instruction_iter, MI3);

						MI.SetOpcode(InstStore);
						MI.SetOp<0>(dst);
						MI.SetOp<1>(tmp_fp);
					}
					else
					{
						MachineOperand tmp = lowering_ctx.VirtualReg(src.GetType());
						MachineInstruction MI2(InstMove);
						MI2.SetOp<0>(tmp);
						MI2.SetOp<1>(src);
						instructions.insert(instruction_iter, MI2);

						MI.SetOpcode(InstStore);
						MI.SetOp<0>(dst);
						MI.SetOp<1>(tmp);
					}
					break;
				}

				if (dst.GetType() == MachineType::Ptr && src.IsMemoryOperand())
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
				else if (dst.IsMemoryOperand() && src.IsMemoryOperand())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(src.GetType());
					MI.SetOpcode(InstLoad);
					MI.SetOp<0>(tmp);
					MI.SetOp<1>(src);

					MachineInstruction MI2(InstStore);
					MI2.SetOp<0>(dst);
					MI2.SetOp<1>(tmp);
					instructions.insert(++instruction_iter, MI2);
				}
				else if (dst.GetType() == MachineType::Ptr && (src.IsRelocable() || src.IsStackObject()))
				{
					MI.SetOpcode(InstLoadGlobalAddress);
				}
				else if (dst.IsMemoryOperand())
				{
					MI.SetOpcode(InstStore);
					MI.SetOp<0>(dst);
					MI.SetOp<1>(src);
				}
				else if (src.IsMemoryOperand())
				{
					MI.SetOpcode(InstLoad);
				}
			}
			break;

			case InstStore:
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand src = MI.GetOperand(1);

				if (dst.GetType() == MachineType::Ptr && src.IsMemoryOperand())
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
				else if (src.IsImmediate())
				{
					if (src.GetType() == MachineType::Float64)
					{
						MachineOperand tmp_int = lowering_ctx.VirtualReg(MachineType::Int64);
						MachineOperand tmp_fp = lowering_ctx.VirtualReg(MachineType::Float64);

						MachineInstruction MI2(InstMove);
						MI2.SetOp<0>(tmp_int);
						MI2.SetOp<1>(src);
						instructions.insert(instruction_iter, MI2);

						MachineInstruction MI3(ARM_InstFMov);
						MI3.SetOp<0>(tmp_fp);
						MI3.SetOp<1>(tmp_int);
						instructions.insert(instruction_iter, MI3);

						MI.SetOp<1>(tmp_fp);
					}
					else
					{
						MachineOperand tmp = lowering_ctx.VirtualReg(src.GetType());
						MachineInstruction MI2(InstMove);
						MI2.SetOp<0>(tmp);
						MI2.SetOp<1>(src);
						instructions.insert(instruction_iter, MI2);
						MI.SetOp<1>(tmp);
					}
				}
				else if (src.IsMemoryOperand())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(src.GetType());
					MachineInstruction MI2(InstLoad);
					MI2.SetOp<0>(tmp);
					MI2.SetOp<1>(src);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<1>(tmp);
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
				// can't have immediate operands (need to load from memory/register)
				if (op2.IsImmediate())
				{
					MachineOperand tmp_int = lowering_ctx.VirtualReg(MachineType::Int64);
					MachineOperand tmp_fp = lowering_ctx.VirtualReg(MachineType::Float64);

					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp_int);
					MI2.SetOp<1>(op2);
					instructions.insert(instruction_iter, MI2);

					MachineInstruction MI3(ARM_InstFMov);
					MI3.SetOp<0>(tmp_fp);
					MI3.SetOp<1>(tmp_int);
					instructions.insert(instruction_iter, MI3);

					MI.SetOp<2>(tmp_fp);
				}
				if (op1.IsImmediate())
				{
					MachineOperand tmp_int = lowering_ctx.VirtualReg(MachineType::Int64);
					MachineOperand tmp_fp = lowering_ctx.VirtualReg(MachineType::Float64);

					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp_int);
					MI2.SetOp<1>(op1);
					instructions.insert(instruction_iter, MI2);

					MachineInstruction MI3(ARM_InstFMov);
					MI3.SetOp<0>(tmp_fp);
					MI3.SetOp<1>(tmp_int);
					instructions.insert(instruction_iter, MI3);

					MI.SetOp<1>(tmp_fp);
				}
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

					if (op1.IsMemoryOperand() || op1.IsStackObject())
					{
						MachineOperand tmp = lowering_ctx.VirtualReg(op1.GetType());
						MachineInstruction load_inst(InstLoad);
						load_inst.SetOp<0>(tmp);
						load_inst.SetOp<1>(op1);
						instructions.insert(instruction_iter, load_inst);
						op1 = tmp;
					}
					if (op2.IsMemoryOperand() || op2.IsStackObject())
					{
						MachineOperand tmp = lowering_ctx.VirtualReg(op2.GetType());
						MachineInstruction load_inst(InstLoad);
						load_inst.SetOp<0>(tmp);
						load_inst.SetOp<1>(op2);
						instructions.insert(instruction_iter, load_inst);
						op2 = tmp;
					}

					MI.SetOp<0>(op1);
					MI.SetOp<1>(op2);

					if (op1.IsImmediate())
					{
						OLA_ASSERT(!op2.IsImmediate());
						MI.SetOp<0>(op2);
						MI.SetOp<1>(op1);

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
							OLA_ASSERT_MSG(false, "Invalid compare operation!");
							return CompareOp::ICmpEQ;
						};
						compare_op = MachineOperand::Immediate((Uint32)GetOppositeCondition(compare_op), MachineType::Int64);
					}

					// ARM cmp only supports 12-bit unsigned immediates (0-4095)
					MachineOperand cmp_op2 = MI.GetOperand(1);
					if (cmp_op2.IsImmediate())
					{
						Int64 imm = cmp_op2.GetImmediate();
						if (imm < 0 || imm > 4095)
						{
							MachineOperand tmp = lowering_ctx.VirtualReg(cmp_op2.GetType());
							MachineInstruction mov_inst(InstMove);
							mov_inst.SetOp<0>(tmp);
							mov_inst.SetOp<1>(cmp_op2);
							instructions.insert(instruction_iter, mov_inst);
							MI.SetOp<1>(tmp);
						}
					}

					auto GetCsetCondition = [](MachineOperand compare_op) -> Uint32
					{
						OLA_ASSERT(compare_op.IsImmediate());
						CompareOp cmp_op = (CompareOp)compare_op.GetImmediate();
						switch (cmp_op)
						{
						case CompareOp::ICmpEQ:  return ARM_InstCsetEQ;
						case CompareOp::ICmpNE:  return ARM_InstCsetNE;
						case CompareOp::ICmpSGT: return ARM_InstCsetGT;
						case CompareOp::ICmpSGE: return ARM_InstCsetGE;
						case CompareOp::ICmpSLT: return ARM_InstCsetLT;
						case CompareOp::ICmpSLE: return ARM_InstCsetLE;
						}
						OLA_ASSERT_MSG(false, "Invalid compare operation!");
						return ARM_InstCset;
					};

					MachineInstruction MI2(GetCsetCondition(compare_op));
					MI2.SetOp<0>(dst);
					instructions.insert(++instruction_iter, MI2);
				}
			}
			break;
			case InstFCmp:
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand op1 = MI.GetOperand(1);
				MachineOperand op2 = MI.GetOperand(2);
				MachineOperand compare_op = MI.GetOperand(3);

				if (op2.IsImmediate())
				{
					MachineOperand tmp_int = lowering_ctx.VirtualReg(MachineType::Int64);
					MachineOperand tmp_fp = lowering_ctx.VirtualReg(MachineType::Float64);

					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp_int);
					MI2.SetOp<1>(op2);
					instructions.insert(instruction_iter, MI2);

					MachineInstruction MI3(ARM_InstFMov);
					MI3.SetOp<0>(tmp_fp);
					MI3.SetOp<1>(tmp_int);
					instructions.insert(instruction_iter, MI3);

					op2 = tmp_fp;
				}
				if (op1.IsImmediate())
				{
					MachineOperand tmp_int = lowering_ctx.VirtualReg(MachineType::Int64);
					MachineOperand tmp_fp = lowering_ctx.VirtualReg(MachineType::Float64);

					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp_int);
					MI2.SetOp<1>(op1);
					instructions.insert(instruction_iter, MI2);

					MachineInstruction MI3(ARM_InstFMov);
					MI3.SetOp<0>(tmp_fp);
					MI3.SetOp<1>(tmp_int);
					instructions.insert(instruction_iter, MI3);

					op1 = tmp_fp;
				}

				MI.SetOp<0>(op1);
				MI.SetOp<1>(op2);
				auto GetCsetCondition = [](MachineOperand compare_op) -> Uint32
				{
					OLA_ASSERT(compare_op.IsImmediate());
					CompareOp cmp_op = (CompareOp)compare_op.GetImmediate();
					switch (cmp_op)
					{
					case CompareOp::FCmpOEQ: return ARM_InstCsetEQ;
					case CompareOp::FCmpONE: return ARM_InstCsetNE;
					case CompareOp::FCmpOGT: return ARM_InstCsetGT;
					case CompareOp::FCmpOGE: return ARM_InstCsetGE;
					case CompareOp::FCmpOLT: return ARM_InstCsetLT;
					case CompareOp::FCmpOLE: return ARM_InstCsetLE;
					}
					OLA_ASSERT_MSG(false, "Invalid compare operation!");
					return ARM_InstCset;
				};

				MachineInstruction MI2(GetCsetCondition(compare_op));
				MI2.SetOp<0>(dst);
				instructions.insert(++instruction_iter, MI2);
			}
			break;

			case InstCMoveEQ:
			case InstCMoveNE:
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand src = MI.GetOperand(1);
				if (src.IsImmediate())
				{
					if (src.GetType() == MachineType::Float64)
					{
						MachineOperand tmp_int = lowering_ctx.VirtualReg(MachineType::Int64);
						MachineOperand tmp_fp = lowering_ctx.VirtualReg(MachineType::Float64);

						MachineInstruction MI2(InstMove);
						MI2.SetOp<0>(tmp_int);
						MI2.SetOp<1>(src);
						instructions.insert(instruction_iter, MI2);

						MachineInstruction MI3(ARM_InstFMov);
						MI3.SetOp<0>(tmp_fp);
						MI3.SetOp<1>(tmp_int);
						instructions.insert(instruction_iter, MI3);

						MI.SetOp<1>(tmp_fp);
					}
					else
					{
						MachineOperand tmp = lowering_ctx.VirtualReg(src.GetType());
						MachineInstruction MI2(InstMove);
						MI2.SetOp<0>(tmp);
						MI2.SetOp<1>(src);
						MI.SetOp<1>(tmp);
						instructions.insert(instruction_iter, MI2);
					}
				}
			}
			break;
			case InstS2F:
			case InstF2S:
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand src = MI.GetOperand(1);
				if (src.IsImmediate())
				{
					MachineType src_type = (MI.GetOpcode() == InstS2F) ? MachineType::Int64 : MachineType::Float64;
					if (src_type == MachineType::Float64)
					{
						MachineOperand tmp_int = lowering_ctx.VirtualReg(MachineType::Int64);
						MachineOperand tmp_fp = lowering_ctx.VirtualReg(MachineType::Float64);

						MachineInstruction MI2(InstMove);
						MI2.SetOp<0>(tmp_int);
						MI2.SetOp<1>(src);
						instructions.insert(instruction_iter, MI2);

						MachineInstruction MI3(ARM_InstFMov);
						MI3.SetOp<0>(tmp_fp);
						MI3.SetOp<1>(tmp_int);
						instructions.insert(instruction_iter, MI3);

						MI.SetOp<1>(tmp_fp);
					}
					else
					{
						MachineOperand tmp = lowering_ctx.VirtualReg(src_type);
						MachineInstruction MI2(InstMove);
						MI2.SetOp<0>(tmp);
						MI2.SetOp<1>(src);
						MI.SetOp<1>(tmp);
						instructions.insert(instruction_iter, MI2);
					}
				}
			}
			break;
			case InstFNeg:
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand src = MI.GetOperand(1);
				if (src.IsImmediate())
				{
					MachineOperand tmp_int = lowering_ctx.VirtualReg(MachineType::Int64);
					MachineOperand tmp_fp = lowering_ctx.VirtualReg(MachineType::Float64);

					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp_int);
					MI2.SetOp<1>(src);
					instructions.insert(instruction_iter, MI2);

					MachineInstruction MI3(ARM_InstFMov);
					MI3.SetOp<0>(tmp_fp);
					MI3.SetOp<1>(tmp_int);
					instructions.insert(instruction_iter, MI3);

					MI.SetOp<1>(tmp_fp);
				}
			}
			break;
			case InstZExt:
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand src = MI.GetOperand(1);
				if (src.IsImmediate())
				{
					MI.SetOpcode(InstMove);
				}
			}
			break;
			case InstSRem:
			case InstURem:
			{
				// ARM doesn't have remainder instruction, expand to:
				// rem = a - (a / b) * b
				// Using msub: rem = a - (quotient * b)
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand op1 = MI.GetOperand(1);
				MachineOperand op2 = MI.GetOperand(2);

				if (op1.IsImmediate())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(op1.GetType());
					MachineInstruction mov_inst(InstMove);
					mov_inst.SetOp<0>(tmp);
					mov_inst.SetOp<1>(op1);
					instructions.insert(instruction_iter, mov_inst);
					op1 = tmp;
				}

				if (op2.IsImmediate())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(op2.GetType());
					MachineInstruction mov_inst(InstMove);
					mov_inst.SetOp<0>(tmp);
					mov_inst.SetOp<1>(op2);
					instructions.insert(instruction_iter, mov_inst);
					op2 = tmp;
				}

				Uint32 div_opcode = (MI.GetOpcode() == InstSRem) ? InstSDiv : InstUDiv;

				MachineOperand quotient = lowering_ctx.VirtualReg(dst.GetType());
				MachineInstruction div_inst(div_opcode);
				div_inst.SetOp<0>(quotient).SetOp<1>(op1).SetOp<2>(op2);
				instructions.insert(instruction_iter, div_inst);

				MI.SetOpcode(ARM_InstMsub);
				MI.SetOp<0>(dst);
				MI.SetOp<1>(quotient);
				MI.SetOp<2>(op2);
				MI.SetOp<3>(op1);
			}
			break;
			case InstAdd:
			case InstSub:
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand op1 = MI.GetOperand(1);
				MachineOperand op2 = MI.GetOperand(2);

				// Handle memory/stack operands - load into temp register
				if (op2.IsMemoryOperand() || op2.IsStackObject())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(op2.GetType());
					MachineInstruction MI2(InstLoad);
					MI2.SetOp<0>(tmp);
					MI2.SetOp<1>(op2);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<2>(tmp);
					op2 = tmp;
				}

				if (op1.IsMemoryOperand() || op1.IsStackObject())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(op1.GetType());
					MachineInstruction MI2(InstLoad);
					MI2.SetOp<0>(tmp);
					MI2.SetOp<1>(op1);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<1>(tmp);
					op1 = tmp;
				}

				// Handle immediate operands
				if (op1.IsImmediate())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(op1.GetType());
					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp);
					MI2.SetOp<1>(op1);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<1>(tmp);
				}
			}
			break;
			case InstSMul:
			case InstUMul:
			case InstSDiv:
			case InstUDiv:
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand op1 = MI.GetOperand(1);
				MachineOperand op2 = MI.GetOperand(2);

				if (op2.IsImmediate())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(op2.GetType());
					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp);
					MI2.SetOp<1>(op2);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<2>(tmp);
				}

				if (op1.IsImmediate())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(op1.GetType());
					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp);
					MI2.SetOp<1>(op1);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<1>(tmp);
				}
			}
			break;
			case InstShl:
			case InstAShr:
			case InstLShr:
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand op1 = MI.GetOperand(1);
				MachineOperand op2 = MI.GetOperand(2);

				if (op1.IsImmediate())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(op1.GetType());
					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp);
					MI2.SetOp<1>(op1);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<1>(tmp);
				}
			}
			break;
			case InstAnd:
			case InstOr:
			case InstXor:
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand op1 = MI.GetOperand(1);
				MachineOperand op2 = MI.GetOperand(2);

				if (op1.IsImmediate())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(op1.GetType());
					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp);
					MI2.SetOp<1>(op1);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<1>(tmp);
				}

				if (op2.IsImmediate())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(op2.GetType());
					MachineInstruction MI2(InstMove);
					MI2.SetOp<0>(tmp);
					MI2.SetOp<1>(op2);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<2>(tmp);
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

				Int64 offset = 0;
				Bool first = true;
				while (size >= 8)
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(MachineType::Int64);
					MachineOperand current_src = src;
					MachineOperand current_dst = dst;

					if (offset > 0)
					{
						MachineOperand src_ptr = lowering_ctx.VirtualReg(MachineType::Ptr);
						MachineInstruction add_src(InstAdd);
						add_src.SetOp<0>(src_ptr).SetOp<1>(src).SetOp<2>(MachineOperand::Immediate(offset, MachineType::Int64));
						if (first)
						{
							MI.SetOpcode(InstAdd);
							MI.SetOp<0>(src_ptr).SetOp<1>(src).SetOp<2>(MachineOperand::Immediate(offset, MachineType::Int64));
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
						add_dst.SetOp<0>(dst_ptr).SetOp<1>(dst).SetOp<2>(MachineOperand::Immediate(offset, MachineType::Int64));
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
					MachineOperand current_src = src;
					MachineOperand current_dst = dst;

					MachineOperand src_ptr = lowering_ctx.VirtualReg(MachineType::Ptr);
					MachineInstruction add_src(InstAdd);
					add_src.SetOp<0>(src_ptr).SetOp<1>(src).SetOp<2>(MachineOperand::Immediate(offset, MachineType::Int64));
					if (first)
					{
						MI.SetOpcode(InstAdd);
						MI.SetOp<0>(src_ptr).SetOp<1>(src).SetOp<2>(MachineOperand::Immediate(offset, MachineType::Int64));
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
					add_dst.SetOp<0>(dst_ptr).SetOp<1>(dst).SetOp<2>(MachineOperand::Immediate(offset, MachineType::Int64));
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

		virtual void PostLegalizeInstruction(InstLegalizeContext& legalize_ctx) const override
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

			if (MI.GetOpcode() == InstLoad)
			{
				MachineOperand src = MI.GetOperand(1);
				if (src.IsStackObject())
				{
					Int32 stack_offset = src.GetStackOffset();
					if (stack_offset < -256 || stack_offset > 255)
					{
						MachineOperand x16 = MachineOperand::ISAReg(ARM_X16, MachineType::Ptr);
						MachineInstruction addr_inst(InstLoadGlobalAddress);
						addr_inst.SetOp<0>(x16);
						addr_inst.SetOp<1>(src);
						instructions.insert(instruction_iter, addr_inst);
						MI.SetOp<1>(x16);
					}
				}
			}
			else if (MI.GetOpcode() == InstStore)
			{
				MachineOperand dst = MI.GetOperand(0);
				if (dst.IsStackObject())
				{
					Int32 stack_offset = dst.GetStackOffset();
					if (stack_offset < -256 || stack_offset > 255)
					{
						MachineOperand x16 = MachineOperand::ISAReg(ARM_X16, MachineType::Ptr);
						MachineInstruction addr_inst(InstLoadGlobalAddress);
						addr_inst.SetOp<0>(x16);
						addr_inst.SetOp<1>(dst);
						instructions.insert(instruction_iter, addr_inst);
						MI.SetOp<0>(x16);
					}
				}
			}
			else if (MI.GetOpcode() == InstLoadGlobalAddress)
			{
				MachineOperand src = MI.GetOperand(1);
				if (src.IsStackObject())
				{
					Int32 stack_offset = src.GetStackOffset();
					Int32 abs_offset = (stack_offset >= 0) ? stack_offset : -stack_offset;
					if (abs_offset > 4095)
					{
						MachineOperand dst = MI.GetOperand(0);
						MachineInstruction mov_inst(InstMove);
						mov_inst.SetOp<0>(dst);
						mov_inst.SetOp<1>(MachineOperand::Immediate(abs_offset, MachineType::Int64));
						instructions.insert(instruction_iter, mov_inst);

						MachineOperand x29 = MachineOperand::ISAReg(ARM_X29, MachineType::Ptr);
						if (stack_offset >= 0)
						{
							MI.SetOpcode(InstAdd);
						}
						else
						{
							MI.SetOpcode(InstSub);
						}
						MI.SetOp<0>(dst);
						MI.SetOp<1>(x29);
						MI.SetOp<2>(dst);
					}
				}
			}

			if (MI.GetOpcode() >= InstMove && MI.GetOpcode() <= InstStore)
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand src = MI.GetOperand(1);

				if (dst.IsMemoryOperand() && src.IsMemoryOperand())
				{
					auto scratch = GetScratchReg(dst.GetType());
					MachineInstruction MI2(InstLoad);
					MI2.SetOp<0>(scratch);
					MI2.SetOp<1>(src);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<1>(scratch);
					MI.SetOpcode(InstStore);
				}
			}
			else if (MI.GetOpcode() == InstAdd || MI.GetOpcode() == InstSub)
			{
				// Handle spilled stack operands from register allocation
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand op1 = MI.GetOperand(1);
				MachineOperand op2 = MI.GetOperand(2);

				if (op2.IsMemoryOperand() || op2.IsStackObject())
				{
					auto scratch = GetScratchReg(op2.GetType());
					MachineInstruction MI2(InstLoad);
					MI2.SetOp<0>(scratch);
					MI2.SetOp<1>(op2);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<2>(scratch);
				}

				if (op1.IsMemoryOperand() || op1.IsStackObject())
				{
					auto scratch = GetScratchReg(op1.GetType());
					MachineInstruction MI2(InstLoad);
					MI2.SetOp<0>(scratch);
					MI2.SetOp<1>(op1);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<1>(scratch);
				}

				if (dst.IsMemoryOperand() || dst.IsStackObject())
				{
					auto scratch = GetScratchReg(dst.GetType());
					MI.SetOp<0>(scratch);
					MachineInstruction store_inst(InstStore);
					store_inst.SetOp<0>(dst);
					store_inst.SetOp<1>(scratch);
					instructions.insert(++instruction_iter, store_inst);
				}
			}
			else if (MI.GetOpcode() == InstLoadGlobalAddress)
			{
				MachineOperand dst = MI.GetOperand(0);
				if (dst.IsMemoryOperand() || dst.IsStackObject())
				{
					auto scratch = GetScratchReg(dst.GetType());
					MI.SetOp<0>(scratch);
					MachineInstruction store_inst(InstStore);
					store_inst.SetOp<0>(dst);
					store_inst.SetOp<1>(scratch);
					instructions.insert(++instruction_iter, store_inst);
				}
			}
			else if (MI.GetOpcode() == InstICmp)
			{
				MachineOperand op1 = MI.GetOperand(0);
				MachineOperand op2 = MI.GetOperand(1);

				Bool op1_is_mem = op1.IsMemoryOperand() || op1.IsStackObject();
				Bool op2_is_mem = op2.IsMemoryOperand() || op2.IsStackObject();
				if (op1_is_mem)
				{
					auto scratch = GetScratchReg(op1.GetType());
					MachineInstruction load_inst(InstLoad);
					load_inst.SetOp<0>(scratch);
					load_inst.SetOp<1>(op1);
					instructions.insert(instruction_iter, load_inst);
					MI.SetOp<0>(scratch);
				}

				if (op2_is_mem)
				{
					MachineOperand scratch = op1_is_mem
						? MachineOperand::ISAReg(ARM_X17, op2.GetType())
						: GetScratchReg(op2.GetType());
					MachineInstruction load_inst(InstLoad);
					load_inst.SetOp<0>(scratch);
					load_inst.SetOp<1>(op2);
					instructions.insert(instruction_iter, load_inst);
					MI.SetOp<1>(scratch);
				}
			}
		}
	};

	class ARMTargetRegisterInfo : public TargetRegisterInfo
	{
		std::vector<Uint32> gp_regs;
		std::vector<Uint32> fp_regs;

	public:
		ARMTargetRegisterInfo()
		{
			gp_regs.reserve(ARM_GPREnd - ARM_GPRBegin + 1);
			for (Uint32 r = ARM_GPRBegin; r <= ARM_GPREnd; ++r)
			{
				// SP, X29 (FP), X30 (LR), X16 (GP scratch), X17 (second GP scratch)
				if (r != ARM_SP && r != ARM_X29 && r != ARM_X30 && r != ARM_X16 && r != ARM_X17)
				{
					gp_regs.push_back(r);
				}
			}

			fp_regs.reserve(ARM_FPREnd - ARM_FPRBegin + 1);
			for (Uint32 r = ARM_FPRBegin; r <= ARM_FPREnd; ++r)
			{
				if (r != ARM_V31) 
				{
					fp_regs.push_back(r);
				}
			}
		}

		virtual Uint32 GetStackPointerRegister() const override
		{
			return ARM_SP;
		}
		virtual Uint32 GetGPScratchRegister() const override
		{
			return ARM_X16;
		}
		virtual Uint32 GetFPScratchRegister() const override
		{
			return ARM_V31;
		}
		virtual Uint32 GetFramePointerRegister() const override
		{
			return ARM_X29;
		}
		virtual Uint32 GetReturnRegister() const override
		{
			return ARM_X0;
		}

		virtual std::vector<Uint32> const& GetGPRegisters() const override
		{
			return gp_regs;
		}

		virtual std::vector<Uint32> GetGPCallerSavedRegisters() const override
		{
			std::vector<Uint32> gp_caller_saved_regs;
			for (Uint32 reg : gp_regs)
			{
				if (ARM_IsCallerSaved(reg)) gp_caller_saved_regs.push_back(reg);
			}
			return gp_caller_saved_regs;
		}
		virtual std::vector<Uint32> GetGPCalleeSavedRegisters() const override
		{
			std::vector<Uint32> gp_callee_saved_regs;
			for (Uint32 reg : gp_regs)
			{
				if (!ARM_IsCallerSaved(reg) && reg != GetStackPointerRegister()
					&& reg != GetFramePointerRegister() && reg != GetGPScratchRegister())
				{
					gp_callee_saved_regs.push_back(reg);
				}
			}
			return gp_callee_saved_regs;
		}

		virtual std::vector<Uint32> const& GetFPRegisters() const override
		{
			return fp_regs;
		}

		virtual std::vector<Uint32> GetFPCallerSavedRegisters() const override
		{
			std::vector<Uint32> fp_caller_saved_regs;
			for (Uint32 reg : fp_regs)
			{
				if (ARM_IsCallerSaved(reg)) fp_caller_saved_regs.push_back(reg);
			}
			return fp_caller_saved_regs;
		}

		virtual std::vector<Uint32> GetFPCalleeSavedRegisters() const override
		{
			std::vector<Uint32> fp_callee_saved_regs;
			for (Uint32 reg : fp_regs)
			{
				if (!ARM_IsCallerSaved(reg) && reg != GetFPScratchRegister())
				{
					fp_callee_saved_regs.push_back(reg);
				}
			}
			return fp_callee_saved_regs;
		}

		virtual Bool IsCallerSaved(Uint32 reg) const override
		{
			return ARM_IsCallerSaved(reg);
		}

		virtual Bool IsCalleeSaved(Uint32 reg) const override
		{
			return !ARM_IsCallerSaved(reg);
		}
	};

	TargetDataLayout const& ARMTarget::GetDataLayout() const
	{
		static ARMTargetDataLayout arm64_target_data_layout{};
		return arm64_target_data_layout;
	}

	TargetInstInfo const& ARMTarget::GetInstInfo() const
	{
		static ARMTargetInstInfo arm64_target_inst_info{};
		return arm64_target_inst_info;
	}

	TargetRegisterInfo const& ARMTarget::GetRegisterInfo() const
	{
		static ARMTargetRegisterInfo arm64_target_register_info{};
		return arm64_target_register_info;
	}

	TargetISelInfo const& ARMTarget::GetISelInfo() const
	{
		static ARMTargetISelInfo arm64_target_isel_info{};
		return arm64_target_isel_info;
	}

	TargetFrameInfo const& ARMTarget::GetFrameInfo() const
	{
		static ARMTargetFrameInfo arm64_target_frame_info{};
		return arm64_target_frame_info;
	}

	void ARMTarget::EmitAssembly(MachineModule& M, std::string_view file) const
	{
		std::ofstream asm_stream(file.data());
		ARMAsmPrinter asm_printer(asm_stream);
		asm_printer.PrintModule(M);
	}
}
