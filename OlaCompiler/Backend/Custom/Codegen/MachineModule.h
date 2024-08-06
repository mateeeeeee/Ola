#pragma once
#include <iosfwd>
#include "MachineGlobal.h"
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
	class ReturnInst;
	class CallInst;
	class AllocaInst;

	class MachineInstruction;
	class MIRInstructionInfo;
	class MachineFunction;

	class Target;

	class MachineModule
	{
	public:
		explicit MachineModule(IRModule& ir_module, Target const& target);
		virtual ~MachineModule() = default;

		Target const& GetTarget() const { return target; }
		auto   const& GetGlobals() const { return globals; }

		void EmitAssembly(std::string_view assembly_file);

	protected:
		std::vector<MachineGlobal> globals;
		LoweringContext lowering_ctx;
		Target const& target;

	private:
		void LowerModule(IRModule*);
		void LowerFunction(Function*);
		void LowerInstruction(Instruction*);

		void LowerUnary(UnaryInst*);
		void LowerBinary(BinaryInst*);
		void LowerCompare(CompareInst*);
		void LowerRet(ReturnInst*);
		void LowerBranch(BranchInst*);
		void LowerLoad(LoadInst*);
		void LowerStore(StoreInst*);
		void LowerCall(CallInst*);
		void LowerCast(CastInst*);

		void LowerCFGAnalysis(Function*);
	};
}