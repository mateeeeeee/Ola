#pragma once

namespace ola
{
	class MIRModule;
	class MIRFunction;
	class ISelContext
	{
	public:
		explicit ISelContext(MIRModule& module) : module(module) {}
		void Run(MIRFunction& func) {}

	private:
		MIRModule& module;
	};
}