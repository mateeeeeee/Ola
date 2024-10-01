#pragma once
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/PassRegistry.h"

namespace ola
{
	class Instruction;
	class BinaryInst;

	class ArithmeticStrengthReductionPass : public FunctionPass
	{
	public:
		inline static char ID = 0;
	public:
		ArithmeticStrengthReductionPass() : FunctionPass(ID) {}

		virtual bool RunOn(Function& F) override;
	};
	OLA_REGISTER_PASS(ArithmeticStrengthReductionPass, "ASR Pass", false);
}