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
	class ReturnInst;
	class BranchInst;
	class LoadInst;
	class StoreInst;

	class MIRModule
	{
	public:
		explicit MIRModule(IRModule& ir_module);
		virtual ~MIRModule() = default;
		
		virtual void EmitPrologue(MIRFunction& MF) = 0;
		virtual bool TryLowerInstruction(Instruction*) { return false; }

	protected:
		std::vector<MIRGlobal> globals;
		LoweringContext ctx;

	private:
		void LowerModule(IRModule*);
		void LowerFunction(Function*);
		void LowerInstruction(Instruction*);

		void LowerUnary(UnaryInst*);
		void LowerBinary(BinaryInst*);
		void LowerRet(ReturnInst*);
		void LowerBranch(BranchInst*);
		void LowerLoad(LoadInst*);
		void LowerStore(StoreInst*);
	};
}