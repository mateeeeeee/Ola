#pragma once
#include "Backend/Custom/PassManager.h"
#include "Backend/Custom/AnalysisManager.h"

namespace ola
{
	class MachineFunction;
	class MachineModule;

	using MachineFunctionPassManager = PassManager<MachineFunction>;
	using MachineFunctionAnalysisManager = AnalysisManager<MachineFunction>;

	class MachineFunctionPass : public Pass
	{
	public:
		explicit MachineFunctionPass(Char pid) : Pass(pid, PassKind::MachineFunction) {}

		virtual void Init(MachineModule&) {}
		virtual void Deinit(IRModule&) {}
		virtual Bool RunOn(MachineFunction&, MachineFunctionAnalysisManager&) = 0;
	};

	class IRModule;
	template<>
	struct UnitTraits<MachineFunction>
	{
		using BasePassT = MachineFunctionPass;
		using ParentUnitT = MachineModule;
	};
}