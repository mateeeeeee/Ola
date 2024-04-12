#pragma once
#include "Backend/Custom/Codegen/Target.h"

namespace ola
{
	class x64Target : public Target
	{
	public:

		x64Target() = default;

		virtual TargetDataLayout const& GetDataLayout() const override;
		virtual TargetInstInfo const& GetInstInfo() const override;
		virtual TargetRegisterInfo const& GetRegisterInfo() const override;
		virtual TargetISelInfo const& GetISelInfo() const override;
	};
}