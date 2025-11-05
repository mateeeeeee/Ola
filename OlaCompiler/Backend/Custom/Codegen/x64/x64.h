#pragma once
#include "Backend/Custom/Codegen/MachineInstruction.h"

namespace ola
{
	enum x64Register : Uint32
	{
		x64_GPRBegin,
		x64_RAX = x64_GPRBegin, x64_RSP, x64_RBP, x64_RCX, x64_RDX, x64_RBX, x64_RSI, x64_RDI,
		x64_R8, x64_R9, x64_R10, x64_R11, x64_R12, x64_R13, x64_R14, x64_R15,
		x64_GPREnd,
		x64_FPRBegin,
		x64_XMM0 = x64_FPRBegin, x64_XMM1, x64_XMM2, x64_XMM3, x64_XMM4, x64_XMM5, x64_XMM6, x64_XMM7,
		x64_XMM8, x64_XMM9, x64_XMM10, x64_XMM11, x64_XMM12, x64_XMM13, x64_XMM14, x64_XMM15,
		x64_FPREnd,
		x64_FLAGS,
		x64_FFLAGS,
	};

	inline constexpr Bool x64_IsGPRReg(Uint32 r)
	{
		return r >= x64_GPRBegin && r <= x64_GPREnd;
	}
	inline constexpr Bool x64_IsFPRReg(Uint32 r)
	{
		return r >= x64_FPRBegin && r <= x64_FPREnd;
	}
	inline constexpr Bool x64_IsCallerSaved(Uint32 r)
	{
		switch (r)
		{
		case x64_RAX:
		case x64_RCX:
		case x64_RDX:
		case x64_R8:
		case x64_R9:
		case x64_R10:
		case x64_R11:
		case x64_XMM0:
		case x64_XMM1:
		case x64_XMM2:
		case x64_XMM3:
		case x64_XMM4:
		case x64_XMM5:
			return true;
		default:
			return false;
		}
	}
	inline constexpr Bool x64_IsCalleeSaved(Uint32 r)
	{
		switch (r)
		{
		case x64_RBX:
		case x64_RBP:
		case x64_RSP:
		case x64_RDI:
		case x64_RSI:
		case x64_R12:
		case x64_R13:
		case x64_R14:
		case x64_R15:
		case x64_XMM6:
		case x64_XMM7:
		case x64_XMM8:
		case x64_XMM9:
		case x64_XMM10:
		case x64_XMM11:
		case x64_XMM12:
		case x64_XMM13:
		case x64_XMM14:
		case x64_XMM15:
			return true;
		default:
			return false;
		}
	}

	enum x64Inst : Uint32
	{
		x64InstBegin = ISASpecificBegin,
		x64_InstSetE,
		x64_InstSetNE,
		x64_InstSetGT,
		x64_InstSetGE,
		x64_InstSetLT,
		x64_InstSetLE,

		x64_InstSetA,
		x64_InstSetAE,
		x64_InstSetB,
		x64_InstSetBE,

		x64_InstCqo,
		x64_InstMoveFP,
		x64_InstStoreFP,
		x64_InstLoadFP,
		x64_InstXorFP
	};

