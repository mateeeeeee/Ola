#include "CFG.h"
#include "Backend/Custom/IR/BasicBlock.h"

namespace ola
{
	static const std::vector<BasicBlock*> empty;

	void CFG::AddPredecessor(BasicBlock* bb, BasicBlock* pred)
	{
		predecessors[bb].push_back(pred);
		successors[pred].push_back(bb);
	}

	void CFG::AddSuccessor(BasicBlock* bb, BasicBlock* succ)
	{
		successors[bb].push_back(succ);
		predecessors[succ].push_back(bb);
	}

	void CFG::AddBasicBlock(BasicBlock* bb)
	{
		basic_blocks.insert(bb);
		bb->SetCFG(this);
	}

	std::vector<BasicBlock*> const& CFG::GetPredecessors(BasicBlock const* bb) const
	{
		auto it = predecessors.find(bb);
		return (it != predecessors.end()) ? it->second : empty;
	}

	std::vector<BasicBlock*> const& CFG::GetSuccessors(BasicBlock const* bb) const
	{
		auto it = successors.find(bb);
		return (it != successors.end()) ? it->second : empty;
	}

}