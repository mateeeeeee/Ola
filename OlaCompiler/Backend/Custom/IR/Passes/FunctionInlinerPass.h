#pragma once
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/IR/PassRegistry.h"

namespace ola
{
	class Instruction;
	class CallInst;

	class FunctionInlinerPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		FunctionInlinerPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		static void const* ID() { return &id; }

	private:
		static Bool ShouldInline(CallInst* CI);
		static Bool InlineFunction(CallInst* Call);
	};
	OLA_REGISTER_PASS(FunctionInlinerPass, "Loop Invariant Code Motion Pass Pass");

	inline FunctionPass* CreateFunctionInlinerPass() { return new FunctionInlinerPass(); }
}