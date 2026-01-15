#include <fstream>
#include "Target.h"
#include "MachineModule.h"
#include "MachineGlobal.h"
#include "MachineFunction.h"
#include "MachineStorage.h"
#include "MachineBasicBlock.h"
#include "MachineIRPrinter.h"
#include "LinearScanRegisterAllocator.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/IR/Passes/DominatorTreeAnalysisPass.h"
#include "Core/Log.h"

namespace ola
{
	MachineModule::MachineModule(IRModule& ir_module, Target const& target, FunctionAnalysisManager& FAM) 
		: machine_ctx(*this), target(target), FAM(FAM)
	{
		LowerModule(&ir_module);
	}

	void MachineModule::EmitMIR(std::string_view mir_file)
	{
		std::ofstream mir_stream(mir_file.data());
		MachineIRPrinter mir_printer(target, mir_stream);
		mir_printer.PrintModule(*this);
	}

	void MachineModule::EmitAssembly(std::string_view assembly_file)
	{
		target.EmitAssembly(*this, assembly_file);
	}

	void MachineModule::LowerModule(IRModule* ir_module)
	{
		auto const& ir_globals = ir_module->Globals();
		globals.reserve(ir_globals.size());
		for (GlobalValue* GV : ir_globals)
		{
			if (GV->IsFunction())
			{
				Function* F = cast<Function>(GV);
				globals.emplace_back(new MachineFunction(F->GetName(), F->IsDeclaration()), F->GetLinkage());
			}
			else
			{
				GlobalVariable* V = cast<GlobalVariable>(GV);
				IRType* type = V->GetValueType();
				Uint32 size = type->GetSize();
				Uint32 alignment = type->GetAlign();

				if (Value* init_value = V->GetInitValue())
				{
					OLA_ASSERT(isa<Constant>(init_value));
					Constant* C = cast<Constant>(init_value);

					MachineDataStorage* data = new MachineDataStorage(V->GetName(), V->IsReadOnly());
					auto ExpandValue = [&](auto&& self, Value* V) -> void
						{
							if (ConstantInt* CI = dyn_cast<ConstantInt>(V))
							{
								Int64 value = CI->GetValue();
								switch (CI->GetBitWidth())
								{
								case 8:
								{
									data->AppendByte((Uint8)value);
									break;
								}
								case 64:
								{
									data->AppendQWord((Uint64)value);
									break;
								}
								}
							}
							else if (ConstantFloat* CF = dyn_cast<ConstantFloat>(V))
							{
								Float64 value = CF->GetValue();
								void* value_ptr = static_cast<void*>(&value);
								data->AppendQWord(*static_cast<Uint64*>(value_ptr));
							}
							else if (ConstantString* CS = dyn_cast<ConstantString>(V))
							{
								data->AppendString(CS->GetValue());
							}
							else if (ConstantArray* CA = dyn_cast<ConstantArray>(V))
							{
								IRArrayType const* array_type = CA->GetArrayType();
								auto const& values = CA->Values();
								for (auto sub : values) self(self, sub);

								Uint32 const remaining_count = array_type->GetArraySize() - values.size();
								if (remaining_count)
								{
									const auto rem_size = array_type->GetElementType()->GetSize() * remaining_count;
									for (Uint32 i = 0; i < remaining_count; ++i)
									{
										data->AppendByte(0);
									}
								}
							}
							else OLA_ASSERT(false);
						};
					ExpandValue(ExpandValue, init_value);

					globals.emplace_back(data, V->GetLinkage(), alignment);
				}
				else
				{
					globals.emplace_back(new MachineZeroStorage(V->GetName(), size), V->GetLinkage(), alignment);
				}
			}
			machine_ctx.MapGlobal(GV, &globals.back());
		}

		TargetFrameInfo const& frame_info = target.GetFrameInfo();
		for (GlobalValue* GV : ir_globals)
		{
			if (GV->IsFunction())
			{
				Function* F = cast<Function>(GV);
				if (!F->IsDeclaration())
				{
					LowerFunction(F);

					MachineGlobal* global = machine_ctx.GetGlobal(F);
					MachineFunction& MF = *static_cast<MachineFunction*>(global->GetRelocable());
					LegalizeInstructions(MF);

					LinearScanRegisterAllocator register_allocator(*this);
					register_allocator.AssignRegisters(MF);
					machine_ctx.SetUsedRegistersInfo(&register_allocator.GetUsedRegistersInfo());

					machine_ctx.SetCurrentBasicBlock(machine_ctx.GetBlock(&F->GetEntryBlock()));
					frame_info.EmitProloguePostRA(MF, machine_ctx);
					machine_ctx.SetCurrentBasicBlock(machine_ctx.GetBlock(&F->GetLastBlock()));
					frame_info.EmitEpiloguePostRA(MF, machine_ctx);

					PostLegalizeInstructions(MF);
				}
			}
		}
	}

