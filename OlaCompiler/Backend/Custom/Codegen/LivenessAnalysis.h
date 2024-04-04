#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace ola
{
	struct LiveRange
	{
		uint64 begin, end;
	};

	inline bool operator<(LiveRange const& lhs, LiveRange const& rhs) 
	{
		return lhs.begin < rhs.begin;
	}

	class LiveInterval 
	{
	public:
		LiveInterval() = default;

		void AddRange(LiveRange const& segment)
		{
			ranges.push_back(segment);
		}
		void EmplaceRange(uint64 beg, uint64 end)
		{
			ranges.emplace_back(beg, end);
		}

	private:
		std::vector<LiveRange> ranges;
	};

	class MIRInstruction;
	class MIRBasicBlock;
	class MIRFunction;
	class MIRModule;

	struct LivenessAnalysisResult
	{
		
	};

	LivenessAnalysisResult DoLivenessAnalysis(MIRModule& M, MIRFunction& MF);
}