#pragma once
#include "Backend/Custom/IR/IRModulePass.h"
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/IR/PassRegistry.h"

namespace ola
{
	template<typename U>
	class PassManager;
	using FunctionPassManager = PassManager<Function>;
	template<typename UnitT>
	class AnalysisManager;
	using FunctionAnalysisManager = AnalysisManager<Function>;

	class FunctionPassManagerModuleAdaptor : public IRModulePass
	{
		inline static Char id = 0;
	public:
		explicit FunctionPassManagerModuleAdaptor(FunctionPassManager& FPM, FunctionAnalysisManager& FAM) : IRModulePass(id), FPM(FPM), FAM(FAM) {}
		virtual Bool RunOn(IRModule&, IRModuleAnalysisManager&) override;

		static void const* ID() { return &id; }

	private:
		FunctionPassManager& FPM;
		FunctionAnalysisManager& FAM;
	};
	OLA_REGISTER_PASS(FunctionPassManagerModuleAdaptor, "IRModule To Function Pass Adaptor");
	inline IRModulePass* CreateFunctionPassManagerModuleAdaptor(FunctionPassManager& FPM, FunctionAnalysisManager& FAM) { return new FunctionPassManagerModuleAdaptor(FPM, FAM); }
}