#include <format>
#include "ARMAsmPrinter.h"
#include "Backend/Custom/Codegen/ARM/ARM.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/Codegen/Target.h"
#include "Backend/Custom/Codegen/MachineModule.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/MachineStorage.h"

namespace ola
{
	static std::string GetOperandString(MachineOperand const& MO, Bool is_address = false)
	{
		if (MO.IsReg())
		{
			OLA_ASSERT_MSG(ARM64_IsISAReg(MO.GetReg().reg), "Virtual register should not exist after register allocation!");
			if (is_address)
			{
				return std::format("[{}]", ARM64_GetRegisterString(MO.GetReg().reg, MachineType::Ptr));
			}
			else
			{
				return ARM64_GetRegisterString(MO.GetReg().reg, MO.GetType());
			}
		}
		else if (MO.IsImmediate())
		{
			return std::format("#{}", MO.GetImmediate());
		}
		else if (MO.IsRelocable())
		{
			std::string symbol = std::string(MO.GetRelocable()->GetSymbol());
#if defined(OLA_PLATFORM_MACOS)
			symbol = "_" + symbol;
#endif
			return symbol;
		}
		else if (MO.IsStackObject())
		{
			Int32 stack_offset = MO.GetStackOffset();
			if (stack_offset >= 0)
				return std::format("[x29, #{}]", stack_offset);
			else
				return std::format("[x29, #-{}]", -stack_offset);
		}
		OLA_ASSERT(false);
		return "";
	}

	static std::string GetConditionString(Uint32 opcode)
	{
		switch (opcode)
		{
		case ARM64_InstCsetEQ: return "eq";
		case ARM64_InstCsetNE: return "ne";
		case ARM64_InstCsetGT: return "gt";
		case ARM64_InstCsetGE: return "ge";
		case ARM64_InstCsetLT: return "lt";
		case ARM64_InstCsetLE: return "le";
		default: return "";
		}
	}

