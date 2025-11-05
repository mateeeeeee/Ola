#include "ARM64TargetInstInfo.h"
#include "Backend/Custom/Codegen/Arm64/arm64.h"

namespace ola
{
	InstInfo ARM64TargetInstInfo::GetInstInfo(Uint32 opcode) const
	{
		OLA_ASSERT_MSG(false, "ARM64 GetInstInfo not yet implemented!");
		return {};
	}

	std::string ARM64TargetInstInfo::GetInstName(Uint32 opcode) const
	{
		return ARM64_GetOpcodeString(opcode);
	}
}
