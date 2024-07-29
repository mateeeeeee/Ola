#pragma once
#include "Backend/Custom/PassManager.h"

namespace ola
{
	class MachineFunction;
	class MachineModule;
	class MachineFunctionPass : public Pass
	{
	public:
		explicit MachineFunctionPass(char pid) : Pass(pid, PassKind::MachineFunction) {}

		virtual void Init(MachineModule&) {}
		virtual void Deinit(IRModule&) {}
		virtual bool RunOn(MachineFunction& F) = 0;
	};

	class IRModule;
	template<>
	struct UnitTraits<MachineFunction>
	{
		using BasePassT = MachineFunctionPass;
		using ParentUnitT = MachineModule;
	};
	using FunctionPassManager = PassManager<MachineFunction>;
}