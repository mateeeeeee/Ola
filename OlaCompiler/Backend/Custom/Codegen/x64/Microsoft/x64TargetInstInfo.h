#pragma once
#include "Backend/Custom/Codegen/Target.h"

namespace ola
{
	class Microsoft_x64TargetInstInfo : public TargetInstInfo
	{
	public:
		virtual InstInfo GetInstInfo(Uint32 opcode) const override;
		virtual std::string GetInstName(Uint32 opcode) const override;
	};
}