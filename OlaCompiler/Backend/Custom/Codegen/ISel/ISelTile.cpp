#include "ISelTile.h"
#include "Utility/RTTI.h"

namespace ola
{
	MachineOperand ISelTile::ResolveOperand(ISelNode* node, MachineContext& ctx, std::vector<ISelNode*>& worklist)
	{
		if (!node)
		{
			return MachineOperand::Undefined();
		}

		if (auto* imm = dyn_cast<ISelImmediateNode>(node))
		{
			return MachineOperand::Immediate(imm->GetImmediate(), imm->GetType());
		}

		if (auto* reg = dyn_cast<ISelRegisterNode>(node))
		{
			if (reg->HasSource())
			{
				worklist.push_back(node);
			}
			return reg->GetRegister();
		}

		worklist.push_back(node);
		return MachineOperand::Undefined();
	}
}
