#pragma once
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/IR/PassRegistry.h"


namespace ola
{
	class Instruction;
	class Loop;

	class LoopInvariantCodeMotionPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		LoopInvariantCodeMotionPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		static void const* ID() { return &id; }

	private:
		static Bool IsLoopInvariant(Instruction* I, Loop const* L);
	};
	OLA_REGISTER_PASS(LoopInvariantCodeMotionPass, "Loop Invariant Code Motion Pass");
	using LICMPass = LoopInvariantCodeMotionPass;

	inline FunctionPass* CreateLICMPass() { return new LICMPass(); }
}