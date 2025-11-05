#pragma once
#include "Backend/Custom/Codegen/x64/x64.h"

namespace ola
{
	// Microsoft x64 ABI calling convention register classification
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
}
