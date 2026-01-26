#pragma once
#include <string>
#include "Backend/Custom/Codegen/MachineOperand.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"

namespace ola
{
	enum ARMRegister : Uint32
	{
		ARM_GPRBegin,
		ARM_X0 = ARM_GPRBegin, ARM_X1, ARM_X2, ARM_X3, ARM_X4, ARM_X5, ARM_X6, ARM_X7,
		ARM_X8, ARM_X9, ARM_X10, ARM_X11, ARM_X12, ARM_X13, ARM_X14, ARM_X15,
		ARM_X16, ARM_X17, ARM_X18, ARM_X19, ARM_X20, ARM_X21, ARM_X22, ARM_X23,
		ARM_X24, ARM_X25, ARM_X26, ARM_X27, ARM_X28, ARM_X29, ARM_X30, ARM_SP,
		ARM_GPREnd = ARM_SP,

		ARM_FPRBegin,
		ARM_V0 = ARM_FPRBegin, ARM_V1, ARM_V2, ARM_V3, ARM_V4, ARM_V5, ARM_V6, ARM_V7,
		ARM_V8, ARM_V9, ARM_V10, ARM_V11, ARM_V12, ARM_V13, ARM_V14, ARM_V15,
		ARM_V16, ARM_V17, ARM_V18, ARM_V19, ARM_V20, ARM_V21, ARM_V22, ARM_V23,
		ARM_V24, ARM_V25, ARM_V26, ARM_V27, ARM_V28, ARM_V29, ARM_V30, ARM_V31,
		ARM_FPREnd = ARM_V31,

		ARM_ISARegBegin = ARM_GPRBegin,
		ARM_ISARegEnd = ARM_FPREnd
	};

	enum ARMInstruction : Uint32
	{
		ARM_InstAdrp = ISASpecificBegin,
		ARM_InstStp,
		ARM_InstLdp,
		ARM_InstMovz,
		ARM_InstMovk,
		ARM_InstFMov,
		ARM_InstMadd,
		ARM_InstMsub,
		ARM_InstFMadd,
		ARM_InstFMsub,
		ARM_InstCset,
		ARM_InstCsetEQ,
		ARM_InstCsetNE,
		ARM_InstCsetGT,
		ARM_InstCsetGE,
		ARM_InstCsetLT,
		ARM_InstCsetLE,
		ARM_InstMrs,
		ARM_InstMsr,
		ARM_InstAddShifted,
		ARM_InstSubShifted,
		ARM_InstLdrShifted,
		ARM_InstStrShifted
	};

	inline constexpr Bool ARM_IsISAReg(Uint32 reg)
	{
		return reg >= ARM_ISARegBegin && reg <= ARM_ISARegEnd;
	}

	inline constexpr Bool ARM_IsGPR(Uint32 reg)
	{
		return reg >= ARM_GPRBegin && reg <= ARM_GPREnd;
	}

	inline constexpr Bool ARM_IsFPR(Uint32 reg)
	{
		return reg >= ARM_FPRBegin && reg <= ARM_FPREnd;
	}

	Char const* ARM_GetOpcodeString(Uint32 opcode);
	std::string ARM_GetRegisterString(Uint32 reg, MachineType type);
	Bool ARM_IsCallerSaved(Uint32 reg);
}
