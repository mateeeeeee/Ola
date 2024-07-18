#pragma once
#include <iosfwd>
#include "MIRGlobal.h"
#include "LoweringContext.h"
#include "LegalizeContext.h"

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
	class AllocaInst;

	class MIRInstruction;
	class MIRInstructionInfo;
	class MIRFunction;

	class Target;

	class MIRModule
	{
	public:
		explicit MIRModule(IRModule& ir_module, Target const& target);
		virtual ~MIRModule() = default;

		Target const& GetTarget() const { return target; }
		auto   const& GetGlobals() const { return globals; }

		void EmitMIR(std::string_view mir_file);
		void EmitAssembly(std::string_view assembly_file);

	protected:
		std::vector<MIRGlobal> globals;
		LoweringContext lowering_ctx;
		LegalizeContext legalize_ctx;
		Target const& target;

		MIRFunction* current_mf;

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
		void LowerAlloca(AllocaInst*);

		void LowerCFGAnalysis(Function*);
	};
}