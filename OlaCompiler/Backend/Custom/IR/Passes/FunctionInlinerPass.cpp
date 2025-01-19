#include <unordered_map>
#include "FunctionInlinerPass.h"
#include "CFGAnalysisPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRBuilder.h"
#include "Backend/Custom/IR/IRContext.h"
#include "Core/Log.h"

namespace ola
{
	Bool FunctionInlinerPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		Bool Changed = false;
		std::vector<CallInst*> CallsToInline;
		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB)
			{
				if (CallInst* CI = dyn_cast<CallInst>(&I))
				{
					if (ShouldInline(CI)) CallsToInline.push_back(CI);
				}
			}
		}
		for (CallInst* CI : CallsToInline)
		{
			if (InlineFunction(CI))
			{
				Changed = true;
			}
		}

		if (Changed)
		{
			FAM.InvalidateCache<CFGAnalysisPass>(F);
			FAM.InvalidateCache<DominatorTreeAnalysisPass>(F);
		}
		return Changed;
	}

	Bool FunctionInlinerPass::ShouldInline(CallInst* CI)
	{
		Function* Callee = CI->GetCalleeAsFunction(); 
		if (!Callee || Callee->IsDeclaration()) return false;
		if (CI->GetBasicBlock()->GetFunction() == Callee) return false;
		if (Callee->IsNoInline())  return false;
		return (Callee->Blocks().Size() <= 3) || Callee->IsForceInline();
	}

	Bool FunctionInlinerPass::InlineFunction(CallInst* CI)
	{
		IRContext& Ctx = CI->GetContext();
		IRBuilder Builder(Ctx);
		Function* Callee = CI->GetCalleeAsFunction();
		BasicBlock* CallBlock = CI->GetBasicBlock();
		Function* Caller = CI->GetCaller();

		std::unordered_map<Value*, Value*> ValueMap;
		auto ArgIt = Callee->ArgBegin();
		for (Uint32 i = 0; i < CI->GetNumOperands() - 1; ++i, ++ArgIt)
		{
			ValueMap[*ArgIt] = CI->GetOperand(i);
		}

		std::unordered_map<BasicBlock*, BasicBlock*> BBMap;
		for (BasicBlock& BB : *Callee)
		{
			std::string name(BB.GetName());
			name += ".inlined";
			BasicBlock* InlinedBB = Builder.AddBlock(Caller, CallBlock->GetNextNode(), name);
			BBMap[&BB] = InlinedBB;
			Builder.SetCurrentBlock(InlinedBB);
			for (Instruction& I : BB)
			{
				if (!isa<ReturnInst>(&I))
				{
					Instruction* NewInst = Builder.CloneInst(&I);
					ValueMap[&I] = NewInst;
				}
			}
		}

		for (auto& [OrigBB, NewBB] : BBMap)
		{
			for (Instruction& NewInst : *NewBB)
			{
				if (BranchInst* BI = dyn_cast<BranchInst>(&NewInst))
				{
					BasicBlock* TrueTarget = BI->GetTrueTarget();
					BasicBlock* FalseTarget = BI->GetFalseTarget();
					BI->SetTrueTarget(BBMap[TrueTarget]);
					if (FalseTarget != nullptr)
					{
						BI->SetFalseTarget(BBMap[FalseTarget]);
					}
					continue;
				}
				for (Uint32 i = 0; i < NewInst.GetNumOperands(); ++i)
				{
					Value* Op = NewInst.GetOperand(i);
					{
						if (Op->IsConstant()) NewInst.SetOperand(i, Op);
						else
						{
							OLA_ASSERT(ValueMap[Op]);
							NewInst.SetOperand(i, ValueMap[Op]);
						}
					}
				}
			}
		}

		BasicBlock* CallBlockRemainder = CallBlock->SplitBasicBlock(CI->GetNextNode());
		CallBlock->GetTerminator()->EraseFromParent();

		Builder.SetCurrentBlock(CallBlock);
		Builder.MakeInst<BranchInst>(Ctx, BBMap[&Callee->GetEntryBlock()]);
		for (BasicBlock& BB : *Callee)
		{
			if (ReturnInst* RI = dyn_cast<ReturnInst>(BB.GetTerminator()))
			{
				BasicBlock* InlinedBB = BBMap[&BB];
				Builder.SetCurrentBlock(InlinedBB);
				if (InlinedBB->GetTerminator() && InlinedBB->GetTerminator()->GetOpcode() == Opcode::Ret) InlinedBB->GetTerminator()->EraseFromParent();

				if (!RI->IsVoid())
				{
					Value* RetVal = RI->GetReturnValue();
					Value* MappedRetVal = ValueMap[RetVal];
					if (MappedRetVal) CI->ReplaceAllUsesWith(MappedRetVal);
					else CI->ReplaceAllUsesWith(RetVal);
				}
				Builder.MakeInst<BranchInst>(Ctx, CallBlockRemainder);
			}
		}
		CI->EraseFromParent();
		return true;
	}
}
