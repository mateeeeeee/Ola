#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <utility>
#include "Utility/IteratorRange.h"
#include "Backend/Custom/PassRegistry.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/FunctionPass.h"
#include "CFGAnalysisPass.h"

namespace ola
{
	class DominatorTree
	{
	public:
		DominatorTree() {}

		void SetImmediateDominator(BasicBlock const* block, BasicBlock const* immediateDominator)
		{
			immediateDominatorMap[block] = immediateDominator;
		}

		void AddDominanceFrontier(BasicBlock const* block, BasicBlock const* dominanceFrontier)
		{
			dominanceFrontierMap[block].insert(dominanceFrontier);
		}

		BasicBlock const* GetImmediateDominator(BasicBlock const* block) const
		{
			auto it = immediateDominatorMap.find(block);
			return it != immediateDominatorMap.end() ? it->second : nullptr;
		}

		std::unordered_set<BasicBlock const*> const& GetDominanceFrontier(BasicBlock* block) const
		{
			return dominanceFrontierMap.at(block);
		}

		void SetImmediatelyDominatedBlocks() 
		{
			immediatelyDominatedBlocksMap.clear();
			for (const auto& [block, immediateDominator] : immediateDominatorMap) 
			{
				if (immediateDominator) 
				{ 
					immediatelyDominatedBlocksMap[immediateDominator].insert(block);
				}
			}
		}

		std::unordered_set<BasicBlock const*> const& GetImmediatelyDominatedBlocks(BasicBlock const* block) const 
		{
			static const std::unordered_set<BasicBlock const*> emptySet;
			auto it = immediatelyDominatedBlocksMap.find(block);
			return it != immediatelyDominatedBlocksMap.end() ? it->second : emptySet;
		}

	private:
		std::unordered_map<BasicBlock const*, BasicBlock const*> immediateDominatorMap;
		std::unordered_map<BasicBlock const*, std::unordered_set<BasicBlock const*>> dominanceFrontierMap;
		std::unordered_map<BasicBlock const*, std::unordered_set<BasicBlock const*>> immediatelyDominatedBlocksMap; 
	};

	class DominatorTreeAnalysisPass : public FunctionPass
	{
	public:
		inline static Char id = 0;
		using Result = DominatorTree;
	public:
		DominatorTreeAnalysisPass() : FunctionPass(id) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		Result const& GetResult() const { return info; }
		static void const* ID() { return &id; }

	private:
		Result info;

	private:
		void CalculateImmediateDominators(Function& F, CFGAnalysisPass::Result const& cfgAnalysis);
		void ComputeDominanceFrontiers(Function& F, CFGAnalysisPass::Result const& cfgAnalysis);

		BasicBlock const* Evaluate(BasicBlock const* block, std::unordered_map<BasicBlock const*, Sint32>& semiDominatorNumbers,
			std::unordered_map<BasicBlock const*, BasicBlock const*>& ancestor, std::unordered_map<BasicBlock const*, BasicBlock const*>& best);
		void DFS(BasicBlock const* startBlock, std::unordered_map<BasicBlock const*, Sint32>& semiDominatorNumbers, 
			std::unordered_map<BasicBlock const*, BasicBlock const*>& parent, std::vector<BasicBlock const*>& dfsOrder, CFGAnalysisPass::Result const& cfgAnalysis);
	};
	OLA_REGISTER_ANALYSIS_PASS(DominatorTreeAnalysisPass, "Dominator Tree Analysis");
}