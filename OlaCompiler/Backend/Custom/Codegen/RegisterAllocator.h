#pragma once
#include <unordered_set>

namespace ola
{
	struct UsedRegistersInfo
	{
		std::unordered_set<Uint32> gpr_used_registers;
		std::unordered_set<Uint32> fpr_used_registers;
	};

	class MachineFunction;
	class MachineModule;
	class RegisterAllocator
	{
	public:
		explicit RegisterAllocator(MachineModule& M) : M(M)  {}
		virtual ~RegisterAllocator() = default;

		virtual void AssignRegisters(MachineFunction&) = 0;
		virtual UsedRegistersInfo const& GetUsedRegistersInfo() const { return used_registers_info; }

	protected:
		MachineModule& M;
		UsedRegistersInfo used_registers_info;
	};
}