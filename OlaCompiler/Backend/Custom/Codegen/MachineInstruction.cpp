#include "MachineInstruction.h"

namespace ola
{
	Char const* MachineOpcodeNames[] = 
	{
		"InstUnknown",
		// control-flow
		"InstCall",
		"InstJump",
		"InstJE",
		"InstJNE",

		// Memory
		"InstMove",
		"InstLoad",
		"InstStore",
		"InstLoadGlobalAddress",
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

	Char const* MachineInstruction::GetOpcodeName() const
	{
		return opcode < ISASpecificBegin ? MachineOpcodeNames[opcode] : "";
	}
}

