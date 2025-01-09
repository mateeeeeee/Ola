#pragma once
#include <vector>
#include <span>
#include <unordered_set>
#include <unordered_map>
#include "BasicBlock.h"

namespace ola
{
	class LoopInfo;

	class Loop
	{
		friend class LoopInfo;
	public:
		Loop() : ParentLoop(nullptr) {}
		explicit Loop(BasicBlock* BB) : ParentLoop(nullptr) 
		{
			Blocks.push_back(BB);
			BlockSet.insert(BB);
		}
		~Loop() 
		{
			SubLoops.clear();
			Blocks.clear();
			BlockSet.clear();
			ParentLoop = nullptr;
		}
		OLA_NONCOPYABLE(Loop)

		Uint32 GetLoopDepth() const 
		{
			Uint32 Depth = 1;
			for (Loop const* CurLoop = ParentLoop; CurLoop;CurLoop = CurLoop->ParentLoop) ++Depth;
			return Depth;
		}
		BasicBlock* GetHeader() const { return Blocks.front(); }
		Loop*	GetParentLoop() const { return ParentLoop; }

		Loop const* GetOutermostLoop() const
		{
			Loop const* L = static_cast<Loop const*>(this);
			while (L->ParentLoop) L = L->ParentLoop;
			return L;
		}
		Loop* GetOutermostLoop() 
		{
			Loop* L = static_cast<Loop*>(this);
			while (L->ParentLoop) L = L->ParentLoop;
			return L;
		}

		void SetParentLoop(Loop* L) 
		{
			ParentLoop = L;
		}

		Bool Contains(Loop const* L) const
		{
			if (L == this) return true;
			if (!L) return false;
			return Contains(L->GetParentLoop());
		}
		Bool Contains(BasicBlock const* BB) const
		{
			return BlockSet.contains(BB);
		}
		Bool Contains(Instruction const* I) const 
		{
			return Contains(I->GetBasicBlock());
		}

		std::vector<Loop*> const& GetSubLoops() const
		{
			return SubLoops;
		}
		std::vector<Loop*>& GetSubLoops()
		{
			return SubLoops;
		}

		using iterator = typename std::vector<Loop*>::const_iterator;
		using reverse_iterator = typename std::vector<Loop*>::const_reverse_iterator;
		iterator begin() const { return GetSubLoops().begin(); }
		iterator end() const { return GetSubLoops().end(); }
		reverse_iterator rbegin() const { return GetSubLoops().rbegin(); }
		reverse_iterator rend() const { return GetSubLoops().rend(); }
		
		Bool IsInnermost() const { return GetSubLoops().empty(); }
		Bool IsOutermost() const { return GetParentLoop() == nullptr; }

		std::span<BasicBlock* const> GetBlocks() const
		{
			return Blocks;
		}
		using block_iterator = typename std::span<BasicBlock* const>::iterator;
		block_iterator block_begin()	const { return GetBlocks().begin(); }
		block_iterator block_end()		const { return GetBlocks().end(); }
		IteratorRange<block_iterator> BlocksRange() const 
		{
			return MakeRange(block_begin(), block_end());
		}
		Uint32 GetNumBlocks() const 
		{
			return Blocks.size();
		}
		auto& GetBlocksVector()
		{
			return Blocks;
		}
		auto& GetBlocksSet() 
		{
			return BlockSet;
		}
		auto const& GetBlocksSet() const 
		{
			return BlockSet;
		}

		Bool IsLoopExiting(BasicBlock const* BB) const;
		Bool IsLoopLatch(BasicBlock const* BB) const;
		Uint32 GetNumBackEdges() const;

		void GetExitingBlocks(std::vector<BasicBlock*>& ExitingBlocks) const;
		BasicBlock* GetExitingBlock() const;
		void GetExitBlocks(std::vector<BasicBlock*>& ExitBlocks) const;
		BasicBlock* GetExitBlock() const;
		Bool HasNoExitBlocks() const;
		Bool HasDedicatedExits() const;

		using Edge = std::pair<BasicBlock*, BasicBlock*>;
		void GetExitEdges(std::vector<Edge>& ExitEdges) const;

		BasicBlock* GetLoopPreheader() const;
		BasicBlock* GetLoopPredecessor() const;
		BasicBlock* GetLoopLatch() const;
		void GetLoopLatches(std::vector<BasicBlock*>& LoopLatches) const;

		void AddChildLoop(Loop* NewChild);
		Loop* RemoveChildLoop(Loop* Child);

		void AddBlockEntry(BasicBlock* BB) 
		{
			Blocks.push_back(BB);
			BlockSet.insert(BB);
		}
		void MoveToHeader(BasicBlock* BB) 
		{
			if (Blocks[0] == BB) return;

			for (Uint32 i = 0; i < Blocks.size(); ++i) 
			{
				if (Blocks[i] == BB) 
				{
					Blocks[i] = Blocks[0];
					Blocks[0] = BB;
					return;
				}
			}
		}
		void RemoveBlockFromLoop(BasicBlock* BB);

	private:
		Loop* ParentLoop;
		std::vector<Loop*> SubLoops;
		std::vector<BasicBlock*> Blocks;
		std::unordered_set<BasicBlock const*> BlockSet;
	};

	class LoopInfo
	{
	public:
		LoopInfo() = default;

		using iterator = typename std::vector<Loop*>::const_iterator;
		using reverse_iterator = typename std::vector<Loop*>::const_reverse_iterator;

		iterator begin() const { return TopLevelLoops.begin(); }
		iterator end() const { return TopLevelLoops.end(); }
		reverse_iterator rbegin() const { return TopLevelLoops.rbegin(); }
		reverse_iterator rend() const { return TopLevelLoops.rend(); }
		Bool Empty() const { return TopLevelLoops.empty(); }

		Loop* GetLoopFor(BasicBlock const* BB) const;
		Loop const* operator[](BasicBlock const* BB) const { return GetLoopFor(BB); }

		Uint32 getLoopDepth(BasicBlock const* BB) const
		{
			Loop const* L = GetLoopFor(BB);
			return L ? L->GetLoopDepth() : 0;
		}
		Bool IsLoopHeader(BasicBlock const* BB) const
		{
			Loop const* L = GetLoopFor(BB);
			return L && L->GetHeader() == BB;
		}

		std::vector<Loop*> const& GetTopLevelLoops() const { return TopLevelLoops; }
		std::vector<Loop*>& GetTopLevelLoops() { return TopLevelLoops; }

		Loop* RemoveLoop(Loop* L);
		void ChangeLoopFor(BasicBlock* BB, Loop* L) 
		{
			if (!L) 
			{
				BBMap.erase(BB);
				return;
			}
			BBMap[BB] = L;
		}

		void ChangeTopLevelLoop(Loop* OldLoop, Loop* NewLoop);
		void AddTopLevelLoop(Loop* New)
		{
			OLA_ASSERT_MSG(New->IsOutermost(), "Loop already in subloop!");
			TopLevelLoops.push_back(New);
		}
		void RemoveBlock(BasicBlock* BB);

	private:
		std::vector<Loop*> TopLevelLoops;
		std::unordered_map<BasicBlock const*, Loop*> BBMap;
	};
}

