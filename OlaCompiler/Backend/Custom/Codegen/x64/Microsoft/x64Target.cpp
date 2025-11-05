#include <fstream>
#include "x64Target.h"
#include "x64Microsoft.h"
#include "Backend/Custom/Codegen/x64/x64.h"
#include "x64TargetFrameInfo.h"
#include "Backend/Custom/Codegen/x64/x64TargetInstInfo.h"
#include "Backend/Custom/Codegen/x64/x64TargetISelInfo.h"
#include "Backend/Custom/Codegen/x64/x64AsmPrinter.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/MachineContext.h"

namespace ola
{
	class Microsoft_x64TargetDataLayout : public TargetDataLayout
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

	class Microsoft_x64TargetRegisterInfo : public TargetRegisterInfo
	{
	public:
		Microsoft_x64TargetRegisterInfo()
		{
			gp_regs.reserve(x64_GPREnd - x64_GPRBegin + 1);
			for (Uint32 r = x64_GPRBegin; r < x64_GPREnd; ++r)
			{
				gp_regs.push_back(r); //skip rbp, rsp
			}

			fp_regs.reserve(x64_FPREnd - x64_FPRBegin + 1);
			for (Uint32 r = x64_FPRBegin; r < x64_FPREnd; ++r)
			{
				fp_regs.push_back(r);
			}
		}

		virtual Uint32 GetStackPointerRegister() const override
		{
			return x64_RSP;
		}
		virtual Uint32 GetGPScratchRegister() const override
		{
			return x64_R15;
		}
		virtual Uint32 GetFPScratchRegister() const override
		{
			return x64_XMM15;
		}
		virtual Uint32 GetFramePointerRegister() const override
		{
			return x64_RBP;
		}
		virtual Uint32 GetReturnRegister() const override
		{
			return x64_RAX;
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
			return x64_IsCallerSaved(r);
		}

		virtual Bool IsCalleeSaved(Uint32 r) const override
		{
			return x64_IsCalleeSaved(r);
		}

	private:
		std::vector<Uint32> gp_regs;
		std::vector<Uint32> fp_regs;
	};

	TargetDataLayout const& Microsoft_x64Target::GetDataLayout() const
	{
		static Microsoft_x64TargetDataLayout x64_target_data_layout{};
		return x64_target_data_layout;
	}

	TargetInstInfo const& Microsoft_x64Target::GetInstInfo() const
	{
		static x64TargetInstInfo x64_target_inst_info{};
		return x64_target_inst_info;
	}

	TargetRegisterInfo const& Microsoft_x64Target::GetRegisterInfo() const
	{
		static Microsoft_x64TargetRegisterInfo x64_target_reg_info{};
		return x64_target_reg_info;
	}

	TargetISelInfo const& Microsoft_x64Target::GetISelInfo() const
	{
		static x64TargetISelInfo x64_target_isel_info{};
		return x64_target_isel_info;
	}

	TargetFrameInfo const& Microsoft_x64Target::GetFrameInfo() const
	{
		static Microsoft_x64TargetFrameInfo x64_target_frame_info{};
		return x64_target_frame_info;
	}

	void Microsoft_x64Target::EmitAssembly(MachineModule& M, std::string_view file) const
	{
		std::ofstream asm_stream(file.data());
		x64AsmPrinter asm_printer(asm_stream);
		asm_printer.PrintModule(M);
	}

}

