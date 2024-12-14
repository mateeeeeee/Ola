#pragma once
#include "Backend/Custom/IR/IRModulePass.h"

namespace ola
{
	class GlobalAttributeInferPass : public IRModulePass
	{
		inline static Char id = 0;
	public:
		GlobalAttributeInferPass() : IRModulePass(id) {}
		virtual Bool RunOn(IRModule&, IRModuleAnalysisManager&) override;

		static void const* ID() { return &id; }
	};
	OLA_REGISTER_PASS(GlobalAttributeInferPass, "Global Attribute Infer Pass");
	inline IRModulePass* CreateGlobalAttributeInferPass() { return new GlobalAttributeInferPass(); }
}