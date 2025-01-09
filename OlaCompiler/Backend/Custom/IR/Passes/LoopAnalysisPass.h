#pragma once
#include <memory>
#include <utility>
#include <span>
#include "Backend/Custom/PassRegistry.h"
#include "Backend/Custom/IR/Loop.h"
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class DominatorTree;
	class LoopAnalysisPass : public FunctionPass
	{
	public:
		inline static Char id = 0;
		using Result = LoopInfo;
	public:
		LoopAnalysisPass() : FunctionPass(id) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		LoopInfo const& GetResult() const { return LI; }
		static void const* ID() { return &id; }

	private:
		LoopInfo LI;

	private:
		void DiscoverLoop(Loop* L, std::span<BasicBlock*> BackEdges, DominatorTree const& DT, LoopInfo& LI);
	};
	OLA_REGISTER_ANALYSIS_PASS(LoopAnalysisPass, "Loop Analysis");
}