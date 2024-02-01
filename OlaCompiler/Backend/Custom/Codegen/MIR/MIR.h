#pragma once
#include <vector>
#include "Backend/Custom/IR/IRFwd.h"
#include "Utility/IntrusiveList.h"

namespace ola
{
	enum class MOperandType 
	{
		Register,
		Immediate,
		Memory
	};
	enum class MOpSize
	{
		Bit_8,
		Bit_16,
		Bit_32,
		Bit_64,
	};
	enum class MOpCode 
	{
		Add,
		Subtract,
		Load,
		Store,
		Jump
	};

	struct MOperand 
	{
		MOperandType type;
		uint64 value;  
		MOpSize size;
		MOperand(MOperandType t, uint64 v, MOpSize s = MOpSize::Bit_64) : type(t), value(v), size(s) {}
	};

	struct MInstruction;
	struct MBasicBlock : IListNode<MInstruction>
	{
		BasicBlock* ir_basic_block = nullptr;
		IList<MInstruction> instructions;
		std::vector<MBasicBlock*> predecessors;
		std::vector<MBasicBlock*> successors;

		void AddSuccessor(MBasicBlock* bb)
		{
			successors.push_back(bb);
			bb->AddPredecessor(this);
		}
	private:
		void AddPredecessor(MBasicBlock* bb)
		{
			predecessors.push_back(bb);
		}
	};

	struct MInstruction : IListNode<MInstruction>
	{
		MBasicBlock* bb;
		MOpCode opcode;
		std::vector<MOperand> operands;

		MInstruction(MOpCode opcode, MBasicBlock* insertAtEnd = nullptr) : bb(insertAtEnd), opcode(opcode)
		{
			if (insertAtEnd) insertAtEnd->instructions.PushBack(this);
		}
		MInstruction(MOpCode opcode, MInstruction* insertBefore) : bb(insertBefore->bb), opcode(opcode)
		{
			if (bb) bb->instructions.Insert(this, insertBefore);
		}
		explicit MInstruction(MOpCode opcode) : opcode(opcode), bb(nullptr) {}
	};

	struct MFunction 
	{
		Function* ir_func;
		IList<MBasicBlock> basic_blocks;
	};

	struct MGlobalVariable 
	{
		char const* name;							// Name of the global variable
		MOperand init_value;						// Initial value of the global variable
		MOpSize size = MOpSize::Bit_64;				// Size of the global variable in bytes
	};
}