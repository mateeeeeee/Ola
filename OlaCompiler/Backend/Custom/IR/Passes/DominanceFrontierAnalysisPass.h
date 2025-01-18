#pragma once
#include "Backend/Custom/IR/PassRegistry.h"
#include "Backend/Custom/IR/DominanceFrontier.h"
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class DominanceFrontierAnalysisPass : public FunctionPass
	{
	public:
		inline static Char id = 0;
		using Result = DominanceFrontier;
	public:
		DominanceFrontierAnalysisPass() : FunctionPass(id) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		DominanceFrontier const& GetResult() const { return DF; }
		static void const* ID() { return &id; }

	private:
		DominanceFrontier DF;
	};
	OLA_REGISTER_ANALYSIS_PASS(DominanceFrontierAnalysisPass, "Dominance Frontier Analysis");

	class DominanceFrontierPrinterPass : public FunctionPass
	{
	public:
		inline static Char id = 0;
		using Result = void;

	public:
		DominanceFrontierPrinterPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;

		static void const* ID() { return &id; }

	private:
		static Uint GetMaxBasicBlockNameLength(DominanceFrontier const& DF);
	};
	OLA_REGISTER_PASS(DominanceFrontierPrinterPass, "Dominance Frontier Printer");
	inline FunctionPass* CreateDominanceFrontierPrinterPass() { return new DominanceFrontierPrinterPass(); }
}