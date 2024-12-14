#pragma once
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class Instruction;

	class DeadCodeEliminationPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		DeadCodeEliminationPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;

		static void const* ID() { return &id; }
	};
	using DCEPass = DeadCodeEliminationPass;
	OLA_REGISTER_PASS(DeadCodeEliminationPass, "Dead Code Elimination Pass");
	inline FunctionPass* CreateDeadCodeEliminationPass() { return new DeadCodeEliminationPass(); }
}