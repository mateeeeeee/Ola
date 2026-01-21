#include "LoopUnrollPass.h"
#include "LoopAnalysisPass.h"
#include "CFGAnalysisPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "DominanceFrontierAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRBuilder.h"
#include "Backend/Custom/IR/IRContext.h"
#include "Backend/Custom/IR/Loop.h"
#include <algorithm>

namespace ola
{
	Bool LoopUnrollPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		LoopInfo& LI = const_cast<LoopInfo&>(FAM.GetResult<LoopAnalysisPass>(F));
		if (LI.Empty())
		{
			return false;
		}

		Bool Changed = false;

		std::vector<Loop*> WorkList;
		for (Loop* L : LI)
		{
			WorkList.push_back(L);
		}

		for (Loop* L : WorkList)
		{
			if (!L->IsInnermost())
			{
				continue;
			}

			LoopUnrollAnalysis Analysis = AnalyzeLoop(L, F);
			if (!Analysis.IsCanonical)
			{
				continue;
			}

			if (!IsSafeToUnroll(L))
			{
				continue;
			}

			Uint32 LoopSize = EstimateLoopSize(L);

			if (Analysis.HasKnownTripCount &&
				Analysis.TripCount > 0 &&
				Analysis.TripCount <= (Int64)Config.FullUnrollThreshold &&
				LoopSize * Analysis.TripCount <= Config.MaxUnrolledSize)
			{
				if (FullUnroll(L, Analysis, F, LI))
				{
					Changed = true;
				}
			}
			else if (Config.AllowPartialUnroll &&
					 LoopSize * Config.UnrollFactor <= Config.MaxUnrolledSize)
			{
				if (PartialUnroll(L, Analysis, Config.UnrollFactor, F))
				{
					Changed = true;
				}
			}
		}

		if (Changed)
		{
			FAM.InvalidateCache(F);
		}

