#include <unordered_set>
#include "ConstantPropagationPass.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRBuilder.h"
#include "Backend/Custom/IR/IRContext.h"

namespace ola
{
	namespace
	{

		Constant* TryConstantFold_BinaryInst(BinaryInst* BI)
		{
			IRContext& ctx = BI->GetContext();

			Value* LHS = BI->GetLHS();
			Value* RHS = BI->GetRHS();

			ConstantInt* CI1 = dyn_cast<ConstantInt>(LHS);
			ConstantInt* CI2 = dyn_cast<ConstantInt>(RHS);
			if (CI1 && CI2)
			{
				switch (BI->GetOpcode())
				{
				case Opcode::Add:  return ctx.GetInt(LHS->GetType(), CI1->GetValue() + CI2->GetValue());
				case Opcode::Sub:  return ctx.GetInt(LHS->GetType(), CI1->GetValue() - CI2->GetValue());
				case Opcode::SMul: return ctx.GetInt(LHS->GetType(), CI1->GetValue() * CI2->GetValue());
				case Opcode::SDiv: return ctx.GetInt(LHS->GetType(), CI1->GetValue() / CI2->GetValue());
				case Opcode::Shl:  return ctx.GetInt(LHS->GetType(), CI1->GetValue() << CI2->GetValue());
				case Opcode::AShr: return ctx.GetInt(LHS->GetType(), CI1->GetValue() >> CI2->GetValue());
				}
			}

			ConstantFloat* CF1 = dyn_cast<ConstantFloat>(LHS);
			ConstantFloat* CF2 = dyn_cast<ConstantFloat>(RHS);
			if (CF1 && CF2)
			{
				OLA_ASSERT(LHS->GetType()->IsFloat());
				switch (BI->GetOpcode())
				{
				case Opcode::FAdd:  return ctx.GetFloat(CF1->GetValue() + CF2->GetValue());
				case Opcode::FSub:  return ctx.GetFloat(CF1->GetValue() - CF2->GetValue());
				case Opcode::FMul:  return ctx.GetFloat(CF1->GetValue() * CF2->GetValue());
				case Opcode::FDiv:  return ctx.GetFloat(CF1->GetValue() / CF2->GetValue());
				}
			}
			return nullptr;
		}
		Constant* TryConstantFold_UnaryInst(UnaryInst* UI)
		{
			IRContext& ctx = UI->GetContext();
			ConstantInt* CI = dyn_cast<ConstantInt>(UI->GetOperand());
			if (CI)
			{
				switch (UI->GetOpcode())
				{
				case Opcode::Neg:  return ctx.GetInt(UI->GetType(), -CI->GetValue());
				case Opcode::Not:  return ctx.GetInt(UI->GetType(), ~CI->GetValue());
				}
			}
			ConstantFloat* CF = dyn_cast<ConstantFloat>(UI->GetOperand());
			if (CF && UI->GetOpcode() == Opcode::Neg)
			{
				ctx.GetFloat(-CF->GetValue());
			}
			return nullptr;
		}
		Constant* TryConstantFold_CompareInst(CompareInst* CI)
		{
			IRContext& ctx = CI->GetContext();
			IRType* bool_type = IRIntType::Get(ctx, 1);

			ConstantInt* CI1 = dyn_cast<ConstantInt>(CI->GetLHS());
			ConstantInt* CI2 = dyn_cast<ConstantInt>(CI->GetRHS());
			if (CI1 && CI2)
			{
				switch (CI->GetOpcode())
				{
				case Opcode::ICmpEQ:  return ctx.GetInt(bool_type, CI1->GetValue() == CI2->GetValue());
				case Opcode::ICmpNE:  return ctx.GetInt(bool_type, CI1->GetValue() != CI2->GetValue());
				case Opcode::ICmpSGE: return ctx.GetInt(bool_type, CI1->GetValue() >= CI2->GetValue());
				case Opcode::ICmpSGT: return ctx.GetInt(bool_type, CI1->GetValue() > CI2->GetValue());
				case Opcode::ICmpSLE: return ctx.GetInt(bool_type, CI1->GetValue() <= CI2->GetValue());
				case Opcode::ICmpSLT: return ctx.GetInt(bool_type, CI1->GetValue() < CI2->GetValue());
				}
			}

			ConstantFloat* CF1 = dyn_cast<ConstantFloat>(CI->GetLHS());
			ConstantFloat* CF2 = dyn_cast<ConstantFloat>(CI->GetRHS());
			if (CF1 && CF2)
			{
				switch (CI->GetOpcode())
				{
				case Opcode::FCmpOEQ: return ctx.GetInt(bool_type, CF1->GetValue() == CF2->GetValue());
				case Opcode::FCmpONE: return ctx.GetInt(bool_type, CF1->GetValue() != CF2->GetValue());
				case Opcode::FCmpOGE: return ctx.GetInt(bool_type, CF1->GetValue() >= CF2->GetValue());
				case Opcode::FCmpOGT: return ctx.GetInt(bool_type, CF1->GetValue() > CF2->GetValue());
				case Opcode::FCmpOLE: return ctx.GetInt(bool_type, CF1->GetValue() <= CF2->GetValue());
				case Opcode::FCmpOLT: return ctx.GetInt(bool_type, CF1->GetValue() < CF2->GetValue());
				}
			}
			return nullptr;
		}
		Value* TryConstantFold_SelectInst(SelectInst* SI)
		{
			ConstantInt* CI = dyn_cast<ConstantInt>(SI->GetPredicate());
			if (CI)
			{
				return CI->GetValue() != 0 ? SI->GetTrueValue() : SI->GetFalseValue();
			}
			return nullptr;
		}
		BranchInst* TryConstantFold_BranchInst(BranchInst* BI)
		{
			if (Value* Condition = BI->GetCondition())
			{
				ConstantInt* CI = dyn_cast<ConstantInt>(Condition);
				if (CI)
				{
					IRContext& ctx = CI->GetContext();
					return CI->GetValue() != 0 ? new BranchInst(ctx, BI->GetTrueTarget()) : new BranchInst(ctx, BI->GetFalseTarget());
				}
			}
			return nullptr;
		}
		Value* TryConstantFold_Instruction(Instruction* I)
		{
			if (BinaryInst* BI = dyn_cast<BinaryInst>(I))
			{
				return TryConstantFold_BinaryInst(BI);
			}
			else if (UnaryInst* UI = dyn_cast<UnaryInst>(I))
			{
				return TryConstantFold_UnaryInst(UI);
			}
			else if (CompareInst* CI = dyn_cast<CompareInst>(I))
			{
				return TryConstantFold_CompareInst(CI);
			}
			else if (SelectInst* SI = dyn_cast<SelectInst>(I))
			{
				return TryConstantFold_SelectInst(SI);
			}
			return nullptr;
		}
	}

