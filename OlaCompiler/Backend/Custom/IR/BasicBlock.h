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

		void AddPhiInst(PhiInst* phi)
		{
			phi->InsertBefore(this, instructions.begin());
			phi_nodes.push_back(phi);
		}
		auto const& PhiInsts() const { return phi_nodes; }
		
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

		template<typename F> requires std::is_invocable_v<F, Instruction&>
		void ForAllInstructions(F&& f)
		{
			for (Instruction& I : instructions) f(I);
		}
		template<typename F> requires std::is_invocable_r_v<Bool, F, Instruction&>
		void ForAllInstructionsUntil(F&& f)
		{
			for (Instruction& I : instructions)
			{
				if (!f(I)) return;
			}
		}

		static Bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::BasicBlock;
		}

	private:
		Function* function;
		Uint32 block_idx;
		IList<Instruction> instructions;
		std::vector<PhiInst*> phi_nodes;
	};
}