#pragma once
#include "Backend/Custom/IR/IRModulePass.h"
#include "Backend/Custom/IR/PassRegistry.h"

namespace ola
{
	class Function;
	class CallGraph;
	class Value;

	// Interprocedural Constant Propagation (IPCP)
	//
	// This pass uses the call graph to propagate constant arguments across function boundaries.
	// If a function parameter is always passed the same constant value at all call sites,
	// the parameter is replaced with that constant inside the function body.
	//
	// Example:
	//   define internal i32 @foo(i32 %x) { return %x + 1 }
	//   call @foo(42)
	//   call @foo(42)
	//
	// After IPCP:
	//   define internal i32 @foo(i32 %x) { return 42 + 1 }  ; %x replaced with 42
	//
	class IPConstantPropagationPass : public IRModulePass
	{
		inline static Char id = 0;
	public:
		IPConstantPropagationPass() : IRModulePass(id) {}
		virtual Bool RunOn(IRModule& M, IRModuleAnalysisManager& MAM) override;
		static void const* ID() { return &id; }

	private:
		Bool PropagateConstantsToFunction(Function* F, CallGraph& CG);
		void ReplaceArgumentUses(Function* F, Uint32 ArgIndex, Value* Replacement);
	};
	OLA_REGISTER_PASS(IPConstantPropagationPass, "Interprocedural Constant Propagation");

	inline IRModulePass* CreateIPConstantPropagationPass() { return new IPConstantPropagationPass(); }
}
