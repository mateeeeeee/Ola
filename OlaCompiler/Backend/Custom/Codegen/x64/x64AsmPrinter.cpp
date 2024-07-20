#include "x64AsmPrinter.h"
#include "x64.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/Codegen/MIRModule.h"
#include "Backend/Custom/Codegen/MIRBasicBlock.h"

namespace ola
{

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


	void x64AsmPrinter::PrintModule(MIRModule const& M)
	{
		EmitPreamble(".intel_syntax noprefix");

		auto const& globals = M.GetGlobals();
		for (MIRGlobal const& global : globals)
		{
			MIRRelocable* relocable = global.GetRelocable();
			if (relocable->IsFunction())
			{
				MIRFunction& MF = *dynamic_cast<MIRFunction*>(relocable);
				if (global.GetLinkage() == Linkage::External)
				{
					EmitText(".globl {}", MF.GetSymbol());
				}
				EmitText("{}:", MF.GetSymbol());
				EmitText("push	rbp");
				EmitText("mov rbp, rsp");

				int32 stack_allocation = MF.GetStackAllocationSize();
				
				if (stack_allocation > 0) EmitText("sub rsp, {}", stack_allocation);
				for (auto& MBB : MF.Blocks())
				{
					EmitText("{}:", MBB->GetSymbol());
					for (MIRInstruction& MI : MBB->Instructions())
					{
						switch (MI.GetOpcode())
						{
						case InstJump:
						{
							MIROperand const& dst = MI.GetOp<0>();
							OLA_ASSERT(dst.IsRelocable());
							MIRRelocable* relocable = dst.GetRelocable();
							EmitText("jmp {}", relocable->GetSymbol());
						}
						break;
						case InstStore:
						{
							MIROperand const& dst = MI.GetOp<0>();
							MIROperand const& src = MI.GetOp<1>();
							EmitText("mov {}, {}", GetOperandString(dst), GetOperandString(src));
						}
						break;
						}
					}
				}
				EmitText("mov	rsp, rbp"); 
				EmitText("pop	rbp");
				EmitText("ret");
			}
			else if (relocable->IsDataStorage())
			{
			}
			else if (relocable->IsZeroStorage())
			{
			}
			else OLA_ASSERT_MSG(false, "Invalid relocable kind!");
		}
		Finalize();
	}

}

