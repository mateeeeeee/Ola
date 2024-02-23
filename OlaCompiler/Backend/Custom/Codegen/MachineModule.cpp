#include <fstream>
#include <unordered_map>
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/Values/GlobalValue.h"
#include "Backend/Custom/IR/Values/BasicBlock.h"
#include "Backend/Custom/IR/Values/Instructions.h"
#include "Backend/Custom/IR/Values/BinaryInstruction.h"
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
		for (auto const& ir_function : ir_module.GetFunctionList())
		{
			functions.PushBack(new MachineFunction(ir_function, functions.Size()));
			MachineFunction& mf = functions.Back();

			std::unordered_map<BasicBlock const*, MachineBasicBlock*> bb_map;
			for (auto const& bb : ir_function)
			{
				MachineBasicBlock* machine_bb = new MachineBasicBlock(mf, &bb);

				mf.PushBack(machine_bb);
				bb_map[&bb] = machine_bb;
			}

			for (auto const& bb : ir_function)
			{
				MachineBasicBlock* machine_bb = bb_map[&bb];
				for (auto& bb_pred : bb.Predecessors()) machine_bb->AddPredecessor(bb_map[bb_pred]);
				for (auto& bb_succ : bb.Successors()) machine_bb->AddSuccessor(bb_map[bb_succ]);
			}

			struct VirtualRegisterAllocator
			{
				MachineOperand Allocate(Value* val)
				{
					if (value_reg_map.contains(val)) return value_reg_map[val];
					MachineOperand virtual_reg(MO_Register);
					virtual_reg.SetReg(current_index++);
					return virtual_reg;
				}
			private:
				uint32 current_index = 0;
				VoidPointerMap<MachineOperand> value_reg_map;
			} virtual_register_allocator;

			for (auto const& bb : ir_function)
			{
				for (auto inst_iterator = bb.begin(); inst_iterator != bb.end(); ++inst_iterator)
				{
					Instruction const* inst = inst_iterator;
					if (ReturnInst const* ret_inst = dyn_cast<ReturnInst>(inst))
					{
						MachineInst* ret = new MachineInst(MachineOpCode::Return);
						if (!ret_inst->IsVoid())
						{
							Value* ret_value = ret_inst->GetReturnValue();
							if (ConstantInt* constant_int = dyn_cast<ConstantInt>(ret_value))
							{
								MachineOperand ret_operand(MO_IntImmediate);
								ret_operand.SetImm(constant_int->GetValue());
								ret->AddOperand(ret_operand);
							}
							else if (ConstantFloat* constant_float = dyn_cast<ConstantFloat>(ret_value))
							{
								MachineOperand ret_operand(MO_FPImmediate);
								ret_operand.SetFPImm(constant_float->GetValue());
								ret->AddOperand(ret_operand);
							}
							else
							{
								//MachineOperand ret_operand = virtual_register_allocator.Allocate(ret_inst->GetReturnValue());
							}
							
						}
						bb_map[&bb]->Insert(ret);
					}
					else if (BinaryOperator const* binary_op = dyn_cast<BinaryOperator>(inst))
					{
					}
				}
			}
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

