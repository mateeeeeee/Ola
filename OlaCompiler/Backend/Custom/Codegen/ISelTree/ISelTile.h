#pragma once
#include <vector>
#include <memory>
#include "ISelNode.h"
#include "Backend/Custom/Codegen/Target.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineContext.h"
#include "Utility/RTTI.h"

namespace ola
{
	struct TileResult
	{
		std::vector<MachineInstruction> instructions;
		std::vector<ISelNode*> worklist;
		Bool success = false;
	};

	class ISelTile
	{
	public:
		virtual ~ISelTile() = default;

		virtual Bool Match(ISelNode* node) = 0;

		virtual TileResult Apply(MachineContext& ctx) = 0;

		virtual TargetArch GetTarget() const { return TargetArch::All; }

		virtual Int GetPriority() const = 0;

	protected:
		MachineOperand ResolveOperand(ISelNode* node, MachineContext& ctx, std::vector<ISelNode*>& worklist);

		static Bool IsValidx64Scale(Int64 scale)
		{
			return scale == 1 || scale == 2 || scale == 4 || scale == 8;
		}

		static Bool IsSpecialx64Scale(Int64 scale)
		{
			return scale == 3 || scale == 5 || scale == 9;
		}

		static ISelBinaryOpNode* GetSourceAsBinaryOp(ISelRegisterNode* reg)
		{
			if (!reg || !reg->HasSource()) return nullptr;
			return dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		}

		static ISelUnaryOpNode* GetSourceAsUnaryOp(ISelRegisterNode* reg)
		{
			if (!reg || !reg->HasSource()) return nullptr;
			return dyn_cast<ISelUnaryOpNode>(reg->GetSource());
		}

		static ISelLoadNode* GetSourceAsLoad(ISelRegisterNode* reg)
		{
			if (!reg || !reg->HasSource()) return nullptr;
			return dyn_cast<ISelLoadNode>(reg->GetSource());
		}

		static ISelCompareNode* GetSourceAsCompare(ISelRegisterNode* reg)
		{
			if (!reg || !reg->HasSource()) return nullptr;
			return dyn_cast<ISelCompareNode>(reg->GetSource());
		}
	};

	using ISelTilePtr = std::unique_ptr<ISelTile>;
}