	inline Char const* x64_GetOpcodeString(Uint32 opcode)
	{
		switch (opcode)
		{
		case InstPush:    return "push";
		case InstPop:     return "pop";
		case InstJump:    return "jmp";
		case InstJE:      return "je";
		case InstJNE:     return "jne";
		case InstCall:    return "call";
		case InstRet:    return "ret";
		case InstStore:
		case InstLoad:
		case InstMove:    return "mov";
		case InstCMoveEQ: return "cmove";
		case InstCMoveNE: return "cmovne";
		case InstLoadGlobalAddress: return "lea";
		case InstNeg:	  return "neg";
		case InstAdd:     return "add";
		case InstSub:     return "sub";
		case InstICmp:    return "cmp";
		case InstFCmp:    return "comisd";
		case x64_InstSetE:    return "sete";
		case x64_InstSetNE:	  return "setne";
		case x64_InstSetGT:	  return "setg";
		case x64_InstSetGE:	  return "setge";
		case x64_InstSetLT:	  return "setl";
		case x64_InstSetLE:	  return "setle";
		case x64_InstSetA:	  return "seta";
		case x64_InstSetAE:   return "setae";
		case x64_InstSetB:    return "setb";
		case x64_InstSetBE:   return "setbe";
		case InstShl:	  return "shl";
		case InstAShr:    return "sar";
		case InstLShr:    return "shr";
		case InstTest:    return "test";
		case InstAnd:     return "and";
		case InstOr:      return "or";
		case InstXor:     return "xor";
		case InstNot:	  return "not";
		case InstSMul:    return "imul";
		case InstSDiv:    return "idiv";
		case x64_InstCqo:     return "cqo";
		case x64_InstStoreFP:
		case x64_InstLoadFP:
		case x64_InstMoveFP:  return "movsd";
		case InstF2S:     return "cvttsd2si";
		case InstS2F:     return "cvtsi2sd";
		case InstFAdd:    return "addsd";
		case InstFSub:    return "subsd";
		case InstFMul:    return "mulsd";
		case InstFDiv:    return "divsd";
		case x64_InstXorFP:   return "xorpd";
		case InstZExt:    return "movzx";
		}
		return "";
	}

	inline Char const* x64_GetRegisterString(Uint32 r, MachineType type)
	{
		using enum MachineType;
		switch (type)
		{
		case Int8:
			switch (r)
			{
			case x64_RAX: return "al";
			case x64_RCX: return "cl";
			case x64_RDX: return "dl";
			case x64_RBX: return "bl";
			case x64_RSI: return "sil";
			case x64_RDI: return "dil";
			case x64_R8:  return "r8b";
			case x64_R9:  return "r9b";
			case x64_R10: return "r10b";
			case x64_R11: return "r11b";
			case x64_R12: return "r12b";
			case x64_R13: return "r13b";
			case x64_R14: return "r14b";
			case x64_R15: return "r15b";
			default: OLA_ASSERT_MSG(false, "Invalid register/type combination!");  return "";
			}
		case Int64:
		case Ptr:
			switch (r)
			{
			case x64_RAX: return "rax";
			case x64_RCX: return "rcx";
			case x64_RDX: return "rdx";
			case x64_RBX: return "rbx";
			case x64_RSP: return "rsp";
			case x64_RBP: return "rbp";
			case x64_RSI: return "rsi";
			case x64_RDI: return "rdi";
			case x64_R8:  return "r8";
			case x64_R9:  return "r9";
			case x64_R10: return "r10";
			case x64_R11: return "r11";
			case x64_R12: return "r12";
			case x64_R13: return "r13";
			case x64_R14: return "r14";
			case x64_R15: return "r15";
			default: OLA_ASSERT_MSG(false, "Invalid register/type combination!");  return "";
			}
		case Float64:
			switch (r)
			{
			case x64_XMM0: return "xmm0";
			case x64_XMM1: return "xmm1";
			case x64_XMM2: return "xmm2";
			case x64_XMM3: return "xmm3";
			case x64_XMM4: return "xmm4";
			case x64_XMM5: return "xmm5";
			case x64_XMM6: return "xmm6";
			case x64_XMM7: return "xmm7";
			case x64_XMM8: return "xmm8";
			case x64_XMM9: return "xmm9";
			case x64_XMM10: return "xmm10";
			case x64_XMM11: return "xmm11";
			case x64_XMM12: return "xmm12";
			case x64_XMM13: return "xmm13";
			case x64_XMM14: return "xmm14";
			case x64_XMM15: return "xmm15";
			default: OLA_ASSERT_MSG(false, "Invalid register/type combination!");  return "";
			}
		default:
			OLA_ASSERT_MSG(false, "Invalid register/type combination!");  return "";
		}
	}
}