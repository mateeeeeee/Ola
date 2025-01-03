#include <vector>
#include "ArithmeticReductionPass.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRBuilder.h"
#include "Backend/Custom/IR/IRContext.h"

namespace ola
{
	inline Bool IsPowerOfTwo(Int64 n)
	{
		return (n > 0) && ((n & (n - 1)) == 0);
	}
	inline Int64 FindPowerOfTwo(Int64 value)
	{
		Int64 num = 0;
		while (value > 1)
		{
			value /= 2;
			num++;
		}
		return num;
	}

	static void TryReducingMul(BinaryInst* BI, std::vector<Instruction*>& instructions_to_remove)
	{
		ConstantInt* left_op = dyn_cast<ConstantInt>(BI->GetLHS());
		ConstantInt* right_op = dyn_cast<ConstantInt>(BI->GetRHS());
		
		IRContext& ctx = BI->GetContext();
		IRBuilder builder(ctx);
		builder.SetInsertPoint(BI->GetBasicBlock(), BI);
		if (left_op && IsPowerOfTwo(left_op->GetValue()))
		{
			Int64 logOfPowerOf2 = FindPowerOfTwo(left_op->GetValue());
			Value* new_inst = builder.MakeInst<BinaryInst>(Opcode::Shl, BI->GetRHS(), ctx.GetInt64(logOfPowerOf2));
			BI->ReplaceAllUsesWith(new_inst);
			instructions_to_remove.push_back(BI);
		}
		else if (right_op && IsPowerOfTwo(right_op->GetValue()))
		{
			Int64 logOfPowerOf2 = FindPowerOfTwo(right_op->GetValue());
			Value* new_inst = builder.MakeInst<BinaryInst>(Opcode::Shl, BI->GetLHS(), ctx.GetInt64(logOfPowerOf2));
			BI->ReplaceAllUsesWith(new_inst);
			instructions_to_remove.push_back(BI);
		}
	}
	static void TryReducingDiv(BinaryInst* BI, std::vector<Instruction*>& instructions_to_remove)
	{
		ConstantInt* right_op = dyn_cast<ConstantInt>(BI->GetRHS());

		IRContext& ctx = BI->GetContext();
		IRBuilder builder(ctx);
		builder.SetInsertPoint(BI->GetBasicBlock(), BI);
		if (right_op && IsPowerOfTwo(right_op->GetValue()))
		{
			Int64 logOfPowerOf2 = FindPowerOfTwo(right_op->GetValue());
			Value* new_inst = builder.MakeInst<BinaryInst>(Opcode::AShr, BI->GetLHS(), ctx.GetInt64(logOfPowerOf2));
			BI->ReplaceAllUsesWith(new_inst);
			instructions_to_remove.push_back(BI);
		}
	}
	static void TryReducingMod(BinaryInst* BI, std::vector<Instruction*>& instructions_to_remove)
	{
		ConstantInt* right_op = dyn_cast<ConstantInt>(BI->GetRHS());
		IRContext& ctx = BI->GetContext();
		IRBuilder builder(ctx);
		builder.SetInsertPoint(BI->GetBasicBlock(), BI);
		if (right_op && IsPowerOfTwo(right_op->GetValue()))
		{
			Int64 mask = right_op->GetValue() - 1;
			Value* new_inst = builder.MakeInst<BinaryInst>(Opcode::And, BI->GetLHS(), ctx.GetInt64(mask));
			BI->ReplaceAllUsesWith(new_inst);
			instructions_to_remove.push_back(BI);
		}
	}
	Bool ArithmeticReductionPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		Bool changed = false;
		std::vector<Instruction*> instructions_to_remove;

		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB.Instructions())
			{
				if (BinaryInst* BI = dyn_cast<BinaryInst>(&I))
				{
					if (BI->GetOpcode() == Opcode::SMul)
					{
						TryReducingMul(BI, instructions_to_remove);
					}
					else if (BI->GetOpcode() == Opcode::SDiv)
					{
						TryReducingDiv(BI, instructions_to_remove);
					}
					else if (BI->GetOpcode() == Opcode::SRem)
					{
						TryReducingMod(BI, instructions_to_remove);
					}
				}
			}
		}
		for (Instruction* I : instructions_to_remove)
		{
			I->EraseFromParent();
			changed = true;
		}
		return changed;
	}

}
