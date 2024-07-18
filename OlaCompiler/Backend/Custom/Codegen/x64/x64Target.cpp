#include <fstream>
#include "x64Target.h"
#include "x64.h"
#include "x64TargetFrameInfo.h"
#include "x64TargetInstInfo.h"
#include "x64AsmPrinter.h"
#include "Backend/Custom/IR/IRType.h"

namespace ola
{

	class x64TargetDataLayout : public TargetDataLayout
	{
	public:
		virtual bool   IsLittleEndian() const override { return true; }
		virtual uint64 GetBuiltinAlignment(IRType const* type) const override
		{
			return type->GetSize();
		}
		virtual uint64 GetPointerSize() const override
		{
			return 8u;
		}
		virtual uint64 GetCodeAlignment() const override
		{
			return 8u;
		}
		virtual uint64 GetStorageAlignment() const override
		{
			return 8u;
		}
	};

	class x64TargetISelInfo : public TargetISelInfo
	{
	public:
		virtual bool IsLegalInstruction(uint32 opcode) const override
		{
			return false;
		}

		virtual bool LowerInstruction(Instruction*, LoweringContext&) const override
		{
			return false;
		}

		virtual bool LegalizeInstruction(MIRInstruction&, LegalizeContext&) const override
		{
			return false;
		}
	};

	class x64TargetRegisterInfo : public TargetRegisterInfo
	{
	public:
		x64TargetRegisterInfo()
		{
			gp_registers.reserve(x64::GPREnd - x64::GPRBegin + 1);
			for (uint32 r = x64::GPRBegin; r < x64::GPREnd; ++r)
			{
				gp_registers.push_back(r);
			}

			fp_registers.reserve(x64::FPREnd - x64::FPRBegin + 1);
			for (uint32 r = x64::FPRBegin; r < x64::FPREnd; ++r)
			{
				fp_registers.push_back(r);
			}
		}

		virtual uint32 GetStackPointerRegister() const override
		{
			return x64::RSP;
		}

		virtual uint32 GetFramePointerRegister() const override
		{
			return x64::RBP;
		}


		virtual uint32 GetReturnRegister() const override
		{
			return x64::RAX;
		}


		virtual std::vector<uint32> const& GetIntegerRegisters() const override
		{
			return gp_registers;
		}

		virtual std::vector<uint32> const& GetFPRegisters() const override
		{
			return fp_registers;
		}


		virtual bool IsCallerSaved(uint32 r) const override
		{
			return x64::IsCallerSaved(r);
		}


		virtual bool IsCalleeSaved(uint32 r) const override
		{
			return x64::IsCalleeSaved(r);
		}

	private:
		std::vector<uint32> gp_registers;
		std::vector<uint32> fp_registers;
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

	void x64Target::EmitAssembly(MIRModule& M, std::string_view file) const
	{
		std::ofstream asm_stream(file.data());
		x64AsmPrinter asm_printer(asm_stream);
		asm_printer.PrintModule(M);
	}

}

