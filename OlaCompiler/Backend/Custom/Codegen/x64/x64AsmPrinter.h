#pragma once
#include "Backend/Custom/Codegen/AsmPrinter.h"

namespace ola
{

	enum x64Section : uint32
	{
		x64Section_Preamble,
		x64Section_Text,
		x64Section_Data,
		x64Section_ReadOnly,
		x64Section_BSS
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
			case x64Section_Text:
				return ".text";
			case x64Section_Data:
				return ".data";
			case x64Section_ReadOnly:
				return ".rodata";
			case x64Section_BSS:
				return ".bss";
			case x64Section_Preamble:
			default:
				return "";
			}
		}

		template<typename... Args>
		void EmitPreamble(char const* fmt, Args&&... args)
		{
			Emit<x64Section_Preamble>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitText(char const* fmt, Args&&... args)
		{
			Emit<x64Section_Text>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitData(char const* fmt, Args&&... args)
		{
			Emit<x64Section_Data>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitReadOnly(char const* fmt, Args&&... args)
		{
			Emit<x64Section_ReadOnly>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitBSS(char const* fmt, Args&&... args)
		{
			Emit<x64Section_BSS>(fmt, std::forward<Args>(args)...);
		}
	};
}