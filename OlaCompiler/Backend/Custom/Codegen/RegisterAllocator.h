#pragma once

namespace ola
{
	class MachineFunction;
	class MachineModule;
	class RegisterAllocator
	{
	public:
		explicit RegisterAllocator(MachineModule& M) : M(M)  {}
		virtual ~RegisterAllocator() = default;

		virtual void AssignRegisters(MachineFunction&) = 0;

	protected:
		MachineModule& M;
	};
}