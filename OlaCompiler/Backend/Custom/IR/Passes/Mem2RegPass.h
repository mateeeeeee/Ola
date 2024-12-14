#pragma once
#include <unordered_map>
#include <stack>
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class CFG;
	class DominatorTree;
	class AllocaInst;
	class PhiNode;
	class Value;
	class DominatorTreeNode;
	class DominanceFrontier;

	class Mem2RegPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		Mem2RegPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		static void const* ID() { return &id; }

	private:
		DominanceFrontier const* DF = nullptr;

	private:
		std::vector<AllocaInst*> FindAllocaInstructions(Function& F);
		void InsertPhiFunctions(std::vector<AllocaInst*> const& Allocas, CFG const& cfg);
		void RenameVariables(std::vector<AllocaInst*> const& Allocas, CFG const& cfg);
	};

	OLA_REGISTER_PASS(Mem2RegPass, "Memory to Register Pass");
	inline FunctionPass* CreateMem2RegPass() { return new Mem2RegPass(); }
}