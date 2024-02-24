#include <fstream>
#include <unordered_map>
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/Values/GlobalValue.h"
#include "Backend/Custom/IR/Values/BasicBlock.h"
#include "Backend/Custom/IR/Values/Instructions.h"
#include "Backend/Custom/IR/Values/BinaryInstruction.h"
#include "Backend/Custom/IR/Values/UnaryInstruction.h"
#include "MachineModule.h"
#include "MIR/MIR.h"


namespace ola
{
	struct VoidPointerHash
	{
		uint64 operator()(void const* ptr) const
		{
			return reinterpret_cast<uint64>(ptr);
		}
	};
	template<typename V>
	using VoidPointerMap = std::unordered_map<void const*, V, VoidPointerHash>;
	struct VirtualRegisterAllocator
	{
		MachineOperand Allocate(Value const* val)
		{
			if (value_reg_map.contains(val)) return value_reg_map[val];
			MachineOperand virtual_reg(MO_Register);
			virtual_reg.SetReg(current_index++);
			return virtual_reg;
		}

	private:
		uint32 current_index = 0;
		VoidPointerMap<MachineOperand> value_reg_map;
	};

	void operator<<(std::ostream& os, MachineResult const& res)
	{
		os << res.no_segment << "\n";
		os << res.rodata_segment << "\n";
		os << res.bss_segment << "\n";
		os << res.data_segment << "\n";
		os << res.text_segment << "\n";
	}

	MachineModule::MachineModule(IRModule& ir_module) : global_variables(ir_module.GetVariableList())
	{
		virtual_reg_allocator = std::make_unique<VirtualRegisterAllocator>();

		for (auto const& ir_function : ir_module.GetFunctionList())
		{
			functions.PushBack(new MachineFunction(ir_function, functions.Size()));
			MachineFunction& MF = functions.Back();

			std::unordered_map<BasicBlock const*, MachineBasicBlock*> bb_map;
			for (auto const& BB : ir_function)
			{
				MachineBasicBlock* MBB = new MachineBasicBlock(MF, &BB);

				MF.PushBack(MBB);
				bb_map[&BB] = MBB;
			}

			for (auto const& BB : ir_function)
			{
				MachineBasicBlock* MBB = bb_map[&BB];
				for (auto& bb_pred : BB.Predecessors()) MBB->AddPredecessor(bb_map[bb_pred]);
				for (auto& bb_succ : BB.Successors()) MBB->AddSuccessor(bb_map[bb_succ]);
			}

			for (auto const& BB : ir_function)
			{
				for (auto inst_iterator = BB.begin(); inst_iterator != BB.end(); ++inst_iterator)
				{
					Instruction const* inst = inst_iterator;
					if (AllocaInst const* alloca_inst = dyn_cast<AllocaInst>(inst))
					{
						MachineInst* alloc = new MachineInst(MachineOpCode::Alloca);
						MachineOperand alloc_size(MO_IntImmediate);
						alloc_size.SetImm((int64)alloca_inst->GetAllocatedType()->GetSize());
						alloc->AddOperand(alloc_size);

						bb_map[&BB]->Insert(alloc);
					}
					else if (StoreInst const* store_inst = dyn_cast<StoreInst>(inst))
					{
						MachineInst* store = new MachineInst(MachineOpCode::Store);
						store->AddOperand(FromValue(store_inst->GetAddressOperand()));
						store->AddOperand(FromValue(store_inst->GetValueOperand()));

						bb_map[&BB]->Insert(store);
					}
					else if (ReturnInst const* ret_inst = dyn_cast<ReturnInst>(inst))
					{
						MachineInst* ret = new MachineInst(MachineOpCode::Return);
						if (!ret_inst->IsVoid())
						{
							Value* ret_value = ret_inst->GetReturnValue();
							ret->AddOperand(FromValue(ret_value));
						}
						bb_map[&BB]->Insert(ret);
					}
				}
			}
		}

		
	}

	MachineOperand MachineModule::FromValue(Value const* V)
	{
		if (ConstantInt const* constant_int = dyn_cast<ConstantInt>(V))
		{
			MachineOperand operand(MO_IntImmediate);
			operand.SetImm(constant_int->GetValue());
			return operand;
		}
		else if (ConstantFloat const* constant_float = dyn_cast<ConstantFloat>(V))
		{
			MachineOperand operand(MO_FPImmediate);
			operand.SetFPImm(constant_float->GetValue());
			return operand;
		}
		else if (AllocaInst const* alloc = dyn_cast<AllocaInst>(V))
		{
			MachineOperand operand(MO_FrameIndex);
		}
		else
		{
			return virtual_reg_allocator->Allocate(V);
		}
	}

	MachineModule::~MachineModule()
	{
	}

	void MachineModule::Print(std::ofstream& of)
	{
		of << result;
	}
}

