#pragma once
#include "Backend/Custom/Codegen/Target.h"
#include "Backend/Custom/Codegen/MachineContext.h"

namespace ola
{
	class BasicBlock;
	class Instruction;
	class UnaryInst;
	class BinaryInst;
	class CompareInst;
	class ReturnInst;
	class BranchInst;
	class LoadInst;
	class StoreInst;
	class CallInst;
	class CastInst;
	class GetElementPtrInst;
	class PtrAddInst;
	class SwitchInst;
	class SelectInst;

	class ISelLegacy
	{
	public:
		explicit ISelLegacy(MachineContext& ctx, Target const& target);
		void SelectBasicBlock(BasicBlock& BB);

	private:
		MachineContext& ctx;
		Target const& target;

	private:
		void LowerInstruction(Instruction* I);
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
	};
}
