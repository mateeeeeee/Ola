#pragma once
#include "Backend/Custom/Codegen/AsmPrinter.h"

namespace ola
{
	enum x64Section : Uint32
	{
		x64Section_Preamble,
		x64Section_ReadOnly,
		x64Section_BSS,
		x64Section_Data,
		x64Section_Text
	};

	class MachineModule;
	class x64AsmPrinter : public AsmPrinter
	{
	public:
		x64AsmPrinter(std::ostream& os) : AsmPrinter(os) {}
		virtual void PrintModule(MachineModule const& M) override;

	private:
		virtual std::string GetSectionLabel(SectionId section) const override
		{
			switch (static_cast<x64Section>(section))
			{
			case x64Section_Text: return ".text";
			case x64Section_Data: return ".data";
			case x64Section_ReadOnly:
#if defined(OLA_PLATFORM_MACOS)
				return ".section __TEXT,__const";
#elif defined(OLA_PLATFORM_WINDOWS)
				return ".section .rdata";
#else
				return ".section .rodata";
#endif
			case x64Section_BSS: return ".bss";
			case x64Section_Preamble:
			default:
				return "";
			}
		}

		std::string GetFPConstantPoolEntry(Int64 value);
		std::string GetIntConstantPoolEntry(Int64 value);

		template<typename... Args>
		void EmitPreamble(Char const* fmt, Args&&... args)
		{
			Emit<x64Section_Preamble>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitText(Char const* fmt, Args&&... args)
		{
			Emit<x64Section_Text>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitData(Char const* fmt, Args&&... args)
		{
			Emit<x64Section_Data>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitReadOnly(Char const* fmt, Args&&... args)
		{
			Emit<x64Section_ReadOnly>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitBSS(Char const* fmt, Args&&... args)
		{
			Emit<x64Section_BSS>(fmt, std::forward<Args>(args)...);
		}
	};
}