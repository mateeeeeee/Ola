#include "Mem2RegPass.h"
#include "DominatorTreeAnalysisPass.h"
namespace ola
{
	Bool Mem2RegPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		DominatorTree const& DomTree = FAM.GetResult<DominatorTreeAnalysisPass>(F);

		PlacePhiNodes(F, DomTree);
		RenameVariables(F, DomTree);

		return true;
	}

	void Mem2RegPass::PlacePhiNodes(Function& F, DominatorTree const& DomTree)
	{

	}

	void Mem2RegPass::RenameVariables(Function& F, DominatorTree const& DomTree)
	{

	}

}

