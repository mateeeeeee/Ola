#include "CFG.h"
#include "Backend/Custom/IR/BasicBlock.h"

namespace ola
{
	static const std::unordered_set<BasicBlock*> empty{};

	void CFG::AddPredecessor(BasicBlock* bb, BasicBlock* pred)
	{
		predecessors[bb].insert(pred);
		successors[pred].insert(bb);
	}

	void CFG::AddSuccessor(BasicBlock* bb, BasicBlock* succ)
	{
		successors[bb].insert(succ);
		predecessors[succ].insert(bb);
	}

	void CFG::RemovePredecessor(BasicBlock* bb, BasicBlock* pred)
	{
		auto& preds = predecessors[bb];
		preds.erase(pred);
		auto& succs = successors[pred];
		succs.erase(bb);
	}

	void CFG::RemoveSuccessor(BasicBlock* bb, BasicBlock* succ)
	{
		auto& succs = successors[bb];
		succs.erase(succ);
		auto& preds = predecessors[succ];
		preds.erase(bb);
	}

	void CFG::AddBasicBlock(BasicBlock* bb)
	{
		basic_blocks.insert(bb);
		bb->SetCFG(this);
	}

	std::unordered_set<BasicBlock*> const& CFG::GetPredecessors(BasicBlock const* bb) const
	{
		auto it = predecessors.find(bb);
		return (it != predecessors.end()) ? it->second : empty;
	}

	std::unordered_set<BasicBlock*> const& CFG::GetSuccessors(BasicBlock const* bb) const
	{
		auto it = successors.find(bb);
		return (it != successors.end()) ? it->second : empty;
	}

	BasicBlock* CFG::GetUniquePredecessor(BasicBlock const* bb) const
	{
		std::unordered_set<BasicBlock*> const& predecessors = GetPredecessors(bb);
		return predecessors.size() == 1 ? *predecessors.begin() : nullptr;
	}

	BasicBlock* CFG::GetUniqueSuccessor(BasicBlock const* bb) const
	{
		std::unordered_set<BasicBlock*> const& successors = GetSuccessors(bb);
		return successors.size() == 1 ? *successors.begin() : nullptr;
	}

}