	void MachineModule::LowerFunction(Function* F)
	{
		DominatorTree const& DT = FAM.GetResult<DominatorTreeAnalysisPass>(*F);

		MachineGlobal* global = machine_ctx.GetGlobal(F);
		MachineFunction& MF = *dynamic_cast<MachineFunction*>(global->GetRelocable());

		TargetFrameInfo const& frame_info = target.GetFrameInfo();

		for (BasicBlock& BB : *F)
		{
			MF.Blocks().push_back(std::make_unique<MachineBasicBlock>(&MF, machine_ctx.GetLabel()));
			auto& MBB = MF.Blocks().back();
			machine_ctx.MapBlock(&BB, MBB.get());
			BB.ForAllInstructions([this, &MF](Instruction& I)
				{
					if (AllocaInst* AI = dyn_cast<AllocaInst>(&I))
					{
						IRType const* type = AI->GetAllocatedType();
						if (type->IsArray())
						{
							IRArrayType const* array_type = cast<IRArrayType>(type);
							MachineOperand const& MO = MF.AllocateLocalStack(array_type->GetSize());
							machine_ctx.MapOperand(AI, MO);
						}
						else if (type->IsStruct())
						{
							IRStructType const* struct_type = cast<IRStructType>(type);
							MachineOperand const& MO = MF.AllocateLocalStack(struct_type->GetSize());
							machine_ctx.MapOperand(AI, MO);
						}
						else
						{
							MachineOperand const& MO = MF.AllocateLocalStack(GetOperandType(type));
							machine_ctx.MapOperand(AI, MO);
						}
					}
					if (isa<PhiInst>(&I))
					{
						MachineOperand const& MO = machine_ctx.VirtualReg(I.GetType());
						machine_ctx.MapOperand(&I, MO);
					}
					else if (CallInst* CI = dyn_cast<CallInst>(&I))
					{
						MF.AddCallInstructionArgCount(CI->ArgSize());
					}
				});
		}

		auto& args = MF.Args();
		for (Uint32 arg_idx = 0; arg_idx < F->GetArgCount(); ++arg_idx)
		{
			Argument* arg = F->GetArg(arg_idx);
			IRType* arg_type = F->GetArgType(arg_idx);
			auto vreg = machine_ctx.VirtualReg(arg_type);
			machine_ctx.MapOperand(arg, vreg);
			args.push_back(vreg);
		}

		machine_ctx.SetCurrentBasicBlock(machine_ctx.GetBlock(&F->GetEntryBlock()));
		frame_info.EmitPrologue(MF, machine_ctx);

		ISelDriver isel_driver(machine_ctx, target, isel_mode);
		for (BasicBlock* BB : DT.Blocks())
		{
			MachineBasicBlock* MBB = machine_ctx.GetBlock(BB);
			machine_ctx.SetCurrentBasicBlock(MBB);
			isel_driver.SelectBasicBlock(*BB);
		}

		machine_ctx.SetCurrentBasicBlock(machine_ctx.GetBlock(&F->GetLastBlock()));
		frame_info.EmitEpilogue(MF, machine_ctx);
	}

	void MachineModule::LegalizeInstructions(MachineFunction& MF)
	{
		TargetISelInfo const& isel_info = target.GetISelInfo();
		for (auto& MBB : MF.Blocks())
		{
			machine_ctx.SetCurrentBasicBlock(MBB.get());
			auto& instructions = MBB->Instructions();
			for (auto MIiterator = instructions.begin(); MIiterator != instructions.end(); MIiterator++)
			{
				MachineInstruction& MI = *MIiterator;
				InstLegalizeContext ctx{ target.GetRegisterInfo(), MI, instructions, MIiterator };
				isel_info.LegalizeInstruction(ctx, machine_ctx);
			}
		}
	}

	void MachineModule::PostLegalizeInstructions(MachineFunction& MF)
	{
		TargetISelInfo const& isel_info = target.GetISelInfo();
		for (auto& MBB : MF.Blocks())
		{
			machine_ctx.SetCurrentBasicBlock(MBB.get());
			auto& instructions = MBB->Instructions();
			for (auto MIiterator = instructions.begin(); MIiterator != instructions.end(); MIiterator++)
			{
				MachineInstruction& MI = *MIiterator;
				InstLegalizeContext ctx{ target.GetRegisterInfo(), MI, instructions, MIiterator };
				isel_info.PostLegalizeInstruction(ctx);
			}
		}
	}

}