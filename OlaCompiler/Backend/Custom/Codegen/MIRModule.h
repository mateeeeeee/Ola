#pragma once
#include <iosfwd>
#include "MIRGlobal.h"

namespace ola
{
	class IRModule;
	class Function;
	class MIRFunction;
	class GlobalValue;

	class MIRModule
	{
	public:
		MIRModule(IRModule& ir_module);
		virtual ~MIRModule() = default;
		virtual void Emit() = 0;
		virtual void Print(std::ofstream& of);

	private:
		std::vector<MIRGlobal> globals;

	private:
		void LowerModule(IRModule&);
		void LowerFunction(Function*, MIRFunction*, std::unordered_map<GlobalValue*, MIRGlobal*>&);
	};
}