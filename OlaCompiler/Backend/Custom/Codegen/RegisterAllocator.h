#pragma once
#include <vector>

namespace ola
{
	class MIRFunction;
	class MIRModule;

	class RegisterAllocator
	{
	public:
		explicit RegisterAllocator(MIRModule& M) : M(M)  {}
		virtual ~RegisterAllocator() = default;

		virtual void AssignRegisters(MIRFunction&) = 0;

	protected:
		MIRModule& M;
	};

	class LiveInterval;
	class LinearScanRegisterAllocator : public RegisterAllocator
	{
	public:
		explicit LinearScanRegisterAllocator(MIRModule& M) : RegisterAllocator(M) {}

		virtual void AssignRegisters(MIRFunction&) override;

	private:
		std::vector<LiveInterval*> active;

	private:
		void ExpireOldIntervals(LiveInterval& LI);
		void SpillAtInterval(LiveInterval& LI);
		void ModifyCode();
	};
}