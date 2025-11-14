#pragma once
#include "Backend/Custom/Codegen/AsmPrinter.h"

namespace ola
{
	enum ARM64Section : Uint32
	{
		ARM64Section_Preamble,
		ARM64Section_ReadOnly,
		ARM64Section_BSS,
		ARM64Section_Data,
		ARM64Section_Text
	};

	class MachineModule;
	class ARM64AsmPrinter : public AsmPrinter
	{
	public:
		ARM64AsmPrinter(std::ostream& os) : AsmPrinter(os) {}
		virtual void PrintModule(MachineModule const& M) override;

	private:
		virtual std::string GetSectionLabel(SectionId section) const override
		{
			switch (static_cast<ARM64Section>(section))
			{
			case ARM64Section_Text:
				return ".text";
			case ARM64Section_Data:
				return ".data";
			case ARM64Section_ReadOnly:
				return ".const";
			case ARM64Section_BSS:
				return ".bss";
			case ARM64Section_Preamble:
			default:
				return "";
			}
		}

		std::string GetFPConstantPoolEntry(Int64 value);
		std::string GetIntConstantPoolEntry(Int64 value);

		template<typename... Args>
		void EmitPreamble(Char const* fmt, Args&&... args)
		{
			Emit<ARM64Section_Preamble>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitText(Char const* fmt, Args&&... args)
		{
			Emit<ARM64Section_Text>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitData(Char const* fmt, Args&&... args)
		{
			Emit<ARM64Section_Data>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitReadOnly(Char const* fmt, Args&&... args)
		{
			Emit<ARM64Section_ReadOnly>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitBSS(Char const* fmt, Args&&... args)
		{
			Emit<ARM64Section_BSS>(fmt, std::forward<Args>(args)...);
		}
	};
}
