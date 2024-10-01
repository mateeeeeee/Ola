#include "IROptimizer.h"
#include "IRModule.h"
#include "GlobalValue.h"
#include "Passes/ArithmeticStrengthReductionPass.h"

namespace ola
{

	IROptimizer::IROptimizer(IRModule& M) : M(M)
	{
	}

	void IROptimizer::Optimize(OptimizationLevel level)
	{
		FunctionPassManager FPM;
		//FPM.AddPass(new ArithmeticStrengthReductionPass());

		for (auto& G : M.Globals())
		{
			if (G->IsFunction())
			{
				FPM.Run(*cast<Function>(G));
			}
		}
	}

}

