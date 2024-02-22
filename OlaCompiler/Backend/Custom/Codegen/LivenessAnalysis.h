#pragma once
#include <vector>

namespace ola
{
	class MachineFunction;

	class LiveInterval 
	{
	public:
		LiveInterval(uint32 reg, uint32 start, uint32 end) : reg(reg), start(start), end(end) {}

		uint32 Reg() const { return reg; }
		uint32 BeginIdx() const { return start; }
		uint32 EndIdx() const { return end; }

	private:
		uint32 reg;
		uint32 start;
		uint32 end;
	};

	std::vector<LiveInterval> LivenessAnalysis(MachineFunction& mf);
}