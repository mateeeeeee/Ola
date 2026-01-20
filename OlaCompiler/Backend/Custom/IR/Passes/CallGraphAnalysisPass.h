#pragma once
#include "Backend/Custom/IR/IRModulePass.h"
#include "Backend/Custom/IR/PassRegistry.h"
#include "Backend/Custom/IR/CallGraph.h"

namespace ola
{
	class CallGraphAnalysisPass : public IRModulePass
	{
		inline static Char id = 0;
	public:
		using Result = CallGraph;

	public:
		CallGraphAnalysisPass() : IRModulePass(id) {}

		virtual Bool RunOn(IRModule& M, IRModuleAnalysisManager& MAM) override
		{
			call_graph = std::make_unique<CallGraph>(M);
			return false;
		}

		CallGraph const& GetResult() const { return *call_graph; }
		CallGraph& GetResult() { return *call_graph; }

		static void const* ID() { return &id; }

	private:
		std::unique_ptr<CallGraph> call_graph;
	};
	OLA_REGISTER_ANALYSIS_PASS(CallGraphAnalysisPass, "Call Graph Analysis");
}
