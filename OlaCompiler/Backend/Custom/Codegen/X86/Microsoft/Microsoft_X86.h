#pragma once
#include "Backend/Custom/Codegen/X86/X86.h"

namespace ola
{
	// Microsoft X86 ABI calling convention register classification
	inline constexpr Bool X86_IsCallerSaved(Uint32 r)
	{
		switch (r)
		{
		case X86_RAX:
		case X86_RCX:
		case X86_RDX:
		case X86_R8:
		case X86_R9:
		case X86_R10:
		case X86_R11:
		case X86_XMM0:
		case X86_XMM1:
		case X86_XMM2:
		case X86_XMM3:
		case X86_XMM4:
		case X86_XMM5:
			return true;
		default:
			return false;
		}
	}

	inline constexpr Bool X86_IsCalleeSaved(Uint32 r)
	{
		switch (r)
		{
		case X86_RBX:
		case X86_RBP:
		case X86_RSP:
		case X86_RDI:  
		case X86_RSI:  
		case X86_R12:
		case X86_R13:
		case X86_R14:
		case X86_R15:
		case X86_XMM6:
		case X86_XMM7:
		case X86_XMM8:
		case X86_XMM9:
		case X86_XMM10:
		case X86_XMM11:
		case X86_XMM12:
		case X86_XMM13:
		case X86_XMM14:
		case X86_XMM15:
			return true;
		default:
			return false;
		}
	}
}
