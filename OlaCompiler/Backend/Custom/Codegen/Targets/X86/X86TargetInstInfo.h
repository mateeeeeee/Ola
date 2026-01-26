#pragma once
#include "Backend/Custom/Codegen/Targets/Target.h"

namespace ola
{
	class X86TargetInstInfo : public TargetInstInfo
	{
	public:
		virtual InstInfo GetInstInfo(Uint32 opcode) const override;
		virtual std::string GetInstName(Uint32 opcode) const override;
	};
}