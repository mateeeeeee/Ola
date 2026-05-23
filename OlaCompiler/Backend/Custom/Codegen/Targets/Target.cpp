#include "Target.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Utility/EnumOperators.h"

namespace ola
{
	ENABLE_ENUM_BIT_OPERATORS(InstFlag);
	ENABLE_ENUM_BIT_OPERATORS(OperandFlag);

	InstInfo TargetInstInfo::GetInstInfo(MachineInstruction const& inst) const
	{
		return GetInstInfo(inst.GetOpcode());
	}

	void InstInfo::SetOpFlag(Uint32 idx, OperandFlag flag)
	{
		operand_flags[idx] |= flag;
	}

	void InstInfo::SetInstFlag(InstFlag inst_flag)
	{
		instruction_flag |= inst_flag;
	}

	void InstInfo::AddImplicitUse(Uint32 reg)
	{
		OLA_ASSERT(num_implicit_uses < MAX_IMPLICITS);
		implicit_uses[num_implicit_uses++] = reg;
	}

	void InstInfo::AddImplicitDef(Uint32 reg)
	{
		OLA_ASSERT(num_implicit_defs < MAX_IMPLICITS);
		implicit_defs[num_implicit_defs++] = reg;
	}

}

