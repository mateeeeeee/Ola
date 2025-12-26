#include "ISelTiler.h"
#include "Utility/RTTI.h"
#include "Core/Log.h"

namespace ola
{
	ISelTiler::ISelTiler(TargetArch arch) : arch(arch)
	{
	}

	std::vector<MachineInstruction> ISelTiler::TileTree(ISelNode* tree, MachineContext& ctx)
	{
		std::vector<MachineInstruction> all_instructions;
		std::vector<ISelNode*> worklist;
		worklist.push_back(tree);

		while (!worklist.empty())
		{
			ISelNode* current = worklist.back();
			worklist.pop_back();

			if (!current) continue;

			if (isa<ISelImmediateNode>(current)) continue;

			if (auto* asm_node = dyn_cast<ISelAsmNode>(current))
			{
				for (auto* inst : asm_node->Instructions())
				{
					if (inst) all_instructions.push_back(*inst);
				}
				continue;
			}

			Bool matched = false;
			for (auto& tile : tiles)
			{
				if (!TileMatchesArch(tile.get())) continue;

				if (tile->Match(current))
				{
					TileResult result = tile->Apply(ctx);

					all_instructions.insert(
						all_instructions.begin(),
						result.instructions.begin(),
						result.instructions.end()
					);

					for (auto* node : result.worklist)
					{
						worklist.push_back(node);
					}

					matched = true;
					break;
				}
			}

			if (!matched)
			{
				OLA_ASSERT_MSG(false, "ISel: No tile matched for node");
			}
		}

		return all_instructions;
	}

	std::vector<MachineInstruction> ISelTiler::TileForest(ISelForest& forest, MachineContext& ctx)
	{
		std::vector<MachineInstruction> all_instructions;

		for (auto& tree : forest.Trees())
		{
			auto insts = TileTree(tree.get(), ctx);
			all_instructions.insert(
				all_instructions.end(),
				insts.begin(),
				insts.end()
			);
		}

		return all_instructions;
	}
}
