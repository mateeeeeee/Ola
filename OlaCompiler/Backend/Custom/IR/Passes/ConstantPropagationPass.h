#pragma once
#include <unordered_set>
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/PassRegistry.h"

namespace ola
{
	class Value;
	class ConstantPropagationPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		ConstantPropagationPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		static void const* ID() { return &id; }
	};
	OLA_REGISTER_PASS(ConstantPropagationPass, "Constant Propagation Pass");
	inline FunctionPass* CreateConstantPropagationPass() { return new ConstantPropagationPass(); }
}