#include "x64AsmPrinter.h"
#include "x64.h"
#include "x64TargetFrameInfo.h"
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
		case MIROperandType::Int64: 
		case MIROperandType::Ptr:
		case MIROperandType::Other: return "qword ptr";
		}
		return "";
	}

	static std::string GetOperandString(MIROperand const& MO)
	{
		if (MO.IsReg())
		{
			OLA_ASSERT_MSG(IsISAReg(MO.GetReg().reg), "Virtual register seen after register allocation!");
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
			if (stack_offset != 0)
			{
				std::string offset = std::to_string(stack_offset);
				if (stack_offset >= 0) offset = "+" + offset;
				return GetOperandPrefix(MO) + " [" + std::string(GetRegisterString(x64::RBP)) + offset + "]";
			}
			return GetOperandPrefix(MO) + " [" + std::string(GetRegisterString(x64::RBP)) + "]";
		}
		OLA_ASSERT(false);
		return "";
	}


	void x64AsmPrinter::PrintModule(MIRModule const& M)
	{
		EmitPreamble(".intel_syntax noprefix\n");

		Target const& target = M.GetTarget();
		TargetFrameInfo const& frame_info = target.GetFrameInfo();

		auto const& globals = M.GetGlobals();
		for (MIRGlobal const& global : globals)
		{
			MIRRelocable* relocable = global.GetRelocable();
			if (relocable->IsFunction())
			{
				MIRFunction& MF = *static_cast<MIRFunction*>(relocable);
				if (global.GetLinkage() == Linkage::External)
				{
					if(!MF.IsDeclaration()) EmitText(".globl {}\n", MF.GetSymbol());
					else EmitText(".extern {}\n", MF.GetSymbol());
				}
				if (MF.IsDeclaration()) continue;

				EmitText("{}:", MF.GetSymbol());
				for (auto& MBB : MF.Blocks())
				{
					EmitText("{}:", MBB->GetSymbol());
					for (MIRInstruction& MI : MBB->Instructions())
					{
						switch (MI.GetOpcode())
						{
						case InstPush:
						{
							MIROperand const& op = MI.GetOp<0>();
							EmitText("push {}", GetOperandString(op));
						}
						break;
						case InstPop:
						{
							MIROperand const& op = MI.GetOp<0>();
							EmitText("pop {}", GetOperandString(op));
						}
						break;
						case InstJump:
						{
							MIROperand const& dst = MI.GetOp<0>();
							OLA_ASSERT(dst.IsRelocable());
							MIRRelocable* relocable = dst.GetRelocable();
							EmitText("jmp {}", relocable->GetSymbol());
						}
						break;
						case InstStore:
						case InstLoad:
						{
							MIROperand const& dst = MI.GetOp<0>();
							MIROperand const& src = MI.GetOp<1>();
							EmitText("mov {}, {}", GetOperandString(dst), GetOperandString(src));
						}
						break;
						case InstAdd:
						{
							MIROperand const& dst = MI.GetOp<0>();
							MIROperand const& src = MI.GetOp<1>();
							EmitText("add {}, {}", GetOperandString(dst), GetOperandString(src));
						}
						break;
						case InstSub:
						{
							MIROperand const& dst = MI.GetOp<0>();
							MIROperand const& src = MI.GetOp<1>();
							EmitText("sub {}, {}", GetOperandString(dst), GetOperandString(src));
						}
						break;
						case InstCall:
						{
							MIROperand const& callee = MI.GetOp<0>();
							EmitText("call {}", GetOperandString(callee));
						}
						break;
						}
					}
				}
				EmitText("ret\n");
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

