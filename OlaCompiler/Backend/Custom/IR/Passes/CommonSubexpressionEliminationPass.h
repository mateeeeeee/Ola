#pragma once
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class Instruction;
	class BasicBlock;

	class CommonSubexpressionEliminationPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		CommonSubexpressionEliminationPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;

		static void const* ID() { return &id; }

	private:
		Bool RunOn(BasicBlock& BB, FunctionAnalysisManager& FAM);
	};
	using CSEPass = CommonSubexpressionEliminationPass;
	OLA_REGISTER_PASS(CommonSubexpressionEliminationPass, "Common Subexpression Elimination Pass");
	inline FunctionPass* CreateCommonSubexpressionEliminationPass() { return new CommonSubexpressionEliminationPass(); }
}

