#include <iostream>
#include "MachineIRPrinter.h"
#include "Target.h"
#include "MachineModule.h"
#include "MachineStorage.h"
#include "MachineFunction.h"
#include "MachineBasicBlock.h"

namespace ola
{

	void MachineIRPrinter::PrintModule(MachineModule const& M)
	{
		auto const& globals = M.GetGlobals();
		for (MachineGlobal const& global : globals)
		{
			if (global.GetRelocable()->IsFunction())
			{
				PrintFunction(global);
			}
			else
			{
				PrintGlobalVariable(global);
			}
		}
		os << output;
	}

	void MachineIRPrinter::PrintGlobalVariable(MachineGlobal const& MG)
	{
		Emit(MG.GetLinkage() == Linkage::External ? "external " : "internal ");
		MachineRelocable* relocable = MG.GetRelocable();
		if (relocable->IsZeroStorage())
		{
			MachineZeroStorage* zero_storage = static_cast<MachineZeroStorage*>(relocable);
			EmitLn("zero storage {} of size {}\n", zero_storage->GetSymbol(), zero_storage->GetSize());
		}
		else if (relocable->IsDataStorage())
		{
			MachineDataStorage* data_storage = static_cast<MachineDataStorage*>(relocable);
			EmitLn("data storage {}\n", data_storage->GetSymbol());
		}
		else if (relocable->IsBlock() || relocable->IsFunction())
		{
			OLA_ASSERT(false);
		}
	}

	void MachineIRPrinter::PrintFunction(MachineGlobal const& MG)
	{
		OLA_ASSERT(MG.GetRelocable()->IsFunction());
		Emit(MG.GetLinkage() == Linkage::External ? "external " : "internal ");
		MachineFunction& MF = *static_cast<MachineFunction*>(MG.GetRelocable());
		auto const& blocks = MF.Blocks();
		if (!blocks.empty())
		{
			EmitLn("{}: ", MF.GetSymbol());
			for (auto const& block : blocks)
			{
				PrintBlock(*block);
			}
		}
		else
		{
			EmitLn("{}\n", MF.GetSymbol());
		}
	}

	void MachineIRPrinter::PrintBlock(MachineBasicBlock const& MBB)
	{
		EmitLn("{}: ", MBB.GetSymbol());
		auto const& instructions = MBB.Instructions();
		for (MachineInstruction const& MI : instructions)
		{
			PrintInstruction(MI);
		}
		EmitLn("");
	}

	void MachineIRPrinter::PrintInstruction(MachineInstruction const& MI)
	{
		Uint32 opcode = MI.GetOpcode();
		TargetInstInfo const& target_inst_info = target.GetInstInfo();
		std::string inst_name = MI.GetOpcodeName();
		if (inst_name.empty())
		{
			inst_name = target_inst_info.GetInstName(opcode);
		}
		Emit("{} - ", inst_name);

		InstInfo const& inst_info = target_inst_info.GetInstInfo(opcode);
		for (Uint32 i = 0; i < inst_info.GetOperandCount(); ++i)
		{
			MachineOperand const& MO = MI.GetOperand(i);
			PrintOperand(MO);
			if (i != inst_info.GetOperandCount() - 1) Emit(", ");
		}
		EmitLn("");
	}

	void MachineIRPrinter::PrintOperand(MachineOperand const& MO)
	{
		MachineType machine_type = MO.GetType();
		switch (machine_type)
		{
		case MachineType::Int64:	Emit("i64 "); break;
		case MachineType::Int8:		Emit("i8 "); break;
		case MachineType::Float64:	Emit("f64 "); break;
		case MachineType::Ptr:		Emit("ptr "); break;
		case MachineType::Other:	break;
		case MachineType::Undef:
		default:
			OLA_ASSERT(false);
		}
		
		if (MO.IsReg())
		{
			MachineRegister machine_reg = MO.GetReg();
			Emit("reg {}", machine_reg.reg);
		}
		else if (MO.IsImmediate())
		{
			Int64 immediate = MO.GetImmediate();
			Emit("imm {}", immediate);
		}
		else if (MO.IsStackObject())
		{
			Int32 offset = MO.GetStackOffset();
			Emit("stack {}", offset);
		}
		else if (MO.IsRelocable())
		{
			MachineRelocable* relocable = MO.GetRelocable();
			Emit("{}", relocable->GetSymbol());
		}
	}

}

