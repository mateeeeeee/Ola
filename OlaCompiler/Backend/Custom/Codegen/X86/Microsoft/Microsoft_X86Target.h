#pragma once
#include "Backend/Custom/Codegen/Target.h"

namespace ola
{
	class Microsoft_X86Target : public Target
	{
	public:
		Microsoft_X86Target() = default;

		virtual TargetArch GetArch() const override { return TargetArch::X86; }
		virtual TargetDataLayout const& GetDataLayout() const override;
		virtual TargetInstInfo const& GetInstInfo() const override;
		virtual TargetRegisterInfo const& GetRegisterInfo() const override;
		virtual TargetISelInfo const& GetISelInfo() const override;
		virtual TargetFrameInfo const& GetFrameInfo() const override;

		virtual void EmitAssembly(MachineModule& M, std::string_view file) const override;
	};
}
