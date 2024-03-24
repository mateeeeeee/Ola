#pragma once
#include "Backend/Custom/PassManager.h"

namespace ola
{
	class MIRModule;
	class MIRModulePass : public Pass
	{
	public:
		explicit MIRModulePass(char pid) : Pass(pid, PassKind::MachineModule) {}

		virtual void Init(MIRModule&) {}
		virtual void Deinit(MIRModule&) {}
		virtual bool RunOn(MIRModule& M) = 0;
	};

	template<>
	struct UnitTraits<MIRModule>
	{
		using BasePassT = MIRModule;
		using ParentUnitT = MIRModule;
	};
	using MIRModulePassManager = PassManager<MIRModule>;
}