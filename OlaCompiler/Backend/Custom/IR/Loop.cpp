#include "Loop.h"
#include "CFG.h"

namespace ola
{

	Bool Loop::IsLoopExiting(BasicBlock const* BB, CFG const& cfg) const
	{
		OLA_ASSERT_MSG(Contains(BB), "Exiting block must be part of the loop");
		for (auto const* Succ : cfg.GetSuccessors(BB))
		{
			if (!Contains(Succ)) return true;
		}
		return false;
	}

	Bool Loop::IsLoopLatch(BasicBlock const* BB, CFG const& cfg) const
	{
		OLA_ASSERT_MSG(Contains(BB), "block does not belong to the loop");
		for (auto const* Succ : cfg.GetSuccessors(BB))
		{
			if (Succ == GetHeader()) return true;
		}
		return false;
	}

	Uint32 Loop::GetNumBackEdges() const
	{
		return 0; //#todo
	}

	void Loop::GetExitingBlocks(std::vector<BasicBlock*>& ExitingBlocks, CFG const& cfg) const
	{
		for (BasicBlock* BB : BlocksRange())
		{
			for (auto* Succ : cfg.GetSuccessors(BB))
			{
				if (!Contains(Succ)) 
				{
					ExitingBlocks.push_back(BB);
					break;
				}
			}
		}
	}

	BasicBlock* Loop::GetExitingBlock(CFG const& cfg) const
	{
		std::vector<BasicBlock*> ExitingBlocks;
		GetExitingBlocks(ExitingBlocks, cfg);
		return ExitingBlocks.size() == 1 ? ExitingBlocks[0] : nullptr;
	}

	void Loop::GetExitBlocks(std::vector<BasicBlock*>& ExitBlocks, CFG const& cfg) const
	{
		for (BasicBlock* BB : BlocksRange())
		{
			for (auto* Succ : cfg.GetSuccessors(BB))
			{
				if (!Contains(Succ))
				{
					ExitBlocks.push_back(Succ);
				}
			}
		}
	}

	BasicBlock* Loop::GetExitBlock(CFG const& cfg) const
	{
		std::vector<BasicBlock*> ExitBlocks;
		GetExitBlocks(ExitBlocks, cfg);
		return ExitBlocks.size() == 1 ? ExitBlocks[0] : nullptr;
	}

	Bool Loop::HasNoExitBlocks(CFG const& cfg) const
	{
		std::vector<BasicBlock*> ExitBlocks;
		GetExitBlocks(ExitBlocks, cfg);
		return ExitBlocks.empty();
	}

	Bool Loop::HasDedicatedExits(CFG const& cfg) const
	{
		std::vector<BasicBlock*> ExitBlocks;
		GetExitBlocks(ExitBlocks, cfg);
		for (BasicBlock* EB : ExitBlocks)
		{
			for (BasicBlock* Predecessor : cfg.GetPredecessors(EB))
			{
				if (!Contains(Predecessor)) return false;
			}
		}
		return true;
	}

}
