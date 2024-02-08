#pragma once
#include <format>
#include <iosfwd>
#include "MIR/MIRFwd.h"
#include "MIR/MachineArch.h"
#include "Utility/IntrusiveList.h"

namespace ola
{
	class IRModule;
	class GlobalVariable;
	class MachineFunction;

	class MachineModule
	{
	public:
		~MachineModule();

		virtual void Emit() = 0;
		virtual void Print(std::ofstream& of);

	protected:
		MachineResult result;
		IList<MachineFunction> functions;
		IList<GlobalVariable> const& global_variables;

	protected:
		explicit MachineModule(IRModule& ir_module);

		template<MachineSegment segment, typename... Ts>
		void EmitLn(std::string_view fmt, Ts&&... args)
		{
			std::string output = std::vformat(fmt, std::make_format_args(std::forward<Ts>(args)...));
			output += "\n";
			if		constexpr (segment == MachineSegment::None)	 result.no_segment += output;
			else if constexpr (segment == MachineSegment::BSS)	 result.bss_segment += output;
			else if constexpr (segment == MachineSegment::Const) result.rodata_segment += output;
			else if constexpr (segment == MachineSegment::Data)	 result.data_segment += output;
			else if constexpr (segment == MachineSegment::Text)	 result.text_segment += output;
		}
	};

}