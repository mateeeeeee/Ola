#pragma once
#include "Backend/Custom/Codegen/AsmPrinter.h"

namespace ola
{
	enum Microsoft_x64Section : Uint32
	{
		Microsoft_x64Section_Preamble,
		Microsoft_x64Section_ReadOnly,
		Microsoft_x64Section_BSS,
		Microsoft_x64Section_Data,
		Microsoft_x64Section_Text
	};

	class MachineModule;
	class Microsoft_x64AsmPrinter : public AsmPrinter
	{
	public:
		Microsoft_x64AsmPrinter(std::ostream& os) : AsmPrinter(os) {}
		virtual void PrintModule(MachineModule const& M) override;

	private:
		virtual std::string GetSectionLabel(SectionId section) const override
		{
			switch (static_cast<Microsoft_x64Section>(section))
			{
			case Microsoft_x64Section_Text:
				return ".section .text";
			case Microsoft_x64Section_Data:
				return ".section .data";
			case Microsoft_x64Section_ReadOnly:
				return ".section .rodata";
			case Microsoft_x64Section_BSS:
				return ".section .bss";
			case Microsoft_x64Section_Preamble:
			default:
				return "";
			}
		}

		std::string GetFPConstantPoolEntry(Int64 value);
		std::string GetIntConstantPoolEntry(Int64 value);

		template<typename... Args>
		void EmitPreamble(Char const* fmt, Args&&... args)
		{
			Emit<Microsoft_x64Section_Preamble>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitText(Char const* fmt, Args&&... args)
		{
			Emit<Microsoft_x64Section_Text>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitData(Char const* fmt, Args&&... args)
		{
			Emit<Microsoft_x64Section_Data>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitReadOnly(Char const* fmt, Args&&... args)
		{
			Emit<Microsoft_x64Section_ReadOnly>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitBSS(Char const* fmt, Args&&... args)
		{
			Emit<Microsoft_x64Section_BSS>(fmt, std::forward<Args>(args)...);
		}
	};
}