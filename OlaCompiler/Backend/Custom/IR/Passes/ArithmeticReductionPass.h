#pragma once
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/PassRegistry.h"

namespace ola
{
	class Instruction;
	class BinaryInst;

	class ArithmeticReductionPass : public FunctionPass
	{
	public:
		inline static Char ID = 0;
	public:
		ArithmeticReductionPass() : FunctionPass(ID) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
	};
	OLA_REGISTER_PASS(ArithmeticReductionPass, "Arithmetic Reduction Pass");
}