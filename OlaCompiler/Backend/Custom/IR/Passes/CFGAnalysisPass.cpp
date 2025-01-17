#include <unordered_set>
#include "CFGAnalysisPass.h"
#include "Backend/Custom/IR/CFGPrinter.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool CFGAnalysisPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		cfg.Clear();
		for (auto& block : F.Blocks())
		{
			Instruction const* terminator = block.GetTerminator();
			if (terminator->IsBranch())
			{
				if (terminator->GetOpcode() == Opcode::Switch)
				{
					SwitchInst const* switch_inst = cast<SwitchInst>(terminator);
					std::unordered_set<BasicBlock*> switch_targets;
					switch_targets.insert(switch_inst->GetDefaultCase());
					for (auto&& [_, target] : switch_inst->Cases())
					{
						switch_targets.insert(target);
					}

					for (BasicBlock* target : switch_targets)
					{
						cfg.AddSuccessor(&block, target);
					}
				}
				else
				{
					BranchInst const* branch_inst = cast<BranchInst>(terminator);
					BasicBlock* true_target = branch_inst->GetTrueTarget();
					BasicBlock* false_target = branch_inst->GetFalseTarget();
					cfg.AddSuccessor(&block, true_target);
					if (false_target && false_target != true_target)
					{
						cfg.AddSuccessor(&block, false_target);
					}
				}
			}
			cfg.AddBasicBlock(&block);
		}
		OLA_ASSERT(cfg.GetPredecessors(&F.GetEntryBlock()).empty());
		cfg.SetEntryBlock(&F.GetEntryBlock());
		return false;
	}

	Bool CFGPrinterPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		CFG const& cfg = FAM.GetResult<CFGAnalysisPass>(F);
		CFGPrinter cfg_printer;
		cfg_printer.Print(&F, cfg);
		return false;
	}

}

