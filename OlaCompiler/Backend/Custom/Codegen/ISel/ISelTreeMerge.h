#pragma once
#include "ISelForest.h"
#include "ISelNode.h"
#include <unordered_map>

namespace ola
{
	class ISelTreeMerge
	{
	public:
		ISelTreeMerge() = default;

		void MergeTrees(ISelForest& forest);

	private:
		void BuildDefMap(ISelForest& forest);

		void CountUses(ISelForest& forest);
		void CountUsesInNode(ISelNode* node);

		Bool CanMerge(ISelRegisterNode* producer, ISelNode* consumer, ISelForest& forest) const;

		void PerformMerge(ISelForest& forest);
		void TryMergeIntoNode(ISelNode* node, ISelForest& forest);

		ISelRegisterNode* FindDefiningTree(MachineOperand const& reg) const;

	private:
		std::unordered_map<Uint32, ISelRegisterNode*> reg_to_def;
		std::unordered_map<ISelNode*, Uint32> use_counts;
	};
}
