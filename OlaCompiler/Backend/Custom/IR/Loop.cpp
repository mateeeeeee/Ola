#include "Loop.h"
#include "CFG.h"

namespace ola
{

	Bool Loop::IsLoopExiting(BasicBlock const* BB) const
	{
		OLA_ASSERT_MSG(Contains(BB), "Exiting block must be part of the loop");
		for (auto const* Succ : BB->GetSuccessors())
		{
			if (!Contains(Succ)) return true;
		}
		return false;
	}

	Bool Loop::IsLoopLatch(BasicBlock const* BB) const
	{
		OLA_ASSERT_MSG(Contains(BB), "Block does not belong to the loop");
		for (auto const* Succ : BB->GetSuccessors())
		{
			if (Succ == GetHeader()) return true;
		}
		return false;
	}

	Uint32 Loop::GetNumBackEdges() const
	{
		Uint32 NumBackEdges = 0;
		BasicBlock* Header = GetHeader();
		for (BasicBlock* Pred : Header->GetPredecessors()) 
		{
			if (Contains(Pred)) NumBackEdges++;
		}
		return NumBackEdges;
	}

	void Loop::GetExitingBlocks(std::vector<BasicBlock*>& ExitingBlocks) const
	{
		for (BasicBlock* BB : BlocksRange())
		{
			for (auto* Succ : BB->GetSuccessors())
			{
				if (!Contains(Succ)) 
				{
					ExitingBlocks.push_back(BB);
					break;
				}
			}
		}
	}

	BasicBlock* Loop::GetExitingBlock() const
	{
		std::vector<BasicBlock*> ExitingBlocks;
		GetExitingBlocks(ExitingBlocks);
		return ExitingBlocks.size() == 1 ? ExitingBlocks[0] : nullptr;
	}

	void Loop::GetExitBlocks(std::vector<BasicBlock*>& ExitBlocks) const
	{
		for (BasicBlock* BB : BlocksRange())
		{
			for (auto* Succ : BB->GetSuccessors())
			{
				if (!Contains(Succ))
				{
					ExitBlocks.push_back(Succ);
				}
			}
		}
	}

	BasicBlock* Loop::GetExitBlock() const
	{
		std::vector<BasicBlock*> ExitBlocks;
		GetExitBlocks(ExitBlocks);
		return ExitBlocks.size() == 1 ? ExitBlocks[0] : nullptr;
	}

	Bool Loop::HasNoExitBlocks() const
	{
		std::vector<BasicBlock*> ExitBlocks;
		GetExitBlocks(ExitBlocks);
		return ExitBlocks.empty();
	}

	Bool Loop::HasDedicatedExits() const
	{
		std::vector<BasicBlock*> ExitBlocks;
		GetExitBlocks(ExitBlocks);
		for (BasicBlock* EB : ExitBlocks)
		{
			for (BasicBlock* Predecessor : EB->GetPredecessors())
			{
				if (!Contains(Predecessor)) return false;
			}
		}
		return true;
	}

	void Loop::GetExitEdges(std::vector<Edge>& ExitEdges) const
	{
		for (BasicBlock* BB : BlocksRange())
		{
			for (auto* Succ : BB->GetSuccessors())
			{
				if (!Contains(Succ))
				{
					ExitEdges.emplace_back(BB, Succ);
				}
			}
		}
	}

	BasicBlock* Loop::GetLoopPreheader() const
	{
		BasicBlock* header = GetHeader();
		if (!header) return nullptr;

		auto const& preds = header->GetPredecessors();

		BasicBlock* preheader = nullptr;
		for (BasicBlock* pred : preds) 
		{
			if (Contains(pred)) continue;
			if (preheader) return nullptr;
			preheader = pred;
		}
		if (!preheader) return nullptr;

		if (preheader->GetSuccessors().size() != 1)
		{
			return nullptr;
		}
		return preheader;
	}

