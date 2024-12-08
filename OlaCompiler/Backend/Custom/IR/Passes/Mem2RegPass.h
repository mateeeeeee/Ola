#pragma once
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class DominatorTree;

	class Mem2RegPass : public FunctionPass
	{
	public:
		inline static Char ID = 0;
	public:
		Mem2RegPass() : FunctionPass(ID) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
	};

	OLA_REGISTER_PASS(Mem2RegPass, "Memory to Register Pass");
}