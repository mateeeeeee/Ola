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

		MIRGlobal* GetGlobal(GlobalValue* GV) const
		{
			return global_map[GV];
		}
		MIRBasicBlock* GetBlock(BasicBlock* BB) const
		{
			return block_map[BB];
		}
		MIROperand GetOperand(Value* V);

		void EmitInst(MIRInstruction const& minst);
		void EmitCopy(MIROperand const& dst, MIROperand const& src)
		{

		}

		MIROperand VirtualReg(IRType const* type) const
		{
			return MIROperand::VirtualReg(virt_reg_id++, GetOperandType(type));
		}
		MIROperand VirtualReg(MIROperandType type) const
		{
			return MIROperand::VirtualReg(virt_reg_id++, type);
		}
		MIROperand StackObject()
		{
			return MIROperand::StackObject(stack_obj_id++, MIROperandType::Other);
		}

		std::string GetLabel() const
		{
			return "label" + std::to_string(label_id++);
		}


	private:
		MIRModule& module;
		MIRBasicBlock* current_block = nullptr;

		mutable std::unordered_map<GlobalValue*, MIRGlobal*> global_map;
		mutable std::unordered_map<BasicBlock*, MIRBasicBlock*> block_map;
		mutable std::unordered_map<Value*, MIROperand> value_map;
		mutable std::unordered_map<Value*, MIROperand> storage_map;
		mutable uint32 virt_reg_id = 0;
		mutable uint32 label_id = 0;
		mutable uint32 stack_obj_id = 0;

	private:
		static MIROperandType GetOperandType(IRType const* type);
	};
}