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
					MI.SetOpcode(ARM64_InstFmov);

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
					instructions.insert(++instruction_iter, MI2);
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

					auto GetOppositeCondition = [](MachineOperand compare_op) -> CompareOp
					{
						OLA_ASSERT(compare_op.IsImmediate());
						CompareOp cmp_op = (CompareOp)compare_op.GetImmediate();
						switch (cmp_op)
						{
						case CompareOp::ICmpEQ: return CompareOp::ICmpEQ;
						case CompareOp::ICmpNE: return CompareOp::ICmpNE;
						case CompareOp::ICmpSGT: return CompareOp::ICmpSLT;
						case CompareOp::ICmpSGE: return CompareOp::ICmpSLE;
						case CompareOp::ICmpSLT: return CompareOp::ICmpSGT;
						case CompareOp::ICmpSLE: return CompareOp::ICmpSGE;
						case CompareOp::ICmpULT: return CompareOp::ICmpUGT;
						case CompareOp::ICmpULE: return CompareOp::ICmpUGE;
						case CompareOp::ICmpUGT: return CompareOp::ICmpULT;
						case CompareOp::ICmpUGE: return CompareOp::ICmpULE;
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
						compare_op = MachineOperand::Immediate((Uint32)GetOppositeCondition(compare_op), MachineType::Other);
					}

					MachineInstruction cset(ARM64_InstCset);
					cset.SetOp<0>(dst);
					cset.SetOp<1>(compare_op);
					instructions.insert(++instruction_iter, cset);

					MachineInstruction andInst(InstAnd);
					andInst.SetOp<0>(dst);
					andInst.SetOp<1>(MachineOperand::Immediate(1, MachineType::Int8));
					instructions.insert(instruction_iter++, andInst);
				}
			}
			break;
			case InstFCmp:
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
						case CompareOp::FCmpOEQ: return CompareOp::FCmpOEQ;
						case CompareOp::FCmpONE: return CompareOp::FCmpONE;
						case CompareOp::FCmpOGT: return CompareOp::FCmpOLT;
						case CompareOp::FCmpOGE: return CompareOp::FCmpOLE;
						case CompareOp::FCmpOLT: return CompareOp::FCmpOGT;
						case CompareOp::FCmpOLE: return CompareOp::FCmpOGE;
						case CompareOp::FCmpUEQ: return CompareOp::FCmpUEQ;
						case CompareOp::FCmpUNE: return CompareOp::FCmpUNE;
						case CompareOp::FCmpUGT: return CompareOp::FCmpULT;
						case CompareOp::FCmpUGE: return CompareOp::FCmpULE;
						case CompareOp::FCmpULT: return CompareOp::FCmpUGT;
						case CompareOp::FCmpULE: return CompareOp::FCmpUGE;
						}
						OLA_ASSERT_MSG(false, "opcode has to be compare instruction!");
						return CompareOp::FCmpOEQ;
					};

					MI.SetOp<0>(op1).SetOp<1>(op2);
					if (op1.IsImmediate())
					{
						OLA_ASSERT(!op2.IsImmediate());
						MI.SetOp<0>(op2);
						MI.SetOp<1>(op1);
						compare_op = MachineOperand::Immediate((Uint32)GetOppositeCondition(compare_op), MachineType::Other);
					}

					MachineInstruction cset(ARM64_InstCset);
					cset.SetOp<0>(dst);
					cset.SetOp<1>(compare_op);
					instructions.insert(++instruction_iter, cset);

					MachineInstruction andInst(InstAnd);
					andInst.SetOp<0>(dst);
					andInst.SetOp<1>(MachineOperand::Immediate(1, MachineType::Int8));
					instructions.insert(instruction_iter++, andInst);
				}
			}
			break;
			default:
				break;
			}
		}

		virtual void PostLegalizeInstruction(InstLegalizeContext& legalize_ctx) const override
		{
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
				if (r != ARM64_SP && r != ARM64_X29) gp_regs.push_back(r);
			}

			fp_regs.reserve(ARM64_FPREnd - ARM64_FPRBegin + 1);
			for (Uint32 r = ARM64_FPRBegin; r <= ARM64_FPREnd; ++r)
			{
				fp_regs.push_back(r);
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
