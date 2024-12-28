#include <iostream>
#include "MachineIRPrinter.h"
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
		EmitLn("{}: ", MF.GetSymbol());

		auto const& blocks = MF.Blocks();
		for (auto const& block : blocks)
		{
			PrintBlock(*block);
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

	}

}