	Bool ConstantPropagationPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		std::unordered_set<Instruction*> WorkList;
		std::vector<Instruction*> WorkListVector;
		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB)
			{
				WorkList.insert(&I);
				WorkListVector.push_back(&I);
			}
		}

		Bool Changed = false;
		while (!WorkList.empty())
		{
			std::vector<Instruction*> NewWorkListVector;
			for (Instruction* I : WorkListVector)
			{
				WorkList.erase(I);
				if (!I->IsTerminator() && !I->HasNUsesOrMore(1)) continue;

				if (Value* V = TryConstantFold_Instruction(I))
				{
					for (Use* U : I->Users())
					{
						if (WorkList.insert(cast<Instruction>(U->GetUser())).second)
							NewWorkListVector.push_back(cast<Instruction>(U->GetUser()));
					}

					I->ReplaceAllUsesWith(V);
					if (!I->HasNUsesOrMore(1))
					{
						I->EraseFromParent();
					}
					Changed = true;
				}
				else if (BranchInst* BI = dyn_cast<BranchInst>(I))
				{
					if (BranchInst* BI2 = TryConstantFold_BranchInst(BI))
					{
						OLA_ASSERT(BI2->IsUnconditional());
						BI->SetCondition(nullptr);
						BI->SetTrueTarget(BI2->GetTrueTarget());
						BI->SetFalseTarget(nullptr);
						OLA_ASSERT(BI->IsUnconditional());
					}
				}
			}
			WorkListVector = std::move(NewWorkListVector);
		}
		return Changed;
	}
}