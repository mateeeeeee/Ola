#pragma once
#include <vector>
#include <unordered_map>
#include "RegisterAllocator.h"

namespace ola
{
	class LiveInterval;
	class LinearScanRegisterAllocator : public RegisterAllocator
	{
	public:
		explicit LinearScanRegisterAllocator(MachineModule& M) : RegisterAllocator(M), frame_register() {}

		virtual void AssignRegisters(MachineFunction&) override;

	private:
		std::vector<LiveInterval*> active;
		std::vector<Uint32> gp_regs;
		std::vector<Uint32> fp_regs;
		Uint32 frame_register;
		std::unordered_map<Uint32, Uint32> vreg2reg_map;

	private:
		void ExpireOldIntervals(LiveInterval& LI);
		void SpillAtInterval(LiveInterval& LI);
		void Finalize(MachineFunction&, std::vector<LiveInterval>&);
	};
}