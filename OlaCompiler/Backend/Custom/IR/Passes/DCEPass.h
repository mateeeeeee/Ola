#pragma once
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class Instruction;

	class DCEPass : public FunctionPass
	{
	public:
		inline static char ID = 0;
	public:
		DCEPass() : FunctionPass(ID) {}

		virtual bool RunOn(Function& F) override;

	private:
		static bool IsInstructionDead(Instruction const* I);
	};
}