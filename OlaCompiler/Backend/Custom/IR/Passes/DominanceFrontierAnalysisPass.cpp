#include <iostream>
#include "DominanceFrontierAnalysisPass.h"
#include "DominatorTreeAnalysisPass.h"
#include "CFGAnalysisPass.h"

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
		for (auto I = DF.begin(), E = DF.end(); I != E; ++I) 
		{
			std::cout << "  DomFrontier for BB ";
			std::cout << I->first->GetName();
			std::cout << " is:\t";
			auto const& Frontier = I->second;
			for (BasicBlock const* BB : Frontier)
			{
				std::cout << ' ';
				if (BB) std::cout << BB->GetName();
			}
			std::cout << '\n';
		}
		return false;
	}

}

