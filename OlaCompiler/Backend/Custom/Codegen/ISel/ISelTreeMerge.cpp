#include "ISelTreeMerge.h"
#include "Utility/RTTI.h"

namespace ola
{
	void ISelTreeMerge::MergeTrees(ISelForest& forest)
	{
		reg_to_def.clear();
		use_counts.clear();

		BuildDefMap(forest);
		CountUses(forest);
		PerformMerge(forest);
	}

	void ISelTreeMerge::BuildDefMap(ISelForest& forest)
	{
		for (auto& tree : forest.Trees())
		{
			if (auto* reg = dyn_cast<ISelRegisterNode>(tree.get()))
			{
				MachineOperand const& op = reg->GetRegister();
				if (op.IsReg() && IsVirtualReg(op.GetReg().reg))
				{
					reg_to_def[op.GetReg().reg] = reg;
				}
			}
		}
	}

	void ISelTreeMerge::CountUses(ISelForest& forest)
	{
		for (auto& tree : forest.Trees())
		{
			CountUsesInNode(tree.get());
		}
	}

	void ISelTreeMerge::CountUsesInNode(ISelNode* node)
	{
		if (!node) return;

		if (auto* reg = dyn_cast<ISelRegisterNode>(node))
		{
			if (!reg->HasSource())
			{
				MachineOperand const& op = reg->GetRegister();
				if (op.IsReg() && IsVirtualReg(op.GetReg().reg))
				{
					if (auto* def = FindDefiningTree(op))
					{
						use_counts[def]++;
					}
				}
			}
			else
			{
				CountUsesInNode(reg->GetSource());
			}
		}
		else if (auto* binary = dyn_cast<ISelBinaryOpNode>(node))
		{
			CountUsesInNode(binary->GetLeft());
			CountUsesInNode(binary->GetRight());
		}
		else if (auto* unary = dyn_cast<ISelUnaryOpNode>(node))
		{
			CountUsesInNode(unary->GetOperand());
		}
		else if (auto* load = dyn_cast<ISelLoadNode>(node))
		{
			CountUsesInNode(load->GetAddress());
		}
		else if (auto* store = dyn_cast<ISelStoreNode>(node))
		{
			CountUsesInNode(store->GetValueNode());
			CountUsesInNode(store->GetAddress());
		}
		else if (auto* cmp = dyn_cast<ISelCompareNode>(node))
		{
			CountUsesInNode(cmp->GetLeft());
			CountUsesInNode(cmp->GetRight());
		}
		else if (auto* sel = dyn_cast<ISelSelectNode>(node))
		{
			CountUsesInNode(sel->GetPredicate());
			CountUsesInNode(sel->GetTrueValue());
			CountUsesInNode(sel->GetFalseValue());
		}
		else if (auto* addr = dyn_cast<ISelAddressNode>(node))
		{
			CountUsesInNode(addr->GetBase());
			CountUsesInNode(addr->GetIndex());
		}
	}

	ISelRegisterNode* ISelTreeMerge::FindDefiningTree(MachineOperand const& reg) const
	{
		if (!reg.IsReg() || !IsVirtualReg(reg.GetReg().reg))
		{
			return nullptr;
		}

		auto it = reg_to_def.find(reg.GetReg().reg);
		return it != reg_to_def.end() ? it->second : nullptr;
	}

	Bool ISelTreeMerge::CanMerge(ISelRegisterNode* producer, ISelNode* consumer, ISelForest& forest) const
	{
		if (!producer || !consumer) return false;

		if (!producer->HasSource()) return false;

		auto it = use_counts.find(producer);
		if (it == use_counts.end() || it->second != 1)
		{
			return false;
		}

		// Only block merging if the producer has a memory operation (load/store).
		// Address calculations (producer without memory ops) can safely merge into
		// loads/stores. The consumer having a memory op is fine - we're just inlining
		// address calculations into the load/store pattern.
		if (forest.HasMemoryOp(producer)  || forest.HasMemoryOp(consumer))
		{
			return false;
		}

		return true;
	}

	void ISelTreeMerge::PerformMerge(ISelForest& forest)
	{
		Bool changed = true;
		while (changed)
		{
			changed = false;

			for (auto& tree : forest.Trees())
			{
				Uint32 old_count = use_counts.size();
				TryMergeIntoNode(tree.get(), forest);

				if (use_counts.size() != old_count)
				{
					changed = true;
				}
			}
		}
	}

	void ISelTreeMerge::TryMergeIntoNode(ISelNode* node, ISelForest& forest)
	{
		if (!node) return;

		if (auto* reg = dyn_cast<ISelRegisterNode>(node))
		{
			if (!reg->HasSource())
			{
				ISelRegisterNode* producer = FindDefiningTree(reg->GetRegister());
				if (producer && CanMerge(producer, node, forest))
				{
					reg->ConsumeSource(producer->TakeSource());

					use_counts.erase(producer);

					forest.RemoveTree(producer);
				}
			}
			else
			{
				TryMergeIntoNode(reg->GetSource(), forest);
			}
		}
		else if (auto* binary = dyn_cast<ISelBinaryOpNode>(node))
		{
			TryMergeIntoNode(binary->GetLeft(), forest);
			TryMergeIntoNode(binary->GetRight(), forest);
		}
		else if (auto* unary = dyn_cast<ISelUnaryOpNode>(node))
		{
			TryMergeIntoNode(unary->GetOperand(), forest);
		}
		else if (auto* load = dyn_cast<ISelLoadNode>(node))
		{
			TryMergeIntoNode(load->GetAddress(), forest);
		}
		else if (auto* store = dyn_cast<ISelStoreNode>(node))
		{
			TryMergeIntoNode(store->GetValueNode(), forest);
			TryMergeIntoNode(store->GetAddress(), forest);
		}
		else if (auto* cmp = dyn_cast<ISelCompareNode>(node))
		{
			TryMergeIntoNode(cmp->GetLeft(), forest);
			TryMergeIntoNode(cmp->GetRight(), forest);
		}
		else if (auto* sel = dyn_cast<ISelSelectNode>(node))
		{
			TryMergeIntoNode(sel->GetPredicate(), forest);
			TryMergeIntoNode(sel->GetTrueValue(), forest);
			TryMergeIntoNode(sel->GetFalseValue(), forest);
		}
		else if (auto* addr = dyn_cast<ISelAddressNode>(node))
		{
			TryMergeIntoNode(addr->GetBase(), forest);
			TryMergeIntoNode(addr->GetIndex(), forest);
		}
	}
}
