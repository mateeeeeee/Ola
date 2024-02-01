#include "UnaryInstruction.h"
#include "Use.h"

namespace ola
{

	UnaryInstruction::UnaryInstruction(ValueKind kind, IRType* type, Value* op, Instruction* position) : Instruction(kind, type, 1, position)
	{
		Op<0>() = op;
	}

	UnaryInstruction::UnaryInstruction(ValueKind kind, IRType* type, Value* op, BasicBlock* bb /*= nullptr*/) : Instruction(kind, type, 1, bb)
	{
		Op<0>() = op;
	}

}

