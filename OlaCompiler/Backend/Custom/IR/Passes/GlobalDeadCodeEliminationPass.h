#pragma once
#include "Backend/Custom/IR/IRModulePass.h"

namespace ola
{
	class GlobalDeadCodeEliminationPass : public IRModulePass
	{
		inline static Char id = 0;
	public:
		GlobalDeadCodeEliminationPass() : IRModulePass(id) {}
		virtual Bool RunOn(IRModule& M, IRModuleAnalysisManager& FAM) override;

		static void const* ID() { return &id; }
	};
	using GlobalDCEPass = GlobalDeadCodeEliminationPass;
	OLA_REGISTER_PASS(GlobalDeadCodeEliminationPass, "Global Dead Code Elimination Pass");

	inline IRModulePass* CreateGlobalDCEPass() { return new GlobalDCEPass(); }
}