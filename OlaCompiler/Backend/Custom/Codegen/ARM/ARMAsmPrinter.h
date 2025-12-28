#pragma once
#include "Backend/Custom/Codegen/AsmPrinter.h"

namespace ola
{
	enum ARMSection : Uint32
	{
		ARMSection_Preamble,
		ARMSection_ReadOnly,
		ARMSection_BSS,
		ARMSection_Data,
		ARMSection_Text
	};

	class MachineModule;
	class ARMAsmPrinter : public AsmPrinter
	{
	public:
		ARMAsmPrinter(std::ostream& os) : AsmPrinter(os) {}
		virtual void PrintModule(MachineModule const& M) override;

	private:
		virtual std::string GetSectionLabel(SectionId section) const override
		{
			switch (static_cast<ARMSection>(section))
			{
			case ARMSection_Text:
				return ".text";
			case ARMSection_Data:
				return ".data";
			case ARMSection_ReadOnly:
				return ".const";
			case ARMSection_BSS:
				return ".bss";
			case ARMSection_Preamble:
			default:
				return "";
			}
		}

		std::string GetFPConstantPoolEntry(Int64 value);
		std::string GetIntConstantPoolEntry(Int64 value);

		template<typename... Args>
		void EmitPreamble(Char const* fmt, Args&&... args)
		{
			Emit<ARMSection_Preamble>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitText(Char const* fmt, Args&&... args)
		{
			Emit<ARMSection_Text>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitData(Char const* fmt, Args&&... args)
		{
			Emit<ARMSection_Data>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitReadOnly(Char const* fmt, Args&&... args)
		{
			Emit<ARMSection_ReadOnly>(fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void EmitBSS(Char const* fmt, Args&&... args)
		{
			Emit<ARMSection_BSS>(fmt, std::forward<Args>(args)...);
		}
	};
}
