#pragma once
#include "Backend/Custom/Codegen/MachineInstruction.h"

namespace ola
{
	enum X86Register : Uint32
	{
		X86_GPRBegin,
		X86_RAX = X86_GPRBegin, X86_RSP, X86_RBP, X86_RCX, X86_RDX, X86_RBX, X86_RSI, X86_RDI,
		X86_R8, X86_R9, X86_R10, X86_R11, X86_R12, X86_R13, X86_R14, X86_R15,
		X86_GPREnd,
		X86_FPRBegin,
		X86_XMM0 = X86_FPRBegin, X86_XMM1, X86_XMM2, X86_XMM3, X86_XMM4, X86_XMM5, X86_XMM6, X86_XMM7,
		X86_XMM8, X86_XMM9, X86_XMM10, X86_XMM11, X86_XMM12, X86_XMM13, X86_XMM14, X86_XMM15,
		X86_FPREnd,
		X86_FLAGS,
		X86_FFLAGS,
	};

	inline constexpr Bool X86_IsGPRReg(Uint32 r)
	{
		return r >= X86_GPRBegin && r <= X86_GPREnd;
	}
	inline constexpr Bool X86_IsFPRReg(Uint32 r)
	{
		return r >= X86_FPRBegin && r <= X86_FPREnd;
	}

	// Caller-saved and callee-saved register classification is ABI-specific.
	// Include "Microsoft/X86Microsoft.h" for Microsoft X86 ABI
	// Include "SysV/X86SysV.h" for SysV X86 ABI

	enum X86Inst : Uint32
	{
		X86InstBegin = ISASpecificBegin,
		X86_InstSetE,
		X86_InstSetNE,
		X86_InstSetGT,
		X86_InstSetGE,
		X86_InstSetLT,
		X86_InstSetLE,

		X86_InstSetA,
		X86_InstSetAE,
		X86_InstSetB,
		X86_InstSetBE,

		X86_InstCqo,
		X86_InstMoveFP,
		X86_InstStoreFP,
		X86_InstLoadFP,
		X86_InstXorFP,
		X86_InstLea
	};

	inline Char const* X86_GetOpcodeString(Uint32 opcode)
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
		case X86_InstSetE:    return "sete";
		case X86_InstSetNE:	  return "setne";
		case X86_InstSetGT:	  return "setg";
		case X86_InstSetGE:	  return "setge";
		case X86_InstSetLT:	  return "setl";
		case X86_InstSetLE:	  return "setle";
		case X86_InstSetA:	  return "seta";
		case X86_InstSetAE:   return "setae";
		case X86_InstSetB:    return "setb";
		case X86_InstSetBE:   return "setbe";
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
		case X86_InstCqo:     return "cqo";
		case X86_InstStoreFP:
		case X86_InstLoadFP:
		case X86_InstMoveFP:  return "movsd";
		case InstF2S:     return "cvttsd2si";
		case InstS2F:     return "cvtsi2sd";
		case InstFAdd:    return "addsd";
		case InstFSub:    return "subsd";
		case InstFMul:    return "mulsd";
		case InstFDiv:    return "divsd";
		case X86_InstXorFP:   return "xorpd";
		case X86_InstLea:     return "lea";
		case InstZExt:    return "movzx";
		}
		return "";
	}

	inline Char const* X86_GetRegisterString(Uint32 r, MachineType type)
	{
		using enum MachineType;
		switch (type)
		{
		case Int8:
			switch (r)
			{
			case X86_RAX: return "al";
			case X86_RCX: return "cl";
			case X86_RDX: return "dl";
			case X86_RBX: return "bl";
			case X86_RSI: return "sil";
			case X86_RDI: return "dil";
			case X86_R8:  return "r8b";
			case X86_R9:  return "r9b";
			case X86_R10: return "r10b";
			case X86_R11: return "r11b";
			case X86_R12: return "r12b";
			case X86_R13: return "r13b";
			case X86_R14: return "r14b";
			case X86_R15: return "r15b";
			default: OLA_ASSERT_MSG(false, "Invalid register/type combination!");  return "";
			}
		case Int64:
		case Ptr:
			switch (r)
			{
			case X86_RAX: return "rax";
			case X86_RCX: return "rcx";
			case X86_RDX: return "rdx";
			case X86_RBX: return "rbx";
			case X86_RSP: return "rsp";
			case X86_RBP: return "rbp";
			case X86_RSI: return "rsi";
			case X86_RDI: return "rdi";
			case X86_R8:  return "r8";
			case X86_R9:  return "r9";
			case X86_R10: return "r10";
			case X86_R11: return "r11";
			case X86_R12: return "r12";
			case X86_R13: return "r13";
			case X86_R14: return "r14";
			case X86_R15: return "r15";
			default: OLA_ASSERT_MSG(false, "Invalid register/type combination!");  return "";
			}
		case Float64:
			switch (r)
			{
			case X86_XMM0: return "xmm0";
			case X86_XMM1: return "xmm1";
			case X86_XMM2: return "xmm2";
			case X86_XMM3: return "xmm3";
			case X86_XMM4: return "xmm4";
			case X86_XMM5: return "xmm5";
			case X86_XMM6: return "xmm6";
			case X86_XMM7: return "xmm7";
			case X86_XMM8: return "xmm8";
			case X86_XMM9: return "xmm9";
			case X86_XMM10: return "xmm10";
			case X86_XMM11: return "xmm11";
			case X86_XMM12: return "xmm12";
			case X86_XMM13: return "xmm13";
			case X86_XMM14: return "xmm14";
			case X86_XMM15: return "xmm15";
			default: OLA_ASSERT_MSG(false, "Invalid register/type combination!");  return "";
			}
		default:
			OLA_ASSERT_MSG(false, "Invalid register/type combination!");  return "";
		}
	}
}