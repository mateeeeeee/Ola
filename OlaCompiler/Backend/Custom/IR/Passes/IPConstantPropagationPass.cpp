#include "IPConstantPropagationPass.h"
#include "CallGraphAnalysisPass.h"
#include "Backend/Custom/IR/CallGraph.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/Constant.h"

namespace ola
{
	Bool IPConstantPropagationPass::RunOn(IRModule& M, IRModuleAnalysisManager& MAM)
	{
		CallGraph& CG = MAM.GetMutableResult<CallGraphAnalysisPass>(M);

		Bool Changed = false;
		for (GlobalValue* G : M.Globals())
		{
			if (Function* F = dyn_cast<Function>(G))
			{
				if (F->GetLinkage() == Linkage::Internal && !F->IsDeclaration())
				{
					Changed |= PropagateConstantsToFunction(F, CG);
				}
			}
		}
		return Changed;
	}

	Bool IPConstantPropagationPass::PropagateConstantsToFunction(Function* F, CallGraph& CG)
	{
		if (F->GetArgCount() == 0)
		{
			return false;
		}
		std::vector<CallInst*> CallSites = CG.GetCallSitesTo(F);
		if (CallSites.empty())
		{
			return false;
		}

		Bool Changed = false;
		Uint64 NumArgs = F->GetArgCount();
		for (Uint64 ArgIdx = 0; ArgIdx < NumArgs; ++ArgIdx)
		{
			Constant* UniqueConstant = nullptr;
			Bool AllSameConstant = true;

			for (CallInst* CI : CallSites)
			{
				if (CI->ArgSize() <= ArgIdx)
				{
					AllSameConstant = false;
					break;
				}

				Value* ArgValue = const_cast<Value*>(CI->GetArgOp(ArgIdx));
				Constant* ArgConstant = dyn_cast<Constant>(ArgValue);

				if (!ArgConstant)
				{
					AllSameConstant = false;
					break;
				}

				if (!UniqueConstant)
				{
					UniqueConstant = ArgConstant;
				}
				else if (UniqueConstant != ArgConstant)
				{
					Bool Equal = false;
					if (ConstantInt* CI1 = dyn_cast<ConstantInt>(UniqueConstant))
					{
						if (ConstantInt* CI2 = dyn_cast<ConstantInt>(ArgConstant))
						{
							Equal = (CI1->GetValue() == CI2->GetValue()) &&
								    (CI1->GetType() == CI2->GetType());
						}
					}
					else if (ConstantFloat* CF1 = dyn_cast<ConstantFloat>(UniqueConstant))
					{
						if (ConstantFloat* CF2 = dyn_cast<ConstantFloat>(ArgConstant))
						{
							Equal = (CF1->GetValue() == CF2->GetValue());
						}
					}

					if (!Equal)
					{
						AllSameConstant = false;
						break;
					}
				}
			}

			if (AllSameConstant && UniqueConstant)
			{
				ReplaceArgumentUses(F, ArgIdx, UniqueConstant);
				Changed = true;
			}
		}
		return Changed;
	}

	void IPConstantPropagationPass::ReplaceArgumentUses(Function* F, Uint32 ArgIndex, Value* Replacement)
	{
		Argument* Arg = F->GetArg(ArgIndex);
		if (!Arg) 
		{
			return;
		}

		for (BasicBlock& BB : *F)
		{
			for (Instruction& I : BB)
			{
				for (Uint32 i = 0; i < I.GetNumOperands(); ++i)
				{
					if (I.GetOperand(i) == Arg)
					{
						I.SetOperand(i, Replacement);
					}
				}
			}
		}
	}
}
