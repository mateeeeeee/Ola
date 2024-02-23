#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "RegisterAllocator.h"
#include "MIR/MIR.h"

namespace ola
{
	class LiveInterval
	{
	public:
		LiveInterval(uint32 reg, uint32 start, uint32 end) : reg(reg), start(start), end(end) {}

		uint32 Reg() const { return reg; }
		uint32 BeginIdx() const { return start; }
		uint32 EndIdx() const { return end; }

		bool operator==(LiveInterval const& other) const
		{
			return start == other.start && end == other.end && reg == other.reg;
		}

	private:
		uint32 reg;
		uint32 start;
		uint32 end;
	};
	static std::vector<LiveInterval> LivenessAnalysis(MachineFunction& MF)
	{
		std::vector<LiveInterval> liveness_intervals;
		std::unordered_map<uint32, std::unordered_set<uint32>> live_vars;
		for (MachineBasicBlock& MBB : MF)
		{
			for (auto I = MBB.rbegin(), E = MBB.rend(); I != E; ++I)
			{
				MachineInst& MI = *I;
				uint32 instr_num = MI.GetInstrNumber();

				std::unordered_set<uint32> live_after = live_vars[instr_num];
				for (uint32 i = 0; i < MI.GetNumOperands(); ++i)
				{
					MachineOperand const& MO = MI.GetOperand(i);
					if (MO.IsReg() && MO.IsDef())
					{
						live_after.erase(MO.GetReg());
					}
				}

				for (uint32 i = 0; i < MI.GetNumOperands(); ++i)
				{
					MachineOperand const& MO = MI.GetOperand(i);
					if (MO.IsReg() && MO.IsUse())
					{
						live_after.insert(MO.GetReg());
					}
				}
				for (uint32 reg : live_after)
				{
					liveness_intervals.emplace_back(reg, instr_num, MI.GetNext()->GetInstrNumber());
				}
				live_vars[instr_num] = live_after;
			}
		}
		return liveness_intervals;
	}

	namespace linear_scan_impl
	{
		void ExpireOldIntervals(std::vector<LiveInterval>& intervals, LiveInterval const& current_interval, std::vector<bool>& registers_allocated)
		{
			for (auto it = intervals.begin(); it != intervals.end();)
			{
				if (it->EndIdx() >= current_interval.BeginIdx()) 
				{
					return;
				}
				for (uint32 reg = 0; reg < registers_allocated.size(); ++reg) 
				{
					if (registers_allocated[reg] && it->Reg() == reg) 
					{
						registers_allocated[reg] = false;
					}
				}
				it = intervals.erase(it);
			}
		}

		uint32 FindFreeRegister(std::vector<bool> const& registers_allocated)
		{
			for (uint32 reg = 0; reg < registers_allocated.size(); ++reg) 
			{
				if (!registers_allocated[reg]) return reg;
			}
			OLA_ASSERT(false);
			return -1;
		}

		void SpillAtInterval(std::vector<LiveInterval>& intervals, LiveInterval const& current_interval)
		{
			LiveInterval* spill = nullptr;
			for (LiveInterval& interval : intervals)
			{
				if (interval.EndIdx() <= current_interval.EndIdx())
				{
					spill = &interval;
				}
				else break;
			}

			if (spill && spill->EndIdx() > current_interval.EndIdx())
			{
				//spill->stack_offset = AllocateStackLocation();
				intervals.erase(std::remove(intervals.begin(), intervals.end(), *spill), intervals.end());
				intervals.push_back(current_interval);
				std::sort(intervals.begin(), intervals.end(), [](LiveInterval const& a, LiveInterval const& b)
					{
					return a.EndIdx() < b.EndIdx();
					});
			}
			else {
				//current_interval.stack_offset = AllocateStackLocation();
			}
		}

	}

	void LinearScanRegisterAllocator::AllocateRegisters(MachineFunction& MF)
	{
		std::vector<LiveInterval> live_intervals = LivenessAnalysis(MF);
		std::vector<bool> registers_allocated(mach_desc.physical_registers_count, false);
		std::unordered_map<uint32, uint32> virt2phys_map;
		for (const LiveInterval& interval : live_intervals) 
		{
			linear_scan_impl::ExpireOldIntervals(live_intervals, interval, registers_allocated);

			if (std::count(registers_allocated.begin(), registers_allocated.end(), false) == 0) 
			{
				linear_scan_impl::SpillAtInterval(live_intervals, interval);
			}
			else 
			{
				uint32 reg = linear_scan_impl::FindFreeRegister(registers_allocated);
				registers_allocated[reg] = true;
				virt2phys_map[interval.Reg()] = reg;
			}
		}

		for (MachineBasicBlock& MBB : MF) 
		{
			for (MachineInst& MI : MBB) 
			{
				for (MachineOperand& MO : MI.Operands()) 
				{
					if (MO.IsReg() && MO.IsVirtual()) 
					{
						MO.SetReg(virt2phys_map[MO.GetReg()]);
					}
				}
			}
		}
	}

}

