#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace ola
{
	struct LiveSegment
	{
		uint64 begin, end;
	};

	inline bool operator<(LiveSegment const& lhs, LiveSegment const& rhs) 
	{
		return lhs.begin < rhs.begin;
	}

	class LiveInterval 
	{
	public:
		LiveInterval() = default;

		void AddSegment(LiveSegment const& segment)
		{
			segments.push_back(segment);
		}
		void EmplaceSegment(uint64 beg, uint64 end)
		{
			segments.emplace_back(beg, end);
		}

	private:
		std::vector<LiveSegment> segments;
	};


	struct BlockLivenessInfo
	{
		std::unordered_set<uint32> uses;
		std::unordered_set<uint32> defs;
		std::unordered_set<uint32> ins;
		std::unordered_set<uint32> outs;
	};

	class MIRInstruction;
	class MIRBasicBlock;
	class MIRFunction;
	class MIRModule;

	struct LivenessAnalysisResult
	{
		std::unordered_map<MIRInstruction*, uint32> instr_num_map;
		std::unordered_map<MIRBasicBlock*, BlockLivenessInfo> block_info_map;
		std::unordered_map<uint32, LiveInterval> reg_interval_map;
	};

	LivenessAnalysisResult DoLivenessAnalysis(MIRModule& M, MIRFunction& MF);
}