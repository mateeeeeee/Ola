#pragma once
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/IR/PassRegistry.h"

namespace ola
{
	class CFG;
	class SimplifyCFGPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		SimplifyCFGPass() : FunctionPass(id), cfg(nullptr) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		static void const* ID() { return &id; }

	private:
		CFG const* cfg;

	private:
		void ResetCFG(Function& F, FunctionAnalysisManager& FAM);
		Bool MergeBlocks(Function& F);
		Bool RemoveUnreachableBlocks(Function& F);
	};
	OLA_REGISTER_PASS(SimplifyCFGPass, "Simplify CFG Pass");

	inline FunctionPass* CreateSimplifyCFGPass() { return new SimplifyCFGPass(); }
}