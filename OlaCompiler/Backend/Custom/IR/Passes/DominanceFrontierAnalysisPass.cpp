#include <iostream>
#include <iomanip>
#include "DominanceFrontierAnalysisPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "CFGAnalysisPass.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool DominanceFrontierAnalysisPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		CFG const& cfg = FAM.GetResult<CFGAnalysisPass>(F);
		DominatorTree const& DT = FAM.GetResult<DominatorTreeAnalysisPass>(F);
		DF.Initialize(DT, cfg);
		return false;
	}

	Bool DominanceFrontierPrinterPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		auto const& DF = FAM.GetResult<DominanceFrontierAnalysisPass>(F);
		Uint MaxBBNameLength = GetMaxBasicBlockNameLength(DF);

		std::cout << "Dominance Frontiers for Function " << F.GetName() << ":\n";
		for (auto I = DF.begin(), E = DF.end(); I != E; ++I) 
		{
			std::cout << "\tDominance Frontier for BB ";
			std::cout << std::left << std::setw(MaxBBNameLength) << I->first->GetName();
			std::cout << " is:\t";
			auto const& Frontier = I->second;
			for (BasicBlock const* BB : Frontier)
			{
				std::cout << ' ';
				if (BB) std::cout << std::left << std::setw(MaxBBNameLength) << BB->GetName();
			}
			std::cout << '\n';
		}
		std::cout << '\n';
		return false;
	}

	Uint DominanceFrontierPrinterPass::GetMaxBasicBlockNameLength(DominanceFrontier const& DF)
	{
		Uint MaxBBNameLength = 0;
		for (auto I = DF.begin(), E = DF.end(); I != E; ++I) 
		{
			Uint BBNameLength = I->first->GetName().size();
			if (BBNameLength > MaxBBNameLength) 
			{
				MaxBBNameLength = BBNameLength;
			}
		}
		return MaxBBNameLength;
	}

}

