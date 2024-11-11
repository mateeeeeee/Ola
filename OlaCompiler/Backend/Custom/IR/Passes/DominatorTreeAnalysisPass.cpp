#include <functional>
#include "DominatorTreeAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool DominatorTreeAnalysisPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		CFGAnalysisPass::Result const& cfgResult = FAM.GetResult<CFGAnalysisPass>(F);
		info = DominatorTree{};  
		CalculateImmediateDominators(F, cfgResult);
		ComputeDominanceFrontiers(F, cfgResult);
		info.SetImmediatelyDominatedBlocks();
		return false; 
	}

	void DominatorTreeAnalysisPass::CalculateImmediateDominators(Function& F, CFGAnalysisPass::Result const& cfgAnalysis)
	{
		std::unordered_map<BasicBlock const*, Sint32> semiDominatorNumbers;
		std::unordered_map<BasicBlock const*, BasicBlock const*> parent, ancestor, best;
		std::vector<BasicBlock const*> dfsOrder;  

		BasicBlock* entryBlock = &F.GetEntryBlock();
		DFS(entryBlock, semiDominatorNumbers, parent, dfsOrder, cfgAnalysis);

		for (Sint64 i = dfsOrder.size() - 1; i >= 1; --i)
		{
			BasicBlock const* w = dfsOrder[i];
			std::vector<BasicBlock const*> predecessors = cfgAnalysis.at(w).predecessors;
			for (BasicBlock const* v : predecessors)
			{
				BasicBlock const* u = Evaluate(v, semiDominatorNumbers, ancestor, best);
				semiDominatorNumbers[w] = std::min(semiDominatorNumbers[w], semiDominatorNumbers[u]);
			}

			BasicBlock const* dom = dfsOrder[semiDominatorNumbers[w]];
			ancestor[w] = parent[w];
			info.SetImmediateDominator(w, dom);
		}

		for (Uint64 i = 1; i < dfsOrder.size(); ++i) 
		{
			BasicBlock const* w = dfsOrder[i];
			if (info.GetImmediateDominator(w) != dfsOrder[semiDominatorNumbers[w]])
			{
				info.SetImmediateDominator(w, info.GetImmediateDominator(info.GetImmediateDominator(w)));
			}
		}
	}

	void DominatorTreeAnalysisPass::ComputeDominanceFrontiers(Function& F, CFGAnalysisPass::Result const& cfgAnalysis)
	{
		for (BasicBlock& block : F.Blocks())
		{
			std::vector<BasicBlock const*> predecessors = cfgAnalysis.at(&block).predecessors;
			if (predecessors.size() > 1)
			{
				for (BasicBlock const* pred : predecessors)
				{
					BasicBlock const* runner = pred;
					while (runner != info.GetImmediateDominator(&block))
					{
						info.AddDominanceFrontier(runner, &block);
						runner = info.GetImmediateDominator(runner);
					}
				}
			}
		}
	}

	BasicBlock const* DominatorTreeAnalysisPass::Evaluate(BasicBlock const* block,
		std::unordered_map<BasicBlock const*, Sint32>& semiDominatorNumbers,
		std::unordered_map<BasicBlock const*, BasicBlock const*>& ancestor,
		std::unordered_map<BasicBlock const*, BasicBlock const*>& best)
	{
		if (!ancestor.count(block)) return block;  
		if (ancestor[block] != ancestor[ancestor[block]]) 
		{
			BasicBlock const* tmp = Evaluate(ancestor[block], semiDominatorNumbers, ancestor, best);
			best[block] = tmp;
			ancestor[block] = ancestor[ancestor[block]];
		}
		return best.count(block) ? best[block] : block;
	}

	void DominatorTreeAnalysisPass::DFS(BasicBlock const* startBlock,
		std::unordered_map<BasicBlock const*, Sint32>& semiDominatorNumbers,
		std::unordered_map<BasicBlock const*, BasicBlock const*>& parent,
		std::vector<BasicBlock const*>& dfsOrder, CFGAnalysisPass::Result const& cfgAnalysis)
	{
		Sint32 currentDFSNumber = 0;  
		std::function<void(BasicBlock const*)> visit = [&](BasicBlock const* block) 
			{
				if (semiDominatorNumbers.count(block)) return;

				semiDominatorNumbers[block] = currentDFSNumber++;
				dfsOrder.push_back(block); 

				std::vector<BasicBlock const*> successors = cfgAnalysis.at(block).successors;
				for (BasicBlock const* succ : successors)
				{
					if (!semiDominatorNumbers.count(succ))
					{
						parent[succ] = block; 
						visit(succ); 
					}
				}
			};
		visit(startBlock);
	}
}

