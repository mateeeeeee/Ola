#include <format>
#include "X86AsmPrinter.h"
#include "Backend/Custom/Codegen/X86/X86.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/Codegen/Target.h"
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

	static std::string GetOperandPrefixForType(MachineType type)
	{
		switch (type)
		{
		case MachineType::Int8:  return "byte ptr";
		case MachineType::Int64:
		case MachineType::Float64:
		case MachineType::Ptr:
		case MachineType::Other: return "qword ptr";
		}
		return "qword ptr";
	}

	static std::string GetOperandString(MachineOperand const& MO, Bool dereference = false)
	{
		if (MO.IsReg())
		{
			OLA_ASSERT_MSG(IsISAReg(MO.GetReg().reg), "Virtual register should not exist after register allocation!");
			if (dereference)
			{
				return std::format("{} [{}]", GetOperandPrefix(MO), X86_GetRegisterString(MO.GetReg().reg, MachineType::Ptr));
			}
			else
			{
				return X86_GetRegisterString(MO.GetReg().reg, MO.GetType());
			}
		}
		else if (MO.IsImmediate())
		{
			return std::to_string(MO.GetImmediate());
		}
		else if (MO.IsRelocable())
		{
			std::string symbol = MO.GetRelocable()->GetMangledSymbol();
			return MO.GetRelocable()->IsFunction() ? symbol
				: std::format("{} {}[rip]", GetOperandPrefix(MO), symbol);
		}
		else if (MO.IsStackObject())
		{
			Int32 stack_offset = MO.GetStackOffset();
			if (stack_offset > 0)		return std::format("{} [{} + {}]", GetOperandPrefix(MO), X86_GetRegisterString(X86_RBP, MachineType::Ptr), stack_offset);
			else if (stack_offset < 0)	return std::format("{} [{} - {}]", GetOperandPrefix(MO), X86_GetRegisterString(X86_RBP, MachineType::Ptr), -stack_offset);
			else						return std::format("{} [{}]", GetOperandPrefix(MO), X86_GetRegisterString(X86_RBP, MachineType::Ptr));
		}
		OLA_ASSERT(false);
		return "";
	}

	static std::string GetMemoryOperandWithType(MachineOperand const& MO, MachineType type)
	{
		std::string prefix = GetOperandPrefixForType(type);
		if (MO.IsReg())
		{
			return std::format("{} [{}]", prefix, X86_GetRegisterString(MO.GetReg().reg, MachineType::Ptr));
		}
		else if (MO.IsStackObject())
		{
			Int32 stack_offset = MO.GetStackOffset();
			if (stack_offset > 0)		return std::format("{} [{} + {}]", prefix, X86_GetRegisterString(X86_RBP, MachineType::Ptr), stack_offset);
			else if (stack_offset < 0)	return std::format("{} [{} - {}]", prefix, X86_GetRegisterString(X86_RBP, MachineType::Ptr), -stack_offset);
			else						return std::format("{} [{}]", prefix, X86_GetRegisterString(X86_RBP, MachineType::Ptr));
		}
		else if (MO.IsRelocable())
		{
			std::string symbol = MO.GetRelocable()->GetMangledSymbol();
			return std::format("{} {}[rip]", prefix, symbol);
		}
		OLA_ASSERT(false);
		return "";
	}

	static std::string GetLeaOperandString(MachineOperand const& MO)
	{
		if (MO.IsReg())
		{
			return X86_GetRegisterString(MO.GetReg().reg, MachineType::Ptr);
		}
		else if (MO.IsStackObject())
		{
			// For stack objects in LEA, we need to reference them as rbp-relative
			// But LEA expects register operands. This shouldn't happen in well-formed LEA.
			// If it does, we need to emit the rbp + offset calculation
			Int32 stack_offset = MO.GetStackOffset();
			return X86_GetRegisterString(X86_RBP, MachineType::Ptr);
		}
		OLA_ASSERT_MSG(false, "LEA operand should be a register");
		return "";
	}

	void X86AsmPrinter::PrintModule(MachineModule const& M)
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
				std::string symbol_name = MF.GetMangledSymbol();
				if (global.GetLinkage() == Linkage::External)
				{
					if(!MF.IsDeclaration()) EmitText(".globl {}\n", symbol_name);
					else EmitText(".extern {}\n", symbol_name);
				}
				if (MF.IsDeclaration()) continue;

				EmitText("{}:", symbol_name);
				for (auto& MBB : MF.Blocks())
				{
					EmitText("{}:", MBB->GetSymbol());
					for (MachineInstruction& MI : MBB->Instructions())
					{
						if (MI.IsDead()) continue;
						Uint32 opcode = MI.GetOpcode();
						Char const* opcode_string = X86_GetOpcodeString(opcode);
						switch (opcode)
						{
						case InstPush:
						case InstPop:
						case InstCall:
						case InstNeg:
						case InstNot:
						case InstSDiv:
						case X86_InstSetE:
						case X86_InstSetNE:
						case X86_InstSetGT:
						case X86_InstSetGE:
						case X86_InstSetLT:
						case X86_InstSetLE:
						case X86_InstSetA:
						case X86_InstSetAE:
						case X86_InstSetB:
						case X86_InstSetBE:
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
						case InstRet:
						case X86_InstCqo:
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
						case X86_InstXorFP:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2));
						}
						break;
						case InstStore:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetMemoryOperandWithType(dst, src.GetType()), GetOperandString(src));
						}
						break;
						case InstLoad:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(dst), GetMemoryOperandWithType(src, dst.GetType()));
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
								std::string symbol = op2.GetRelocable()->GetMangledSymbol();
								EmitText("{} {}, [rip + {}]", opcode_string, GetOperandString(op1), symbol);
							}
							else
							{
								EmitText("{} {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2));
							}
						}
						break;
						case X86_InstStoreFP:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(op1, true), GetOperandString(op2));
						}
						break;
						case X86_InstLoadFP:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2, true));
						}
						break;
						case InstF2S:
						case InstFCmp:
						case X86_InstMoveFP:
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
						case X86_InstLea:
						{
							// lea dst, [base + index*scale + disp]
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& base = MI.GetOp<1>();
							MachineOperand const& index = MI.GetOp<2>();
							MachineOperand const& scale = MI.GetOp<3>();
							MachineOperand const& disp = MI.GetOp<4>();

							std::string addr;
							Bool has_base = !base.IsUndefined();
							Bool has_index = !index.IsUndefined();
							Int64 scale_val = scale.GetImmediate();
							Int64 disp_val = disp.GetImmediate();

							if (has_base && has_index)
							{
								if (scale_val == 1)
								{
									if (disp_val == 0)
										addr = std::format("[{} + {}]", GetOperandString(base), GetOperandString(index));
									else if (disp_val > 0)
										addr = std::format("[{} + {} + {}]", GetOperandString(base), GetOperandString(index), disp_val);
									else
										addr = std::format("[{} + {} - {}]", GetOperandString(base), GetOperandString(index), -disp_val);
								}
								else
								{
									if (disp_val == 0)
										addr = std::format("[{} + {}*{}]", GetOperandString(base), GetOperandString(index), scale_val);
									else if (disp_val > 0)
										addr = std::format("[{} + {}*{} + {}]", GetOperandString(base), GetOperandString(index), scale_val, disp_val);
									else
										addr = std::format("[{} + {}*{} - {}]", GetOperandString(base), GetOperandString(index), scale_val, -disp_val);
								}
							}
							else if (has_base)
							{
								if (disp_val == 0)
									addr = std::format("[{}]", GetOperandString(base));
								else if (disp_val > 0)
									addr = std::format("[{} + {}]", GetOperandString(base), disp_val);
								else
									addr = std::format("[{} - {}]", GetOperandString(base), -disp_val);
							}
							else if (has_index)
							{
								if (scale_val == 1)
								{
									if (disp_val == 0)
										addr = std::format("[{}]", GetOperandString(index));
									else if (disp_val > 0)
										addr = std::format("[{} + {}]", GetOperandString(index), disp_val);
									else
										addr = std::format("[{} - {}]", GetOperandString(index), -disp_val);
								}
								else
								{
									if (disp_val == 0)
										addr = std::format("[{}*{}]", GetOperandString(index), scale_val);
									else if (disp_val > 0)
										addr = std::format("[{}*{} + {}]", GetOperandString(index), scale_val, disp_val);
									else
										addr = std::format("[{}*{} - {}]", GetOperandString(index), scale_val, -disp_val);
								}
							}
							else
							{
								addr = std::format("[{}]", disp_val);
							}
							EmitText("{} {}, {}", opcode_string, GetOperandString(dst), addr);
						}
						break;
						default:
							OLA_ASSERT(false);
						}
					}
				}
			}
			else if (relocable->IsDataStorage())
			{
				MachineDataStorage& MDS = *static_cast<MachineDataStorage*>(relocable);
				auto const& storage = MDS.GetStorage();

				std::string data_symbol = relocable->GetMangledSymbol();

				if (MDS.IsReadOnly())
				{
					EmitReadOnly("{}:", data_symbol);
					for (auto const& element : storage)
					{
						std::visit([&](auto&& arg)
							{
								using T = std::decay_t<decltype(arg)>;
								if constexpr (std::is_same_v<T, Uint8>)					EmitReadOnly(".byte {}", arg);
								else if constexpr (std::is_same_v<T, Uint16>)			EmitReadOnly(".word {}", arg);
								else if constexpr (std::is_same_v<T, Uint32>)			EmitReadOnly(".long {}", arg);
								else if constexpr (std::is_same_v<T, Uint64>)			EmitReadOnly(".quad {}", arg);
								else if constexpr (std::is_same_v<T, std::string>)		EmitReadOnly(".string \"{}\"", arg);
								else if constexpr (std::is_same_v<T, MachineSymbolRef>)	EmitReadOnly(".quad {}", arg.name);
							}, element);
					}
					EmitReadOnly("\n");
				}
				else
				{
					EmitData("{}:", data_symbol);
					for (auto const& element : storage)
					{
						std::visit([&](auto&& arg)
							{
								using T = std::decay_t<decltype(arg)>;
								if constexpr (std::is_same_v<T, Uint8>)					EmitData(".byte {}", arg);
								else if constexpr (std::is_same_v<T, Uint16>)			EmitData(".word {}", arg);
								else if constexpr (std::is_same_v<T, Uint32>)			EmitData(".long {}", arg);
								else if constexpr (std::is_same_v<T, Uint64>)			EmitData(".quad {}", arg);
								else if constexpr (std::is_same_v<T, std::string>)		EmitData(".string \"{}\"", arg);
								else if constexpr (std::is_same_v<T, MachineSymbolRef>)	EmitData(".quad {}", arg.name);
							}, element);
					}
					EmitData("\n");
				}
			}
			else if (relocable->IsZeroStorage())
			{
				MachineZeroStorage& MZS = *static_cast<MachineZeroStorage*>(relocable);
				std::string bss_symbol = relocable->GetMangledSymbol();
				EmitBSS("{}:", bss_symbol);
				EmitBSS(".zero {}", MZS.GetSize());
			}
			else OLA_ASSERT_MSG(false, "Invalid relocable kind!");
		}
		Finalize();
	}


	std::string X86AsmPrinter::GetFPConstantPoolEntry(Int64 value)
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

	std::string X86AsmPrinter::GetIntConstantPoolEntry(Int64 value)
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

