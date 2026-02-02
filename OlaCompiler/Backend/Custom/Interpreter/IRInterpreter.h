#pragma once
#include <stack>
#include <vector>
#include "InterpreterValue.h"
#include "InterpreterMemory.h"
#include "InterpreterFrame.h"
#include "Intrinsics.h"

namespace ola
{
	class IRModule;
	class IRContext;
	class Function;
	class BasicBlock;
	class Instruction;
	class Value;
	class GlobalVariable;
	class ConstantInt;
	class ConstantFloat;
	class ConstantString;
	class ConstantArray;
	class ConstantStruct;

	class IRInterpreter
	{
	public:
		explicit IRInterpreter(IRModule& module);
		~IRInterpreter() = default;

		Int Execute();

	private:
		IRModule& module;
		InterpreterMemory memory;
		std::stack<InterpreterFrame> call_stack;
		Intrinsics intrinsics;

	private:
		void ExecuteFunction(Function* func, std::vector<InterpreterValue> const& args);
		void ExecuteBasicBlock(BasicBlock* bb);
		void ExecuteInstruction(Instruction* inst);

		InterpreterValue ExecuteTerminator(Instruction* inst);
		InterpreterValue ExecuteBinaryOp(Instruction* inst);
		InterpreterValue ExecuteUnaryOp(Instruction* inst);
		InterpreterValue ExecuteCompareOp(Instruction* inst);
		InterpreterValue ExecuteCastOp(Instruction* inst);
		InterpreterValue ExecuteMemoryOp(Instruction* inst);
		InterpreterValue ExecuteAlloca(Instruction* inst);
		InterpreterValue ExecuteGetElementPtr(Instruction* inst);
		InterpreterValue ExecutePtrAdd(Instruction* inst);
		InterpreterValue ExecuteSelect(Instruction* inst);
		InterpreterValue ExecuteCall(Instruction* inst);
		InterpreterValue ExecutePhi(Instruction* inst);
		InterpreterValue ExecuteSwitch(Instruction* inst);

		InterpreterValue GetOperandValue(Value* v);
		Function* FindMainFunction();
		void InitializeGlobals();
		void InitializeGlobalValue(Uint8* addr, Value* init_val);

		Uint32 GetFieldOffset(IRType* struct_type, Uint32 field_index);
	};
}
