#pragma once
#include <unordered_map>

namespace ola
{
	class Function;
	class BasicBlock;
	class CFG
	{
	public:
		CFG() = default;

		void SetEntryBlock(BasicBlock* bb)
		{
			entry_block = bb;
		}
		BasicBlock* GetEntryBlock() const { return entry_block; }
		void AddPredecessor(BasicBlock* bb, BasicBlock* pred);
		void AddSuccessor(BasicBlock* bb, BasicBlock* succ);

		std::vector<BasicBlock*> const& GetPredecessors(BasicBlock const* bb) const;
		std::vector<BasicBlock*> const& GetSuccessors(BasicBlock const* bb) const;

	private:
		BasicBlock* entry_block = nullptr;
		std::unordered_map<BasicBlock const*, std::vector<BasicBlock*>> predecessors;
		std::unordered_map<BasicBlock const*, std::vector<BasicBlock*>> successors;
	};
}