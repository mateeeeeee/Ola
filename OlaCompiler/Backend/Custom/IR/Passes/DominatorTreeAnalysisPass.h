#pragma once
#include <memory>
#include <utility>
#include "Backend/Custom/PassRegistry.h"
#include "Backend/Custom/IR/DominatorTree.h"
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{

	class DominatorTreeAnalysisPass : public FunctionPass
	{
	public:
		inline static Char id = 0;
		using Result = DominatorTree;
	public:
		DominatorTreeAnalysisPass() : FunctionPass(id) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		Result const& GetResult() const { return dom_tree; }
		static void const* ID() { return &id; }

	private:
		Result dom_tree;
	};
	OLA_REGISTER_ANALYSIS_PASS(DominatorTreeAnalysisPass, "Dominator Tree Analysis");
}