#include <fstream>
#include <unordered_map>
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/Values/GlobalValue.h"
#include "Backend/Custom/IR/Values/BasicBlock.h"
#include "MachineModule.h"
#include "MIR/MIR.h"


namespace ola
{
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

			for (auto const& bb : ir_function)
			{
				for (auto inst_iterator = bb.begin(); inst_iterator != bb.end(); ++inst_iterator)
				{
					Instruction const* inst = inst_iterator;
					//if (dyn_cast<BinaryInstruction>(inst))
					//{
					//
					//}
					//else
					//{
					//
					//}
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

