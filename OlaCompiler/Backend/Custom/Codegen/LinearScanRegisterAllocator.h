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
		explicit LinearScanRegisterAllocator(MIRModule& M) : RegisterAllocator(M), frame_register() {}

		virtual void AssignRegisters(MIRFunction&) override;

	private:
		std::vector<LiveInterval*> active;
		std::vector<uint32> registers;
		std::vector<uint32> fp_registers;
		uint32 frame_register;
		std::unordered_map<uint32, uint32> vreg2reg_map;

	private:
		void ExpireOldIntervals(LiveInterval& LI);
		void SpillAtInterval(LiveInterval& LI);
		void Finalize(MIRFunction&, std::vector<LiveInterval>&);
	};
}