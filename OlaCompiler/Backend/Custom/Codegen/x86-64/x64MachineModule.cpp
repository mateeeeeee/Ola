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
			bool has_init = gvar.GetInitValue() != nullptr;
			bool is_const = gvar.IsConst();
			bool is_external = gvar.GetLinkage() == Linkage::External;
			IRType* type = gvar.GetValueType();
			std::string_view name = gvar.GetName();

			if (is_external)
			{
				if (has_init) EmitLn<Data>(".globl {}", name);
				EmitLn<BSS>(".globl {}", name);
			}

			if (has_init)
			{
				Value* init = gvar.GetInitValue();
				if (is_const)
				{
					EmitLn<Const>("{} : {} {}", name);
				}
				else
				{
					EmitLn<Data>("{} : {} {}", name);
				}
			}
			else
			{
				//.section.bss
				//uninitializedVar: .space  8
				EmitLn<BSS>("");

				//.section.bss
				//.globl externalVar
				//.lcomm externalVar, 8
			}
		}
	}

}