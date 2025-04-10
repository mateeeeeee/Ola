#include <fstream>
#include "x64Target.h"
#include "x64.h"
#include "x64TargetFrameInfo.h"
#include "x64TargetInstInfo.h"
#include "x64AsmPrinter.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/MachineContext.h"

namespace ola
{
	class x64TargetDataLayout : public TargetDataLayout
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

	class x64TargetISelInfo : public TargetISelInfo
	{
	public:
		virtual Bool LowerInstruction(Instruction* I, MachineContext& ctx) const override
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
					move_to_rax.SetOp<0>(MachineOperand::ISAReg(x64::RAX, MachineType::Int64));
					move_to_rax.SetOp<1>(op1);
					ctx.EmitInst(move_to_rax);

					MachineInstruction cqo(x64::InstCqo);
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
						move_quotient.SetOp<1>(MachineOperand::ISAReg(x64::RAX, MachineType::Int64));
						ctx.EmitInst(move_quotient);
					}
					else if (opcode == Opcode::SRem)
					{
						MachineInstruction move_remainder(InstMove);
						move_remainder.SetOp<0>(dst);
						move_remainder.SetOp<1>(MachineOperand::ISAReg(x64::RDX, MachineType::Int64));
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
					MI.SetOpcode(x64::InstMoveFP);

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
					MI3.SetOp<0>(MachineOperand::ISAReg(x64::Register::RCX, op2.GetType()));
					MI3.SetOp<1>(op2);
					instructions.insert(instruction_iter, MI3);
					MI.SetOp<1>(MachineOperand::ISAReg(x64::Register::RCX, MachineType::Int8));
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
							case CompareOp::ICmpEQ:  return x64::InstSetE;
							case CompareOp::ICmpNE:  return x64::InstSetNE;
							case CompareOp::ICmpSGT: return x64::InstSetGT;
							case CompareOp::ICmpSGE: return x64::InstSetGE;
							case CompareOp::ICmpSLT: return x64::InstSetLT;
							case CompareOp::ICmpSLE: return x64::InstSetLE;
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
				MachineInstruction MI2(x64::InstMoveFP);
				MI2.SetOp<0>(dst);
				MI2.SetOp<1>(op1);

				instructions.insert(instruction_iter, MI2);

				if (op2.IsImmediate())
				{
					MachineOperand tmp = lowering_ctx.VirtualReg(MachineType::Float64);
					
					MachineInstruction MI3(x64::InstMoveFP);
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

				MachineInstruction MI2(x64::InstMoveFP);
				MI2.SetOp<0>(dst);
				MI2.SetOp<1>(src);
				instructions.insert(instruction_iter, MI2);

				MachineInstruction MI3(x64::InstMoveFP);
				MachineOperand neg_mask = lowering_ctx.VirtualReg(MachineType::Float64);
				MI3.SetOp<0>(neg_mask);
				MI3.SetOp<1>(MachineOperand::Immediate(0x8000000000000000, MachineType::Float64));
				instructions.insert(instruction_iter, MI3);

				MI.SetOpcode(x64::InstXorFP);
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
						case CompareOp::FCmpOEQ: return x64::InstSetE;
						case CompareOp::FCmpONE: return x64::InstSetNE;
						case CompareOp::FCmpOGT: return x64::InstSetA;
						case CompareOp::FCmpOGE: return x64::InstSetAE;
						case CompareOp::FCmpOLT: return x64::InstSetB;
						case CompareOp::FCmpOLE: return x64::InstSetBE;
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
					MachineInstruction MI2(InstZExt);
					MI2.SetOp<0>(tmp).SetOp<1>(src);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<1>(tmp);
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

			switch (MI.GetOpcode())
			{
			case InstMove:
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
			break;
			}

			if (MI.GetOpcode() >= InstMove && MI.GetOpcode() <= InstStore)
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand src = MI.GetOperand(1);
				if (dst.IsMemoryOperand() && src.IsMemoryOperand()) //this can happen if register spilling occurs
				{
					auto scratch = GetScratchReg(dst.GetType());
					MachineInstruction MI2(InstLoad);
					MI2.SetOp<0>(scratch).SetOp<1>(src);
					instructions.insert(instruction_iter, MI2);
					MI.SetOp<1>(scratch);
					MI.SetOpcode(InstStore);
				}
			}

			if (MI.GetOpcode() >= InstMove && MI.GetOpcode() <= InstStore)
			{
				MachineOperand dst = MI.GetOperand(0);
				MachineOperand src = MI.GetOperand(1);
				if (src.GetType() == MachineType::Float64 && MI.GetOpcode() == InstStore)
				{
					MI.SetOpcode(x64::InstStoreFP);
				}
				else if (dst.GetType() == MachineType::Float64 && MI.GetOpcode() == InstLoad)
				{
					MI.SetOpcode(x64::InstLoadFP);
				}
				else if (dst.GetType() == MachineType::Float64 || src.GetType() == MachineType::Float64)
				{
					if (MI.GetOpcode() == InstMove) MI.SetOpcode(x64::InstMoveFP);
				}
			}
		}
	};

	class x64TargetRegisterInfo : public TargetRegisterInfo
	{
	public:
		x64TargetRegisterInfo()
		{
			gp_regs.reserve(x64::GPREnd - x64::GPRBegin + 1);
			for (Uint32 r = x64::GPRBegin; r < x64::GPREnd; ++r)
			{
				gp_regs.push_back(r); //skip rbp, rsp
			}

			fp_regs.reserve(x64::FPREnd - x64::FPRBegin + 1);
			for (Uint32 r = x64::FPRBegin; r < x64::FPREnd; ++r)
			{
				fp_regs.push_back(r);
			}
		}

		virtual Uint32 GetStackPointerRegister() const override
		{
			return x64::RSP;
		}
		virtual Uint32 GetGPScratchRegister() const override
		{
			return x64::R15;
		}
		virtual Uint32 GetFPScratchRegister() const override
		{
			return x64::XMM15;
		}
		virtual Uint32 GetFramePointerRegister() const override
		{
			return x64::RBP;
		}
		virtual Uint32 GetReturnRegister() const override
		{
			return x64::RAX;
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
				if (IsCallerSaved(reg)) gp_caller_saved_regs.push_back(reg);
			}
			return gp_caller_saved_regs;
		}
		virtual std::vector<Uint32> GetGPCalleeSavedRegisters() const override
		{
			std::vector<Uint32> gp_callee_saved_regs;
			for (Uint32 reg : gp_regs)
			{
				if (IsCalleeSaved(reg) && reg != GetStackPointerRegister() 
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
				if (IsCallerSaved(reg)) fp_caller_saved_regs.push_back(reg);
			}
			return fp_caller_saved_regs;
		}
		virtual std::vector<Uint32> GetFPCalleeSavedRegisters() const override
		{
			std::vector<Uint32> fp_callee_saved_regs;
			for (Uint32 reg : fp_regs)
			{
				if (IsCalleeSaved(reg) && reg != GetFPScratchRegister()) fp_callee_saved_regs.push_back(reg);
			}
			return fp_callee_saved_regs;
		}

		virtual Bool IsCallerSaved(Uint32 r) const override
		{
			return x64::IsCallerSaved(r);
		}

		virtual Bool IsCalleeSaved(Uint32 r) const override
		{
			return x64::IsCalleeSaved(r);
		}

	private:
		std::vector<Uint32> gp_regs;
		std::vector<Uint32> fp_regs;
	};

	TargetDataLayout const& x64Target::GetDataLayout() const
	{
		static x64TargetDataLayout x64_target_data_layout{};
		return x64_target_data_layout;
	}

	TargetInstInfo const& x64Target::GetInstInfo() const
	{
		static x64TargetInstInfo x64_target_inst_info{};
		return x64_target_inst_info;
	}

	TargetRegisterInfo const& x64Target::GetRegisterInfo() const
	{
		static x64TargetRegisterInfo x64_target_reg_info{};
		return x64_target_reg_info;
	}

	TargetISelInfo const& x64Target::GetISelInfo() const
	{
		static x64TargetISelInfo x64_target_isel_info{};
		return x64_target_isel_info;
	}

	TargetFrameInfo const& x64Target::GetFrameInfo() const
	{
		static x64TargetFrameInfo x64_target_frame_info{};
		return x64_target_frame_info;
	}

	void x64Target::EmitAssembly(MachineModule& M, std::string_view file) const
	{
		std::ofstream asm_stream(file.data());
		x64AsmPrinter asm_printer(asm_stream);
		asm_printer.PrintModule(M);
	}

}

