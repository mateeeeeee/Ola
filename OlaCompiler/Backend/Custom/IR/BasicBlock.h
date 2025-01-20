#pragma once
#include <string>
#include "Instruction.h"
#include "Utility/IntrusiveList.h"

namespace ola
{
	class IRContext;
	class Function;
	class Instruction;
	class CFG;

	class BasicBlock : public TrackableValue, public IListNode<BasicBlock>
	{
	public:
		BasicBlock() : TrackableValue(ValueKind::BasicBlock, nullptr), function(nullptr), block_idx(-1), current_cfg(nullptr) {}
		explicit BasicBlock(IRContext& C, Function* function, Uint32 idx);
		~BasicBlock();

		auto begin() { return instructions.begin(); }
		auto begin() const { return instructions.begin(); }
		auto end() { return instructions.end(); }
		auto end() const { return instructions.end(); }
		auto rbegin() { return instructions.rbegin(); }
		auto rbegin() const { return instructions.rbegin(); }
		auto rend() { return instructions.rend(); }
		auto rend() const { return instructions.rend(); }
		Instruction& front() { return *begin(); }
		Instruction const& front() const { return *begin(); }
		Instruction& back() { return *rbegin(); }
		Instruction const& back() const { return *rbegin(); }

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
		Bool HasPhiInsts() const { return !phi_nodes.empty(); }
		
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
		OLA_MAYBE_UNUSED BasicBlock* RemoveFromParent();
		OLA_MAYBE_UNUSED IListIterator<BasicBlock> EraseFromParent();

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

		BasicBlock* SplitBasicBlock(Instruction* SplitBefore);

		void SetCFG(CFG* cfg)
		{
			current_cfg = cfg;
		}
		void AddPredecessor(BasicBlock* pred);
		void AddSuccessor(BasicBlock* succ);
		void RemovePredecessor(BasicBlock* pred);
		void RemoveSuccessor(BasicBlock* succ);
		std::unordered_set<BasicBlock*> const& GetPredecessors() const;
		std::unordered_set<BasicBlock*> const& GetSuccessors() const;
		BasicBlock* GetUniquePredecessor() const;
		BasicBlock* GetUniqueSuccessor() const;

		static Bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind::BasicBlock;
		}

	private:
		Function* function;
		Uint32 block_idx;
		IList<Instruction> instructions;
		std::vector<PhiInst*> phi_nodes;
		CFG* current_cfg;
	};
}