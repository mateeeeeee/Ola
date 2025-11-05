#pragma once
#include "Backend/Custom/Codegen/AsmPrinter.h"

namespace ola
{
	enum SysV_x64Section : Uint32
	{
		SysV_x64Section_Preamble,
		SysV_x64Section_ReadOnly,
		SysV_x64Section_BSS,
		SysV_x64Section_Data,
		SysV_x64Section_Text
	};

	class MachineModule;
	class SysV_x64AsmPrinter : public AsmPrinter
	{
	public:
		SysV_x64AsmPrinter(std::ostream& os) : AsmPrinter(os) {}
		virtual void PrintModule(MachineModule const& M) override;

	private:
		virtual std::string GetSectionLabel(SectionId section) const override
		{
			switch (static_cast<SysV_x64Section>(section))
			{
			case SysV_x64Section_Text:
				return ".section .text";
			case SysV_x64Section_Data:
				return ".section .data";
			case SysV_x64Section_ReadOnly:
				return ".section .rodata";
			case SysV_x64Section_BSS:
				return ".section .bss";
			case SysV_x64Section_Preamble:
			default:
				return "";
			}
		}

		std::string GetFPConstantPoolEntry(Int64 value);
		std::string GetIntConstantPoolEntry(Int64 value);

		template<typename... Args>
		void EmitPreamble(Char const* fmt, Args&&... args)
		{
			Emit<SysV_x64Section_Preamble>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitText(Char const* fmt, Args&&... args)
		{
			Emit<SysV_x64Section_Text>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitData(Char const* fmt, Args&&... args)
		{
			Emit<SysV_x64Section_Data>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitReadOnly(Char const* fmt, Args&&... args)
		{
			Emit<SysV_x64Section_ReadOnly>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitBSS(Char const* fmt, Args&&... args)
		{
			Emit<SysV_x64Section_BSS>(fmt, std::forward<Args>(args)...);
		}
	};
}
