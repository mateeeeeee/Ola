#pragma once
#include <iosfwd>
#include "MachineGlobal.h"
#include "MachineContext.h"

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
	class GetElementPtrInst;
	class SwitchInst;
	class PtrAddInst;
	class SelectInst;
	class PhiInst;
	template<typename UnitT>
	class AnalysisManager;
	using FunctionAnalysisManager = AnalysisManager<Function>;

	class MachineInstruction;
	class MIRInstructionInfo;
	class MachineFunction;

	class Target;

	class MachineModule
	{
	public:
		MachineModule(IRModule& ir_module, Target const& target, FunctionAnalysisManager& FAM);
		virtual ~MachineModule() = default;

		Target const& GetTarget() const { return target; }
		auto   const& GetGlobals() const { return globals; }

		void EmitMIR(std::string_view mir_file);
		void EmitAssembly(std::string_view assembly_file);

	protected:
		std::vector<MachineGlobal> globals;
		MachineContext machine_ctx;
		Target const& target;
		FunctionAnalysisManager& FAM;

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
		void LowerGEP(GetElementPtrInst*);
		void LowerPtrAdd(PtrAddInst*);
		void LowerSwitch(SwitchInst*);
		void LowerSelect(SelectInst*);
		void EmitJump(Uint32 jump_opcode, BasicBlock* dst, BasicBlock* src);

		void LegalizeInstructions(MachineFunction& MF);
		void PostLegalizeInstructions(MachineFunction& MF);
	};
}