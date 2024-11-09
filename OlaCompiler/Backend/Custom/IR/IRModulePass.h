#pragma once
#include "Backend/Custom/PassManager.h"
#include "Backend/Custom/AnalysisManager.h"

namespace ola
{
	class IRModule;
	using IRModulePassManager = PassManager<IRModule>;
	using IRModuleAnalysisManager = AnalysisManager<IRModule>;

	class IRModulePass : public Pass
	{
	public:
		explicit IRModulePass(Char& pid) : Pass(pid, PassKind::Module) {}

		virtual void Init(IRModule&) {}
		virtual void Deinit(IRModule&) {}
		virtual Bool RunOn(IRModule&, IRModuleAnalysisManager&) = 0;
	};

	template<>
	struct UnitTraits<IRModule>
	{
		using BasePassT		= IRModulePass;
		using ParentUnitT	= IRModule;
	};
}