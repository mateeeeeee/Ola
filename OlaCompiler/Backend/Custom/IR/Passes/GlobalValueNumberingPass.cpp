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

		// First pass: assign value numbers to all phi nodes
		for (BasicBlock* BB : blocks)
		{
			for (Instruction& I : *BB)
			{
				if (I.GetOpcode() == Opcode::Phi)
				{
					AssignNewVN(&I);
				}
			}
		}

		std::vector<Instruction*> ToErase;
		for (BasicBlock* BB : blocks)
		{
			for (Instruction& I : *BB)
			{
				if (I.GetOpcode() == Opcode::Phi)
				{
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
				hash.Combine(reinterpret_cast<Uint64>(I.GetType()));
				if (I.GetOpcode() == Opcode::Load)
				{
					Value* ptr = I.GetOperand(0);
					if (ptr)
					{
						auto store_it = LastStoreToMemory.find(ptr);
						if (store_it != LastStoreToMemory.end())
						{
							auto store_vn_it = ValueNumberMap.find(store_it->second);
							if (store_vn_it != ValueNumberMap.end())
							{
								hash.Combine(store_vn_it->second);
							}
						}
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

					if (existing_value->GetType() != I.GetType())
					{
						Uint64 new_vn = AssignNewVN(&I);
						ExpressionNumberMap[expr_hash] = new_vn;
						continue;
					}

					if (Instruction* existing_inst = dyn_cast<Instruction>(existing_value))
					{
						if (!DT.Dominates(existing_inst->GetBasicBlock(), BB) || existing_inst->GetNumOperands() != I.GetNumOperands())
						{
							Uint64 new_vn = AssignNewVN(&I);
							ExpressionNumberMap[expr_hash] = new_vn;
							continue;
						}

						Bool operands_match = true;
						for (Uint32 op_idx = 0; op_idx < I.GetNumOperands(); ++op_idx)
						{
							if (I.GetOperand(op_idx) != existing_inst->GetOperand(op_idx))
							{
								if (!ValueNumberMap.contains(I.GetOperand(op_idx)) || 
									!ValueNumberMap.contains(existing_inst->GetOperand(op_idx)))
								{
									operands_match = false;
									break;
								}

								Uint64 const vn1 = ValueNumberMap[I.GetOperand(op_idx)];
								Uint64 const vn2 = ValueNumberMap[existing_inst->GetOperand(op_idx)];
								if (vn1 != vn2)
								{
									operands_match = false;
									break;
								}
							}
						}
						if (!operands_match)
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

		for (BasicBlock* BB : blocks)
		{
			for (Instruction& I : *BB)
			{
				if (I.GetOpcode() != Opcode::Phi)
				{
					continue;
				}

				Instruction* Phi = &I;

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

				std::vector<std::pair<Uint64, Uint64>> operand_block_pairs;
				for (Uint32 i = 0; i < Phi->GetNumOperands(); i += 2)
				{
					Value* value_op = Phi->GetOperand(i);
					Value* block_op = Phi->GetOperand(i + 1);

					if (value_op && block_op && isa<BasicBlock>(block_op))
					{
						auto val_it = ValueNumberMap.find(value_op);
						auto block_it = ValueNumberMap.find(block_op);

						if (val_it == ValueNumberMap.end())
						{
							AssignNewVN(value_op);
							val_it = ValueNumberMap.find(value_op);
						}
						if (block_it == ValueNumberMap.end())
						{
							AssignNewVN(block_op);
							block_it = ValueNumberMap.find(block_op);
						}

						operand_block_pairs.push_back({ val_it->second, block_it->second });
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

				auto it = ExpressionNumberMap.find(expr_hash);
				if (it != ExpressionNumberMap.end())
				{
					Uint64 existing_vn = it->second;
					Value* existing_value = NumberValueMap[existing_vn];

					if (Instruction* existing_inst = dyn_cast<Instruction>(existing_value))
					{
						if (!DT.Dominates(existing_inst->GetBasicBlock(), BB))
						{
							Uint64 phi_vn = ValueNumberMap[Phi];
							ExpressionNumberMap[expr_hash] = phi_vn;
							continue;
						}
					}

					Uint64 phi_vn = ValueNumberMap[Phi];
					ValueNumberMap[Phi] = existing_vn;
					Phi->ReplaceAllUsesWith(existing_value);
					ToErase.push_back(Phi);
					Changed = true;
				}
				else
				{
					Uint64 phi_vn = ValueNumberMap[Phi];
					ExpressionNumberMap[expr_hash] = phi_vn;
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