#pragma once

namespace ola
{
	class MIRFunction;
	class MIRModule;

	class RegisterAllocator
	{
	public:
		explicit RegisterAllocator(MIRModule& M) : M(M)  {}
		virtual void AssignRegisters(MIRFunction&) const = 0;

	private:
		MIRModule& M;
	};

	
}