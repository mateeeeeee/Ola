#pragma once
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/IR/PassRegistry.h"

namespace ola
{
	class CFG;
	class BasicBlock;

	class CriticalEdgeSplittingPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		CriticalEdgeSplittingPass() : FunctionPass(id), cfg(nullptr) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		static void const* ID() { return &id; }

	private:
		CFG const* cfg;
		Uint32 edge_block_counter = 0;

	private:
		Bool SplitCriticalEdges(Function& F);
		BasicBlock* SplitEdge(BasicBlock* src, BasicBlock* dst, Function& F);
	};

	OLA_REGISTER_PASS(CriticalEdgeSplittingPass, "Critical Edge Splitting Pass");

	inline FunctionPass* CreateCriticalEdgeSplittingPass() { return new CriticalEdgeSplittingPass(); }
}
