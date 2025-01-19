#include "CFG.h"
#include "Backend/Custom/IR/BasicBlock.h"

namespace ola
{
	static const std::vector<BasicBlock*> empty{};

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

	void CFG::RemovePredecessor(BasicBlock* bb, BasicBlock* pred)
	{
		auto& preds = predecessors[bb];
		for (Uint32 i = 0; i < preds.size(); ++i) 
		{
			if (preds[i] == pred) 
			{
				std::swap(preds[i], preds.back());
				preds.pop_back();
				break;
			}
		}
		auto& succs = successors[pred];
		for (Uint32 i = 0; i < succs.size(); ++i) 
		{
			if (succs[i] == bb) 
			{
				std::swap(succs[i], succs.back());
				succs.pop_back();
				break;
			}
		}
	}

	void CFG::RemoveSuccessor(BasicBlock* bb, BasicBlock* succ)
	{
		auto& succs = successors[bb];
		for (Uint32 i = 0; i < succs.size(); ++i)
		{
			if (succs[i] == succ)
			{
				std::swap(succs[i], succs.back());
				succs.pop_back();
				break;
			}
		}

		auto& preds = predecessors[succ];
		for (Uint32 i = 0; i < preds.size(); ++i)
		{
			if (preds[i] == bb) 
			{
				std::swap(preds[i], preds.back());
				preds.pop_back();
				break;
			}
		}
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

	BasicBlock* CFG::GetUniquePredecessor(BasicBlock const* bb) const
	{
		std::vector<BasicBlock*> const& predecessors = GetPredecessors(bb);
		return predecessors.size() == 1 ? predecessors[0] : nullptr;
	}

	BasicBlock* CFG::GetUniqueSuccessor(BasicBlock const* bb) const
	{
		std::vector<BasicBlock*> const& successors = GetSuccessors(bb);
		return successors.size() == 1 ? successors[0] : nullptr;
	}

}