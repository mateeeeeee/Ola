#pragma once
#include "Backend/Custom/Codegen/Targets/AsmPrinter.h"

namespace ola
{
	enum X86Section : Uint32
	{
		X86Section_Preamble,
		X86Section_ReadOnly,
		X86Section_BSS,
		X86Section_Data,
		X86Section_Text
	};

	class MachineModule;
	class X86AsmPrinter : public AsmPrinter
	{
	public:
		X86AsmPrinter(std::ostream& os) : AsmPrinter(os) {}
		virtual void PrintModule(MachineModule const& M) override;

	private:
		virtual std::string GetSectionLabel(SectionId section) const override
		{
			switch (static_cast<X86Section>(section))
			{
			case X86Section_Text: return ".text";
			case X86Section_Data: return ".data";
			case X86Section_ReadOnly:
#if defined(OLA_PLATFORM_WINDOWS)
				return ".section .rodata";
#else
				return ".section __TEXT,__const";
#endif
			case X86Section_BSS: return ".bss";
			case X86Section_Preamble:
			default:
				return "";
			}
		}

		std::string GetFPConstantPoolEntry(Int64 value);
		std::string GetIntConstantPoolEntry(Int64 value);

		template<typename... Args>
		void EmitPreamble(Char const* fmt, Args&&... args)
		{
			Emit<X86Section_Preamble>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitText(Char const* fmt, Args&&... args)
		{
			Emit<X86Section_Text>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitData(Char const* fmt, Args&&... args)
		{
			Emit<X86Section_Data>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitReadOnly(Char const* fmt, Args&&... args)
		{
			Emit<X86Section_ReadOnly>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitBSS(Char const* fmt, Args&&... args)
		{
			Emit<X86Section_BSS>(fmt, std::forward<Args>(args)...);
		}
	};
}