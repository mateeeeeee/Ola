#include "LivenessAnalysis.h"
#include <unordered_map>
#include <unordered_set>
#include "MIR/MIR.h"


namespace ola
{
	std::vector<LiveInterval> LivenessAnalysis(MachineFunction& MF)
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

}

