#include <fstream>
#include <format>
#include "MachineModule.h"
#include "MIR/MIR.h"
#include "Backend/Custom/IR/IRModule.h"

namespace ola
{
	void operator<<(std::ostream& os, MachineResult const& res)
	{
		os << res.no_segment << "\n";
		os << res.rodata_segment << "\n";
		os << res.bss_segment << "\n";
		os << res.data_segment << "\n";
		os << res.text_segment << "\nend\n";
	}

	MachineModule::MachineModule(IRModule& ir_module) : global_variables(ir_module.GetVariableList())
	{

	}

	template<MachineSegment segment, typename... Ts>
	void MachineModule::Emit(std::string_view fmt, Ts&&... args)
	{
		std::string output = std::vformat(fmt, std::make_format_args(std::forward<Ts>(args)...));
		output += "\n";
		if		constexpr (segment == MachineSegment::None)	 result.no_segment += output;
		else if constexpr (segment == MachineSegment::BSS)	 result.bss_segment += output;
		else if constexpr (segment == MachineSegment::Const) result.rodata_segment += output;
		else if constexpr (segment == MachineSegment::Data)	 result.data_segment += output;
		else if constexpr (segment == MachineSegment::Text)	 result.text_segment += output;
	}

	void MachineModule::Print(std::ofstream& of)
	{
		of << result;
	}

}

