#include <unordered_map>
#include "GlobalValueNumberingPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "DominanceFrontierAnalysisPass.h"
#include "CFGAnalysisPass.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Utility/Hash.h"

namespace ola
{
	Bool GlobalValueNumberingPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		DominatorTree const& DT = FAM.GetResult<DominatorTreeAnalysisPass>(F);
		CFG const& cfg = FAM.GetResult<CFGAnalysisPass>(F);

		Bool Changed = false;
		std::unordered_map<Value*, Uint64> ValueNumberMap;
		std::unordered_map<Uint64, Value*> NumberValueMap;
		Uint64 NextVN = 0;

		std::unordered_map<Uint64, Uint64> ExpressionNumberMap; 
		auto AssignNewVN = [&](Value* V) -> Uint64 
		{
			Uint64 vn = NextVN++;
			ValueNumberMap[V] = vn;
			NumberValueMap[vn] = V;
			return vn;
		};

		for (auto ArgIt = F.ArgBegin(); ArgIt != F.ArgEnd(); ++ArgIt) 
		{
			AssignNewVN(*ArgIt);
		}

		auto AssignConstantVN = [&](Constant* C) -> Uint64
		{
			if (auto it = ValueNumberMap.find(C); it != ValueNumberMap.end())
			{
				return it->second;
			}
			return AssignNewVN(C);
		};

		std::vector<BasicBlock*> blocks;
		OLA_TODO("Why does this have only 2 blocks for test?");
		DT.VisitReversePostOrder([&](DominatorTreeNode const* node) -> Bool 
		{
			blocks.push_back(node->GetBasicBlock());
			return true;
		});
		
		for (BasicBlock* BB : blocks) 
		{
			for (Instruction& I : *BB) 
			{
				for (Uint32 i = 0; i < I.GetNumOperands(); ++i) 
				{
					if (Value* op = I.GetOperand(i)) 
					{
						if (Constant* C = dyn_cast<Constant>(op); C && !ValueNumberMap.contains(C))
						{
							AssignConstantVN(C);

						}
					}
				}

				if (I.IsTerminator() || I.HasSideEffects()) 
				{
					AssignNewVN(&I);
					continue;
				}

				std::vector<Uint64> operand_vns;
				for (Uint32 i = 0; i < I.GetNumOperands(); ++i) 
				{
					if (Value* op = I.GetOperand(i))
					{
						auto it = ValueNumberMap.find(op);
						OLA_ASSERT(it != ValueNumberMap.end() && "Operand VN not assigned!");
						operand_vns.push_back(it->second);
					}
				}
				if (I.GetOpcode() != Opcode::Phi && I.IsCommutative())
				{
					std::sort(operand_vns.begin(), operand_vns.end());
				}

				HashState hash{};
				hash.Combine(I.GetOpcode());
				for (Uint64 ovn : operand_vns) 
				{
					hash.Combine(ovn);
				}
				Uint64 expr_hash = hash;
				auto it = ExpressionNumberMap.find(expr_hash);
				if (it != ExpressionNumberMap.end())
				{
					Uint64 existing_vn = it->second;
					Value* existing_value = NumberValueMap[existing_vn];
					I.ReplaceAllUsesWith(existing_value);
					I.EraseFromParent();
					Changed = true;
				}
				else 
				{
					Uint64 new_vn = AssignNewVN(&I);
					ExpressionNumberMap[expr_hash] = new_vn;
				}
			}
		}
		if (Changed) 
		{
			FAM.InvalidateCache<CFGAnalysisPass>(F);
			FAM.InvalidateCache<DominatorTreeAnalysisPass>(F);
			FAM.InvalidateCache<DominanceFrontierAnalysisPass>(F);
		}

		return Changed;
	}
}