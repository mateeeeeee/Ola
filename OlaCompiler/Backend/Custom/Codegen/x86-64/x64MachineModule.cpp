#include "x64MachineModule.h"
#include "Backend/Custom/IR/IR.h"

namespace ola
{
	using enum MachineSegment; 

	x64MachineModule::x64MachineModule(IRModule& ir_module) : MachineModule(ir_module)
	{
		EmitLn<None>(".intel_syntax noprefix");
		EmitLn<Text>(".section .text");
		EmitLn<Data>(".section .data");
		EmitLn<Const>(".section .rodata");
		EmitLn<BSS>(".section .bss");

		EmitGlobalVariables();
	}

	void x64MachineModule::Emit()
	{
		EmitLn<Text>(".globl main");
		EmitLn<Text>("main:");
		EmitLn<Text>("push    rbp");
		EmitLn<Text>("mov     rbp, rsp");
		EmitLn<Text>("mov     dword ptr[rbp - 4], 0");
		EmitLn<Text>("mov eax, 0");
		EmitLn<Text>("pop rbp");
		EmitLn<Text>("ret");
	}

	void x64MachineModule::EmitGlobalVariables()
	{
		for (auto const& gvar : global_variables)
		{

		}
	}

}