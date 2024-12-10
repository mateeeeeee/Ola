#pragma once
#include <unordered_map>
#include <unordered_set>

namespace ola
{
	class BasicBlock;
	class CFG;
	class DominatorTree;

	class DominanceFrontier
	{
		using DominanceFrontierMap = std::unordered_map<BasicBlock*, std::unordered_set<BasicBlock*>>;
	public:
		DominanceFrontier() : dominance_frontier_map{} {}
		void Initialize(DominatorTree const& DT, CFG const& cfg);
		std::unordered_set<BasicBlock*> const& GetFrontier(BasicBlock* BB) const
		{
			OLA_ASSERT(dominance_frontier_map.contains(BB));
			return dominance_frontier_map.find(BB)->second;
		}

		using iterator = typename DominanceFrontierMap::iterator;
		using const_iterator = typename DominanceFrontierMap::const_iterator;
		iterator begin() { return dominance_frontier_map.begin(); }
		const_iterator begin() const { return dominance_frontier_map.begin(); }
		iterator end() { return dominance_frontier_map.end(); }
		const_iterator end() const { return dominance_frontier_map.end(); }

	private:
		DominanceFrontierMap dominance_frontier_map;
	};
}
