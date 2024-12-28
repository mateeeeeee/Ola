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

namespace ola
{
	MachineModule::MachineModule(IRModule& ir_module, Target const& target) : machine_ctx(*this), target(target)
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

					PostLegalizeInstructions(MF);
				}
			}
		}
	}

	void MachineModule::LowerFunction(Function* F)
	{
		MachineGlobal* global = machine_ctx.GetGlobal(F);
		MachineFunction& MF = *dynamic_cast<MachineFunction*>(global->GetRelocable());

		TargetFrameInfo const& frame_info = target.GetFrameInfo();
		TargetISelInfo const& isel_info = target.GetISelInfo();

		for (BasicBlock& BB : F->Blocks())
		{
			MF.Blocks().push_back(std::make_unique<MachineBasicBlock>(&MF, machine_ctx.GetLabel()));
			auto& MBB = MF.Blocks().back();
			machine_ctx.MapBlock(&BB, MBB.get());
			BB.ForAllInstructions([this, &MF](Instruction& I)
				{
					if (I.GetOpcode() == Opcode::Alloca)
					{
						AllocaInst* AI = cast<AllocaInst>(&I);
						IRType const* type = AI->GetAllocatedType();
						if (type->IsArray())
						{
							IRArrayType const* array_type = cast<IRArrayType>(type);
							MachineOperand const& MO = MF.AllocateStack(array_type->GetSize());
							machine_ctx.MapOperand(AI, MO);
						}
						else
						{
							MachineOperand const& MO = MF.AllocateStack(GetOperandType(type));
							machine_ctx.MapOperand(AI, MO);
						}
					}
					if (I.GetOpcode() == Opcode::Phi)
					{
						MachineOperand const& MO = machine_ctx.VirtualReg(I.GetType());
						machine_ctx.MapOperand(&I, MO);
					}
					else if (I.GetOpcode() == Opcode::Call)
					{
						MF.SetHasCallInstructions(true);
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
		for (BasicBlock& BB : F->Blocks())
		{
			MachineBasicBlock* MBB = machine_ctx.GetBlock(&BB);
			machine_ctx.SetCurrentBasicBlock(MBB);
			for (Instruction& I : BB.Instructions())
			{
				if (!isel_info.LowerInstruction(&I, machine_ctx))
				{
					LowerInstruction(&I);
				}
			}
		}
		frame_info.EmitEpilogue(MF, machine_ctx);
	}

	void MachineModule::LowerInstruction(Instruction* I)
	{
		switch (I->GetOpcode())
		{
		case Opcode::Add:
		case Opcode::Sub:
		case Opcode::SMul:
		case Opcode::SDiv:
		case Opcode::SRem:
		case Opcode::And:
		case Opcode::Or:
		case Opcode::Xor:
		case Opcode::Shl:
		case Opcode::LShr:
		case Opcode::AShr:
		case Opcode::FAdd:
		case Opcode::FSub:
		case Opcode::FMul:
		case Opcode::FDiv:
			LowerBinary(cast<BinaryInst>(I));
			break;
		case Opcode::ICmpEQ:
		case Opcode::ICmpNE:
		case Opcode::ICmpSGE:
		case Opcode::ICmpSGT:
		case Opcode::ICmpSLE:
		case Opcode::ICmpSLT:
		case Opcode::FCmpOEQ:
		case Opcode::FCmpONE:
		case Opcode::FCmpOGE:
		case Opcode::FCmpOGT:
		case Opcode::FCmpOLE:
		case Opcode::FCmpOLT:
			LowerCompare(cast<CompareInst>(I));
			break;
		case Opcode::Neg:
		case Opcode::Not:
		case Opcode::FNeg:
			LowerUnary(cast<UnaryInst>(I));
			break;
		case Opcode::Ret:
			LowerRet(cast<ReturnInst>(I));
			break;
		case Opcode::Branch:
			LowerBranch(cast<BranchInst>(I));
			break;
		case Opcode::Load:
			LowerLoad(cast<LoadInst>(I));
			break;
		case Opcode::Store:
			LowerStore(cast<StoreInst>(I));
			break;
		case Opcode::Call:
			LowerCall(cast<CallInst>(I));
			break;
		case Opcode::ZExt:
		case Opcode::F2S:
		case Opcode::S2F:
			LowerCast(cast<CastInst>(I));
			break;
		case Opcode::GetElementPtr:
			LowerGEP(cast<GetElementPtrInst>(I));
			break;
		case Opcode::PtrAdd:
			LowerPtrAdd(cast<PtrAddInst>(I));
			break;
		case Opcode::Switch:
			LowerSwitch(cast<SwitchInst>(I));
			break;
		case Opcode::Select:
			LowerSelect(cast<SelectInst>(I));
			break;
		case Opcode::Phi:
		case Opcode::Bitcast:
		case Opcode::Alloca:
			break;
		default:
			OLA_ASSERT_MSG(false, "Not implemented yet");
		}
	}

	void MachineModule::LowerBinary(BinaryInst* BI)
	{
		MachineOperand ret = machine_ctx.VirtualReg(BI->GetType());
		MachineInstruction MI(GetMachineOpcode(BI->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(machine_ctx.GetOperand(BI->GetLHS())).SetOp<2>(machine_ctx.GetOperand(BI->GetRHS()));
		machine_ctx.EmitInst(MI);
		machine_ctx.MapOperand(BI, ret);
	}

	void MachineModule::LowerCompare(CompareInst* CI)
	{
		MachineOperand ret = machine_ctx.VirtualReg(CI->GetType());
		MachineInstruction MI(GetMachineOpcode(CI->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(machine_ctx.GetOperand(CI->GetLHS()))
			.SetOp<2>(machine_ctx.GetOperand(CI->GetRHS()))
			.SetOp<3>(MachineOperand::Immediate((Uint32)CI->GetCompareOp(), MachineType::Other));
		MachineInstruction& inserted = machine_ctx.EmitInst(MI);

		machine_ctx.MapOperand(CI, ret);
	}

	void MachineModule::LowerUnary(UnaryInst* UI)
	{
		if (UI->GetName() == "nop") return;
		MachineOperand ret = machine_ctx.VirtualReg(UI->GetType());
		MachineInstruction MI(GetMachineOpcode(UI->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(machine_ctx.GetOperand(UI->GetOperand()));
		machine_ctx.EmitInst(MI);
		machine_ctx.MapOperand(UI, ret);
	}

	void MachineModule::LowerRet(ReturnInst* RI)
	{
		target.GetFrameInfo().EmitReturn(RI, machine_ctx);
	}

	void MachineModule::LowerBranch(BranchInst* BI)
	{
		BasicBlock* src_block = BI->GetBasicBlock();
		if (BI->IsUnconditional())
		{
			BasicBlock* target = BI->GetTrueTarget();
			EmitJump(InstJump, target, src_block);
		}
		else
		{
			Value* condition = BI->GetCondition();
			BasicBlock* true_target = BI->GetTrueTarget();
			BasicBlock* false_target = BI->GetFalseTarget();

			MachineOperand const& cond_op = machine_ctx.GetOperand(condition);

			MachineInstruction testMI(InstTest);
			testMI.SetOp<0>(cond_op);
			testMI.SetOp<1>(cond_op);
			machine_ctx.EmitInst(testMI);
			EmitJump(InstJNE, true_target, src_block);
			EmitJump(InstJump, false_target, src_block);
		}
	}

	void MachineModule::LowerLoad(LoadInst* LI)
	{
		MachineOperand const& ret = machine_ctx.VirtualReg(LI->GetType());
		MachineOperand ptr = machine_ctx.GetOperand(LI->GetAddressOp());
		ptr.SetType(ret.GetType());
		MachineInstruction MI(InstLoad);
		MI.SetOp<0>(ret).SetOp<1>(ptr);
		machine_ctx.EmitInst(MI);
		machine_ctx.MapOperand(LI, ret);
	}

	void MachineModule::LowerStore(StoreInst* SI)
	{
		MachineOperand const& ptr = machine_ctx.GetOperand(SI->GetAddressOp());
		MachineOperand const& val = machine_ctx.GetOperand(SI->GetValueOp());
		MachineInstruction MI(InstStore);
		MI.SetOp<0>(ptr).SetOp<1>(val);
		machine_ctx.EmitInst(MI);
	}

	void MachineModule::LowerCall(CallInst* CI)
	{
		target.GetFrameInfo().EmitCall(CI, machine_ctx);
	}

	void MachineModule::LowerCast(CastInst* CI)
	{
		MachineOperand ret = machine_ctx.VirtualReg(CI->GetDestType());
		MachineInstruction MI(GetMachineOpcode(CI->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(machine_ctx.GetOperand(CI->GetSrc()));
		machine_ctx.EmitInst(MI);
		machine_ctx.MapOperand(CI, ret);
	}

	void MachineModule::LowerGEP(GetElementPtrInst* GEPI)
	{
		Value* base = GEPI->GetBaseOperand();
		MachineOperand base_op = machine_ctx.GetOperand(base);  
		MachineOperand result = machine_ctx.VirtualReg(GEPI->GetType());  
		IRType* current_type = GEPI->GetType();  

		if (AllocaInst* AI = dyn_cast<AllocaInst>(base); AI && AI->GetAllocatedType()->IsArray())
		{
			machine_ctx.EmitInst(MachineInstruction(InstLoadGlobalAddress)
				.SetOp<0>(result)
				.SetOp<1>(base_op));
		}
		else
		{
			machine_ctx.EmitInst(MachineInstruction(InstMove)
				.SetOp<0>(result)
				.SetOp<1>(base_op));
		}

		for (Value* index : GEPI->Indices())
		{
			MachineOperand index_op = machine_ctx.GetOperand(index);

			if (IRArrayType* array_type = dyn_cast<IRArrayType>(current_type))
			{
				Uint32 element_size = array_type->GetElementType()->GetSize();

				MachineOperand offset = machine_ctx.VirtualReg(index->GetType());
				machine_ctx.EmitInst(MachineInstruction(InstSMul)
					.SetOp<0>(offset)
					.SetOp<1>(index_op)
					.SetOp<2>(MachineOperand::Immediate(element_size, index_op.GetType())));

				MachineOperand new_result = machine_ctx.VirtualReg(GEPI->GetType());
				machine_ctx.EmitInst(MachineInstruction(InstAdd)
					.SetOp<0>(new_result)
					.SetOp<1>(result)
					.SetOp<2>(offset));

				result = new_result;
				current_type = array_type->GetElementType();
			}
			else if (IRStructType* struct_type = dyn_cast<IRStructType>(current_type))
			{
				OLA_ASSERT(false);
			}
			else if (IRPtrType* pointer_type = dyn_cast<IRPtrType>(current_type))
			{
				Uint32 pointer_size = pointer_type->GetPointeeType()->GetSize();

				MachineOperand offset = machine_ctx.VirtualReg(index->GetType());
				machine_ctx.EmitInst(MachineInstruction(InstSMul)
					.SetOp<0>(offset)
					.SetOp<1>(index_op)
					.SetOp<2>(MachineOperand::Immediate(pointer_size, index_op.GetType())));

				MachineOperand new_result = machine_ctx.VirtualReg(GEPI->GetType());
				machine_ctx.EmitInst(MachineInstruction(InstAdd)
					.SetOp<0>(new_result)
					.SetOp<1>(result)
					.SetOp<2>(offset));

				result = new_result;
				current_type = pointer_type->GetPointeeType();
			}
			else
			{
				OLA_ASSERT_MSG(false, "Unhandled type in GEP lowering!");
			}
		}

		result.SetType(GetOperandType(GEPI->GetResultElementType()));
		machine_ctx.MapOperand(GEPI, result);
	}

	void MachineModule::LowerPtrAdd(PtrAddInst* PAI)
	{
		Value* base = PAI->GetBase();
		ConstantInt* offset = cast<ConstantInt>(PAI->GetOffset());

		MachineOperand base_op = machine_ctx.GetOperand(base);
		MachineOperand base_register = machine_ctx.VirtualReg(PAI->GetType());
		if (AllocaInst* AI = dyn_cast<AllocaInst>(base); AI && AI->GetAllocatedType()->IsArray())
		{
			machine_ctx.EmitInst(MachineInstruction(InstLoadGlobalAddress)
				.SetOp<0>(base_register)
				.SetOp<1>(base_op));
		}
		else
		{
			machine_ctx.EmitInst(MachineInstruction(InstMove)
				.SetOp<0>(base_register)
				.SetOp<1>(base_op));
		}

		if (offset->GetValue() == 0)
		{
			machine_ctx.MapOperand(PAI, base_register);
		}
		else
		{
			MachineOperand result = machine_ctx.VirtualReg(MachineType::Ptr);
			machine_ctx.EmitInst(MachineInstruction(InstAdd)
				.SetOp<0>(result)
				.SetOp<1>(base_register)
				.SetOp<2>(MachineOperand::Immediate(offset->GetValue(), MachineType::Int64)));
			result.SetType(GetOperandType(PAI->GetResultElementType()));
			machine_ctx.MapOperand(PAI, result);
		}
	}

	void MachineModule::LowerSwitch(SwitchInst* SI)
	{
		if (!SI || SI->GetNumCases() == 0) return;
		BasicBlock* src_block = SI->GetBasicBlock();
		Value* cond_value = SI->GetCondition();
		MachineOperand cond_op = machine_ctx.GetOperand(cond_value);

		for (auto& case_pair : SI->Cases())
		{
			Int64 case_value = case_pair.first;
			BasicBlock* case_block = case_pair.second;

			if (!cond_op.IsImmediate())
			{
				MachineInstruction testMI(InstICmp);
				testMI.SetOp<0>(cond_op);
				testMI.SetOp<1>(MachineOperand::Immediate(case_value, MachineType::Int64));
				machine_ctx.EmitInst(testMI);

				EmitJump(InstJE, case_block, src_block);
			}
			else
			{
				Int64 imm = cond_op.GetImmediate();
				if (imm != 0)
				{
					EmitJump(InstJump, case_block, src_block);
				}
			}
		}
		if (BasicBlock* default_block = SI->GetDefaultCase())
		{
			EmitJump(InstJump, default_block, src_block);
		}
	}

	void MachineModule::LowerSelect(SelectInst* SI)
	{
		Value* predicate = SI->GetPredicate();
		Value* true_value = SI->GetTrueValue();
		Value* false_value = SI->GetFalseValue();

		MachineOperand result_reg = machine_ctx.VirtualReg(SI->GetType());
		MachineOperand true_op = machine_ctx.GetOperand(true_value);
		MachineOperand false_op = machine_ctx.GetOperand(false_value);
		MachineOperand predicate_op = machine_ctx.GetOperand(predicate);

		machine_ctx.EmitInst(MachineInstruction(InstMove)
			.SetOp<0>(result_reg)   
			.SetOp<1>(false_op));

		MachineInstruction testMI(InstTest);
		testMI.SetOp<0>(predicate_op);
		testMI.SetOp<1>(predicate_op);
		MachineInstruction& inserted = machine_ctx.EmitInst(testMI);

		machine_ctx.EmitInst(MachineInstruction(InstCMoveNE)
			.SetOp<0>(result_reg)    
			.SetOp<1>(true_op).SetIgnoreDef());
		machine_ctx.MapOperand(SI, result_reg);
	}

	void MachineModule::EmitJump(Uint32 jump_opcode, BasicBlock* dst, BasicBlock* src)
	{
		OLA_ASSERT(jump_opcode >= InstJump && jump_opcode <= InstJNE);
		std::vector<MachineOperand> dst_operands;
		std::vector<MachineOperand> src_operands;

		for (auto const& Phi : dst->PhiInsts()) 
		{
			Value* V = Phi->GetIncomingValueForBlock(src);
			if (V)
			{
				MachineInstruction MI(InstMove);
				MI.SetOp<0>(machine_ctx.GetOperand(Phi)).SetOp<1>(machine_ctx.GetOperand(V));
				machine_ctx.EmitInst(MI);
			}
		}

		MachineOperand dst_operand = MachineOperand::Relocable(machine_ctx.GetBlock(dst));
		MachineInstruction MI(jump_opcode);
		MI.SetOp<0>(dst_operand);
		machine_ctx.EmitInst(MI);
	}

	void MachineModule::LegalizeInstructions(MachineFunction& MF)
	{
		TargetISelInfo const& isel_info = target.GetISelInfo();
		for (auto& MBB : MF.Blocks())
		{
			auto& instructions = MBB->Instructions();
			for (auto MIiterator = instructions.begin(); MIiterator != instructions.end(); MIiterator++)
			{
				MachineInstruction& MI = *MIiterator;
				InstLegalizeContext ctx{ MI, instructions, MIiterator };
				isel_info.LegalizeInstruction(ctx, machine_ctx);
			}
		}
	}

	void MachineModule::PostLegalizeInstructions(MachineFunction& MF)
	{
		TargetISelInfo const& isel_info = target.GetISelInfo();

		for (auto& MBB : MF.Blocks())
		{
			auto& instructions = MBB->Instructions();
			for (auto MIiterator = instructions.begin(); MIiterator != instructions.end(); MIiterator++)
			{
				MachineInstruction& MI = *MIiterator;
				InstLegalizeContext ctx{ MI, instructions, MIiterator };
				isel_info.PostLegalizeInstruction(ctx);
			}
		}
	}

}