#pragma once
#include <vector>

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
}