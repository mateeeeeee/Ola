#include <fstream>
#include "x64Target.h"
#include "x64.h"
#include "x64TargetFrameInfo.h"
#include "x64TargetInstInfo.h"
#include "x64AsmPrinter.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/MIRInstruction.h"
#include "Backend/Custom/Codegen/LoweringContext.h"

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
		virtual bool LowerInstruction(Instruction* I, LoweringContext& ctx) const override
		{
			return false;
		}

		virtual void LegalizeInstruction(InstLegalizeContext& legalize_ctx, LoweringContext& lowering_ctx) const override
		{
			MIRInstruction& MI = legalize_ctx.instruction;
			auto& instructions = legalize_ctx.instructions;
			auto& instruction_iter = legalize_ctx.instruction_iterator;

			if (MI.GetOpcode() == InstStore) 
			{
				MIROperand dst = MI.GetOperand(0);
				MIROperand src = MI.GetOperand(1);
				if ((src.IsStackObject() || src.IsRelocable()) && (dst.IsStackObject() || dst.IsRelocable()))
				{
					MIROperand tmp = lowering_ctx.VirtualReg(src.GetType());
					MI.SetOp<0>(tmp);
					MI.SetIgnoringDefFlag();

					MIRInstruction MI2(InstStore);
					MI2.SetOp<0>(dst);
					MI2.SetOp<1>(tmp);
					instructions.insert(++instruction_iter, MI2);
				}
			}
			if (MI.GetOpcode() == InstAdd || MI.GetOpcode() == InstSub)
			{
				MIROperand dst = MI.GetOperand(0);
				MIROperand op1 = MI.GetOperand(1);
				MIROperand op2 = MI.GetOperand(2);
				if (!op2.IsUnused())
				{
					MI.SetOp<1>(op2);
					MI.SetIgnoringDefFlag();
					MIRInstruction MI2(InstLoad);
					MI2.SetOp<0>(dst);
					MI2.SetOp<1>(op1);
					instructions.insert(instruction_iter, MI2);
				}
			}
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