		return Changed;
	}

	LoopUnrollAnalysis LoopUnrollPass::AnalyzeLoop(Loop* L, Function& F) const
	{
		LoopUnrollAnalysis Analysis;

		Analysis.Header = L->GetHeader();
		Analysis.Preheader = L->GetLoopPreheader();
		Analysis.Latch = L->GetLoopLatch();
		Analysis.ExitBlock = L->GetExitBlock();

		if (!Analysis.Header || !Analysis.Preheader || !Analysis.Latch)
		{
			return Analysis;
		}

		if (!Analysis.ExitBlock)
		{
			return Analysis;
		}

		if (L->GetNumBackEdges() != 1)
		{
			return Analysis;
		}

		if (!FindInductionVariable(L, Analysis.IV))
		{
			return Analysis;
		}

		if (!FindExitCondition(L, Analysis.IV, Analysis.ExitCond))
		{
			return Analysis;
		}

		Analysis.IsCanonical = true;

		Int64 TripCount = -1;
		if (ComputeTripCount(Analysis.IV, Analysis.ExitCond, TripCount))
		{
			Analysis.HasKnownTripCount = true;
			Analysis.TripCount = TripCount;
		}

		return Analysis;
	}

	Bool LoopUnrollPass::FindInductionVariable(Loop* L, InductionVariable& IV) const
	{
		BasicBlock* Header = L->GetHeader();
		BasicBlock* Latch = L->GetLoopLatch();
		BasicBlock* Preheader = L->GetLoopPreheader();

		if (!Header || !Latch || !Preheader)
		{
			return false;
		}

		for (PhiInst* Phi : Header->PhiInsts())
		{
			Value* PreheaderVal = nullptr;
			Value* LatchVal = nullptr;

			for (Uint32 i = 0; i < Phi->GetNumIncomingValues(); ++i)
			{
				BasicBlock* IncomingBB = Phi->GetIncomingBlock(i);
				Value* IncomingVal = Phi->GetIncomingValue(i);

				if (IncomingBB == Preheader)
				{
					PreheaderVal = IncomingVal;
				}
				else if (IncomingBB == Latch || L->Contains(IncomingBB))
				{
					LatchVal = IncomingVal;
				}
			}

			if (!PreheaderVal || !LatchVal)
			{
				continue;
			}

			Instruction* StepInst = dyn_cast<Instruction>(LatchVal);
			if (!StepInst)
			{
				continue;
			}

			if (BinaryInst* BinOp = dyn_cast<BinaryInst>(StepInst))
			{
				Opcode Op = BinOp->GetOpcode();
				if (Op != Opcode::Add && Op != Opcode::Sub)
				{
					continue;
				}

				Value* LHS = BinOp->GetLHS();
				Value* RHS = BinOp->GetRHS();

				Value* StepVal = nullptr;
				Bool UsesIV = false;

				if (LHS == Phi)
				{
					StepVal = RHS;
					UsesIV = true;
				}
				else if (RHS == Phi && Op == Opcode::Add)
				{
					StepVal = LHS;
					UsesIV = true;
				}

				if (UsesIV && StepVal)
				{
					if (Instruction* StepValInst = dyn_cast<Instruction>(StepVal))
					{
						if (L->Contains(StepValInst))
						{
							continue;
						}
					}

					IV.Phi = Phi;
					IV.InitValue = PreheaderVal;
					IV.StepValue = StepVal;
					IV.StepInst = StepInst;
					IV.IsIncrement = (Op == Opcode::Add);
					return true;
				}
			}
		}

		return false;
	}

	Bool LoopUnrollPass::FindExitCondition(Loop* L, InductionVariable const& IV, LoopExitCondition& ExitCond) const
	{
		BasicBlock* ExitingBlock = L->GetExitingBlock();
		if (!ExitingBlock)
		{
			return false;
		}

		Instruction* Term = ExitingBlock->GetTerminator();
		BranchInst* Branch = dyn_cast<BranchInst>(Term);
		if (!Branch || !Branch->IsConditional())
		{
			return false;
		}

		Value* Cond = Branch->GetCondition();
		CompareInst* Cmp = dyn_cast<CompareInst>(Cond);
		if (!Cmp)
		{
			return false;
		}

		Value* LHS = Cmp->GetLHS();
		Value* RHS = Cmp->GetRHS();

		Value* BoundVal = nullptr;

		if (LHS == IV.Phi || LHS == IV.StepInst)
		{
			BoundVal = RHS;
		}
		else if (RHS == IV.Phi || RHS == IV.StepInst)
		{
			BoundVal = LHS;
		}
		else
		{
			return false;
		}

		BasicBlock* TrueTarget = Branch->GetTrueTarget();
		Bool ExitOnTrue = !L->Contains(TrueTarget);

		ExitCond.Compare = Cmp;
		ExitCond.Bound = BoundVal;
		ExitCond.ExitOnTrue = ExitOnTrue;

		return true;
	}

	Bool LoopUnrollPass::ComputeTripCount(InductionVariable const& IV, LoopExitCondition const& ExitCond, Int64& TripCount) const
	{
		ConstantInt* InitConst = dyn_cast<ConstantInt>(IV.InitValue);
		ConstantInt* StepConst = dyn_cast<ConstantInt>(IV.StepValue);
		ConstantInt* BoundConst = dyn_cast<ConstantInt>(ExitCond.Bound);

		if (!InitConst || !StepConst || !BoundConst)
		{
			return false;
		}

		Int64 Init = InitConst->GetValue();
		Int64 Step = StepConst->GetValue();
		Int64 Bound = BoundConst->GetValue();

		if (Step == 0)
		{
			return false;
		}

		if (!IV.IsIncrement)
		{
			Step = -Step;
		}

		CompareOp CmpOp = ExitCond.Compare->GetCompareOp();
		Bool ExitOnTrue = ExitCond.ExitOnTrue;

		Int64 Distance = Bound - Init;
		Int64 Iterations = -1;

		switch (CmpOp)
		{
		case CompareOp::ICmpSLT:
			if (ExitOnTrue)
			{
				if (Step > 0)
				{
					if (Init >= Bound) Iterations = 0;
					else Iterations = (Distance + Step - 1) / Step;
				}
			}
			else
			{
				if (Step > 0)
				{
					if (Init >= Bound) Iterations = 0;
					else Iterations = Distance / Step;
				}
			}
			break;

		case CompareOp::ICmpSLE:
			if (ExitOnTrue)
			{
				if (Step > 0)
				{
					if (Init > Bound) Iterations = 0;
					else Iterations = (Distance + Step) / Step;
				}
			}
			else
			{
				if (Step > 0)
				{
					if (Init > Bound) Iterations = 0;
					else Iterations = (Distance + 1 + Step - 1) / Step;
				}
			}
			break;

		case CompareOp::ICmpSGT:
			if (ExitOnTrue)
			{
				if (Step < 0)
				{
					if (Init <= Bound) Iterations = 0;
					else Iterations = (-Distance - Step - 1) / (-Step);
				}
			}
			break;

		case CompareOp::ICmpSGE:
			if (ExitOnTrue)
			{
				if (Step < 0)
				{
					if (Init < Bound) Iterations = 0;
					else Iterations = (-Distance - Step) / (-Step);
				}
			}
			break;

		case CompareOp::ICmpEQ:
			if (ExitOnTrue)
			{
				if (Step > 0 && Init < Bound && (Distance % Step) == 0)
				{
					Iterations = Distance / Step;
				}
				else if (Step < 0 && Init > Bound && ((-Distance) % (-Step)) == 0)
				{
					Iterations = (-Distance) / (-Step);
				}
			}
			break;

		case CompareOp::ICmpNE:
			if (!ExitOnTrue)
			{
				if (Step > 0 && Init < Bound && (Distance % Step) == 0)
				{
					Iterations = Distance / Step;
				}
				else if (Step < 0 && Init > Bound && ((-Distance) % (-Step)) == 0)
				{
					Iterations = (-Distance) / (-Step);
				}
			}
			break;

		default:
			return false;
		}

		if (Iterations < 0)
		{
			return false;
		}

		TripCount = Iterations;
		return true;
	}

	Bool LoopUnrollPass::FullUnroll(Loop* L, LoopUnrollAnalysis const& Analysis, Function& F, LoopInfo& LI)
	{
		if (Analysis.TripCount <= 0)
		{
			return false;
		}

		IRContext& Ctx = F.GetContext();
		IRBuilder Builder(Ctx);
		Builder.SetCurrentFunction(&F);

		BasicBlock* Preheader = Analysis.Preheader;
		BasicBlock* Header = Analysis.Header;
		BasicBlock* ExitBlock = Analysis.ExitBlock;

		std::unordered_map<Value*, Value*> CurrentValueMap;
		for (PhiInst* Phi : Header->PhiInsts())
		{
			Value* InitVal = Phi->GetIncomingValueForBlock(Preheader);
			if (InitVal)
			{
				CurrentValueMap[Phi] = InitVal;
			}
		}

		std::vector<Instruction*> AllNewInstructions;

		for (Int64 Iter = 0; Iter < Analysis.TripCount; ++Iter)
		{
			for (BasicBlock* BB : L->GetBlocks())
			{
				for (Instruction& OrigInst : *BB)
				{
					if (isa<PhiInst>(&OrigInst))
					{
						continue;
					}
					if (OrigInst.IsTerminator())
					{
						continue;
					}
					// Skip loop control instructions - they're not needed after unrolling
					if (&OrigInst == Analysis.ExitCond.Compare)
					{
						continue;
					}
					if (&OrigInst == Analysis.IV.StepInst)
					{
						continue;
					}

					Instruction* NewInst = OrigInst.Clone();
					if (!NewInst)
					{
						continue;
					}

					for (Uint32 i = 0; i < NewInst->GetNumOperands(); ++i)
					{
						Value* Op = NewInst->GetOperand(i);
						auto It = CurrentValueMap.find(Op);
						if (It != CurrentValueMap.end())
						{
							NewInst->SetOperand(i, It->second);
						}
					}

					NewInst->InsertBefore(Preheader, Preheader->GetTerminator());
					AllNewInstructions.push_back(NewInst);

					CurrentValueMap[&OrigInst] = NewInst;
				}
			}

			for (PhiInst* Phi : Header->PhiInsts())
			{
				if (Phi == Analysis.IV.Phi)
				{
					ConstantInt* InitConst = dyn_cast<ConstantInt>(Analysis.IV.InitValue);
					ConstantInt* StepConst = dyn_cast<ConstantInt>(Analysis.IV.StepValue);
					if (InitConst && StepConst)
					{
						Int64 Init = InitConst->GetValue();
						Int64 Step = StepConst->GetValue();
						Int64 NextVal = Analysis.IV.IsIncrement ? (Init + (Iter + 1) * Step) : (Init - (Iter + 1) * Step);
						CurrentValueMap[Phi] = Ctx.GetInt64(NextVal);
					}
					continue;
				}

				for (Uint32 i = 0; i < Phi->GetNumIncomingValues(); ++i)
				{
					BasicBlock* IncomingBB = Phi->GetIncomingBlock(i);
					if (IncomingBB != Preheader && L->Contains(IncomingBB))
					{
						Value* LatchVal = Phi->GetIncomingValue(i);
						auto It = CurrentValueMap.find(LatchVal);
						if (It != CurrentValueMap.end())
						{
							CurrentValueMap[Phi] = It->second;
						}
						else
						{
							CurrentValueMap[Phi] = LatchVal;
						}
						break;
					}
				}
			}
		}

		if (Analysis.IV.StepInst)
		{
			CurrentValueMap[Analysis.IV.StepInst] = CurrentValueMap[Analysis.IV.Phi];
		}

		Instruction* PreheaderTerm = Preheader->GetTerminator();
		if (BranchInst* Branch = dyn_cast<BranchInst>(PreheaderTerm))
		{
			if (Branch->IsUnconditional())
			{
				Branch->SetTrueTarget(ExitBlock);
			}
		}

		for (auto const& [OrigVal, NewVal] : CurrentValueMap)
		{
			if (Instruction* OrigInst = dyn_cast<Instruction>(OrigVal))
			{
				if (L->Contains(OrigInst))
				{
					std::vector<Use*> UsesToReplace;
					for (Use* U : OrigInst->Users())
					{
						if (Instruction* UserInst = dyn_cast<Instruction>(U->GetUser()))
						{
							if (!L->Contains(UserInst))
							{
								UsesToReplace.push_back(U);
							}
						}
					}
					for (Use* U : UsesToReplace)
					{
						U->Set(NewVal);
					}
				}
			}
		}

		for (PhiInst* ExitPhi : ExitBlock->PhiInsts())
		{
			for (Uint32 i = 0; i < ExitPhi->GetNumIncomingValues(); ++i)
			{
				BasicBlock* IncomingBB = ExitPhi->GetIncomingBlock(i);
				if (L->Contains(IncomingBB))
				{
					ExitPhi->SetIncomingBlock(i, Preheader);
				}
			}
		}

		std::vector<BasicBlock*> BlocksToRemove;
		for (BasicBlock* BB : L->GetBlocks())
		{
			BlocksToRemove.push_back(BB);
		}

		for (BasicBlock* BB : BlocksToRemove)
		{
			for (auto It = BB->begin(); It != BB->end(); )
			{
				Instruction& I = *It;
				++It;
				if (!I.IsUsed())
				{
					I.EraseFromParent();
				}
			}
		}

		for (BasicBlock* BB : BlocksToRemove)
		{
			LI.RemoveBlock(BB);
			BB->EraseFromParent();
		}

		return true;
	}

	Bool LoopUnrollPass::PartialUnroll(Loop* L, LoopUnrollAnalysis const& Analysis, Uint32 Factor, Function& F)
	{
		if (Factor <= 1)
		{
			return false;
		}

		BasicBlock* Header = Analysis.Header;
		BasicBlock* Latch = Analysis.Latch;

		std::unordered_map<PhiInst*, Value*> PhiLatchValues;
		for (PhiInst* Phi : Header->PhiInsts())
		{
			for (Uint32 i = 0; i < Phi->GetNumIncomingValues(); ++i)
			{
				BasicBlock* IncomingBB = Phi->GetIncomingBlock(i);
				if (L->Contains(IncomingBB))
				{
					PhiLatchValues[Phi] = Phi->GetIncomingValue(i);
					break;
				}
			}
		}

		std::unordered_map<Value*, Value*> CurrentMap;
		for (PhiInst* Phi : Header->PhiInsts())
		{
			CurrentMap[Phi] = Phi;
		}

		for (Uint32 Iter = 1; Iter < Factor; ++Iter)
		{
			for (PhiInst* Phi : Header->PhiInsts())
			{
				Value* LatchVal = PhiLatchValues[Phi];
				auto It = CurrentMap.find(LatchVal);
				if (It != CurrentMap.end())
				{
					CurrentMap[Phi] = It->second;
				}
				else
				{
					CurrentMap[Phi] = LatchVal;
				}
			}

			for (BasicBlock* BB : L->GetBlocks())
			{
				for (Instruction& OrigInst : *BB)
				{
					if (isa<PhiInst>(&OrigInst))
					{
						continue;
					}
					if (OrigInst.IsTerminator())
					{
						continue;
					}
					if (&OrigInst == Analysis.ExitCond.Compare)
					{
						continue;
					}

					Instruction* NewInst = OrigInst.Clone();
					if (!NewInst)
					{
						continue;
					}

					for (Uint32 j = 0; j < NewInst->GetNumOperands(); ++j)
					{
						Value* Op = NewInst->GetOperand(j);
						auto It = CurrentMap.find(Op);
						if (It != CurrentMap.end())
						{
							NewInst->SetOperand(j, It->second);
						}
					}

					NewInst->InsertBefore(Latch, Latch->GetTerminator());
					CurrentMap[&OrigInst] = NewInst;
				}
			}
		}

		for (PhiInst* Phi : Header->PhiInsts())
		{
			Value* OrigLatchVal = PhiLatchValues[Phi];
			auto It = CurrentMap.find(OrigLatchVal);
			Value* FinalVal = (It != CurrentMap.end()) ? It->second : OrigLatchVal;

			for (Uint32 i = 0; i < Phi->GetNumIncomingValues(); ++i)
			{
				BasicBlock* IncomingBB = Phi->GetIncomingBlock(i);
				if (L->Contains(IncomingBB))
				{
					Phi->SetIncomingValue(i, FinalVal);
					break;
				}
			}
		}

		Value* FinalIV = CurrentMap[Analysis.IV.StepInst];
		if (FinalIV)
		{
			for (Uint32 i = 0; i < Analysis.ExitCond.Compare->GetNumOperands(); ++i)
			{
				Value* Op = Analysis.ExitCond.Compare->GetOperand(i);
				if (Op == Analysis.IV.Phi || Op == Analysis.IV.StepInst)
				{
					Analysis.ExitCond.Compare->SetOperand(i, FinalIV);
					break;
				}
			}
		}

		return true;
	}

	std::unordered_map<Value*, Value*> LoopUnrollPass::CloneLoopBody(
		Loop* L,
		BasicBlock* InsertBefore,
		std::unordered_map<Value*, Value*> const& ValueMap,
		Function& F)
	{
		std::unordered_map<Value*, Value*> NewValueMap = ValueMap;

		for (BasicBlock* BB : L->GetBlocks())
		{
			for (Instruction& OrigInst : *BB)
			{
				if (isa<PhiInst>(&OrigInst) || OrigInst.IsTerminator())
				{
					continue;
				}

				Instruction* NewInst = OrigInst.Clone();
				if (!NewInst)
				{
					continue;
				}

				for (Uint32 i = 0; i < NewInst->GetNumOperands(); ++i)
				{
					Value* Op = NewInst->GetOperand(i);
					auto It = NewValueMap.find(Op);
					if (It != NewValueMap.end())
					{
						NewInst->SetOperand(i, It->second);
					}
				}

				NewInst->InsertBefore(InsertBefore, InsertBefore->GetTerminator());
				NewValueMap[&OrigInst] = NewInst;
			}
		}

		return NewValueMap;
	}

	Bool LoopUnrollPass::CanCloneInstruction(Instruction const* I)
	{
		if (isa<AllocaInst>(I))
		{
			return false;
		}
		return true;
	}

	Bool LoopUnrollPass::IsSafeToUnroll(Loop* L) const
	{
		BasicBlock* ExitingBlock = L->GetExitingBlock();
		for (BasicBlock* BB : L->GetBlocks())
		{
			if (BB != ExitingBlock)
			{
				Instruction* Term = BB->GetTerminator();
				BranchInst* Branch = dyn_cast<BranchInst>(Term);
				if (!Branch || Branch->IsConditional())
				{
					return false;
				}
			}

			for (Instruction& I : *BB)
			{
				if (isa<AllocaInst>(&I))
				{
					return false;
				}
			}
		}

		if (!L->IsInnermost())
		{
			return false;
		}

		return true;
	}

	Uint32 LoopUnrollPass::EstimateLoopSize(Loop* L) const
	{
		Uint32 Size = 0;
		for (BasicBlock* BB : L->GetBlocks())
		{
			for (Instruction& I : *BB)
			{
				if (!isa<PhiInst>(&I) && !I.IsTerminator())
				{
					++Size;
				}
			}
		}
		return Size;
	}
}
