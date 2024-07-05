#pragma once
#include <string>
#include "Instruction.h"
#include "Utility/IntrusiveList.h"

namespace ola
{
	class IRContext;
	class Function;
	class Instruction;

	class BasicBlock : public Value, public IListNode<BasicBlock>
	{
	public:
		BasicBlock() : Value(ValueKind::BasicBlock, nullptr), function(nullptr), block_idx(-1) {}
		explicit BasicBlock(IRContext& C, Function* function, uint32 idx = -1);
		~BasicBlock() {}
		auto& Instructions()
		{
			return instructions;
		}
		auto const& Instructions() const
		{
			return instructions;
		}
		Instruction const& GetTerminator() const 
		{
			return instructions.Back();
		}
		Instruction& GetTerminator() 
		{
			return instructions.Back();
		}

		Function* GetFunction() const 
		{
			return function;
		}
		void SetFunction(Function* func) 
		{
			function = func;
		}

		uint32 GetIndex() const
		{
			return block_idx;
		}
		void SetIndex(uint32 idx)
		{
			block_idx = idx;
		}

	private:
		Function* function;
		std::string label;
		uint32 block_idx;
		IList<Instruction> instructions;

		std::vector<BasicBlock*> predecessors;
	};
}