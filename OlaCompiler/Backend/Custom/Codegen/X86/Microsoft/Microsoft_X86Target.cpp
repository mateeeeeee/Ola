#include <fstream>
#include "Microsoft_X86Target.h"
#include "Microsoft_X86.h"
#include "Backend/Custom/Codegen/X86/X86.h"
#include "Microsoft_X86TargetFrameInfo.h"
#include "Backend/Custom/Codegen/X86/X86TargetInstInfo.h"
#include "Backend/Custom/Codegen/X86/X86TargetISelInfo.h"
#include "Backend/Custom/Codegen/X86/X86AsmPrinter.h"
#include "Backend/Custom/IR/IRType.h"

namespace ola
{
	class Microsoft_X86TargetDataLayout : public TargetDataLayout
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

	class Microsoft_X86TargetRegisterInfo : public TargetRegisterInfo
	{
	public:
		Microsoft_X86TargetRegisterInfo()
		{
			gp_regs.reserve(X86_GPREnd - X86_GPRBegin + 1);
			for (Uint32 r = X86_GPRBegin; r < X86_GPREnd; ++r)
			{
				gp_regs.push_back(r); //skip rbp, rsp
			}

			fp_regs.reserve(X86_FPREnd - X86_FPRBegin + 1);
			for (Uint32 r = X86_FPRBegin; r < X86_FPREnd; ++r)
			{
				fp_regs.push_back(r);
			}
		}

		virtual Uint32 GetStackPointerRegister() const override
		{
			return X86_RSP;
		}
		virtual Uint32 GetGPScratchRegister() const override
		{
			return X86_R15;
		}
		virtual Uint32 GetFPScratchRegister() const override
		{
			return X86_XMM15;
		}
		virtual Uint32 GetFramePointerRegister() const override
		{
			return X86_RBP;
		}
		virtual Uint32 GetReturnRegister() const override
		{
			return X86_RAX;
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
			return X86_IsCallerSaved(r);
		}

		virtual Bool IsCalleeSaved(Uint32 r) const override
		{
			return X86_IsCalleeSaved(r);
		}

	private:
		std::vector<Uint32> gp_regs;
		std::vector<Uint32> fp_regs;
	};

	TargetDataLayout const& Microsoft_X86Target::GetDataLayout() const
	{
		static Microsoft_X86TargetDataLayout X86_target_data_layout{};
		return X86_target_data_layout;
	}

	TargetInstInfo const& Microsoft_X86Target::GetInstInfo() const
	{
		static X86TargetInstInfo X86_target_inst_info{};
		return X86_target_inst_info;
	}

	TargetRegisterInfo const& Microsoft_X86Target::GetRegisterInfo() const
	{
		static Microsoft_X86TargetRegisterInfo X86_target_reg_info{};
		return X86_target_reg_info;
	}

	TargetISelInfo const& Microsoft_X86Target::GetISelInfo() const
	{
		static X86TargetISelInfo X86_target_isel_info{};
		return X86_target_isel_info;
	}

	TargetFrameInfo const& Microsoft_X86Target::GetFrameInfo() const
	{
		static Microsoft_X86TargetFrameInfo X86_target_frame_info{};
		return X86_target_frame_info;
	}

	void Microsoft_X86Target::EmitAssembly(MachineModule& M, std::string_view file) const
	{
		std::ofstream asm_stream(file.data());
		X86AsmPrinter asm_printer(asm_stream);
		asm_printer.PrintModule(M);
	}

}

