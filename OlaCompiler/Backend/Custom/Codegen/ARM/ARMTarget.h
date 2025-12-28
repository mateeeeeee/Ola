#pragma once
#include "Backend/Custom/Codegen/Target.h"

namespace ola
{
	class ARMTarget : public Target
	{
	public:
		ARMTarget() = default;

		virtual TargetArch GetArch() const override { return TargetArch::ARM; }
		virtual TargetDataLayout const& GetDataLayout() const override;
		virtual TargetInstInfo const& GetInstInfo() const override;
		virtual TargetRegisterInfo const& GetRegisterInfo() const override;
		virtual TargetISelInfo const& GetISelInfo() const override;
		virtual TargetFrameInfo const& GetFrameInfo() const override;

		virtual void EmitAssembly(MachineModule& M, std::string_view file) const override;
	};
}
