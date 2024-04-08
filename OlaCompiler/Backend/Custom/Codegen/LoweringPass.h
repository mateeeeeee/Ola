#pragma once
#include <unordered_map>
#include "MIROperand.h"

namespace ola
{
	class MIRModule;
	class MIRFunction;
	class MIRBasicBlock;
	class MIRInstruction;
	class MIRGlobal;
	class IRModule;
	class GlobalValue;
	class BasicBlock;
	class Value;
	class Function;
	class IRType;
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

	class LoweringPass
	{
	public:
		explicit LoweringPass(MIRModule& module) : module(module) {}

		void RunOnModule(IRModule* M);

		void EmitInst(MIRInstruction const& minst);
		MIROperand VirtualReg(IRType const* type) const
		{
			return MIROperand::VirtualReg(virt_reg_id++, GetOperandType(type));
		}
		MIROperand VirtualReg(MIROperandType type) const
		{
			return MIROperand::VirtualReg(virt_reg_id++, type);
		}
		std::string GetLabel() const
		{
			return "label" + std::to_string(label_id++);
		}

	private:
		MIRModule& module;
		MIRBasicBlock* current_block = nullptr;

		mutable std::unordered_map<GlobalValue const*, MIRGlobal*> global_map;
		mutable std::unordered_map<BasicBlock const*, MIRBasicBlock*> block_map;
		mutable std::unordered_map<Value const*, MIROperand> value_map;
		mutable std::unordered_map<Value const*, MIROperand> storage_map;
		mutable uint32 virt_reg_id = 0;
		mutable uint32 label_id = 0;

	private:
		static MIROperandType GetOperandType(IRType const* type);

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

		void LowerCFGAnalysis(Function*);

		void SetCurrentBasicBlock(MIRBasicBlock* block)
		{
			current_block = block;
		}
		MIRBasicBlock* GetCurrentBasicBlock() const
		{
			return current_block;
		}

		void AddGlobal(GlobalValue* GV, MIRGlobal* MG)
		{
			global_map[GV] = MG;
		}
		void AddBlock(BasicBlock* BB, MIRBasicBlock* MBB)
		{
			block_map[BB] = MBB;
		}
		void AddOperand(Value* V, MIROperand MO)
		{
			value_map[V] = MO;
		}

		MIRGlobal* GetGlobal(GlobalValue const* GV) const
		{
			return global_map[GV];
		}
		MIRBasicBlock* GetBlock(BasicBlock const* BB) const
		{
			return block_map[BB];
		}
		MIROperand GetOperand(Value const* V);

	};
}