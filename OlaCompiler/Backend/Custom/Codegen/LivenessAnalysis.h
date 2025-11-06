#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace ola
{

	struct LiveInterval
	{
		Uint64 begin, end;
		Uint32 vreg;
		Uint32 reg;
		Int32  stack_offset;
		Bool spilled;
		Bool is_float;

		void Extend(Uint64 val)
		{
			if (val < begin) 
			{
				begin = val;
			}
			else if (val > end) 
			{
				end = val;
			}
		}
	};

	inline Bool operator<(LiveInterval const& lhs, LiveInterval const& rhs)
	{
		return lhs.begin < rhs.begin;
	}


	class MachineInstruction;
	class MachineBasicBlock;
	class MachineFunction;
	class MachineModule;

	struct LivenessAnalysisResult
	{
		std::vector<LiveInterval> live_intervals;
		std::unordered_map<MachineInstruction*, Uint64> instruction_numbering_map;
	};

	LivenessAnalysisResult DoLivenessAnalysis(MachineModule& M, MachineFunction& MF);
}