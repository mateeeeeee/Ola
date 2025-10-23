#include <unordered_map>
#include <map>
#include <vector>
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

		std::vector<BasicBlock*> blocks;
		DT.VisitReversePostOrder([&](DominatorTreeNode const* node) -> Bool
		{
			blocks.push_back(node->GetBasicBlock());
			return true;
		});

		std::unordered_map<Value*, Uint64> ValueNumberMap;
		std::unordered_map<Uint64, Value*> NumberValueMap;
		Uint64 NextVN = 0;
		std::unordered_map<Uint64, Uint64> ExpressionNumberMap;

		// Track the last store to each pointer
		std::unordered_map<Value*, Instruction*> LastStoreToMemory;

		auto AssignNewVN = [&](Value* V) -> Uint64
		{
			Uint64 vn = NextVN++;
			ValueNumberMap[V] = vn;
			NumberValueMap[vn] = V;
			return vn;
		};
		auto AssignConstantVN = [&](Constant* C) -> Uint64
		{
			if (auto it = ValueNumberMap.find(C); it != ValueNumberMap.end())
			{
				return it->second;
			}
			return AssignNewVN(C);
		};

		for (auto ArgIt = F.ArgBegin(); ArgIt != F.ArgEnd(); ++ArgIt)
		{
			AssignNewVN(*ArgIt);
		}

		std::vector<Instruction*> ToErase;
		std::vector<Instruction*> PhiNodes;
		for (BasicBlock* BB : blocks)
		{
			for (Instruction& I : *BB)
			{
				if (I.GetOpcode() == Opcode::Phi)
				{
					PhiNodes.push_back(&I);
					continue;
				}

				if (I.GetOpcode() == Opcode::Alloca)
				{
					AssignNewVN(&I);
					continue;
				}

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

				if (I.GetOpcode() == Opcode::Store)
				{
					Value* ptr = I.GetOperand(1);
					if (ptr)
					{
						LastStoreToMemory[ptr] = &I;
					}
					AssignNewVN(&I);
					continue;
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

				HashState hash{};
				hash.Combine(I.GetOpcode());
				if (I.GetOpcode() == Opcode::Load)
				{
					Value* ptr = I.GetOperand(0);
					if (ptr)
					{
						Instruction* last_store = LastStoreToMemory[ptr]; 
						hash.Combine(reinterpret_cast<Uintptr>(last_store));
					}
				}

				if (I.IsCommutative())
				{
					std::sort(operand_vns.begin(), operand_vns.end());
				}
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

					if (Instruction* existing_inst = dyn_cast<Instruction>(existing_value))
					{
						if (!DT.Dominates(existing_inst->GetBasicBlock(), BB))
						{
							Uint64 new_vn = AssignNewVN(&I);
							ExpressionNumberMap[expr_hash] = new_vn;
							continue;
						}
					}

					ValueNumberMap[&I] = existing_vn;
					I.ReplaceAllUsesWith(existing_value);
					ToErase.push_back(&I);
					Changed = true;
				}
				else
				{
					Uint64 new_vn = AssignNewVN(&I);
					ExpressionNumberMap[expr_hash] = new_vn;
				}
			}
		}

		for (Instruction* Phi : PhiNodes)
		{
			for (Uint32 i = 0; i < Phi->GetNumOperands(); ++i)
			{
				if (Value* op = Phi->GetOperand(i))
				{
					if (Constant* C = dyn_cast<Constant>(op); C && !ValueNumberMap.contains(C))
					{
						AssignConstantVN(C);
					}
				}
			}

			std::vector<Uint64> operand_vns;
			for (Uint32 i = 0; i < Phi->GetNumOperands(); ++i)
			{
				if (Value* op = Phi->GetOperand(i); op && !isa<BasicBlock>(op))
				{
					auto it = ValueNumberMap.find(op);
					OLA_ASSERT(it != ValueNumberMap.end() && "Phi operand VN not assigned!");
					operand_vns.push_back(it->second);
				}
			}

			HashState hash{};
			hash.Combine(Opcode::Phi);
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

				ValueNumberMap[Phi] = existing_vn;
				Phi->ReplaceAllUsesWith(existing_value);
				ToErase.push_back(Phi);
				Changed = true;
			}
			else
			{
				Uint64 new_vn = AssignNewVN(Phi);
				ExpressionNumberMap[expr_hash] = new_vn;
			}
		}

		for (Instruction* I : ToErase)
		{
			I->EraseFromParent();
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