#include <vector>
#include "ArithmeticStrengthReductionPass.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRBuilder.h"
#include "Backend/Custom/IR/IRContext.h"

namespace ola
{
	inline Bool IsPowerOfTwo(Sint64 n)
	{
		return (n > 0) && ((n & (n - 1)) == 0);
	}
	inline Sint64 FindPowerOfTwo(Sint64 value)
	{
		Sint64 num = 0;
		while (value > 1)
		{
			value /= 2;
			num++;
		}
		return num;
	}

	static void TryReducingMul(BinaryInst* BI, std::vector<Instruction*>& instructions_to_remove)
	{
		ConstantInt* left_op = dyn_cast<ConstantInt>(BI->LHS());
		ConstantInt* right_op = dyn_cast<ConstantInt>(BI->RHS());
		
		IRContext& ctx = BI->GetContext();
		IRBuilder builder(ctx);
		builder.SetInsertPoint(BI->GetBasicBlock(), BI);
		if (left_op && IsPowerOfTwo(left_op->GetValue()))
		{
			Sint64 logOfPowerOf2 = FindPowerOfTwo(left_op->GetValue());
			Value* new_inst = builder.MakeInst<BinaryInst>(Opcode::Shl, BI->RHS(), ctx.GetInt64(logOfPowerOf2));
			BI->ReplaceAllUseWith(new_inst);
			instructions_to_remove.push_back(BI);
		}
		else if (right_op && IsPowerOfTwo(right_op->GetValue()))
		{
			Sint64 logOfPowerOf2 = FindPowerOfTwo(right_op->GetValue());
			Value* new_inst = builder.MakeInst<BinaryInst>(Opcode::Shl, BI->LHS(), ctx.GetInt64(logOfPowerOf2));
			BI->ReplaceAllUseWith(new_inst);
			instructions_to_remove.push_back(BI);
		}
	}
	static void TryReducingDiv(BinaryInst* BI, std::vector<Instruction*>& instructions_to_remove)
	{
		ConstantInt* right_op = dyn_cast<ConstantInt>(BI->RHS());

		IRContext& ctx = BI->GetContext();
		IRBuilder builder(ctx);
		builder.SetInsertPoint(BI->GetBasicBlock(), BI);
		if (right_op && IsPowerOfTwo(right_op->GetValue()))
		{
			Sint64 logOfPowerOf2 = FindPowerOfTwo(right_op->GetValue());
			Value* new_inst = builder.MakeInst<BinaryInst>(Opcode::AShr, BI->LHS(), ctx.GetInt64(logOfPowerOf2));
			BI->ReplaceAllUseWith(new_inst);
			instructions_to_remove.push_back(BI);
		}
	}

	Bool ArithmeticStrengthReductionPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
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
