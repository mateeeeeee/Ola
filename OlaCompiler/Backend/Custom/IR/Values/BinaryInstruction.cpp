#include "BinaryInstruction.h"
#include "Use.h"

namespace ola
{

	BinaryInstruction::BinaryInstruction(ValueKind kind, IRType* type, Value* op1, Value* op2, Instruction* position) : Instruction(kind, type, 2, position)
	{
		Op<0>() = op1;
		Op<1>() = op2;
	}

	BinaryInstruction::BinaryInstruction(ValueKind kind, IRType* type, Value* op1, Value* op2, BasicBlock* bb) : Instruction(kind, type, 2, bb)
	{
		Op<0>() = op1;
		Op<1>() = op2;
	}

}
