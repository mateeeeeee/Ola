#pragma once
#include <iosfwd>
#include "MIRGlobal.h"
#include "LoweringContext.h"

namespace ola
{
	class IRModule;
	class Function;
	class Instruction;
	class GlobalValue;
	class UnaryInst;
	class BinaryInst;

	class MIRModule
	{
	public:
		MIRModule(IRModule& ir_module);
		virtual ~MIRModule() = default;
		
		virtual void EmitPrologue(MIRFunction& MF) = 0;
		virtual bool TryLowerInstruction(Instruction*) = 0;

	protected:
		std::vector<MIRGlobal> globals;
		LoweringContext lowering_ctx;

	private:
		void LowerModule(IRModule&);
		void LowerFunction(Function*);
		void LowerInstruction(Instruction*);

		void LowerUnary(UnaryInst*);
		void LowerBinary(BinaryInst*);
	};
}