#include <fstream>
#include "x64Target.h"
#include "x64.h"
#include "x64TargetFrameInfo.h"
#include "x64TargetInstInfo.h"
#include "x64AsmPrinter.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/Codegen/MIRModule.h"
#include "Backend/Custom/Codegen/MIRBasicBlock.h"

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

	static std::string GetOperandPrefix(MIROperand const& MO)
	{
		switch (MO.GetType())
		{
		case MIROperandType::Int8:  return "byte ptr";
		case MIROperandType::Int16: return "word ptr";
		case MIROperandType::Int32: return "dword ptr";
		case MIROperandType::Int64:
		case MIROperandType::Ptr:   
		case MIROperandType::Other:
									return "qword ptr";
		}
		return "";
	}

	static std::string GetOperandString(MIROperand const& MO)
	{
		if (MO.IsReg())
		{
			OLA_ASSERT(IsISAReg(MO.GetReg().reg));
			return x64::GetRegisterString(MO.GetReg().reg);
		}
		else if (MO.IsImmediate())
		{
			return std::to_string(MO.GetImmediate());
		}
		else if (MO.IsRelocable())
		{
			return std::string(MO.GetRelocable()->GetSymbol());
		}
		else if (MO.IsStackObject())
		{
			int32 stack_offset = MO.GetStackOffset();
			std::string offset = std::to_string(stack_offset);
			if (stack_offset >= 0) offset = "+" + offset;
			return GetOperandPrefix(MO) + " [" + std::string(GetRegisterString(x64::RBP)) + offset + "]";
		}
		OLA_ASSERT(false);
		return "";
	}

	void x64Target::EmitAssembly(MIRModule& M, char const* file) const
	{
		x64AsmPrinter asm_printer(file);
		asm_printer.EmitPreamble(".intel_syntax noprefix");

		auto const& globals = M.GetGlobals();
		for (MIRGlobal const& global : globals)
		{
			MIRRelocable* relocable = global.GetRelocable();
			if (relocable->IsFunction())
			{
				MIRFunction& MF = *dynamic_cast<MIRFunction*>(relocable);
				if (global.GetLinkage() == Linkage::External)
				{
					asm_printer.EmitText(".globl {}", MF.GetSymbol());
				}
				asm_printer.EmitText("{}:", MF.GetSymbol());
				asm_printer.EmitText("push	rbp");
				asm_printer.EmitText("mov rbp, rsp");
				for (auto& MBB : MF.Blocks())
				{
					asm_printer.EmitText("{}:", MBB->GetSymbol());
					for (MIRInstruction& MI : MBB->Instructions())
					{
						switch (MI.GetOpcode())
						{
						case InstJump:
						{
							MIROperand const& dst = MI.GetOp<0>();
							OLA_ASSERT(dst.IsRelocable());
							MIRRelocable* relocable = dst.GetRelocable();
							asm_printer.EmitText("jmp {}", relocable->GetSymbol());
						}
						break;
						case InstMove:
						{
							MIROperand const& dst = MI.GetOp<0>();
							MIROperand const& src = MI.GetOp<1>();
							asm_printer.EmitText("mov {}, {}", GetOperandString(dst), GetOperandString(src));
						}
						break;
						}
					}
				}
				asm_printer.EmitText("pop	rbp");
				asm_printer.EmitText("ret");
			}
			else if (relocable->IsDataStorage())
			{
			}
			else if (relocable->IsZeroStorage())
			{
			}
			else OLA_ASSERT_MSG(false, "Invalid relocable kind!");
		}
		asm_printer.Finalize();
	}

}

