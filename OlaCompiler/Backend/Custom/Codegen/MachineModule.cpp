#include <fstream>
#include <functional>
#include "MachineModule.h"
#include "MIR/MIR.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/Values/GlobalValue.h"
#include "Backend/Custom/IR/Values/BasicBlock.h"
#include "Backend/Custom/IR/Values/Instructions.h"
#include "Backend/Custom/IR/Values/BinaryInstruction.h"
#include "Backend/Custom/IR/Values/UnaryInstruction.h"

namespace ola
{

	MachineOpCode ToMachineOpcode(BinaryOpcode op)
	{
		switch (op)
		{
		case Binary_Add: return MachineOpCode::Add;
		case Binary_Sub: return MachineOpCode::Sub;
		case Binary_Mul: return MachineOpCode::Mul;
		case Binary_Div: return MachineOpCode::Div;
		}
		return MachineOpCode::Invalid;
	}
	MachineOpCode ToMachineOpcode(UnaryOpcode op)
	{
		switch (op)
		{
		case Unary_Neg: return MachineOpCode::Neg;
		}
		return MachineOpCode::Invalid;
	}

	struct VirtualRegisterAllocator
	{
		[[maybe_unused]] MachineOperand Allocate(Value const* V)
		{
			if (value_reg_map.contains(V)) return value_reg_map[V];
			MachineOperand virtual_reg(MO_Register);
			virtual_reg.SetReg(current_index++);
			virtual_reg.SetSize(V->GetType()->GetSize());
			value_reg_map[V] = virtual_reg;
			return virtual_reg;
		}

	private:
		uint32 current_index = 0;
		VoidPointerMap<MachineOperand> value_reg_map;
	};
	struct MFStackAllocator
	{
		explicit MFStackAllocator(MachineFunction& MF) : MF(MF) {}

		MachineOperand Allocate(AllocaInst const* alloc)
		{
			if (value_stack_alloc_map.contains(alloc)) return value_stack_alloc_map[alloc];
			MachineOperand stack_alloc(MO_FrameIndex);
			uint32 alloc_size = alloc->GetAllocatedType()->GetSize();
			stack_alloc.SetFrameOffset(MF.AllocateStack(alloc_size));
			stack_alloc.SetSize(alloc_size);
			value_stack_alloc_map[alloc] = stack_alloc;
			return stack_alloc;
		}

		MachineFunction& MF;
		VoidPointerMap<MachineOperand> value_stack_alloc_map;
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
		ir_module.PrintIR("test.oll");

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

			MFStackAllocator stack_allocator(MF);
			VirtualRegisterAllocator virtual_reg_allocator;

			std::function<MachineOperand(Value const*)> OperandFromValue = [&](Value const* V) -> MachineOperand
				{
					if (ConstantInt const* constant_int = dyn_cast<ConstantInt>(V))
					{
						MachineOperand operand(MO_IntImmediate);
						operand.SetImm(constant_int->GetValue());
						operand.SetSize(constant_int->GetIntegerType()->GetWidth());
						constant_int->GetBitWidth();
						return operand;
					}
					else if (ConstantFloat const* constant_float = dyn_cast<ConstantFloat>(V))
					{
						MachineOperand operand(MO_FPImmediate);
						operand.SetFPImm(constant_float->GetValue());
						operand.SetSize(constant_float->GetType()->GetSize());
						return operand;
					}
					else if (AllocaInst const* alloc = dyn_cast<AllocaInst>(V))
					{
						return stack_allocator.Allocate(alloc);
					}
					else if (LoadInst const* load = dyn_cast<LoadInst>(V))
					{
						return OperandFromValue(load->GetPointerOperand());
					}
					else
					{
						return virtual_reg_allocator.Allocate(V);
					}
				};
			for (auto const& BB : ir_function)
			{
				for (auto inst_iterator = BB.begin(); inst_iterator != BB.end(); ++inst_iterator)
				{
					MachineBasicBlock* MBB = bb_map[&BB];
					Instruction const* inst = inst_iterator;
					if (AllocaInst const* alloca_inst = dyn_cast<AllocaInst>(inst))
					{
						MachineInst* alloc = new MachineInst(MachineOpCode::Alloca);
						alloc->AddOperand(stack_allocator.Allocate(alloca_inst));
						MBB->Insert(alloc);
					}
					else if (StoreInst const* store_inst = dyn_cast<StoreInst>(inst))
					{
						MachineInst* store = new MachineInst(MachineOpCode::Store);
						store->AddOperand(OperandFromValue(store_inst->GetAddressOperand()));
						store->AddOperand(OperandFromValue(store_inst->GetValueOperand()));

						MBB->Insert(store);
					}
					else if (ReturnInst const* ret_inst = dyn_cast<ReturnInst>(inst))
					{
						MachineInst* ret = new MachineInst(MachineOpCode::Return);
						if (!ret_inst->IsVoid())
						{
							Value* ret_value = ret_inst->GetReturnValue();
							ret->AddOperand(OperandFromValue(ret_value));
						}
						MBB->Insert(ret);
					}
					else if (BinaryOperator const* binary_op = dyn_cast<BinaryOperator>(inst))
					{
						MachineInst* machine_binary_op = new MachineInst(ToMachineOpcode(binary_op->GetOpcode()));
						MachineOperand lhs_operand = OperandFromValue(binary_op->LHS());
						MachineOperand rhs_operand = OperandFromValue(binary_op->RHS());
						machine_binary_op->AddOperand(lhs_operand);
						machine_binary_op->AddOperand(rhs_operand);

						MachineOperand reg_operand = virtual_reg_allocator.Allocate(binary_op);
						machine_binary_op->SetReg(reg_operand.GetReg());

						MBB->Insert(machine_binary_op);
					}
					else if (UnaryOperator const* unary_op = dyn_cast<UnaryOperator>(inst))
					{
						MachineInst* machine_unary_op = new MachineInst(ToMachineOpcode(unary_op->GetOpcode()));
						MachineOperand operand = OperandFromValue(unary_op->GetOperand(0));
						machine_unary_op->AddOperand(operand);

						MachineOperand reg_operand = virtual_reg_allocator.Allocate(unary_op);
						machine_unary_op->SetReg(reg_operand.GetReg());

						MBB->Insert(machine_unary_op);
					}
				}
			}
		}
	}

	MachineModule::~MachineModule() {}

	void MachineModule::Print(std::ofstream& of)
	{
		of << result;
	}
}

