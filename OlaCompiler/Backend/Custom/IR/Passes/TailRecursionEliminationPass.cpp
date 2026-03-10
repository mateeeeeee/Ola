#include "TailRecursionEliminationPass.h"
#include "CFGAnalysisPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "DominanceFrontierAnalysisPass.h"
#include "LoopAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRBuilder.h"

// reference: https://llvm.org/doxygen/TailRecursionElimination_8cpp_source.html#l00087

namespace ola
{
	struct TailCallCandidate
	{
		BasicBlock* CallBB;
		CallInst* CI;
	};

	// handles two common cases:
	//   1. call @F(...) followed by ret (same block)
	//   2. call @F(...) followed by br to a block that does phi+ret
	static Bool FindTailRecursiveCall(BasicBlock& BB, Function& F, TailCallCandidate& Out)
	{
		Instruction* Terminator = BB.GetTerminator();
		if (ReturnInst* Ret = dyn_cast<ReturnInst>(Terminator))
		{
			for (auto It = BB.rbegin(); It != BB.rend(); ++It)
			{
				Instruction& I = *It;
				if (&I == Ret) 
				{
					continue;
				}

				if (CallInst* C = dyn_cast<CallInst>(&I))
				{
					if (C->GetCalleeAsFunction() != &F) 
					{
						return false;
					}

					if (!Ret->IsVoid() && Ret->GetReturnValue() != C) 
					{
						return false;
					}
					Out = { &BB, C };
					return true;
				}

				if (I.HasSideEffects()) 
				{
					return false;
				}
				if (!Ret->IsVoid() && Ret->GetReturnValue() == &I) 
				{
					return false;
				}
			}
			return false;
		}

		BranchInst* BI = dyn_cast<BranchInst>(Terminator);
		if (!BI || BI->IsConditional()) 
		{
			return false;
		}

		BasicBlock* Succ = BI->GetTrueTarget();
		if (!Succ)
		{
			 return false;
		}

		Instruction* SuccTerm = Succ->GetTerminator();
		ReturnInst* Ret = dyn_cast<ReturnInst>(SuccTerm);
		if (!Ret) 
		{
			return false;
		}

		for (auto& I : *Succ)
		{
			if (&I == Ret || isa<PhiInst>(&I)) 
			{
				continue;
			}
			return false; 
		}

		for (auto It = BB.rbegin(); It != BB.rend(); ++It)
		{
			Instruction& I = *It;
			if (&I == BI) 
			{
				continue;
			}
			if (CallInst* C = dyn_cast<CallInst>(&I))
			{
				if (C->GetCalleeAsFunction() != &F) 
				{
					return false;
				}

				if (!Ret->IsVoid())
				{
					Value* RetVal = Ret->GetReturnValue();
					PhiInst* RetPhi = dyn_cast<PhiInst>(RetVal);
					if (!RetPhi) 
					{
						return false;
					}

					Value* InVal = RetPhi->GetIncomingValueForBlock(&BB);
					if (InVal != C)
					{
						 return false;
					}
				}
				Out = { &BB, C };
				return true;
			}

			if (I.HasSideEffects()) 
			{
				return false;
			}
		}
		return false;
	}

	Bool TailRecursionEliminationPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		if (F.IsDeclaration())
		{
			return false;
		}

		for (Uint64 i = 0; i < F.GetArgCount(); ++i)
		{
			if (F.GetArgType(i)->IsAggregate()) 
			{
				return false;
			}
		}

		std::vector<TailCallCandidate> TailCalls;
		for (BasicBlock& BB : F)
		{
			TailCallCandidate Candidate{};
			if (FindTailRecursiveCall(BB, F, Candidate))
			{
				TailCalls.push_back(Candidate);
			}
		}

		if (TailCalls.empty()) 
		{
			return false;
		}

		IRContext& Ctx = F.GetContext();
		IRBuilder Builder(Ctx);
		Builder.SetCurrentFunction(&F);

		// create the loop header by splitting the entry block.
		//   NewEntry (preheader):  br -> HeaderBB
		//   HeaderBB (original entry, now loop header):
		//     PHI nodes for each argument
		//     ... original entry block instructions ...
		BasicBlock* OrigEntry = &F.GetEntryBlock();
		BasicBlock* NewEntry = Builder.AddBlock(&F, OrigEntry, "entry");
		OrigEntry->SetName("tailrecurse");

		std::vector<PhiInst*> ArgPHIs;
		ArgPHIs.reserve(F.GetArgCount());
		for (Uint64 i = 0; i < F.GetArgCount(); ++i)
		{
			Argument* Arg = F.GetArg(i);
			PhiInst* PN = new PhiInst(Arg->GetType());
			PN->SetName(std::string(Arg->GetName()) + ".tr");
			OrigEntry->AddPhiInst(PN);
			PN->AddIncoming(Arg, NewEntry);
			ArgPHIs.push_back(PN);
		}

		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB)
			{
				if (std::find(ArgPHIs.begin(), ArgPHIs.end(), &I) != ArgPHIs.end()) 
				{
					continue;
				}

				for (Uint32 OpIdx = 0; OpIdx < I.GetNumOperands(); ++OpIdx)
				{
					Value* Op = I.GetOperand(OpIdx);
					if (Argument* Arg = dyn_cast<Argument>(Op))
					{
						for (Uint64 ai = 0; ai < F.GetArgCount(); ++ai)
						{
							if (F.GetArg(ai) == Arg)
							{
								I.SetOperand(OpIdx, ArgPHIs[ai]);
								break;
							}
						}
					}
				}
			}
		}

		Builder.SetCurrentBlock(NewEntry);
		Builder.MakeInst<BranchInst>(Ctx, OrigEntry);

		{
			std::vector<AllocaInst*> AllocasToMove;
			for (Instruction& I : *OrigEntry)
			{
				if (AllocaInst* AI = dyn_cast<AllocaInst>(&I))
				{
					AllocasToMove.push_back(AI);
				}
			}
			for (AllocaInst* AI : AllocasToMove)
			{
				AI->RemoveFromParent();
				AI->InsertBefore(NewEntry, NewEntry->begin());
			}
		}

		for (auto& Site : TailCalls)
		{
			BasicBlock* BB = Site.CallBB;
			CallInst* CI = Site.CI;

			for (Uint64 i = 0; i < F.GetArgCount(); ++i)
			{
				Value* CallArg = const_cast<Value*>(CI->GetArgOp(i));
				ArgPHIs[i]->AddIncoming(CallArg, BB);
			}

			Instruction* Term = BB->GetTerminator();
			if (BranchInst* BI = dyn_cast<BranchInst>(Term))
			{
				BasicBlock* Succ = BI->GetTrueTarget();
				if (Succ)
				{
					for (PhiInst* Phi : Succ->PhiInsts())
					{
						Int Idx = Phi->GetBasicBlockIndex(BB);
						if (Idx >= 0) Phi->RemoveIncomingValue(Idx);
					}
				}
			}

			Term->EraseFromParent();
			CI->EraseFromParent();
			Builder.SetCurrentBlock(BB);
			Builder.MakeInst<BranchInst>(Ctx, OrigEntry);
		}

		{
			Uint32 idx = 0;
			for (BasicBlock& BB : F)
			{
				BB.SetIndex(idx++);
			}
		}

		FAM.InvalidateCache(F);
		return true;
	}
}
