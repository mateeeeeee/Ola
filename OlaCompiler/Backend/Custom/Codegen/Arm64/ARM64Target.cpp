#include <fstream>
#include "ARM64Target.h"
#include "Backend/Custom/Codegen/Arm64/arm64.h"
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
			OLA_ASSERT_MSG(false, "ARM64 LegalizeInstruction not yet implemented!");
		}

		virtual void PostLegalizeInstruction(InstLegalizeContext& legalize_ctx) const override
		{
			OLA_ASSERT_MSG(false, "ARM64 PostLegalizeInstruction not yet implemented!");
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
