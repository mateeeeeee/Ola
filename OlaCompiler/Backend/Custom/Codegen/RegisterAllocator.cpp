#include <algorithm>
#include "RegisterAllocator.h"
#include "LivenessAnalysis.h"
#include "MIRGlobal.h"
#include "MIRModule.h"

namespace ola
{

	void LinearScanRegisterAllocator::AssignRegisters(MIRFunction& MF)
	{
		LivenessAnalysisResult liveness = DoLivenessAnalysis(M, MF);
		std::vector<LiveInterval>& live_intervals = liveness.live_intervals;

		std::vector<uint32> registers, fp_registers;
		M.GetRegisters(registers);
		M.GetFPRegisters(fp_registers);
		for (LiveInterval& LI : live_intervals)
		{
			ExpireOldIntervals(LI);
			if (registers.empty())
			{
				SpillAtInterval(LI);
			}
			else 
			{
				uint32 reg = registers.back();
				registers.pop_back();

				LI.reg = reg;

				active.push_back(&LI);
				std::sort(active.begin(), active.end(), [](LiveInterval* L, LiveInterval* R) { return L->end < R->end; });
			}
		}
		ModifyCode();
	}

	void LinearScanRegisterAllocator::ExpireOldIntervals(LiveInterval& LI)
	{

	}

	void LinearScanRegisterAllocator::SpillAtInterval(LiveInterval& LI)
	{

	}

	void LinearScanRegisterAllocator::ModifyCode()
	{

	}

}
