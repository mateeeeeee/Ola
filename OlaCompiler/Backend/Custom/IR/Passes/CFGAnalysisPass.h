#pragma once
#include <vector>
#include <unordered_map>
#include "Backend/Custom/PassRegistry.h"
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/IR/CFG.h"

namespace ola
{
	class BasicBlock;
	class CFGAnalysisPass : public FunctionPass
	{
	public:
		inline static Char id = 0;
		using Result = CFG;

	public:
		CFGAnalysisPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;

		Result const& GetResult() const { return cfg; }
		static void const* ID() { return &id; }

	private:
		Result cfg;
	};
	OLA_REGISTER_ANALYSIS_PASS(CFGAnalysisPass, "CFG Analysis");

	class CFGPrinterPass : public FunctionPass
	{
	public:
		inline static Char id = 0;
		using Result = void;

	public:
		CFGPrinterPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;

		static void const* ID() { return &id; }
	};
	OLA_REGISTER_PASS(CFGPrinterPass, "CFG Printer");
}