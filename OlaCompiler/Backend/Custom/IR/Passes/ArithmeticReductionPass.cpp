#include <vector>
#include "ArithmeticReductionPass.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRBuilder.h"
#include "Backend/Custom/IR/IRContext.h"
#include "Backend/Custom/IR/PatternMatch.h"

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

	Bool ArithmeticReductionPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		Bool changed = false;
		std::vector<Instruction*> instructions_to_remove;

		auto SwapOperands = [](Instruction& I) -> Bool
		{
			switch (I.GetOpcode())
			{
			case Opcode::Add:
			case Opcode::SMul:
			case Opcode::Or:
			case Opcode::Xor:
			case Opcode::And:
			case Opcode::FAdd:
			case Opcode::FMul:
			{
				if (I.GetOperand(0)->IsConstant() && !I.GetOperand(1)->IsConstant())
				{
					I.SwapOperands(0, 1);
					return true;
				}
			}
			}
			return false;
		};
		auto ReplaceInstruction = [&changed, &instructions_to_remove](Instruction& I, Value* V)
		{
			I.ReplaceAllUsesWith(V);
			instructions_to_remove.push_back(&I);
		};

		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB.Instructions())
			{
				changed |= SwapOperands(I);

				IRBuilder builder(I.GetContext());
				builder.SetInsertPoint(I.GetBasicBlock(), &I);

				PatternMatchContext<Value> ctx(&I);
				Value* V = nullptr;
				Int64 i = 0;
				Float64 f = 0.0;
				if (Add_(Any_(V), CInt_(0))(ctx))
				{
					ReplaceInstruction(I, V);
				}
				else if (FAdd_(Any_(V), CFloat_(0.0))(ctx))
				{
					ReplaceInstruction(I, V);
				}
				else if (Sub_(Any_(V), CInt_(0))(ctx))
				{
					ReplaceInstruction(I, V);
				}
				else if (FSub_(Any_(V), CFloat_(0.0))(ctx))
				{
					ReplaceInstruction(I, V);
				}
				else if (Sub_(CInt_(0), Any_(V))(ctx))
				{
					ReplaceInstruction(I, builder.MakeInst<UnaryInst>(Opcode::Neg, V));
				}
				else if (FSub_(CFloat_(0.0), Any_(V))(ctx))
				{
					ReplaceInstruction(	I, builder.MakeInst<UnaryInst>(Opcode::FNeg, V));
				}
				else if (Sub_(Any_(V), Exact_(V))(ctx))
				{
					ReplaceInstruction(I, I.GetContext().GetInt64(0));
				}
				else if (FSub_(Any_(V), Exact_(V))(ctx))
				{
					ReplaceInstruction(I, I.GetContext().GetZeroFloat());
				}
				else if (Mul_(Any_(V), CInt_(0))(ctx))
				{
					ReplaceInstruction(I, I.GetContext().GetInt64(0));
				}
				else if (FMul_(Any_(V), CFloat_(0.0))(ctx))
				{
					ReplaceInstruction(I, I.GetContext().GetZeroFloat());
				}
				else if (Mul_(Any_(V), CInt_(1))(ctx))
				{
					ReplaceInstruction(I, V);
				}
				else if (FMul_(Any_(V), CFloat_(1.0))(ctx))
				{
					ReplaceInstruction(I, V);
				}
				else if (Mul_(Any_(V), CInt_(2))(ctx))
				{
					ReplaceInstruction(I, builder.MakeInst<BinaryInst>(Opcode::Add, V, V));
				}
				else if (FMul_(Any_(V), CFloat_(2.0))(ctx))
				{
					ReplaceInstruction(I, builder.MakeInst<BinaryInst>(Opcode::FAdd, V, V));
				}
				else if (Mul_(Any_(V), CInt_(-1))(ctx))
				{
					ReplaceInstruction(I, builder.MakeInst<UnaryInst>(Opcode::Neg, V));
				}
				else if (FMul_(Any_(V), CFloat_(-1.0))(ctx))
				{
					ReplaceInstruction(I, builder.MakeInst<UnaryInst>(Opcode::FNeg, V));
				}
				else if (SDiv_(Any_(V), Exact_(V))(ctx))
				{
					ReplaceInstruction(I, I.GetContext().GetInt64(1));
				}
				else if (FDiv_(Any_(V), Exact_(V))(ctx))
				{
					ReplaceInstruction(I, I.GetContext().GetFloat(0));
				}
				else if (SDiv_(Any_(V), CInt_(1))(ctx))
				{
					ReplaceInstruction(I, V);
				}
				else if (FDiv_(Any_(V), CFloat_(0.0))(ctx))
				{
					ReplaceInstruction(I, V);
				}
				else if (Mul_(Any_(V), Int_(i))(ctx))
				{
					if (IsPowerOfTwo(i))
					{
						Int64 const shift = FindPowerOfTwo(i);
						ReplaceInstruction(I, builder.MakeInst<BinaryInst>(Opcode::Shl, V, I.GetContext().GetInt64(shift)));
					}
				}
				else if (SDiv_(Any_(V), Int_(i))(ctx))
				{
					if (IsPowerOfTwo(i))
					{
						Int64 const shift = FindPowerOfTwo(i);
						ReplaceInstruction(I, builder.MakeInst<BinaryInst>(Opcode::AShr, V, I.GetContext().GetInt64(shift)));
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
