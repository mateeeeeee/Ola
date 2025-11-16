#pragma once
#include <string>
#include "Backend/Custom/Codegen/MachineOperand.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"

namespace ola
{
	enum ARM64Register : Uint32
	{
		ARM64_GPRBegin,
		ARM64_X0 = ARM64_GPRBegin, ARM64_X1, ARM64_X2, ARM64_X3, ARM64_X4, ARM64_X5, ARM64_X6, ARM64_X7,
		ARM64_X8, ARM64_X9, ARM64_X10, ARM64_X11, ARM64_X12, ARM64_X13, ARM64_X14, ARM64_X15,
		ARM64_X16, ARM64_X17, ARM64_X18, ARM64_X19, ARM64_X20, ARM64_X21, ARM64_X22, ARM64_X23,
		ARM64_X24, ARM64_X25, ARM64_X26, ARM64_X27, ARM64_X28, ARM64_X29, ARM64_X30, ARM64_SP,
		ARM64_GPREnd = ARM64_SP,

		ARM64_FPRBegin,
		ARM64_V0 = ARM64_FPRBegin, ARM64_V1, ARM64_V2, ARM64_V3, ARM64_V4, ARM64_V5, ARM64_V6, ARM64_V7,
		ARM64_V8, ARM64_V9, ARM64_V10, ARM64_V11, ARM64_V12, ARM64_V13, ARM64_V14, ARM64_V15,
		ARM64_V16, ARM64_V17, ARM64_V18, ARM64_V19, ARM64_V20, ARM64_V21, ARM64_V22, ARM64_V23,
		ARM64_V24, ARM64_V25, ARM64_V26, ARM64_V27, ARM64_V28, ARM64_V29, ARM64_V30, ARM64_V31,
		ARM64_FPREnd = ARM64_V31,

		ARM64_ISARegBegin = ARM64_GPRBegin,
		ARM64_ISARegEnd = ARM64_FPREnd
	};

	enum ARM64Instruction : Uint32
	{
		ARM64_InstAdrp = ISASpecificBegin,
		ARM64_InstStp,
		ARM64_InstLdp,
		ARM64_InstMovz,
		ARM64_InstMovk,
		ARM64_InstFMov,
		ARM64_InstCset,
		ARM64_InstCsetEQ,
		ARM64_InstCsetNE,
		ARM64_InstCsetGT,
		ARM64_InstCsetGE,
		ARM64_InstCsetLT,
		ARM64_InstCsetLE,
		ARM64_InstMrs,
		ARM64_InstMsr,
	};

	inline constexpr Bool ARM64_IsISAReg(Uint32 reg)
	{
		return reg >= ARM64_ISARegBegin && reg <= ARM64_ISARegEnd;
	}

	inline constexpr Bool ARM64_IsGPR(Uint32 reg)
	{
		return reg >= ARM64_GPRBegin && reg <= ARM64_GPREnd;
	}

	inline constexpr Bool ARM64_IsFPR(Uint32 reg)
	{
		return reg >= ARM64_FPRBegin && reg <= ARM64_FPREnd;
	}

	Char const* ARM64_GetOpcodeString(Uint32 opcode);
	std::string ARM64_GetRegisterString(Uint32 reg, MachineType type);
	Bool ARM64_IsCallerSaved(Uint32 reg);
}