	BasicBlock* Loop::GetLoopPredecessor() const
	{
		BasicBlock* header = GetHeader();
		if (!header) return nullptr;


		auto const& preds = header->GetPredecessors();

		// We need exactly one predecessor from outside the loop
		BasicBlock* predecessor = nullptr;
		for (BasicBlock* pred : preds) 
		{
			if (Contains(pred)) continue;
			if (predecessor) return nullptr;
			predecessor = pred;
		}
		return predecessor; 
	}

	BasicBlock* Loop::GetLoopLatch() const
	{
		BasicBlock* header = GetHeader();
		if (!header) return nullptr;

		BasicBlock* latch = nullptr;

		for (BasicBlock* pred : header->GetPredecessors()) 
		{
			if (!Contains(pred)) continue;
			if (latch) return nullptr;
			latch = pred;
		}
		return latch;
	}

	void Loop::GetLoopLatches(std::vector<BasicBlock*>& LoopLatches) const
	{
		BasicBlock* header = GetHeader();
		for (const auto Pred : header->GetPredecessors())
		{
			if (Contains(Pred))
			{
				LoopLatches.push_back(Pred);
			}
		}
	}

	void Loop::AddChildLoop(Loop* NewChild)
	{
		OLA_ASSERT_MSG(!NewChild->ParentLoop, "NewChild already has a parent!");
		NewChild->ParentLoop = static_cast<Loop*>(this);
		SubLoops.push_back(NewChild);
	}

	Loop* Loop::RemoveChildLoop(Loop* Child)
	{
		OLA_ASSERT_MSG(Child->ParentLoop == this, "Child is not a child of this loop!");
		auto ChildIt = std::find(SubLoops.begin(), SubLoops.end(), Child);
		OLA_ASSERT_MSG(ChildIt != SubLoops.end(), "Cannot remove end iterator!");
		SubLoops.erase(SubLoops.begin() + (ChildIt - begin()));
		Child->ParentLoop = nullptr;
		return Child;
	}

	void Loop::RemoveBlockFromLoop(BasicBlock* BB)
	{
		auto BlockIt = std::find(Blocks.begin(), Blocks.end(), BB);
		OLA_ASSERT_MSG(BlockIt != Blocks.end(), "N is not in this list!");
		Blocks.erase(BlockIt);
		BlockSet.erase(BB);
	}

	Loop* LoopInfo::GetLoopFor(BasicBlock const* BB) const
	{
		auto LoopIt = BBMap.find(BB);
		return LoopIt != BBMap.end() ? LoopIt->second : nullptr;
	}

	Loop* LoopInfo::RemoveLoop(Loop* L)
	{
		auto LoopIt = std::find(TopLevelLoops.begin(), TopLevelLoops.end(), L);
		OLA_ASSERT_MSG(LoopIt != end(), "Cannot remove end iterator!");
		OLA_ASSERT_MSG(L->IsOutermost(), "Not a top-level loop!");
		TopLevelLoops.erase(TopLevelLoops.begin() + (LoopIt - begin()));
		return L;
	}

	void LoopInfo::ChangeTopLevelLoop(Loop* OldLoop, Loop* NewLoop)
	{
		auto LoopIt = std::find(TopLevelLoops.begin(), TopLevelLoops.end(), OldLoop);
		OLA_ASSERT_MSG(LoopIt != TopLevelLoops.end(), "Old loop not at top level!");
		*LoopIt = NewLoop;
		OLA_ASSERT_MSG(!NewLoop->ParentLoop && !OldLoop->ParentLoop, "Loops already embedded into a subloop!");
	}

	void LoopInfo::RemoveBlock(BasicBlock* BB)
	{
		auto I = BBMap.find(BB);
		if (I != BBMap.end())
		{
			for (Loop* L = I->second; L; L = L->GetParentLoop()) L->RemoveBlockFromLoop(BB);
			BBMap.erase(I);
		}
	}

}
