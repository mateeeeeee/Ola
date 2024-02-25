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
		EmitLn<Text>("push rbp");
		EmitLn<Text>("mov rbp, rsp");
		if (MF.GetStackSize() > 0)
		{
			EmitLn<Text>("sub rsp, {}", MF.GetStackSize());
			EmitLn<Text>("and rsp, -16");
		}
		for (MachineBasicBlock& MBB : MF) EmitBasicBlock(MBB);

		EmitLn<Text>("mov rsp, rbp");
		EmitLn<Text>("pop rbp");
		EmitLn<Text>("ret");
	}

	void x64MachineModule::EmitBasicBlock(MachineBasicBlock& MBB)
	{
		if (MBB.Empty()) return;

		EmitLn<Text>("{}:", MBB.GetName());
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
					char const* return_reg_name = ToString(x86_64::windows::return_register);
					MachineOperand const& MO = MI.Op<0>();

					std::string ret_value = GetOperandAsString(MO);
					EmitLn<Text>("mov {}, {}", return_reg_name, ret_value);
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
		}
		break;
		case MachineOpCode::Store:
		{
			MachineOperand const& address = MI.Op<0>();
			MachineOperand const& value = MI.Op<1>();
			std::string value_string = GetOperandAsString(value);
			std::string address_string = GetOperandAsString(address);
			EmitLn<Text>("mov {}, {}", address_string, value_string);
		}
		break;
		case MachineOpCode::Add:
		{
			MachineOperand const& lhs = MI.Op<0>();
			MachineOperand const& rhs = MI.Op<1>();

			std::string lhs_string = GetOperandAsString(lhs);
			std::string rhs_string = GetOperandAsString(rhs);

			uint32 result_reg_idx = MI.GetReg(); result_reg_idx = result_reg_idx & ~(1u << 31);
			x86_64::Register reg = x86_64::windows::callee_saved_registers[result_reg_idx];
			std::string res_string = ToString(reg);

			EmitLn<Text>("mov {}, {}", res_string, lhs_string);
			EmitLn<Text>("add {}, {}", res_string, rhs_string);
		}
		break;
		}
	}

	std::string x64MachineModule::GetOperandAsString(MachineOperand const& MO)
	{
		if (MO.IsIntImmediate())
		{
			return std::to_string(MO.GetImm());
		}
		else if (MO.IsFPImmediate())
		{
			return std::to_string(MO.GetFPImm());
		}
		else if (MO.IsReg())
		{
			uint32 reg_idx = MO.GetReg();
			reg_idx = reg_idx & ~(1u << 31);
			x86_64::Register reg = x86_64::windows::callee_saved_registers[reg_idx];
			return ToString(reg);
		}
		else if (MO.IsMemoryRef())
		{
			MemoryRef mem_ref = MO.GetMemoryRef();
		}
		else if (MO.IsFrameOffset())
		{
			return std::format("qword ptr [rbp - {}]", MO.GetFrameOffset());
		}
		else if (MO.IsGlobalVariable())
		{
			std::string_view gvar_name = MO.GetGlobalVariable();
			return std::string(gvar_name);
		}
		return "";
	}

}