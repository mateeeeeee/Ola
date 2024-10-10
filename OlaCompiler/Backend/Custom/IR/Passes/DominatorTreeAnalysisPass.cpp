#include "DominatorTreeAnalysisPass.h"

namespace ola
{
	bool DominatorTree::Dominates(const BasicBlock* BB, const Use& U) const
	{
		return false;
	}

	bool DominatorTree::IsReachableFromEntry(const Use& U) const
	{
		return false;
	}

	Instruction* DominatorTree::FindNearestCommonDominator(Instruction* I1, Instruction* I2) const
	{
		return nullptr;
	}

	bool DominatorTree::Dominates(const BasicBlockEdge& BBE1, const BasicBlockEdge& BBE2) const
	{
		return false;
	}

	bool DominatorTree::Dominates(const BasicBlockEdge& BBE, const BasicBlock* BB) const
	{
		return false;
	}

	bool DominatorTree::Dominates(const BasicBlockEdge& BBE, const Use& U) const
	{
		return false;
	}

	bool DominatorTree::Dominates(const Instruction* Def, const BasicBlock* BB) const
	{
		return false;
	}

	bool DominatorTree::Dominates(const Value* Def, const Instruction* User) const
	{
		return false;
	}

	bool DominatorTree::Dominates(const Value* Def, const Use& U) const
	{
		return false;
	}

	bool DominatorTreeAnalysisPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		return false;
	}

}

