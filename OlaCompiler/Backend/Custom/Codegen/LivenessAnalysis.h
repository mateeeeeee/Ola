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


	class MIRInstruction;
	class MIRBasicBlock;
	class MIRFunction;
	class MIRModule;


	struct LivenessAnalysisResult
	{
		std::vector<LiveInterval> live_intervals;
		std::unordered_map<MIRInstruction*, uint64> instruction_numbering_map;
	};

	LivenessAnalysisResult DoLivenessAnalysis(MIRModule& M, MIRFunction& MF);
}