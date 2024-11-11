#pragma once
#include "Backend/Custom/PassManager.h"
#include "Backend/Custom/AnalysisManager.h"

namespace ola
{
	class Function;
	using FunctionPassManager = PassManager<Function>;
	using FunctionAnalysisManager = AnalysisManager<Function>;

	class FunctionPass : public Pass
	{
	public:
		explicit FunctionPass(Char& pid) : Pass(pid, PassKind::Function) {}

		virtual void Init(IRModule&) {}
		virtual void Deinit(IRModule&) {}
		virtual Bool RunOn(Function&, FunctionAnalysisManager&) = 0;
	};

	class IRModule;
	template<>
	struct UnitTraits<Function>
	{
		using BasePassT = FunctionPass;
		using ParentUnitT = IRModule;
		using AnalysisManagerT = FunctionAnalysisManager;
	};
}