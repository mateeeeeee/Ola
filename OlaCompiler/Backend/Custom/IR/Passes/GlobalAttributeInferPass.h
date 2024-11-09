#pragma once
#include "Backend/Custom/IR/IRModulePass.h"
#include "Backend/Custom/PassRegistry.h"

namespace ola
{
	class GlobalAttributeInferPass : public IRModulePass
	{
	public:
		inline static Char ID = 0;
	public:
		explicit GlobalAttributeInferPass() : IRModulePass(ID) {}

		virtual Bool RunOn(IRModule&, IRModuleAnalysisManager&) override;
	};
	OLA_REGISTER_PASS(GlobalAttributeInferPass, "Global Attribute Infer Pass");
}