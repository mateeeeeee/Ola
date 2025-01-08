#pragma once
#include <vector>
#include <span>
#include <unordered_set>
#include "BasicBlock.h"

namespace ola
{
	class CFG;

	class Loop
	{
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

		Bool IsLoopExiting(BasicBlock const* BB, CFG const& cfg) const;
		Bool IsLoopLatch(BasicBlock const* BB, CFG const& cfg) const;
		Uint32 GetNumBackEdges() const;

		void GetExitingBlocks(std::vector<BasicBlock*>& ExitingBlocks, CFG const& cfg) const;
		BasicBlock* GetExitingBlock(CFG const& cfg) const;
		void GetExitBlocks(std::vector<BasicBlock*>& ExitBlocks, CFG const& cfg) const;
		BasicBlock* GetExitBlock(CFG const& cfg) const;
		Bool HasNoExitBlocks(CFG const& cfg) const;
		Bool HasDedicatedExits(CFG const& cfg) const;

	private:
		Loop* ParentLoop;
		std::vector<Loop*> SubLoops;
		std::vector<BasicBlock*> Blocks;
		std::unordered_set<BasicBlock const*> BlockSet;
	};
}

