#pragma once
#include "Backend/Custom/PassManager.h"

namespace ola
{
	class MIRFunction;
	class MIRModule;
	class MIRFunctionPass : public Pass
	{
	public:
		explicit MIRFunctionPass(char pid) : Pass(pid, PassKind::MachineFunction) {}

		virtual void Init(MIRModule&) {}
		virtual void Deinit(IRModule&) {}
		virtual bool RunOn(MIRFunction& F) = 0;
	};

	class IRModule;
	template<>
	struct UnitTraits<MIRFunction>
	{
		using BasePassT = MIRFunctionPass;
		using ParentUnitT = MIRModule;
	};
	using FunctionPassManager = PassManager<MIRFunction>;
}