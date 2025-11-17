#include <fstream>
#include "ARM64Target.h"
#include "Backend/Custom/Codegen/ARM64/ARM64.h"
#include "ARM64TargetFrameInfo.h"
#include "ARM64TargetInstInfo.h"
#include "ARM64AsmPrinter.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/MachineContext.h"

namespace ola
{
	class ARM64TargetDataLayout : public TargetDataLayout
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

	class ARM64TargetISelInfo : public TargetISelInfo
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

					MI.SetOpcode(ARM64_InstFMov);
					MI.SetOp<1>(tmp);  
					break;
				}

				if (dst.GetType() == MachineType::Float64 || src.GetType() == MachineType::Float64)
				{
					MI.SetOpcode(ARM64_InstFMov);
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

						MachineInstruction MI3(ARM64_InstFMov);
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

				if (dst.IsMemoryOperand() && src.IsMemoryOperand())
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

						MachineInstruction MI3(ARM64_InstFMov);
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

					MachineInstruction MI3(ARM64_InstFMov);
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

					MachineInstruction MI3(ARM64_InstFMov);
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
					//cmp op1, op2
					MI.SetOp<0>(op1);
					MI.SetOp<1>(op2);

					auto GetCsetCondition = [](MachineOperand compare_op) -> Uint32
					{
						OLA_ASSERT(compare_op.IsImmediate());
						CompareOp cmp_op = (CompareOp)compare_op.GetImmediate();
						switch (cmp_op)
						{
						case CompareOp::ICmpEQ:  return ARM64_InstCsetEQ;
						case CompareOp::ICmpNE:  return ARM64_InstCsetNE;
						case CompareOp::ICmpSGT: return ARM64_InstCsetGT;
						case CompareOp::ICmpSGE: return ARM64_InstCsetGE;
						case CompareOp::ICmpSLT: return ARM64_InstCsetLT;
						case CompareOp::ICmpSLE: return ARM64_InstCsetLE;
						}
						OLA_ASSERT_MSG(false, "Invalid compare operation!");
						return ARM64_InstCset;
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

					MachineInstruction MI3(ARM64_InstFMov);
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

					MachineInstruction MI3(ARM64_InstFMov);
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
					case CompareOp::FCmpOEQ: return ARM64_InstCsetEQ;
					case CompareOp::FCmpONE: return ARM64_InstCsetNE;
					case CompareOp::FCmpOGT: return ARM64_InstCsetGT;
					case CompareOp::FCmpOGE: return ARM64_InstCsetGE;
					case CompareOp::FCmpOLT: return ARM64_InstCsetLT;
					case CompareOp::FCmpOLE: return ARM64_InstCsetLE;
					}
					OLA_ASSERT_MSG(false, "Invalid compare operation!");
					return ARM64_InstCset;
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

						MachineInstruction MI3(ARM64_InstFMov);
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

						MachineInstruction MI3(ARM64_InstFMov);
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
		}
	};

	class ARM64TargetRegisterInfo : public TargetRegisterInfo
	{
		std::vector<Uint32> gp_regs;
		std::vector<Uint32> fp_regs;

	public:
		ARM64TargetRegisterInfo()
		{
			gp_regs.reserve(ARM64_GPREnd - ARM64_GPRBegin + 1);
			for (Uint32 r = ARM64_GPRBegin; r <= ARM64_GPREnd; ++r)
			{
				// SP, X29 (FP), X30 (LR), X16 (GP scratch)
				if (r != ARM64_SP && r != ARM64_X29 && r != ARM64_X30 && r != ARM64_X16) 
				{
					gp_regs.push_back(r);
				}
			}

			fp_regs.reserve(ARM64_FPREnd - ARM64_FPRBegin + 1);
			for (Uint32 r = ARM64_FPRBegin; r <= ARM64_FPREnd; ++r)
			{
				if (r != ARM64_V31) 
				{
					fp_regs.push_back(r);
				}
			}
		}

		virtual Uint32 GetStackPointerRegister() const override
		{
			return ARM64_SP;
		}
		virtual Uint32 GetGPScratchRegister() const override
		{
			return ARM64_X16;
		}
		virtual Uint32 GetFPScratchRegister() const override
		{
			return ARM64_V31;
		}
		virtual Uint32 GetFramePointerRegister() const override
		{
			return ARM64_X29;
		}
		virtual Uint32 GetReturnRegister() const override
		{
			return ARM64_X0;
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
				if (ARM64_IsCallerSaved(reg)) gp_caller_saved_regs.push_back(reg);
			}
			return gp_caller_saved_regs;
		}
		virtual std::vector<Uint32> GetGPCalleeSavedRegisters() const override
		{
			std::vector<Uint32> gp_callee_saved_regs;
			for (Uint32 reg : gp_regs)
			{
				if (!ARM64_IsCallerSaved(reg) && reg != GetStackPointerRegister()
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
				if (ARM64_IsCallerSaved(reg)) fp_caller_saved_regs.push_back(reg);
			}
			return fp_caller_saved_regs;
		}

		virtual std::vector<Uint32> GetFPCalleeSavedRegisters() const override
		{
			std::vector<Uint32> fp_callee_saved_regs;
			for (Uint32 reg : fp_regs)
			{
				if (!ARM64_IsCallerSaved(reg) && reg != GetFPScratchRegister())
				{
					fp_callee_saved_regs.push_back(reg);
				}
			}
			return fp_callee_saved_regs;
		}

		virtual Bool IsCallerSaved(Uint32 reg) const override
		{
			return ARM64_IsCallerSaved(reg);
		}

		virtual Bool IsCalleeSaved(Uint32 reg) const override
		{
			return !ARM64_IsCallerSaved(reg);
		}
	};

	TargetDataLayout const& ARM64Target::GetDataLayout() const
	{
		static ARM64TargetDataLayout arm64_target_data_layout{};
		return arm64_target_data_layout;
	}

	TargetInstInfo const& ARM64Target::GetInstInfo() const
	{
		static ARM64TargetInstInfo arm64_target_inst_info{};
		return arm64_target_inst_info;
	}

	TargetRegisterInfo const& ARM64Target::GetRegisterInfo() const
	{
		static ARM64TargetRegisterInfo arm64_target_register_info{};
		return arm64_target_register_info;
	}

	TargetISelInfo const& ARM64Target::GetISelInfo() const
	{
		static ARM64TargetISelInfo arm64_target_isel_info{};
		return arm64_target_isel_info;
	}

	TargetFrameInfo const& ARM64Target::GetFrameInfo() const
	{
		static ARM64TargetFrameInfo arm64_target_frame_info{};
		return arm64_target_frame_info;
	}

	void ARM64Target::EmitAssembly(MachineModule& M, std::string_view file) const
	{
		std::ofstream asm_stream(file.data());
		ARM64AsmPrinter asm_printer(asm_stream);
		asm_printer.PrintModule(M);
	}
}
