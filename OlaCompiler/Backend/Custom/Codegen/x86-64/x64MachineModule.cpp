#include "Backend/Custom/IR/IR.h"
#include "Backend/Custom/Codegen/MIR/MIR.h"
#include "x64MachineModule.h"
#include "x86_64.h"


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

		for (auto& MF : functions)
		{
			EmitFunction(MF);
		}
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

	void x64MachineModule::EmitFunction(MachineFunction& MF)
	{
		if (MF.GetFunction().GetLinkage() == Linkage::External) EmitLn<Text>(".globl {}", MF.GetName());
		EmitLn<Text>("{}:", MF.GetName());
		//EmitLn<Text>("push rbp");
		//EmitLn<Text>("mov rbp, rsp");
		//if (MF.GetStackSize() > 0)
		//{
		//	EmitLn<Text>("sub rsp, {}", MF.GetStackSize());
		//	EmitLn<Text>("and rsp, -16");
		//}
		for (MachineBasicBlock& MBB : MF) EmitBasicBlock(MBB);

		EmitLn<Text>("{}:", MF.GetEndLabel());
		//EmitLn<Text>("mov rsp, rbp");
		//EmitLn<Text>("pop rsp");
		EmitLn<Text>("ret");
	}

	void x64MachineModule::EmitBasicBlock(MachineBasicBlock& MBB)
	{
		for (MachineInst& MI : MBB) EmitInstruction(MI);
	}

	void x64MachineModule::EmitInstruction(MachineInst& MI)
	{
		MachineOpCode opcode = MI.GetOpCode();
		switch (opcode)
		{
		case MachineOpCode::Return:
		{
			auto* MBB = MI.GetParent();
			auto* MF = MBB->GetParent();
			if (MI.GetNumOperands() > 0)
			{
				IRType* ret_type = MF->GetFunction().GetReturnType();
				if (ret_type->IsIntegerType())
				{
					char const* return_reg_name = ToString(x86_64_CallInfo::MicrosoftX64ABI.return_register);
					MachineOperand const& MO = MI.Op<0>();
					if (MO.IsIntImmediate())
					{
						int64 ret_value = MO.GetImm();
						EmitLn<Text>("mov {}, {}", return_reg_name, ret_value);
					}
					else if (MO.IsFrameOffset())
					{
						std::string address_string;
						if (MO.IsFrameOffset())
						{
							address_string = std::format("qword ptr [rbp - {}]", MO.GetFrameOffset());
						}
						EmitLn<Text>("mov {}, {}", return_reg_name, address_string);
					}
				}

				//else if (ret_type->IsFloatType())
				//{
				//	double ret_value = MI.Op<0>().GetFPImm();
				//	static uint32 i = 0;
				//	std::string float_literal_label = "__return" + std::to_string(i++);
				//	EmitLn<Const>("{} dq {}", float_literal_label, ret_value);
				//	EmitLn<Text>("movss {}, [{}]", ToString(x86_64_CallInfo::MicrosoftX64ABI.fp_return_register), float_literal_label);
				//}
			}
			EmitLn<Text>("jmp {}", MF->GetEndLabel());
		}
		break;
		case MachineOpCode::Store:
		{
			MachineOperand const& address = MI.Op<0>();
			MachineOperand const& value = MI.Op<1>();

			std::string value_string;
			if (value.IsIntImmediate())
			{
				value_string = std::to_string(value.GetImm());
			}
			std::string address_string;
			if (address.IsFrameOffset())
			{
				address_string = std::format("qword ptr [rbp - {}]", address.GetFrameOffset());
			}
			EmitLn<Text>("mov {}, {}", address_string, value_string);
		}
		break;
		}
	}

}