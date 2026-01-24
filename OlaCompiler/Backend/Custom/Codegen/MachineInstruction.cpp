#include "MachineInstruction.h"

namespace ola
{
	Char const* MachineOpcodeNames[] =
	{
		"InstUnknown",
		// control-flow
		"InstCall",
		"InstRet",
		"InstJump",
		"InstJE",
		"InstJNE",

		// Memory
		"InstMove",
		"InstLoad",
		"InstStore",
		"InstLoadGlobalAddress",
		"InstMemCpy",
		"InstCMoveEQ",
		"InstCMoveNE",

		// Stack
		"InstPush",
		"InstPop",

		// Arithmetic
		"InstAdd",
		"InstSub",
		"InstUMul",
		"InstSMul",
		"InstUDiv",
		"InstURem",

		// Signed Div/Rem
		"InstSDiv",
		"InstSRem",

		// Bitwise
		"InstAnd",
		"InstOr",
		"InstXor",
		"InstShl",
		"InstLShr",
		"InstAShr",

		// Unary
		"InstNeg",
		"InstNot",

		// FP
		"InstFAdd",
		"InstFSub",
		"InstFMul",
		"InstFDiv",
		"InstFNeg",

		// Comparison
		"InstICmp",
		"InstFCmp",
		"InstTest",

		// Conversion
		"InstZExt",
		"InstF2S",
		"InstS2F",
	};
	static_assert(std::size(MachineOpcodeNames) == InstOpcodeCount);

	Char const* MachineInstruction::GetOpcodeName() const
	{
		return opcode < ISASpecificBegin ? MachineOpcodeNames[opcode] : "";
	}
}

