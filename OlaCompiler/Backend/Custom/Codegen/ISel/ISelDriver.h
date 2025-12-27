#pragma once
#include "ISelLegacy.h"
#include "ISelTreeGen.h"
#include "ISelTreeMerge.h"
#include "ISelTiler.h"

namespace ola
{
	class BasicBlock;
	class MachineContext;
	class Target;

	enum class ISelMode : Uint8
	{
		Legacy,
		TreePattern
	};

	class ISelDriver
	{
	public:
		explicit ISelDriver(MachineContext& ctx, Target const& target, ISelMode mode = ISelMode::TreePattern);

		void SelectBasicBlock(BasicBlock& BB);
		ISelMode GetMode() const { return mode; }

	private:
		void RegisterTiles();

	private:
		MachineContext& ctx;
		Target const& target;
		ISelMode mode;

		ISelLegacy legacy;
		ISelTreeGen tree_gen;
		ISelTreeMerge tree_merge;
		ISelTiler tiler;
	};
}
