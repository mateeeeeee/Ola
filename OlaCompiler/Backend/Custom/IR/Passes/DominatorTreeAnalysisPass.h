#pragma once
#include <memory>
#include <utility>
#include "Backend/Custom/PassRegistry.h"
#include "Backend/Custom/IR/DominatorTree.h"
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	class DominatorTreeAnalysisPass : public FunctionPass
	{
	public:
		inline static Char id = 0;
		using Result = DominatorTree;
	public:
		DominatorTreeAnalysisPass() : FunctionPass(id) {}

		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		DominatorTree const& GetResult() const { return DT; }
		static void const* ID() { return &id; }

	private:
		DominatorTree DT;
	};
	OLA_REGISTER_ANALYSIS_PASS(DominatorTreeAnalysisPass, "Dominator Tree Analysis");

	class DominatorTreePrinterPass : public FunctionPass
	{
	public:
		inline static Char id = 0;
		using Result = void;

	public:
		DominatorTreePrinterPass() : FunctionPass(id) {}
		virtual Bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;

		static void const* ID() { return &id; }
	};
	OLA_REGISTER_PASS(DominatorTreePrinterPass, "Dominator Tree Printer");

}