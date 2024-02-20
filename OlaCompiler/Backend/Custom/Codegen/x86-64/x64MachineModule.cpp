#include "x64MachineModule.h"
#include "x86_64.h"
#include "Backend/Custom/IR/IR.h"
#include "Backend/Custom/Codegen/MIR/MIR.h"


namespace ola
{
	using enum MachineSegment; 

	x64MachineModule::x64MachineModule(IRModule& ir_module) : MachineModule(ir_module)
	{
	}

	void x64MachineModule::Emit()
	{
		EmitLn<None>(".intel_syntax noprefix");
		EmitLn<Text>(".section .text");
		EmitLn<Data>(".section .data");
		EmitLn<Const>(".section .rodata");
		EmitLn<BSS>(".section .bss");
		EmitGlobalVariables();

		for (auto& machine_function : functions)
		{
			EmitFunction(machine_function);
		}

		//EmitLn<Text>(".globl main");
		//EmitLn<Text>("main:");
		//EmitLn<Text>("push    rbp");
		//EmitLn<Text>("mov     rbp, rsp");
		//EmitLn<Text>("mov     dword ptr[rbp - 4], 0");
		//EmitLn<Text>("mov eax, 0");
		//EmitLn<Text>("pop rbp");
		//EmitLn<Text>("ret");
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

	void x64MachineModule::EmitFunction(MachineFunction& mf)
	{
		if (mf.GetFunction().GetLinkage() == Linkage::External) EmitLn<Text>(".globl {}", mf.GetName());
		EmitLn<Text>("{}:", mf.GetName());

		for (MachineBasicBlock& mbb : mf) EmitBasicBlock(mbb);
	}

	void x64MachineModule::EmitBasicBlock(MachineBasicBlock& mbb)
	{
		for (MachineInst& minst : mbb) EmitInstruction(minst);
	}

	void x64MachineModule::EmitInstruction(MachineInst& minst)
	{
		if (minst.GetOpCode() == MachineOpCode::Return)
		{
			if (minst.GetOpCount() > 0)
			{
				int64 ret_value = minst.Op<0>().GetImm();
				EmitLn<Text>("mov {}, {}", ToString(x86_64_CallInfo::MicrosoftX64ABI.return_register), ret_value);

			}
			EmitLn<Text>("ret");
		}
	}

}