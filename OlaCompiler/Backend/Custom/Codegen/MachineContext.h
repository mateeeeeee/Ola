#pragma once
#include <span>
#include <unordered_map>
#include "MachineOperand.h"

namespace ola
{
	class MachineModule;
	class MachineFunction;
	class MachineBasicBlock;
	class MachineInstruction;
	class MachineGlobal;
	class GlobalValue;
	class BasicBlock;
	class Value;
	class IRType;
	struct UsedRegistersInfo;

	enum MachineOpcode : Uint32;
	enum class Opcode : Uint32;

	MachineType GetOperandType(IRType const* type);
	MachineOpcode GetMachineOpcode(Opcode opcode);

	class MachineContext
	{
	public:
		explicit MachineContext(MachineModule& module) : module(module) {}

		void SetCurrentBasicBlock(MachineBasicBlock* block)
		{
			current_block = block;
		}
		MachineBasicBlock* GetCurrentBasicBlock() const
		{
			return current_block;
		}

		MachineModule& GetModule() const
		{
			return module;
		}

		void MapGlobal(GlobalValue* GV, MachineGlobal* MG)
		{
			global_map[GV] = MG;
		}
		void MapBlock(BasicBlock* BB, MachineBasicBlock* MBB)
		{
			block_map[BB] = MBB;
		}
		void MapOperand(Value* V, MachineOperand MO)
		{
			value_map[V] = MO;
		}

		MachineGlobal* GetGlobal(GlobalValue const* GV) const
		{
			return global_map[GV];
		}
		MachineBasicBlock* GetBlock(BasicBlock const* BB) const
		{
			return block_map[BB];
		}
		MachineOperand GetOperand(Value const* V);

		MachineInstruction& EmitInst(MachineInstruction const& MI);
		MachineInstruction& EmitInstAtStart(MachineInstruction const& MI);
		MachineInstruction& EmitInstBeforeTerminator(MachineInstruction const& MI);
		std::list<MachineInstruction>::iterator EmitInst(std::list<MachineInstruction>::iterator where, MachineInstruction const& MI);

		MachineOperand VirtualReg(IRType const* type) const
		{
			return MachineOperand::VirtualReg(virt_reg_id++, GetOperandType(type));
		}
		MachineOperand VirtualReg(MachineType type) const
		{
			return MachineOperand::VirtualReg(virt_reg_id++, type);
		}
		std::string GetLabel() const
		{
			return "label" + std::to_string(label_id++);
		}

		void SetUsedRegistersInfo(UsedRegistersInfo const* reg_info)
		{
			OLA_ASSERT(reg_info);
			used_reg_info = reg_info;
		}
		UsedRegistersInfo const* GetUsedRegistersInfo() const
		{
			OLA_ASSERT(used_reg_info);
			return used_reg_info;
		}

	private:
		MachineModule& module;
		MachineBasicBlock* current_block = nullptr;
		UsedRegistersInfo const* used_reg_info = nullptr;

		mutable std::unordered_map<GlobalValue const*, MachineGlobal*> global_map;
		mutable std::unordered_map<BasicBlock const*, MachineBasicBlock*> block_map;
		mutable std::unordered_map<Value const*, MachineOperand> value_map;
		mutable std::unordered_map<Value const*, MachineOperand> storage_map;
		mutable Uint32 virt_reg_id = 0;
		mutable Uint32 label_id = 0;
	};
}