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

		void SetEntryBlock(BasicBlock const* bb)
		{
			entry_block = bb;
		}
		BasicBlock const* GetEntryBlock() const { return entry_block; }
		void AddPredecessor(BasicBlock const* bb, BasicBlock const* pred);
		void AddSuccessor(BasicBlock const* bb, BasicBlock const* succ);

		std::vector<BasicBlock const*> const& GetPredecessors(BasicBlock const* bb) const;
		std::vector<BasicBlock const*> const& GetSuccessors(BasicBlock const* bb) const;

	private:
		BasicBlock const* entry_block = nullptr;
		std::unordered_map<BasicBlock const*, std::vector<BasicBlock const*>> predecessors;
		std::unordered_map<BasicBlock const*, std::vector<BasicBlock const*>> successors;
	};
}