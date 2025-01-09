#pragma once
#include <unordered_map>
#include <unordered_set>

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
		void AddBasicBlock(BasicBlock* bb);

		std::vector<BasicBlock*> const& GetPredecessors(BasicBlock const* bb) const;
		std::vector<BasicBlock*> const& GetSuccessors(BasicBlock const* bb) const;

		using iterator = std::unordered_set<BasicBlock*>::iterator;
		using const_iterator = std::unordered_set<BasicBlock*>::const_iterator;

		iterator	   begin()		  { return basic_blocks.begin(); }
		iterator	   end()		  { return basic_blocks.end(); }
		const_iterator begin()	const { return cbegin(); }
		const_iterator end()	const { return cend(); }
		const_iterator cbegin() const { return basic_blocks.cbegin(); }
		const_iterator cend()	const { return basic_blocks.cend(); }

	private:
		BasicBlock* entry_block = nullptr;
		std::unordered_set<BasicBlock*> basic_blocks;
		std::unordered_map<BasicBlock const*, std::vector<BasicBlock*>> predecessors;
		std::unordered_map<BasicBlock const*, std::vector<BasicBlock*>> successors;
	};
}