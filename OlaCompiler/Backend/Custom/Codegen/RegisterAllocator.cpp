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

		void SpillAtInterval(MachineFunction& MF, std::vector<LiveInterval>& live_intervals, std::unordered_map<uint32, uint32>& virt2stack, LiveInterval const& interval)
		{
			LiveInterval* spill = nullptr;
			for (LiveInterval& live_interval : live_intervals)
			{
				if (live_interval.EndIdx() <= interval.EndIdx())
				{
					spill = &live_interval;
				}
				else break;
			}

			if (spill && spill->EndIdx() > interval.EndIdx())
			{
				virt2stack[spill->Reg()] = MF.AllocateStack(8); 
				live_intervals.erase(std::remove(live_intervals.begin(), live_intervals.end(), *spill), live_intervals.end());
				live_intervals.push_back(interval);
				std::sort(live_intervals.begin(), live_intervals.end(), [](LiveInterval const& a, LiveInterval const& b)
					{
					return a.EndIdx() < b.EndIdx();
					});
			}
			else 
			{
				virt2stack[interval.Reg()] = MF.AllocateStack(8);
			}
		}
	}

	void LinearScanRegisterAllocator::AllocateRegisters(MachineFunction& MF)
	{
		std::vector<LiveInterval> live_intervals = LivenessAnalysis(MF);
		std::vector<bool> registers_allocated(mach_desc.physical_registers_count, false);
		std::unordered_map<uint32, uint32> virt2phys_map;
		std::unordered_map<uint32, uint32> virt2stack_map;
		for (LiveInterval const& interval : live_intervals)
		{
			linear_scan_impl::ExpireOldIntervals(live_intervals, interval, registers_allocated);
			if (std::count(registers_allocated.begin(), registers_allocated.end(), false) == 0) 
			{
				linear_scan_impl::SpillAtInterval(MF, live_intervals, virt2stack_map, interval);
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
						if (virt2phys_map.contains(MO.GetReg()))
						{
							MO.SetReg(virt2phys_map[MO.GetReg()]);
						}
						else if (virt2stack_map.contains(MO.GetReg()))
						{
							MO.SetFrameOffset(virt2stack_map[MO.GetReg()]);
						}
					}
				}
			}
		}
	}

}

