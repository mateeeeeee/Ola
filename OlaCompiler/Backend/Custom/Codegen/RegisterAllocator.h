#pragma once

namespace ola
{
	class MIRFunction;
	class MIRModule;

	class RegisterAllocator
	{
	public:
		explicit RegisterAllocator(MIRModule& M) : M(M)  {}
		virtual ~RegisterAllocator() = default;

		virtual void AssignRegisters(MIRFunction&) const = 0;

	protected:
		MIRModule& M;
	};

	class LinearScanRegisterAllocator : public RegisterAllocator
	{
	public:
		explicit LinearScanRegisterAllocator(MIRModule& M) : RegisterAllocator(M) {}

		virtual void AssignRegisters(MIRFunction&) const override;
	};
}