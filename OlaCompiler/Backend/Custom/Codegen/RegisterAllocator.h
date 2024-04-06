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

		virtual void AssignRegisters(MIRFunction&) = 0;

	protected:
		MIRModule& M;
	};
}