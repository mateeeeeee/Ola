#pragma once
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/PassRegistry.h"

namespace ola
{
	class Instruction;
	class BinaryInst;

	class ArithmeticReductionPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		ArithmeticReductionPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		static void const* ID() { return &id; }
	};
	OLA_REGISTER_PASS(ArithmeticReductionPass, "Arithmetic Reduction Pass");
}