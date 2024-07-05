#pragma once
#include "Backend/Custom/PassManager.h"

namespace ola
{
	class IRModule;
	class IRModulePass : public Pass
	{
	public:
		explicit IRModulePass(char pid) : Pass(pid, PassKind::Module) {}

		virtual void Init(IRModule&) {}
		virtual void Deinit(IRModule&) {}
		virtual bool RunOn(IRModule& M) = 0;
	};

	template<>
	struct UnitTraits<IRModule>
	{
		using BasePassT = IRModule;
		using ParentUnitT = IRModule;
	};
	using IRModulePassManager = PassManager<IRModule>;
}