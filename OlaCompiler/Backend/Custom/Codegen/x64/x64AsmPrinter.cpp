#include "x64AsmPrinter.h"
#include "x64.h"
#include "x64TargetFrameInfo.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/Codegen/MachineModule.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"

namespace ola
{

	static std::string GetOperandPrefix(MachineOperand const& MO)
	{
		switch (MO.GetType())
		{
		case MachineOperandType::Int8:  return "byte ptr";
		case MachineOperandType::Int64: 
		case MachineOperandType::Ptr:
		case MachineOperandType::Other: return "qword ptr";
		}
		return "";
	}

	static std::string GetOperandString(MachineOperand const& MO)
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


	void x64AsmPrinter::PrintModule(MachineModule const& M)
	{
		EmitPreamble(".intel_syntax noprefix\n");

		Target const& target = M.GetTarget();
		TargetFrameInfo const& frame_info = target.GetFrameInfo();

		auto const& globals = M.GetGlobals();
		for (MachineGlobal const& global : globals)
		{
			MachineRelocable* relocable = global.GetRelocable();
			if (relocable->IsFunction())
			{
				MachineFunction& MF = *static_cast<MachineFunction*>(relocable);
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
					for (MachineInstruction& MI : MBB->Instructions())
					{
						switch (MI.GetOpcode())
						{
						case InstPush:
						{
							MachineOperand const& op = MI.GetOp<0>();
							EmitText("push {}", GetOperandString(op));
						}
						break;
						case InstPop:
						{
							MachineOperand const& op = MI.GetOp<0>();
							EmitText("pop {}", GetOperandString(op));
						}
						break;
						case InstJump:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							OLA_ASSERT(dst.IsRelocable());
							MachineRelocable* relocable = dst.GetRelocable();
							EmitText("jmp {}", relocable->GetSymbol());
						}
						break;
						case InstStore:
						case InstLoad:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();
							EmitText("mov {}, {}", GetOperandString(dst), GetOperandString(src));
						}
						break;
						case InstAdd:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();
							EmitText("add {}, {}", GetOperandString(dst), GetOperandString(src));
						}
						break;
						case InstSub:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();
							EmitText("sub {}, {}", GetOperandString(dst), GetOperandString(src));
						}
						break;
						case InstCall:
						{
							MachineOperand const& callee = MI.GetOp<0>();
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