	void ARM64AsmPrinter::PrintModule(MachineModule const& M)
	{
		EmitPreamble("");

		Target const& target = M.GetTarget();
		TargetFrameInfo const& frame_info = target.GetFrameInfo();

		auto const& globals = M.GetGlobals();
		for (MachineGlobal const& global : globals)
		{
			MachineRelocable* relocable = global.GetRelocable();
			if (relocable->IsFunction())
			{
				MachineFunction& MF = *static_cast<MachineFunction*>(relocable);
				std::string symbol_name(MF.GetSymbol());
#if defined(OLA_PLATFORM_MACOS)
				symbol_name = "_" + symbol_name;
#endif
				if (global.GetLinkage() == Linkage::External)
				{
					if (!MF.IsDeclaration()) EmitText(".globl {}", symbol_name);
					else EmitText(".extern {}", symbol_name);
				}
				if (MF.IsDeclaration()) 
				{
					continue;
				}

				EmitText("{}:", symbol_name);
				for (auto& MBB : MF.Blocks())
				{
					EmitText("{}:", MBB->GetSymbol());
					for (MachineInstruction& MI : MBB->Instructions())
					{
						if (MI.IsDead()) 
						{
							continue;
						}
						Uint32 opcode = MI.GetOpcode();
						Char const* opcode_string = ARM64_GetOpcodeString(opcode);

						switch (opcode)
						{
						case InstNeg:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(dst), GetOperandString(src));
						}
						break;
						case InstNot:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(dst), GetOperandString(src));
						}
						break;
						case InstFNeg:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(dst), GetOperandString(src));
						}
						break;
						case InstJump:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							OLA_ASSERT(dst.IsRelocable());
							MachineRelocable* relocable = dst.GetRelocable();
							EmitText("{} {}", opcode_string, relocable->GetSymbol());
						}
						break;

						case InstJE:
						case InstJNE:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							OLA_ASSERT(dst.IsRelocable());
							MachineRelocable* relocable = dst.GetRelocable();
							Char const* cond = (opcode == InstJE) ? "b.eq" : "b.ne";
							EmitText("{} {}", cond, relocable->GetSymbol());
						}
						break;
						case InstCall:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							std::string symbol = GetOperandString(dst);
							EmitText("{} {}", opcode_string, symbol);
						}
						break;
						case InstRet:
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
						case InstLShr:
						case InstSMul:
						case InstUMul:
						case InstSDiv:
						case InstUDiv:
						case InstSRem:
						case InstURem:
						case InstFAdd:
						case InstFSub:
						case InstFMul:
						case InstFDiv:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& op1 = MI.GetOp<1>();
							MachineOperand const& op2 = MI.GetOp<2>();
							EmitText("{} {}, {}, {}", opcode_string, GetOperandString(dst), GetOperandString(op1), GetOperandString(op2));
						}
						break;
						case InstICmp:
						case InstFCmp:
						case InstTest:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2));
						}
						break;
						case InstLoad:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();

							std::string opcode_suffix = (dst.GetType() == MachineType::Int8) ? "b" : "";

							if (src.IsStackObject())
							{
								EmitText("{}{} {}, {}", opcode_string, opcode_suffix, GetOperandString(dst), GetOperandString(src));
							}
							else if (src.IsRelocable())
							{
								std::string symbol = GetOperandString(src);
								std::string dst_str = GetOperandString(dst);
								if (dst.GetType() == MachineType::Float64)
								{
									EmitText("adrp x16, {}@PAGE", symbol);
									EmitText("{}{} {}, [x16, {}@PAGEOFF]", opcode_string, opcode_suffix, dst_str, symbol);
								}
								else
								{
									// For adrp and base addressing, we always need the X register version
									std::string dst_x_str = ARM64_GetRegisterString(dst.GetReg().reg, MachineType::Ptr);
									EmitText("adrp {}, {}@PAGE", dst_x_str, symbol);
									EmitText("{}{} {}, [{}, {}@PAGEOFF]", opcode_string, opcode_suffix, dst_str, dst_x_str, symbol);
								}
							}
							else
							{
								EmitText("{}{} {}, {}", opcode_string, opcode_suffix, GetOperandString(dst), GetOperandString(src, true));
							}
						}
						break;
						case InstStore:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();

							std::string opcode_suffix = (src.GetType() == MachineType::Int8) ? "b" : "";

							if (dst.IsStackObject())
							{
								EmitText("{}{} {}, {}", opcode_string, opcode_suffix, GetOperandString(src), GetOperandString(dst));
							}
							else if (dst.IsRelocable())
							{
								std::string symbol = GetOperandString(dst);
								std::string src_str = GetOperandString(src);
								EmitText("adrp x16, {}@PAGE", symbol);
								EmitText("{}{} {}, [x16, {}@PAGEOFF]", opcode_string, opcode_suffix, src_str, symbol);
							}
							else
							{
								EmitText("{}{} {}, {}", opcode_string, opcode_suffix, GetOperandString(src), GetOperandString(dst, true));
							}
						}
						break;
						case InstMove:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();

							if (src.IsImmediate())
							{
								Int64 imm = src.GetImmediate();
								if (imm >= 0 && imm <= 65535)
								{
									EmitText("{} {}, #{}", opcode_string, GetOperandString(dst), imm);
								}
								else if (imm < 0 && imm >= -65536)
								{
									EmitText("{} {}, #{}", opcode_string, GetOperandString(dst), imm);
								}
								else
								{
									std::string pool_label = GetIntConstantPoolEntry(imm);
									std::string dst_str = GetOperandString(dst);
									EmitText("adrp {}, {}@PAGE", dst_str, pool_label);
									EmitText("ldr {}, [{}, {}@PAGEOFF]", dst_str, dst_str, pool_label);
								}
							}
							else
							{
								EmitText("{} {}, {}", opcode_string, GetOperandString(dst), GetOperandString(src));
							}
						}
						break;
						case InstLoadGlobalAddress:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();

							if (src.IsRelocable())
							{
								std::string symbol = GetOperandString(src);
								std::string dst_str = GetOperandString(dst);
								//ADRP loads page address, ADD adds page offset
								EmitText("adrp {}, {}@PAGE", dst_str, symbol);
								EmitText("add {}, {}, {}@PAGEOFF", dst_str, dst_str, symbol);
							}
							else if (src.IsStackObject())
							{
								Int32 stack_offset = src.GetStackOffset();
								std::string dst_str = GetOperandString(dst);
								if (stack_offset >= 0)
								{
									EmitText("add {}, x29, #{}", dst_str, stack_offset);
								}
								else
								{
									EmitText("sub {}, x29, #{}", dst_str, -stack_offset);
								}
							}
							else
							{
								EmitText("add {}, {}, #0", GetOperandString(dst), GetOperandString(src));
							}
						}
						break;
						case InstCMoveEQ:
						case InstCMoveNE:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();
							Char const* cond = (opcode == InstCMoveEQ) ? "eq" : "ne";
							Char const* inst = (dst.GetType() == MachineType::Float64) ? "fcsel" : "csel";
							EmitText("{} {}, {}, {}, {}", inst, GetOperandString(dst), GetOperandString(src), GetOperandString(dst), cond);
						}
						break;
						case InstF2S:
						case InstS2F:
						case InstZExt:
						case ARM64_InstFMov:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(dst), GetOperandString(src));
						}
						break;
						case ARM64_InstStp:
						case ARM64_InstLdp:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							MachineOperand const& addr = MI.GetOp<2>();

							std::string addr_str;
							if (addr.IsStackObject())
							{
								Int32 offset = addr.GetStackOffset();
								if (offset >= 0)
								{
									addr_str = std::format("[sp, #{}]", offset);
								}
								else
								{
									addr_str = GetOperandString(addr);
								}
							}
							else
							{
								addr_str = GetOperandString(addr);
							}
							EmitText("{} {}, {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2), addr_str);
						}
						break;
						case ARM64_InstAdrp:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& src = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(dst), GetOperandString(src));
						}
						break;
						case ARM64_InstMovz:
						case ARM64_InstMovk:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& imm = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(dst), GetOperandString(imm));
						}
						break;
						case ARM64_InstCset:
						case ARM64_InstCsetEQ:
						case ARM64_InstCsetNE:
						case ARM64_InstCsetGT:
						case ARM64_InstCsetGE:
						case ARM64_InstCsetLT:
						case ARM64_InstCsetLE:
						{
							MachineOperand const& dst = MI.GetOp<0>();
							std::string cond = GetConditionString(opcode);
							EmitText("{} {}, {}", opcode_string, GetOperandString(dst), cond);
						}
						break;
						case ARM64_InstMrs:
						case ARM64_InstMsr:
						{
							MachineOperand const& op1 = MI.GetOp<0>();
							MachineOperand const& op2 = MI.GetOp<1>();
							EmitText("{} {}, {}", opcode_string, GetOperandString(op1), GetOperandString(op2));
						}
						break;
						case ARM64_InstMsub:
						{
							//msub Xd, Xn, Xm, Xa  =>  Xd = Xa - (Xn * Xm)
							MachineOperand const& dst = MI.GetOp<0>();
							MachineOperand const& op1 = MI.GetOp<1>();
							MachineOperand const& op2 = MI.GetOp<2>();
							MachineOperand const& op3 = MI.GetOp<3>();
							EmitText("{} {}, {}, {}, {}", opcode_string, GetOperandString(dst), GetOperandString(op1), GetOperandString(op2), GetOperandString(op3));
						}
						break;

						default:
							OLA_ASSERT_MSG(false, "Unhandled ARM64 instruction in assembly printer!");
						}
					}
				}
			}
			else if (relocable->IsDataStorage())
			{
				MachineDataStorage& MDS = *static_cast<MachineDataStorage*>(relocable);
				auto const& storage = MDS.GetStorage();

				std::string data_symbol(relocable->GetSymbol());
#if defined(OLA_PLATFORM_MACOS)
				data_symbol = "_" + data_symbol;
#endif

				if (MDS.IsReadOnly())
				{
					EmitReadOnly("{}:", data_symbol);
					for (auto const& element : storage)
					{
						std::visit([&](auto&& arg)
							{
								using T = std::decay_t<decltype(arg)>;
								if constexpr (std::is_same_v<T, Uint8>)				EmitReadOnly(".byte {}", arg);
								else if constexpr (std::is_same_v<T, Uint16>)		EmitReadOnly(".short {}", arg);
								else if constexpr (std::is_same_v<T, Uint32>)		EmitReadOnly(".long {}", arg);
								else if constexpr (std::is_same_v<T, Uint64>)		EmitReadOnly(".quad {}", arg);
								else if constexpr (std::is_same_v<T, std::string>)	EmitReadOnly(".string \"{}\"", arg);
							}, element);
					}
					EmitReadOnly(".p2align 3");  
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
								if constexpr (std::is_same_v<T, Uint8>)				EmitData(".byte {}", arg);
								else if constexpr (std::is_same_v<T, Uint16>)		EmitData(".short {}", arg);
								else if constexpr (std::is_same_v<T, Uint32>)		EmitData(".long {}", arg);
								else if constexpr (std::is_same_v<T, Uint64>)		EmitData(".quad {}", arg);
								else if constexpr (std::is_same_v<T, std::string>)	EmitData(".string \"{}\"", arg);
							}, element);
					}
					EmitData(".p2align 3");  
					EmitData("\n");
				}
			}
			else if (relocable->IsZeroStorage())
			{
				MachineZeroStorage& MZS = *static_cast<MachineZeroStorage*>(relocable);
				std::string bss_symbol(relocable->GetSymbol());
#if defined(OLA_PLATFORM_MACOS)
				bss_symbol = "_" + bss_symbol;
#endif
				EmitBSS("{}:", bss_symbol);
				EmitBSS(".zero {}", MZS.GetSize());
			}
			else OLA_ASSERT_MSG(false, "Invalid relocable kind!");
		}
		Finalize();
	}

	std::string ARM64AsmPrinter::GetFPConstantPoolEntry(Int64 value)
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

	std::string ARM64AsmPrinter::GetIntConstantPoolEntry(Int64 value)
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
