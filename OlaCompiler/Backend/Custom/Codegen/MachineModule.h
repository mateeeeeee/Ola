#pragma once
#include <iosfwd>
#include "MIR/MIRFwd.h"
#include "MIR/MachineArch.h"
#include "Utility/IntrusiveList.h"

namespace ola
{
	class IRModule;
	class GlobalVariable;

	class MachineModule
	{
	public:
		explicit MachineModule(IRModule& ir_module);
		~MachineModule() {}

		virtual void Emit() = 0;

		virtual void Print(std::ofstream& of);

	protected:
		MachineResult result;
		IList<MachineFunction> functions;
		IList<GlobalVariable> const& global_variables;

	protected:
		template<MachineSegment segment, typename... Ts>
		void Emit(std::string_view fmt, Ts&&... args);
	};

}