#pragma once
#include "Backend/Custom/PassManager.h"

namespace ola
{
	class Function;
	class FunctionPass : public Pass
	{
	public:
		explicit FunctionPass(char pid) : Pass(pid, PassKind::Function) {}

		virtual void Init(IRModule&) {}
		virtual void Deinit(IRModule&) {}
		virtual bool RunOn(Function& F) = 0;
	};

	class IRModule;
	template<>
	struct UnitTraits<Function>
	{
		using BasePassT = FunctionPass;
		using ParentUnitT = IRModule;
	};
	using FunctionPassManager = PassManager<Function>;
}