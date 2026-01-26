#include "ISelDriver.h"
#include "Tiles/CommonTiles.h"
#include "Backend/Custom/Codegen/Targets/Target.h"
#include "Backend/Custom/Codegen/Targets/X86/ISel/X86Tiles.h"
#include "Backend/Custom/Codegen/Targets/ARM/ISel/ARMTiles.h"
#include "Backend/Custom/Codegen/MachineContext.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"

namespace ola
{
	ISelDriver::ISelDriver(MachineContext& ctx, Target const& target, ISelMode mode)
		: ctx(ctx)
		, target(target)
		, mode(mode)
		, legacy(ctx, target)
		, tree_gen(ctx)
		, tiler(target.GetArch())
	{
		RegisterTiles();
	}

	void ISelDriver::RegisterTiles()
	{
		RegisterCommonTiles(tiler);

		switch (target.GetArch())
		{
		case TargetArch::X86:
			RegisterX86Tiles(tiler);
			break;
		case TargetArch::ARM:
			RegisterARMTiles(tiler);
			break;
		default:
			break;
		}
	}

	void ISelDriver::SelectBasicBlock(BasicBlock& BB)
	{
		if (mode == ISelMode::Legacy)
		{
			legacy.SelectBasicBlock(BB);
			return;
		}

		ISelForest forest = tree_gen.GenerateTrees(BB);
		tree_merge.MergeTrees(forest);
		std::vector<MachineInstruction> instructions = tiler.TileForest(forest, ctx);
		for (MachineInstruction& inst : instructions)
		{
			ctx.EmitInst(inst);
		}
	}
}
