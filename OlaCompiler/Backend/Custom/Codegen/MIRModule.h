#pragma once
#include <iosfwd>
#include "MIRGlobal.h"
#include "LoweringPass.h"

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
	class InstructionLegalizer;

	class MIRInstruction;
	class MIRInstructionInfo;

	struct ModuleRegisterInfo
	{
		std::vector<uint32> regs;
		std::vector<uint32> fp_regs;
		uint32 frame_reg;
	};

	class MIRModule
	{
		friend class LoweringPass;
	public:
		explicit MIRModule(IRModule& ir_module);
		virtual ~MIRModule() = default;

		void EmitMachineCode();
		LoweringPass& GetLoweringPass() { return lowering_pass; }

		virtual InstructionLegalizer* GetLegalizer() = 0;

		virtual void EmitPrologue(MIRFunction&) = 0;
		virtual void EmitReturn(ReturnInst*) = 0;
		virtual void EmitCall(CallInst*) = 0;

		virtual MIRInstructionInfo const& GetInstInfo(MIRInstruction const&) = 0;
		virtual ModuleRegisterInfo const& GetRegisterInfo() const = 0;

	protected:
		IRModule& ir_module;
		std::vector<MIRGlobal> globals;
		LoweringPass lowering_pass;
	};
}