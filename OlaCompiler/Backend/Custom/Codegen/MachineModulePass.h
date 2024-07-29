#pragma once
#include "Backend/Custom/PassManager.h"

namespace ola
{
	class MachineModule;
	class MachineModulePass : public Pass
	{
	public:
		explicit MachineModulePass(char pid) : Pass(pid, PassKind::MachineModule) {}

		virtual void Init(MachineModule&) {}
		virtual void Deinit(MachineModule&) {}
		virtual bool RunOn(MachineModule& M) = 0;
	};

	template<>
	struct UnitTraits<MachineModule>
	{
		using BasePassT = MachineModule;
		using ParentUnitT = MachineModule;
	};
	using MIRModulePassManager = PassManager<MachineModule>;
}