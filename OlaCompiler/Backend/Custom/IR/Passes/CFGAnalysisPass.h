#pragma once
#include <vector>
#include <unordered_map>
#include "Backend/Custom/PassRegistry.h"
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class BasicBlock;
	struct BasicBlockCFGInfo  
	{
		std::vector<BasicBlock const*> predecessors;
		std::vector<BasicBlock const*> successors;
	};

	class CFGAnalysisPass : public FunctionPass
	{
	public:
		inline static Char id = 0;
		using Result = std::unordered_map<BasicBlock const*, BasicBlockCFGInfo>;

	public:
		CFGAnalysisPass() : FunctionPass(id) {}

		Bool RunOn(Function const& F);
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;

		Result const& GetResult() const { return info; }
		static void const* ID() { return &id; }

	private:
		Result info;
	};
	OLA_REGISTER_ANALYSIS_PASS(CFGAnalysisPass, "CFG Analysis");
}