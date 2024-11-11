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

	private:
		void PlacePhiNodes(Function& F, DominatorTree const& DomTree);
		void RenameVariables(Function& F, DominatorTree const& DomTree);
	};

	OLA_REGISTER_PASS(Mem2RegPass, "Memory to Register Pass");
}