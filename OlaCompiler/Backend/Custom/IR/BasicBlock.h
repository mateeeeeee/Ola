#pragma once
#include <string>
#include "Utility/IntrusiveList.h"

namespace ola
{
	class Function;
	class Instruction;

	class BasicBlock : public IListNode<BasicBlock>
	{
	public:
		BasicBlock() : function(nullptr), block_idx(-1) {}
		explicit BasicBlock(Function* function, uint32 idx = -1) : function(function), block_idx(idx) {}
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

		std::string_view GetLabel() const 
		{
			return label;
		}
		void SetLabel(std::string_view label)
		{
			label = label;
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
	};
}