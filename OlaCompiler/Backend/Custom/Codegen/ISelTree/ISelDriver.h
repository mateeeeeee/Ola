#pragma once
#include "ISelTreeGen.h"
#include "ISelTreeMerge.h"
#include "ISelTiler.h"

namespace ola
{
	class BasicBlock;
	class MachineContext;

	enum class ISelMode : Uint8
	{
		Legacy,
		TreePattern
	};

	class ISelDriver
	{
	public:
		explicit ISelDriver(MachineContext& ctx, TargetArch arch);

		void SelectBasicBlock(BasicBlock& BB);
		void SetMode(ISelMode mode) { this->mode = mode; }
		ISelMode GetMode() const { return mode; }

	private:
		void RegisterTiles();

	private:
		MachineContext& ctx;
		TargetArch arch;
		ISelMode mode = ISelMode::Legacy;

		ISelTreeGen tree_gen;
		ISelTreeMerge tree_merge;
		ISelTiler tiler;
	};
}
