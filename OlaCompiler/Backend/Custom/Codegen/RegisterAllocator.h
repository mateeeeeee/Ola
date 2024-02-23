#pragma once


namespace ola
{
	class MachineFunction;
	class LiveInterval;

	struct TargetMachineDesc
	{
		uint32 physical_registers_count;
	};

	class RegisterAllocator
	{
	public:
		virtual void AllocateRegisters(MachineFunction& mf) = 0;
		virtual ~RegisterAllocator() {}

	protected:
		TargetMachineDesc mach_desc;

	protected:
		explicit RegisterAllocator(TargetMachineDesc const& mach_desc) : mach_desc(mach_desc) {}
	};

	class LinearScanRegisterAllocator : public RegisterAllocator
	{
	public:
		explicit LinearScanRegisterAllocator(TargetMachineDesc const& desc) : RegisterAllocator(desc) {}

		void AllocateRegisters(MachineFunction& mf);
	};
}