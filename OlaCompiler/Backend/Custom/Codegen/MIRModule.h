#pragma once
#include <iosfwd>
#include "MIRGlobal.h"

namespace ola
{
	class IRModule;
	class MIRModule
	{
	public:
		MIRModule(IRModule& ir_module);

		virtual void Emit() = 0;
		virtual void Print(std::ofstream& of);

	private:
		IRModule& ir_module;
		std::vector<MIRGlobal> globals;
	};
}