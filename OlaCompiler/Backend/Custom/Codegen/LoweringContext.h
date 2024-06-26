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
	class GlobalValue;
	class BasicBlock;
	class Value;
	class IRType;

	class LoweringContext
	{
	public:
		explicit LoweringContext(MIRModule& module) : module(module) {}

		void SetCurrentBasicBlock(MIRBasicBlock* block)
		{
			current_block = block;
		}
		MIRBasicBlock* GetCurrentBasicBlock() const
		{
			return current_block;
		}

		MIRModule& getModule() const
		{
			return module;
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
	};
}