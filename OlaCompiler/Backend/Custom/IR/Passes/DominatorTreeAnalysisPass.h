#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <utility>
#include "Utility/IteratorRange.h"
#include "Backend/Custom/PassRegistry.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	struct DominatorTree
	{

	};

	class DominatorTreeAnalysisPass : public FunctionPass
	{
	public:
		inline static Char id = 0;
		using Result = DominatorTree;
	public:
		DominatorTreeAnalysisPass() : FunctionPass(id) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		Result const& GetResult() const { return info; }
		static void const* ID() { return &id; }

	private:
		Result info;
	};
	OLA_REGISTER_ANALYSIS_PASS(DominatorTreeAnalysisPass, "Dominator Tree Analysis");
}