#pragma once
#include "Backend/Custom/Codegen/MachineInstruction.h"

namespace ola::x64
{
	enum Register : Uint32
	{
		GPRBegin,
		RAX = GPRBegin, RSP, RBP, RCX, RDX, RBX, RSI, RDI,
		R8, R9, R10, R11, R12, R13, R14, R15,
		GPREnd,
		FPRBegin,
		XMM0 = FPRBegin, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7,
		XMM8, XMM9, XMM10, XMM11, XMM12, XMM13, XMM14, XMM15,
		FPREnd,
		FLAGS,
		FFLAGS,
	};

	inline constexpr Bool IsGPRReg(Uint32 r)
	{
		return r >= GPRBegin && r <= GPREnd;
	}
	inline constexpr Bool IsFPRReg(Uint32 r)
	{
		return r >= FPRBegin && r <= FPREnd;
	}
	inline constexpr Bool IsCallerSaved(Uint32 r)
	{
		switch (r)
		{
		case RAX:
		case RCX:
		case RDX:
		case R8:
		case R9:
		case R10:
		case R11:
		case XMM0:
		case XMM1:
		case XMM2:
		case XMM3:
		case XMM4:
		case XMM5:
			return true;
		default:
			return false;
		}
	}
	inline constexpr Bool IsCalleeSaved(Uint32 r)
	{
		switch (r)
		{
		case RBX:
		case RBP:
		case RSP:
		case RDI:
		case RSI:
		case R12:
		case R13:
		case R14:
		case R15:
		case XMM6:
		case XMM7:
		case XMM8:
		case XMM9:
		case XMM10:
		case XMM11:
		case XMM12:
		case XMM13:
		case XMM14:
		case XMM15:
			return true;
		default:
			return false;
		}
	}

	enum x64Inst : Uint32
	{
		x64InstBegin = ISASpecificBegin,
		InstSetE,
		InstSetNE,
		InstSetGT,
		InstSetGE,
		InstSetLT,
		InstSetLE,

		InstSetA,
		InstSetAE,
		InstSetB,
		InstSetBE,

		InstCqo,
		InstMoveFP,
		InstStoreFP,
		InstLoadFP,
		InstXorFP
	};

	inline Char const* GetOpcodeString(Uint32 opcode)
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
		case InstSetE:    return "sete";
		case InstSetNE:	  return "setne";
		case InstSetGT:	  return "setg";
		case InstSetGE:	  return "setge";
		case InstSetLT:	  return "setl";
		case InstSetLE:	  return "setle";
		case InstSetA:	  return "seta";
		case InstSetAE:   return "setae";
		case InstSetB:    return "setb";
		case InstSetBE:   return "setbe";
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
		case InstCqo:     return "cqo";
		case InstStoreFP:
		case InstLoadFP:
		case InstMoveFP:  return "movsd";
		case InstF2S:     return "cvttsd2si";
		case InstS2F:     return "cvtsi2sd";
		case InstFAdd:    return "addsd";
		case InstFSub:    return "subsd";
		case InstFMul:    return "mulsd";
		case InstFDiv:    return "divsd";
		case InstXorFP:   return "xorpd";
		case InstZExt:    return "movzx";
		}
		return "";
	}

	inline Char const* GetRegisterString(Uint32 r, MachineType type)
	{
		using enum MachineType;
		switch (type)
		{
		case Int8:
			switch (r)
			{
			case RAX: return "al";
			case RCX: return "cl";
			case RDX: return "dl";
			case RBX: return "bl";
			case RSI: return "sil";
			case RDI: return "dil";
			case R8:  return "r8b";
			case R9:  return "r9b";
			case R10: return "r10b";
			case R11: return "r11b";
			case R12: return "r12b";
			case R13: return "r13b";
			case R14: return "r14b";
			case R15: return "r15b";
			default: OLA_ASSERT_MSG(false, "Invalid register/type combination!");  return "";
			}
		case Int64:
		case Ptr:
			switch (r)
			{
			case RAX: return "rax";
			case RCX: return "rcx";
			case RDX: return "rdx";
			case RBX: return "rbx";
			case RSP: return "rsp";
			case RBP: return "rbp";
			case RSI: return "rsi";
			case RDI: return "rdi";
			case R8:  return "r8";
			case R9:  return "r9";
			case R10: return "r10";
			case R11: return "r11";
			case R12: return "r12";
			case R13: return "r13";
			case R14: return "r14";
			case R15: return "r15";
			default: OLA_ASSERT_MSG(false, "Invalid register/type combination!");  return "";
			}
		case Float64:
			switch (r)
			{
			case XMM0: return "xmm0";
			case XMM1: return "xmm1";
			case XMM2: return "xmm2";
			case XMM3: return "xmm3";
			case XMM4: return "xmm4";
			case XMM5: return "xmm5";
			case XMM6: return "xmm6";
			case XMM7: return "xmm7";
			case XMM8: return "xmm8";
			case XMM9: return "xmm9";
			case XMM10: return "xmm10";
			case XMM11: return "xmm11";
			case XMM12: return "xmm12";
			case XMM13: return "xmm13";
			case XMM14: return "xmm14";
			case XMM15: return "xmm15";
			default: OLA_ASSERT_MSG(false, "Invalid register/type combination!");  return "";
			}
		default:
			OLA_ASSERT_MSG(false, "Invalid register/type combination!");  return "";
		}
	}
}