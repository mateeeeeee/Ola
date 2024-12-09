#pragma once
#include "Backend/Custom/IR/IRModulePass.h"
#include "Backend/Custom/PassRegistry.h"

namespace ola
{
	class GlobalAttributeInferPass : public IRModulePass
	{
		inline static Char id = 0;
	public:
		explicit GlobalAttributeInferPass() : IRModulePass(id) {}
		virtual Bool RunOn(IRModule&, IRModuleAnalysisManager&) override;

		static void const* ID() { return &id; }
	};
	OLA_REGISTER_PASS(GlobalAttributeInferPass, "Global Attribute Infer Pass");
}