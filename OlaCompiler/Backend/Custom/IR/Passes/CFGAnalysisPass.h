#pragma once
#include <vector>
#include <unordered_map>
#include "Backend/Custom/IR/PassRegistry.h"
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/IR/CFG.h"

namespace ola
{
	class BasicBlock;
	class CFGAnalysisPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		using Result = CFG;
	public:
		CFGAnalysisPass() : FunctionPass(id) {}
		OLA_MAYBE_UNUSED virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;

		CFG const& GetResult() const { return cfg; }
		static void const* ID() { return &id; }

	private:
		CFG cfg;
	};
	OLA_REGISTER_ANALYSIS_PASS(CFGAnalysisPass, "CFG Analysis");

	class CFGPrinterPass : public FunctionPass
	{
		inline static Char id = 0;
	public:
		using Result = void;
	public:
		CFGPrinterPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;

		static void const* ID() { return &id; }
	};
	OLA_REGISTER_PASS(CFGPrinterPass, "CFG Printer");
	inline FunctionPass* CreateCFGPrinterPass() { return new CFGPrinterPass(); }
}