#include <format>
#include "x64AsmPrinter.h"
#include "x64.h"
#include "x64TargetFrameInfo.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/Codegen/MachineModule.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/MachineStorage.h"

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

	static std::string GetOperandString(MachineOperand const& MO, bool dereference = false)
	{
		if (MO.IsReg())
		{
			OLA_ASSERT_MSG(IsISAReg(MO.GetReg().reg), "Virtual register should not exist after register allocation!");
			std::string reg_name = x64::GetRegisterString(MO.GetReg().reg, MO.GetType());
			if (dereference)
			{
				return std::format("{} [{}]", GetOperandPrefix(MO), reg_name);
			}
			else
			{
				return reg_name;
			}
		}
		else if (MO.IsImmediate())
		{
			return std::to_string(MO.GetImmediate());
		}
		else if (MO.IsRelocable())
		{
			return MO.GetRelocable()->IsFunction() ? std::string(MO.GetRelocable()->GetSymbol())
				: std::format("{} {}[rip]", GetOperandPrefix(MO), MO.GetRelocable()->GetSymbol());
		}
		else if (MO.IsStackObject())
		{
			int32 stack_offset = MO.GetStackOffset();
			if (stack_offset > 0)		return std::format("{} [{} + {}]", GetOperandPrefix(MO), GetRegisterString(x64::RBP, MachineOperandType::Ptr), stack_offset);
			else if (stack_offset < 0)	return std::format("{} [{} - {}]", GetOperandPrefix(MO), GetRegisterString(x64::RBP, MachineOperandType::Ptr), -stack_offset);
			else						return std::format("{} [{}]", GetOperandPrefix(MO), GetRegisterString(x64::RBP, MachineOperandType::Ptr));
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
						uint32 opcode = MI.GetOpcode();
						char const* opcode_string = x64::GetOpcodeString(opcode);
						switch (opcode)
						{
						case InstPush:
						case InstPop:
						case InstCall:
						case InstNeg:
						case InstSDiv:
						case x64::InstSetE:
						case x64::InstSetNE:
						case x64::InstSetGT:
						case x64::InstSetGE:
						case x64::InstSetLT:
						case x64::InstSetLE:
						{
							MachineOperand const& op = MI.GetOp<0>();
							EmitText("{} {}", opcode_string, GetOperandString(op));
						}
						break;
						case InstJump:
						case InstJE:
						case InstJNE:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							OLA_ASSERT(dst.IsRelocable());
							MachineRelocable* relocable = dst.GetRelocable();
							EmitText("{} {}", opcode_string, relocable->GetSymbol());
						}
						break;
						case InstAdd:
						case InstSub:
						case InstAnd:
						case InstOr:
						case InstXor:
						case InstShl:
						case InstAShr:
						case InstTest:
						case InstSMul:
						case x64::InstICmp:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2));
						}
						break;
						case InstStore:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(op1, true), GetOperandString(op2));
						}
						break;
						case InstLoad:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2, true));
						}
						break;
						case InstMove:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2));
						}
						break;
						case InstLoadGlobalAddress:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							OLA_ASSERT(op2.IsRelocable());
							EmitText("{} {}, [rip + {}]", opcode_string, GetOperandString(op1), op2.GetRelocable()->GetSymbol());
						}
						break;
						case x64::InstCqo:
						{
							EmitText("{}", opcode_string);
						}
						break;
						default: 
							OLA_ASSERT(false);
						}
					}
				}
				EmitText("ret\n");
			}
			else if (relocable->IsDataStorage())
			{
				MachineDataStorage& MDS = *static_cast<MachineDataStorage*>(relocable);
				auto const& storage = MDS.GetStorage();

				EmitText("{}:", relocable->GetSymbol());
				for (auto const& element : storage)
				{
					std::visit([&](auto&& arg)
						{
							using T = std::decay_t<decltype(arg)>;
							if constexpr (std::is_same_v<T, uint8>)		  EmitText(".byte {}", arg);
							else if constexpr (std::is_same_v<T, uint16>) EmitText(".word {}", arg);
							else if constexpr (std::is_same_v<T, uint32>) EmitText(".long {}", arg);
							else if constexpr (std::is_same_v<T, uint64>) EmitText(".quad {}", arg);
							else static_assert(false, "non-exhaustive visitor!");
						}, element);
				}
				EmitText("\n");
			}
			else if (relocable->IsZeroStorage())
			{
				MachineZeroStorage& MZS = *static_cast<MachineZeroStorage*>(relocable);
				EmitText("{}:", relocable->GetSymbol());
				EmitText(".zero {}", MZS.GetSize());
			}
			else OLA_ASSERT_MSG(false, "Invalid relocable kind!");
		}
		Finalize();
	}

}

