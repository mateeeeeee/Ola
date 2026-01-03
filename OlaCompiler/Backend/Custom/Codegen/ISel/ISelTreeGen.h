#pragma once
#include "ISelNode.h"
#include "ISelForest.h"
#include "Backend/Custom/Codegen/MachineContext.h"

namespace ola
{
	class Function;
	class BasicBlock;
	class Instruction;
	class BinaryInst;
	class UnaryInst;
	class CompareInst;
	class CastInst;
	class LoadInst;
	class StoreInst;
	class BranchInst;
	class ReturnInst;
	class SwitchInst;
	class CallInst;
	class SelectInst;
	class AllocaInst;
	class GetElementPtrInst;
	class PtrAddInst;
	class PhiInst;

	class ISelTreeGen
	{
	public:
		explicit ISelTreeGen(MachineContext& ctx);

		ISelForest GenerateTrees(BasicBlock& BB);
		ISelValueMap const& GetValueMap() const { return value_map; }
		ISelUseCount const& GetUseCount() const { return use_count; }

	private:
		MachineContext& ctx;
		ISelForest forest;
		ISelValueMap value_map;
		ISelUseCount use_count;
		std::vector<MachineInstruction> pending_leaf_instructions;

	private:
		ISelNodePtr CreateNodeForValue(Value* V);
		ISelNodePtr CreateLeafNode(Value* V);

		void ProcessInstruction(Instruction& I);
		void ProcessBinaryInst(BinaryInst& I);
		void ProcessUnaryInst(UnaryInst& I);
		void ProcessCompareInst(CompareInst& I);
		void ProcessCastInst(CastInst& I);
		void ProcessLoadInst(LoadInst& I);
		void ProcessStoreInst(StoreInst& I);
		void ProcessBranchInst(BranchInst& I);
		void ProcessReturnInst(ReturnInst& I);
		void ProcessSwitchInst(SwitchInst& I);
		void ProcessCallInst(CallInst& I);
		void ProcessSelectInst(SelectInst& I);
		void ProcessAllocaInst(AllocaInst& I);
		void ProcessGetElementPtrInst(GetElementPtrInst& I);
		void ProcessPtrAddInst(PtrAddInst& I);
		void ProcessPhiInst(PhiInst& I);

		void EmitJumpWithPhiCopies(Uint32 jump_opcode, BasicBlock* dst, BasicBlock* src);

		void AddTree(ISelNodePtr tree, std::vector<ISelNode*> const& leaves, Bool has_memory);
		void AddAsmNode(std::vector<MachineInstruction> instructions);
		void CountUses(BasicBlock& BB);
		MachineType GetMachineTypeForValue(Value* V) const;

		template<typename Func>
		std::vector<MachineInstruction> CaptureEmittedInstructions(Func&& f);
	};
}
