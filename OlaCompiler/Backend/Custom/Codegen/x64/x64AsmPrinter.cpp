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
		case MachineType::Int8:  return "byte ptr";
		case MachineType::Int64: 
		case MachineType::Float64: 
		case MachineType::Ptr:
		case MachineType::Other: return "qword ptr";
		}
		OLA_ASSERT_MSG(false, "There should be no Undef operands at this point");
		return "";
	}

	static std::string GetOperandString(MachineOperand const& MO, Bool dereference = false)
	{
		if (MO.IsReg())
		{
			OLA_ASSERT_MSG(IsISAReg(MO.GetReg().reg), "Virtual register should not exist after register allocation!");
			if (dereference)
			{
				return std::format("{} [{}]", GetOperandPrefix(MO), x64::GetRegisterString(MO.GetReg().reg, MachineType::Ptr));
			}
			else
			{
				return x64::GetRegisterString(MO.GetReg().reg, MO.GetType());
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
			Int32 stack_offset = MO.GetStackOffset();
			if (stack_offset > 0)		return std::format("{} [{} + {}]", GetOperandPrefix(MO), GetRegisterString(x64::RBP, MachineType::Ptr), stack_offset);
			else if (stack_offset < 0)	return std::format("{} [{} - {}]", GetOperandPrefix(MO), GetRegisterString(x64::RBP, MachineType::Ptr), -stack_offset);
			else						return std::format("{} [{}]", GetOperandPrefix(MO), GetRegisterString(x64::RBP, MachineType::Ptr));
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
						Uint32 opcode = MI.GetOpcode();
						Char const* opcode_string = x64::GetOpcodeString(opcode);
						switch (opcode)
						{
						case InstPush:
						case InstPop:
						case InstCall:
						case InstNeg:
						case InstNot:
						case InstSDiv:
						case x64::InstSetE:
						case x64::InstSetNE:
						case x64::InstSetGT:
						case x64::InstSetGE:
						case x64::InstSetLT:
						case x64::InstSetLE:
						case x64::InstSetA:
						case x64::InstSetAE:
						case x64::InstSetB:
						case x64::InstSetBE:
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
						case x64::InstCqo:
						{
							EmitText("{}", opcode_string);
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
						case InstICmp:
						case InstFAdd:
						case InstFSub:
						case InstFMul:
						case InstFDiv:
						case x64::InstXorFP:
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
						case InstCMoveEQ:
						case InstCMoveNE:
						case InstZExt:
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
							if (op2.IsRelocable())
							{
								EmitText("{} {}, [rip + {}]", opcode_string, GetOperandString(op1), op2.GetRelocable()->GetSymbol());
							}
							else
							{
								EmitText("{} {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2));
							}
						}
						break;
						case x64::InstStoreFP:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(op1, true), GetOperandString(op2));
						}
						break;
						case x64::InstLoadFP:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2, true));
						}
						break;
						case InstF2S:
						case InstFCmp:
						case x64::InstMoveFP:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							if (op2.IsImmediate())
							{
								Int64 imm = op2.GetImmediate();
								std::string entry = GetFPConstantPoolEntry(imm);
								EmitText("{} {}, {} [rip + {}]", opcode_string, GetOperandString(op1), GetOperandPrefix(op2), entry);
							}
							else
							{
								EmitText("{} {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2));
							}
						}
						break;
						case InstS2F:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							if (op2.IsImmediate())
							{
								Int64 imm = op2.GetImmediate();
								std::string entry = GetIntConstantPoolEntry(imm);
								EmitText("{} {}, {} [rip + {}]", opcode_string, GetOperandString(op1), GetOperandPrefix(op2), entry);
							}
							else
							{
								EmitText("{} {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2));
							}
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

				if (MDS.IsReadOnly())
				{
					EmitReadOnly("{}:", relocable->GetSymbol());
					for (auto const& element : storage)
					{
						std::visit([&](auto&& arg)
							{
								using T = std::decay_t<decltype(arg)>;
								if constexpr (std::is_same_v<T, Uint8>)				EmitReadOnly(".byte {}", arg);
								else if constexpr (std::is_same_v<T, Uint16>)		EmitReadOnly(".word {}", arg);
								else if constexpr (std::is_same_v<T, Uint32>)		EmitReadOnly(".long {}", arg);
								else if constexpr (std::is_same_v<T, Uint64>)		EmitReadOnly(".quad {}", arg);
								else if constexpr (std::is_same_v<T, std::string>)	EmitReadOnly(".string \"{}\"", arg);
							}, element);
					}
					EmitReadOnly("\n");
				}
				else
				{
					EmitData("{}:", relocable->GetSymbol());
					for (auto const& element : storage)
					{
						std::visit([&](auto&& arg)
							{
								using T = std::decay_t<decltype(arg)>;
								if constexpr (std::is_same_v<T, Uint8>)				EmitData(".byte {}", arg);
								else if constexpr (std::is_same_v<T, Uint16>)		EmitData(".word {}", arg);
								else if constexpr (std::is_same_v<T, Uint32>)		EmitData(".long {}", arg);
								else if constexpr (std::is_same_v<T, Uint64>)		EmitData(".quad {}", arg);
								else if constexpr (std::is_same_v<T, std::string>)	EmitData(".string \"{}\"", arg);
							}, element);
					}
					EmitData("\n");
				}
			}
			else if (relocable->IsZeroStorage())
			{
				MachineZeroStorage& MZS = *static_cast<MachineZeroStorage*>(relocable);
				EmitBSS("{}:", relocable->GetSymbol());
				EmitBSS(".zero {}", MZS.GetSize());
			}
			else OLA_ASSERT_MSG(false, "Invalid relocable kind!");
		}
		Finalize();
	}


	std::string x64AsmPrinter::GetFPConstantPoolEntry(Int64 value)
	{
		static std::unordered_map<Int64, std::string> fp_constant_pool;
		if (!fp_constant_pool.contains(value))
		{
			static Uint32 entry_index = 0;
			fp_constant_pool[value] = "_FP" + std::to_string(entry_index++);
			EmitReadOnly("{}:", fp_constant_pool[value]);
			EmitReadOnly(".quad {}", value);
			EmitReadOnly("\n");
		}
		return fp_constant_pool[value];
	}

	std::string x64AsmPrinter::GetIntConstantPoolEntry(Int64 value)
	{
		static std::unordered_map<Int64, std::string> int_constant_pool;
		if (!int_constant_pool.contains(value))
		{
			static Uint32 entry_index = 0;
			int_constant_pool[value] = "_INT" + std::to_string(entry_index++);
			EmitReadOnly("{}:", int_constant_pool[value]);
			EmitReadOnly(".quad {}", value);
			EmitReadOnly("\n");
		}
		return int_constant_pool[value];
	}

}

