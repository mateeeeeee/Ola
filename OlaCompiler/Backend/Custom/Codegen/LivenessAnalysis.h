#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace ola
{

	struct LiveInterval
	{
		uint64 begin, end;
		uint32 vreg;
		uint32 reg;
		int32  stack_offset;
		bool spilled;
	};

	inline bool operator<(LiveInterval const& lhs, LiveInterval const& rhs)
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
		std::unordered_map<MachineInstruction*, uint64> instruction_numbering_map;
	};

	LivenessAnalysisResult DoLivenessAnalysis(MachineModule& M, MachineFunction& MF);
}