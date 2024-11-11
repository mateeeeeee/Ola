#pragma once
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class Instruction;

	class DeadCodeEliminationPass : public FunctionPass
	{
	public:
		inline static Char ID = 0;
	public:
		DeadCodeEliminationPass() : FunctionPass(ID) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;

	private:
		static Bool IsInstructionDead(Instruction const* I);
	};
	using DCEPass = DeadCodeEliminationPass;
	OLA_REGISTER_PASS(DeadCodeEliminationPass, "Dead Code Elimination Pass");
}