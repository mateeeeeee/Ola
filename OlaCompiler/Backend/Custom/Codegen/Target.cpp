#include "Target.h"
#include "MIRInstruction.h"
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


	InstInfo const& TargetInstInfo::GetInstInfo(MIRInstruction const& inst) const
	{
		return GetInstInfo(inst.GetOpcode());
	}

	bool TargetISelInfo::IsLegalInstruction(MIRInstruction const& inst) const
	{
		return IsLegalInstruction(inst.GetOpcode());
	}

}

