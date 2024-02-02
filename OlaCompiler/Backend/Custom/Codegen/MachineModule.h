#pragma once
#include <vector>
#include <functional>
#include "MIR/MIRFwd.h"
#include "Utility/IntrusiveList.h"

namespace ola
{
	class IRModule;
	class MachineModule
	{
	public:
		explicit MachineModule(IRModule& ir_module) : ir_module(ir_module) {}

		~MachineModule()
		{
		}

		virtual void Emit(std::function<void(char const*)>&& emit_callback) = 0;

	private:
		IRModule& ir_module;
	};
}