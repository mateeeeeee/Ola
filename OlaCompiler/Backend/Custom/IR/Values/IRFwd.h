#pragma once

namespace ola
{
	class IRContext;
	class IRModule;

	class Value;
	class Use;
	class User;
	class Instruction;
	class StoreInst;
	class LoadInst;
	class AllocaInst;
	class BranchInst;
	class ReturnInst;
	class BasicBlock;
	class Function;
	class GlobalVariable;
	class Argument;
	class UnaryInstruction;
	class UnaryOperator;
	class BinaryInstruction;
	class BinaryOperator;
	class CmpInst;
	class ConstantInt;
	class ConstantString;
	class ConstantFloat;
	class ConstantArray;
	class ConstantStruct;
	class SwitchInst;

	enum UnaryOpcode : uint8;
	enum BinaryOpcode : uint8;
	enum CmpPredicate : uint16;
}