#pragma once
#include "Backend/Custom/IR/IRModulePass.h"
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/PassRegistry.h"

namespace ola
{
	template<typename U>
	class PassManager;
	using FunctionPassManager = PassManager<Function>;

	class FunctionPassManagerModuleAdaptor : public IRModulePass
	{
		inline static Char id = 0;
	public:
		explicit FunctionPassManagerModuleAdaptor(FunctionPassManager& FPM) : IRModulePass(id), FPM(FPM) {}
		virtual Bool RunOn(IRModule&, IRModuleAnalysisManager&) override;

		static void const* ID() { return &id; }

	private:
		FunctionPassManager& FPM;
	};
	OLA_REGISTER_PASS(FunctionPassManagerModuleAdaptor, "IRModule To Function Pass Adaptor");
	inline IRModulePass* CreateFunctionPassManagerModuleAdaptor(FunctionPassManager& FPM) { return new FunctionPassManagerModuleAdaptor(FPM); }
}