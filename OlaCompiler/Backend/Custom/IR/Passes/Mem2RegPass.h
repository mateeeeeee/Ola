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

	class Mem2RegPass : public FunctionPass
	{
	public:
		inline static Char ID = 0;
	public:
		Mem2RegPass() : FunctionPass(ID) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;

	private:
		std::unordered_map<AllocaInst*, std::stack<Value*>>		ValueStacks;
		std::unordered_map<AllocaInst*, std::vector<PhiNode*>>	PhiNodes;
		DominatorTree const* DT = nullptr;

	private:
		std::vector<AllocaInst*> FindAllocaInstructions(Function& F);
		void InsertPhiFunctions(Function& F, CFG const& cfg, std::vector<AllocaInst*> const& Allocas);
		void RenameVariables(AllocaInst* AI, DominatorTreeNode const* Node);
	};

	OLA_REGISTER_PASS(Mem2RegPass, "Memory to Register Pass");
}