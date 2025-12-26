#include "ISelDriver.h"
#include "Tiles/CommonTiles.h"
#include "Backend/Custom/Codegen/x64/x64Tiles.h"
#include "Backend/Custom/Codegen/ARM64/ARM64Tiles.h"
#include "Backend/Custom/Codegen/MachineContext.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"

namespace ola
{
	ISelDriver::ISelDriver(MachineContext& ctx, TargetArch arch)
		: ctx(ctx)
		, arch(arch)
		, tree_gen(ctx)
		, tiler(arch)
	{
		RegisterTiles();
	}

	void ISelDriver::RegisterTiles()
	{
		RegisterCommonTiles(tiler);

		switch (arch)
		{
		case TargetArch::x64:
			Registerx64Tiles(tiler);
			break;
		case TargetArch::ARM64:
			RegisterARM64Tiles(tiler);
			break;
		default:
			break;
		}
	}

	void ISelDriver::SelectBasicBlock(BasicBlock& BB)
	{
		if (mode == ISelMode::Legacy)
		{
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
