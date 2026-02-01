#pragma once
#include <unordered_map>
#include <vector>
#include "InterpreterValue.h"

namespace ola
{
	class Function;
	class BasicBlock;
	class Value;

	class InterpreterFrame
	{
	public:
		explicit InterpreterFrame(Function* func, std::vector<InterpreterValue> const& args);

		void SetValue(Value* v, InterpreterValue val);
		InterpreterValue GetValue(Value* v) const;
		Bool HasValue(Value* v) const;

		BasicBlock* GetCurrentBlock() const { return current_block; }
		void SetCurrentBlock(BasicBlock* bb);
		BasicBlock* GetPreviousBlock() const { return previous_block; }

		Function* GetFunction() const { return function; }

		void SetReturnValue(InterpreterValue val) { return_value = val; has_returned = true; }
		InterpreterValue GetReturnValue() const { return return_value; }
		Bool HasReturned() const { return has_returned; }

	private:
		Function* function;
		BasicBlock* current_block = nullptr;
		BasicBlock* previous_block = nullptr;

		std::unordered_map<Value*, InterpreterValue> value_map;

		InterpreterValue return_value;
		Bool has_returned = false;
	};
}
