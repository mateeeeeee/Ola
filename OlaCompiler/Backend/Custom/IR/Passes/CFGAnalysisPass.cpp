#include <unordered_set>
#include "CFGAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool CFGAnalysisPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		return RunOn(F);
	}

	Bool CFGAnalysisPass::RunOn(Function const& F)
	{
		for (auto& block : F.Blocks())
		{
			BasicBlockCFGInfo& self_info = info[&block];
			Instruction const* terminator = block.GetTerminator();
			if (terminator->IsBranch())
			{
				if (terminator->GetOpcode() == Opcode::Switch)
				{
					SwitchInst const* switch_inst = cast<SwitchInst>(terminator);
					std::unordered_set<BasicBlock const*> switch_targets;
					switch_targets.insert(switch_inst->GetDefaultCase());
					for (auto&& [_, target] : switch_inst->Cases())
					{
						switch_targets.insert(target);
					}

					for (BasicBlock const* target : switch_targets)
					{
						self_info.successors.push_back(target);
						info[target].predecessors.push_back(&block);
					}
				}
				else
				{
					BranchInst const* branch_inst = cast<BranchInst>(terminator);
					BasicBlock const* true_target = branch_inst->GetTrueTarget();
					BasicBlock const* false_target = branch_inst->GetFalseTarget();
					self_info.successors.push_back(true_target);
					info[true_target].predecessors.push_back(&block);
					if (false_target && false_target != true_target)
					{
						self_info.successors.push_back(false_target);
						info[false_target].predecessors.push_back(&block);
					}
				}
			}
		}
		OLA_ASSERT(info[&F.GetEntryBlock()].predecessors.empty());
		return true;
	}

}

