#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include "GlobalValueNumberingPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "DominanceFrontierAnalysisPass.h"
#include "CFGAnalysisPass.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Utility/Hash.h"

namespace ola
{
	namespace
	{
		BasicBlock* FindLCA(DominatorTree const& DT, BasicBlock* A, BasicBlock* B)
		{
			if (!A) return B;
			if (!B) return A;
			if (A == B) return A;

			auto nodeA = DT.GetTreeNode(A);
			auto nodeB = DT.GetTreeNode(B);
			if (!nodeA || !nodeB) 
			{
				return nullptr;
			}

			for (auto curr = nodeA; curr; curr = DT.GetImmediateDominator(curr))
			{
				if (DT.Dominates(curr, nodeB))
				{
					return curr->GetBasicBlock();
				}
			}
			return nullptr;
		}

		Bool IsPureExpression(Instruction const* I)
		{
			if (I->IsTerminator()) return false;
			if (I->HasSideEffects()) return false;
			if (isa<LoadInst>(I)) return false;
			if (isa<PhiInst>(I)) return false;
			return true;
		}

		struct ExpressionHasher
		{
			std::unordered_map<Value*, Uint64> const& ValueNumbers;

			Uint64 operator()(Instruction const* I) const
			{
				HashState hash{};
				hash.Combine(I->GetOpcode());
				hash.Combine(reinterpret_cast<Uint64>(I->GetType()));
				std::vector<Uint64> operand_vns;
				for (Uint32 i = 0; i < I->GetNumOperands(); ++i)
				{
					if (Value* op = I->GetOperand(i))
					{
						auto it = ValueNumbers.find(op);
						if (it != ValueNumbers.end())
						{
							operand_vns.push_back(it->second);
						}
						else
						{
							operand_vns.push_back(reinterpret_cast<Uint64>(op));
						}
					}
				}

				if (I->IsCommutative())
				{
					std::sort(operand_vns.begin(), operand_vns.end());
				}
				for (Uint64 vn : operand_vns)
				{
					hash.Combine(vn);
				}
				return hash;
			}
		};

		Bool ExpressionsEqual(Instruction const* A, Instruction const* B,
			std::unordered_map<Value*, Uint64> const& ValueNumbers)
		{
			if (A->GetOpcode() != B->GetOpcode()) return false;
			if (A->GetType() != B->GetType()) return false;
			if (A->GetNumOperands() != B->GetNumOperands()) return false;

			for (Uint32 i = 0; i < A->GetNumOperands(); ++i)
			{
				Value* opA = A->GetOperand(i);
				Value* opB = B->GetOperand(i);
				if (opA == opB) continue;

				auto itA = ValueNumbers.find(opA);
				auto itB = ValueNumbers.find(opB);
				if (itA == ValueNumbers.end() || itB == ValueNumbers.end()) return false;
				if (itA->second != itB->second) return false;
			}
			return true;
		}
	}

	Bool GlobalValueNumberingPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		DominatorTree const& DT = FAM.GetResult<DominatorTreeAnalysisPass>(F);
		Bool Changed = false;

		std::vector<BasicBlock*> blocks;
		DT.VisitReversePostOrder([&](DominatorTreeNode const* node) -> Bool
			{
				blocks.push_back(node->GetBasicBlock());
				return true;
			});

		std::unordered_map<Value*, Uint64> ValueNumbers;
		Uint64 NextVN = 0;
		auto AssignVN = [&](Value* V) -> Uint64
			{
				if (auto it = ValueNumbers.find(V); it != ValueNumbers.end())
				{
					return it->second;
				}
				Uint64 vn = NextVN++;
				ValueNumbers[V] = vn;
				return vn;
			};

		for (auto ArgIt = F.ArgBegin(); ArgIt != F.ArgEnd(); ++ArgIt)
		{
			AssignVN(*ArgIt);
		}

		for (BasicBlock* BB : blocks)
		{
			AssignVN(BB);
			for (Instruction& I : *BB)
			{
				AssignVN(&I);
				for (Uint32 i = 0; i < I.GetNumOperands(); ++i)
				{
					if (Value* op = I.GetOperand(i))
					{
						AssignVN(op);
					}
				}
			}
		}

