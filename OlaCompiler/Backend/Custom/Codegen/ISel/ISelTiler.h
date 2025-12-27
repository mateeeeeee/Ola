#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "ISelTile.h"
#include "ISelForest.h"

namespace ola
{
	class Target;

	class ISelTiler
	{
	public:
		explicit ISelTiler(TargetArch arch);

		void RegisterTile(ISelTilePtr tile)
		{
			tiles.push_back(std::move(tile));
			SortTiles();
		}

		template<typename T, typename... Args>
		void AddTile(Args&&... args)
		{
			RegisterTile(std::make_unique<T>(std::forward<Args>(args)...));
		}

		std::vector<MachineInstruction> TileTree(ISelNode* tree, MachineContext& ctx);

		std::vector<MachineInstruction> TileForest(ISelForest& forest, MachineContext& ctx);

		TargetArch GetArch() const { return arch; }

	private:
		void SortTiles()
		{
			std::sort(tiles.begin(), tiles.end(),
				[](ISelTilePtr const& a, ISelTilePtr const& b)
				{
					return a->GetPriority() > b->GetPriority();
				});
		}

		Bool TileMatchesArch(ISelTile* tile) const
		{
			TargetArch tile_arch = tile->GetTarget();
			return tile_arch == TargetArch::All || tile_arch == arch;
		}

	private:
		TargetArch arch;
		std::vector<ISelTilePtr> tiles;
	};
}
