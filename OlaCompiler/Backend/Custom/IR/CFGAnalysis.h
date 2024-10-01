#pragma once
#include <vector>
#include <unordered_map>
#include "FunctionPass.h"
#include "Backend/Custom/PassRegistry.h"

namespace ola
{
	class BasicBlock;
	struct BasicBlockCFGInfo  
	{
		std::vector<BasicBlock const*> predecessors;
		std::vector<BasicBlock const*> successors;
	};

	using CFGResult = std::unordered_map<BasicBlock const*, BasicBlockCFGInfo>;
	class CFGAnalysisPass : public FunctionPass
	{
	public:
		inline static char ID = 0;
	public:
		CFGAnalysisPass() : FunctionPass(ID) {}

		virtual bool RunOn(Function& F) override;

		CFGResult const& GetResult() const { return info; }

	private:
		CFGResult info;
	};
	OLA_REGISTER_PASS(CFGAnalysisPass, "CFG Analysis", true);
}