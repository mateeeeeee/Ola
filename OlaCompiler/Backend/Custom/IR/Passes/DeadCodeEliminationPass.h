#pragma once
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class Instruction;

	class DeadCodeEliminationPass : public FunctionPass
	{
	public:
		inline static char ID = 0;
	public:
		DeadCodeEliminationPass() : FunctionPass(ID) {}

		virtual bool RunOn(Function& F) override;

	private:
		static bool IsInstructionDead(Instruction const* I);
	};
	using DCEPass = DeadCodeEliminationPass;
}