#pragma once
#include "Backend/Custom/Codegen/MachineInstruction.h"

namespace ola::x64
{
	enum Register : uint32
	{
		GPRBegin,
		RAX = GPRBegin, RCX, RDX, RBX, RSP, RBP, RSI, RDI,
		R8, R9, R10, R11, R12, R13, R14, R15,
		GPREnd,
		FPRBegin,
		XMM0 = FPRBegin, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7,
		XMM8, XMM9, XMM10, XMM11, XMM12, XMM13, XMM14, XMM15,
		FPREnd,
		FLAGS, 
		FFLAGS,
	};

	inline constexpr bool IsGPRReg(uint32 r)
	{
		return r >= GPRBegin && r <= GPREnd;
	}
	inline constexpr bool IsFPRReg(uint32 r)
	{
		return r >= FPRBegin && r <= FPREnd;
	}
	inline constexpr bool IsCallerSaved(uint32 r)
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
	inline constexpr bool IsCalleeSaved(uint32 r) 
	{
		switch (r)
		{
		case RBX:
		case RBP:
		case RDI:
		case RSI:
		case R12:
		case R13:
		case R14:
		case R15:
			return true;
		default:
			return false;
		}
	}

	enum class X64Condition : uint32
	{
		Equal,
		NotEqual,
		AboveOrEqual,
		Below,
		Negative,
		PositiveOrZero,
		Above,
		BelowOrEqual,
		GreaterOrEqual,
		LessThan,
		GreaterThan,
		LessOrEqual,
		Always
	};

	enum x64Inst : uint32
	{
		x64InstBegin = ISASpecificBegin,
		InstMov = x64InstBegin,
	};

	inline char const* GetRegisterString(uint32 r)
	{
		switch (r)
		{
		case RAX:
			return "rax";
		case RCX:
			return "rcx";
		case RDX:
			return "rdx";
		case RBX:
			return "rbx";
		case RSP:
			return "rsp";
		case RBP:
			return "rbp";
		case RSI:
			return "rsi";
		case RDI:
			return "rdi";
		case R8:
			return "r8";
		case R9:
			return "r9";
		case R10:
			return "r10";
		case R11:
			return "r11";
		case R12:
			return "r12";
		case R13:
			return "r13";
		case R14:
			return "r14";
		case R15:
			return "r15";
		case XMM0:
			return "xmm0";
		case XMM1:
			return "xmm1";
		case XMM2:
			return "xmm2";
		case XMM3:
			return "xmm3";
		case XMM4:
			return "xmm4";
		case XMM5:
			return "xmm5";
		case XMM6:
			return "xmm6";
		case XMM7:
			return "xmm7";
		case XMM8:
			return "xmm8";
		case XMM9:
			return "xmm9";
		case XMM10:
			return "xmm10";
		case XMM11:
			return "xmm11";
		case XMM12:
			return "xmm12";
		case XMM13:
			return "xmm13";
		case XMM14:
			return "xmm14";
		case XMM15:
			return "xmm15";
		default:
			OLA_ASSERT(false);
		}
		return "";
	}
}