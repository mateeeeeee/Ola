#include "Target.h"
#include "MachineInstruction.h"
#include "Utility/EnumOperators.h"

namespace ola
{
	template <>
	struct EnumBitmaskOperators<InstFlag>
	{
		static constexpr bool enable = true;
	};

	template <>
	struct EnumBitmaskOperators<OperandFlag>
	{
		static constexpr bool enable = true;
	};


	InstInfo TargetInstInfo::GetInstInfo(MachineInstruction const& inst) const
	{
		return GetInstInfo(inst.GetOpcode());
	}

	void InstInfo::SetOpFlag(uint32 idx, OperandFlag flag)
	{
		operand_flags[idx] |= flag;
	}

	void InstInfo::SetInstFlag(InstFlag inst_flag)
	{
		instruction_flag |= inst_flag;
	}

}

