#pragma once
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class Instruction;
	class BasicBlock;

	class GlobalValueNumberingPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		GlobalValueNumberingPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;

		static void const* ID() { return &id; }
	};
	using GVNPass = GlobalValueNumberingPass;
	OLA_REGISTER_PASS(GlobalValueNumberingPass, "Global Value Numbering Pass");

	inline FunctionPass* CreateGVNPass() { return new GVNPass(); }
}