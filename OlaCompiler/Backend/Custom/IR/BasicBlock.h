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
		explicit BasicBlock(IRContext& C, Function* function, Uint32 idx);
		~BasicBlock() {}

		auto& Instructions()
		{
			return instructions;
		}
		auto const& Instructions() const
		{
			return instructions;
		}

		void AddPhiNode(PhiNode* phi)
		{
			instructions.Insert(instructions.begin(), phi);
			phi_nodes.push_back(phi);
		}
		auto const& PhiNodes() const { return phi_nodes; }
		
		Instruction const* GetTerminator() const 
		{
			return instructions.Size() && instructions.Back().IsTerminator() ? &instructions.Back() : nullptr;
		}
		Instruction* GetTerminator() 
		{
			return instructions.Size() && instructions.Back().IsTerminator() ? &instructions.Back() : nullptr;
		}

		Function* GetFunction() const 
		{
			return function;
		}
		void SetFunction(Function* func) 
		{
			function = func;
		}
		Function* GetParent() const
		{
			return function;
		}
		void SetParent(Function* func)
		{
			function = func;
		}

		Uint32 GetIndex() const
		{
			return block_idx;
		}
		void SetIndex(Uint32 idx)
		{
			block_idx = idx;
		}
		Bool IsEntryBlock() const;

		static Bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::BasicBlock;
		}

	private:
		Function* function;
		Uint32 block_idx;
		IList<Instruction> instructions;
		std::vector<PhiNode*> phi_nodes;
	};
}