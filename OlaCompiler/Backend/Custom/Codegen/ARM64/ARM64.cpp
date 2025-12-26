#include "ARM64.h"
#include "Backend/Custom/Codegen/MachineOperand.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"

namespace ola
{
	Char const* ARM64_GetOpcodeString(Uint32 opcode)
	{
		switch (opcode)
		{
		case InstAdd:    return "add";
		case InstSub:    return "sub";
		case InstSMul:   return "mul";
		case InstUMul:   return "mul";
		case InstSDiv:   return "sdiv";
		case InstUDiv:   return "udiv";
		case InstAnd:    return "and";
		case InstOr:     return "orr";
		case InstXor:    return "eor";
		case InstShl:    return "lsl";
		case InstAShr:   return "asr";
		case InstLShr:   return "lsr";
		case InstNeg:    return "neg";
		case InstNot:    return "mvn";
		case InstMove:   return "mov";
		case InstLoad:   return "ldr";
		case InstStore:  return "str";
		case InstJump:   return "b";
		case InstJE:     return "b.eq";
		case InstJNE:    return "b.ne";
		case InstRet:    return "ret";
		case InstCall:   return "bl";
		case InstICmp:   return "cmp";
		case InstFCmp:   return "fcmp";
		case InstTest:   return "tst";
		case InstFAdd:   return "fadd";
		case InstFSub:   return "fsub";
		case InstFMul:   return "fmul";
		case InstFDiv:   return "fdiv";
		case InstFNeg:   return "fneg";
		case InstS2F:    return "scvtf";
		case InstF2S:    return "fcvtzs";
		case InstZExt:   return "uxtb";

		case ARM64_InstAdrp:   return "adrp";
		case ARM64_InstStp:    return "stp";
		case ARM64_InstLdp:    return "ldp";
		case ARM64_InstMovz:   return "movz";
		case ARM64_InstMovk:   return "movk";
		case ARM64_InstFMov:   return "fmov";
		case ARM64_InstMadd:   return "madd";
		case ARM64_InstMsub:   return "msub";
		case ARM64_InstFMadd:  return "fmadd";
		case ARM64_InstFMsub:  return "fmsub";
		case ARM64_InstCset:   return "cset";
		case ARM64_InstCsetEQ: return "cset";
		case ARM64_InstCsetNE: return "cset";
		case ARM64_InstCsetGT: return "cset";
		case ARM64_InstCsetGE: return "cset";
		case ARM64_InstCsetLT: return "cset";
		case ARM64_InstCsetLE: return "cset";
		case ARM64_InstMrs:    return "mrs";
		case ARM64_InstMsr:    return "msr";
		case ARM64_InstAddShifted: return "add";
		case ARM64_InstSubShifted: return "sub";
		case ARM64_InstLdrShifted: return "ldr";
		case ARM64_InstStrShifted: return "str";

		default:
			return "unknown";
		}
	}

	std::string ARM64_GetRegisterString(Uint32 reg, MachineType type)
	{
		if (ARM64_IsGPR(reg))
		{
			Bool is_64bit = type == MachineType::Int64 || type == MachineType::Ptr || type == MachineType::Other;
			switch (reg)
			{
			case ARM64_X0:  return is_64bit ? "x0" : "w0";
			case ARM64_X1:  return is_64bit ? "x1" : "w1";
			case ARM64_X2:  return is_64bit ? "x2" : "w2";
			case ARM64_X3:  return is_64bit ? "x3" : "w3";
			case ARM64_X4:  return is_64bit ? "x4" : "w4";
			case ARM64_X5:  return is_64bit ? "x5" : "w5";
			case ARM64_X6:  return is_64bit ? "x6" : "w6";
			case ARM64_X7:  return is_64bit ? "x7" : "w7";
			case ARM64_X8:  return is_64bit ? "x8" : "w8";
			case ARM64_X9:  return is_64bit ? "x9" : "w9";
			case ARM64_X10: return is_64bit ? "x10" : "w10";
			case ARM64_X11: return is_64bit ? "x11" : "w11";
			case ARM64_X12: return is_64bit ? "x12" : "w12";
			case ARM64_X13: return is_64bit ? "x13" : "w13";
			case ARM64_X14: return is_64bit ? "x14" : "w14";
			case ARM64_X15: return is_64bit ? "x15" : "w15";
			case ARM64_X16: return is_64bit ? "x16" : "w16";
			case ARM64_X17: return is_64bit ? "x17" : "w17";
			case ARM64_X18: return is_64bit ? "x18" : "w18";
			case ARM64_X19: return is_64bit ? "x19" : "w19";
			case ARM64_X20: return is_64bit ? "x20" : "w20";
			case ARM64_X21: return is_64bit ? "x21" : "w21";
			case ARM64_X22: return is_64bit ? "x22" : "w22";
			case ARM64_X23: return is_64bit ? "x23" : "w23";
			case ARM64_X24: return is_64bit ? "x24" : "w24";
			case ARM64_X25: return is_64bit ? "x25" : "w25";
			case ARM64_X26: return is_64bit ? "x26" : "w26";
			case ARM64_X27: return is_64bit ? "x27" : "w27";
			case ARM64_X28: return is_64bit ? "x28" : "w28";
			case ARM64_X29: return is_64bit ? "x29" : "w29"; // FP
			case ARM64_X30: return is_64bit ? "x30" : "w30"; // LR
			case ARM64_SP:  return "sp";
			default: OLA_ASSERT(false); return "x?";
			}
		}
		else if (ARM64_IsFPR(reg))
		{
			Uint32 reg_idx = reg - ARM64_FPRBegin;
			Bool is_double = type == MachineType::Float64;
			return (is_double ? "d" : "s") + std::to_string(reg_idx);
		}
		OLA_ASSERT(false);
		return "?";
	}

	Bool ARM64_IsCallerSaved(Uint32 reg)
	{
		if (ARM64_IsGPR(reg))
		{
			return reg >= ARM64_X0 && reg <= ARM64_X18;
		}
		else if (ARM64_IsFPR(reg))
		{
			Uint32 reg_idx = reg - ARM64_FPRBegin;
			return reg_idx <= 7 || reg_idx >= 16;
		}
		return false;
	}
}