		std::vector<Instruction*> ToErase;
		ExpressionHasher hasher{ ValueNumbers };
		// hash -> list of (vn, set of equivalent instructions)
		std::unordered_map<Uint64, std::vector<std::pair<Uint64, std::vector<Instruction*>>>> ExprGroups;

		for (BasicBlock* BB : blocks)
		{
			for (Instruction& I : *BB)
			{
				if (!IsPureExpression(&I)) 
				{
					continue;
				}

				Uint64 hash = hasher(&I);
				auto& groups = ExprGroups[hash];

				Bool found = false;
				for (auto& [vn, insts] : groups)
				{
					if (!insts.empty() && ExpressionsEqual(&I, insts.front(), ValueNumbers))
					{
						insts.push_back(&I);
						found = true;
						break;
					}
				}
				if (!found)
				{
					Uint64 vn = AssignVN(&I);
					groups.push_back({ vn, { &I } });
				}
			}
		}

		for (auto& [hash, groups] : ExprGroups)
		{
			for (auto& [vn, instructions] : groups)
			{
				if (instructions.size() <= 1) 
				{
					continue;
				}

				BasicBlock* lca = nullptr;
				for (Instruction* I : instructions)
				{
					lca = FindLCA(DT, lca, I->GetBasicBlock());
				}
				if (!lca)
				{
					continue;
				}

				// Find representative: pick the earliest instruction in program order
				// that's in the LCA block (to avoid use-before-def issues)
				Instruction* representative = nullptr;
				for (Instruction& LcaInst : *lca)
				{
					for (Instruction* I : instructions)
					{
						if (I == &LcaInst)
						{
							representative = I;
							break;
						}
					}
					if (representative) break;
				}

				if (!representative)
				{
					for (Instruction* I : instructions)
					{
						Bool dominates_all = true;
						for (Instruction* other : instructions)
						{
							if (I != other && !DT.Dominates(I->GetBasicBlock(), other->GetBasicBlock()))
							{
								dominates_all = false;
								break;
							}
						}
						if (dominates_all)
						{
							representative = I;
							break;
						}
					}
				}

				if (!representative) 
				{
					continue;
				}

				for (Instruction* I : instructions)
				{
					if (I != representative)
					{
						I->ReplaceAllUsesWith(representative);
						ToErase.push_back(I);
						Changed = true;
					}
				}
			}
		}

		std::unordered_map<Uint64, Instruction*> PhiExpressions;
		for (BasicBlock* BB : blocks)
		{
			for (Instruction& I : *BB)
			{
				if (I.GetOpcode() != Opcode::Phi) 
				{
					continue;
				}
				if (std::find(ToErase.begin(), ToErase.end(), &I) != ToErase.end()) continue;

				Instruction* Phi = &I;

				std::vector<std::pair<Uint64, Uint64>> operand_block_pairs;
				for (Uint32 i = 0; i < Phi->GetNumOperands(); i += 2)
				{
					Value* value_op = Phi->GetOperand(i);
					Value* block_op = Phi->GetOperand(i + 1);

					if (value_op && block_op && isa<BasicBlock>(block_op))
					{
						Uint64 val_vn = AssignVN(value_op);
						Uint64 block_vn = AssignVN(block_op);
						operand_block_pairs.push_back({ val_vn, block_vn });
					}
				}

				std::sort(operand_block_pairs.begin(), operand_block_pairs.end());

				HashState hash{};
				hash.Combine(Opcode::Phi);
				for (auto const& [val_vn, block_vn] : operand_block_pairs)
				{
					hash.Combine(val_vn);
					hash.Combine(block_vn);
				}
				Uint64 expr_hash = hash;

				auto it = PhiExpressions.find(expr_hash);
				if (it != PhiExpressions.end())
				{
					Instruction* existing = it->second;
					if (DT.Dominates(existing->GetBasicBlock(), BB))
					{
						Phi->ReplaceAllUsesWith(existing);
						ToErase.push_back(Phi);
						Changed = true;
					}
				}
				else
				{
					PhiExpressions[expr_hash] = Phi;
				}
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
