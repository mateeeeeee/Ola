#pragma once
#include "Backend/Custom/PassManager.h"
#include "Backend/Custom/AnalysisManager.h"

namespace ola
{
	class MachineModule;
	using MachineModulePassManager = PassManager<MachineModule>;
	using MachineModuleAnalysisManager = AnalysisManager<MachineModule>;

	class MachineModulePass : public Pass
	{
	public:
		explicit MachineModulePass(char pid) : Pass(pid, PassKind::MachineModule) {}

		virtual void Init(MachineModule&) {}
		virtual void Deinit(MachineModule&) {}
		virtual bool RunOn(MachineModule&, MachineModuleAnalysisManager&) = 0;
	};

	template<>
	struct UnitTraits<MachineModule>
	{
		using BasePassT = MachineModule;
		using ParentUnitT = MachineModule;
	};
}