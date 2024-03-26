#pragma once
#include <iosfwd>
#include "MIRGlobal.h"
#include "LoweringContext.h"
#include "ISelContext.h"

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
	class ReturnInst;
	class CallInst;

	class MIRInstruction;
	class MIRInstructionInfo;

	class MIRModule
	{
	public:
		explicit MIRModule(IRModule& ir_module);
		virtual ~MIRModule() = default;
		
		virtual void EmitPrologue(MIRFunction&) = 0;

		virtual void EmitReturn(ReturnInst*) = 0;
		virtual void EmitCall(CallInst*) = 0;
		virtual bool TryLowerInstruction(Instruction*) { return false; }
		virtual MIRInstructionInfo const& GetInstInfo(MIRInstruction&) = 0;

	protected:
		std::vector<MIRGlobal> globals;
		LoweringContext lowering_ctx;
		ISelContext isel_ctx;

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
		void LowerCall(CallInst*);
	};
}