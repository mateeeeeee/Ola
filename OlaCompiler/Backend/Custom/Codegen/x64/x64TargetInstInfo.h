#pragma once
#include "Backend/Custom/Codegen/Target.h"

namespace ola
{

	class x64TargetInstInfo : public TargetInstInfo
	{
	public:
		virtual InstInfo GetInstInfo(uint32 opcode) const override;
	};

}

