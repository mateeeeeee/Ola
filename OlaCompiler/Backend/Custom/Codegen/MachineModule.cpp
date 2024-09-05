#include <fstream>
#include "Target.h"
#include "MachineModule.h"
#include "MachineGlobal.h"
#include "MachineFunction.h"
#include "MachineStorage.h"
#include "MachineBasicBlock.h"
#include "LinearScanRegisterAllocator.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/CFGAnalysis.h"

namespace ola
{
	MachineModule::MachineModule(IRModule& ir_module, Target const& target) : lowering_ctx(*this), target(target)
	{
		LowerModule(&ir_module);
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
				uint32 size = type->GetSize();
				uint32 alignment = type->GetAlign();

				if (Value* init_value = V->GetInitValue())
				{
					OLA_ASSERT(isa<Constant>(init_value));
					Constant* C = cast<Constant>(init_value);

					bool const read_only = V->IsReadOnly();
					MachineDataStorage* data = new MachineDataStorage(V->GetName(), read_only);

					auto ExpandValue = [&](auto&& self, Value* V) -> void
						{
							if (ConstantInt* CI = dyn_cast<ConstantInt>(V))
							{
								int64 value = CI->GetValue();
								switch (CI->GetBitWidth())
								{
								case 8:
								{
									data->AppendByte((uint8)value);
									break;
								}
								case 64:
								{
									data->AppendQWord((uint64)value);
									break;
								}
								}
							}
							else if (ConstantFloat* CF = dyn_cast<ConstantFloat>(V))
							{
								double value = CF->GetValue();
								void* value_ptr = static_cast<void*>(&value);
								data->AppendQWord(*static_cast<uint64*>(value_ptr));
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

								uint32 const remaining_count = array_type->GetArraySize() - values.size();
								if (remaining_count)
								{
									const auto rem_size = array_type->GetElementType()->GetSize() * remaining_count;
									for (uint32 i = 0; i < remaining_count; ++i)
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
			lowering_ctx.AddGlobal(GV, &globals.back());
		}

		for (GlobalValue* GV : ir_globals)
		{
			if (GV->IsFunction())
			{
				Function* F = cast<Function>(GV);
				if (!F->IsDeclaration())
				{
					LowerFunction(F);

					MachineGlobal* global = lowering_ctx.GetGlobal(F);
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
		MachineGlobal* global = lowering_ctx.GetGlobal(F);
		MachineFunction& MF = *dynamic_cast<MachineFunction*>(global->GetRelocable());

		TargetFrameInfo const& frame_info = target.GetFrameInfo();
		TargetISelInfo const& isel_info = target.GetISelInfo();

		bool is_leaf = true;
		for (BasicBlock& BB : F->Blocks())
		{
			MF.Blocks().push_back(std::make_unique<MachineBasicBlock>(&MF, lowering_ctx.GetLabel()));
			auto& MBB = MF.Blocks().back();
			lowering_ctx.AddBlock(&BB, MBB.get());
			for (auto& I : BB.Instructions())
			{
				if (I.GetOpcode() == Opcode::Alloca)
				{
					AllocaInst* AI = cast<AllocaInst>(&I);
					IRType const* type = AI->GetAllocatedType();
					if (type->IsArray())
					{
						IRArrayType const* array_type = cast<IRArrayType>(type);
						MachineOperand const& MO = MF.AllocateStack(array_type->GetSize());
						lowering_ctx.AddOperand(AI, MO);
					}
					else
					{
						MachineOperand const& MO = MF.AllocateStack(GetOperandType(type));
						lowering_ctx.AddOperand(AI, MO);
					}
				}
				else if (I.GetOpcode() == Opcode::Call)
				{
					is_leaf = false;
				}
			}
		}
		if (!is_leaf) MF.AllocateStack(32); //temp hack for win64 until stack layout resolve is made

		auto& args = MF.Args();
		for (uint32 arg_idx = 0; arg_idx < F->GetArgCount(); ++arg_idx)
		{
			Argument* arg = F->GetArg(arg_idx);
			IRType* arg_type = F->GetArgType(arg_idx);
			auto vreg = lowering_ctx.VirtualReg(arg_type);
			lowering_ctx.AddOperand(arg, vreg);
			args.push_back(vreg);
		}
		lowering_ctx.SetCurrentBasicBlock(lowering_ctx.GetBlock(&F->GetEntryBlock()));

		frame_info.EmitPrologue(MF, lowering_ctx);
		for (BasicBlock& BB : F->Blocks())
		{
			MachineBasicBlock* MBB = lowering_ctx.GetBlock(&BB);
			lowering_ctx.SetCurrentBasicBlock(MBB);
			for (Instruction& inst : BB.Instructions())
			{
				if (!isel_info.LowerInstruction(&inst, lowering_ctx))
				{
					LowerInstruction(&inst);
				}
			}
		}
		frame_info.EmitEpilogue(MF, lowering_ctx);
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
			LowerBinary(cast<BinaryInst>(I));
			break;
		case Opcode::ICmpEQ:
		case Opcode::ICmpNE:
		case Opcode::ICmpSGE:
		case Opcode::ICmpSGT:
		case Opcode::ICmpSLE:
		case Opcode::ICmpSLT:
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
		case Opcode::Bitcast:
		case Opcode::Alloca:
		case Opcode::Phi:
			break;
		default:
			OLA_ASSERT_MSG(false, "Not implemented yet");
		}
	}

	void MachineModule::LowerBinary(BinaryInst* BI)
	{
		MachineOperand ret = lowering_ctx.VirtualReg(BI->GetType());
		MachineInstruction MI(GetMachineOpcode(BI->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(lowering_ctx.GetOperand(BI->LHS())).SetOp<2>(lowering_ctx.GetOperand(BI->RHS()));
		lowering_ctx.EmitInst(MI);
		lowering_ctx.AddOperand(BI, ret);
	}

	void MachineModule::LowerCompare(CompareInst* CI)
	{
		MachineOperand ret = lowering_ctx.VirtualReg(CI->GetType());
		MachineInstruction MI(GetMachineOpcode(CI->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(lowering_ctx.GetOperand(CI->LHS()))
			.SetOp<2>(lowering_ctx.GetOperand(CI->RHS()))
			.SetOp<3>(MachineOperand::Immediate((uint32)CI->GetCompareOp(), MachineOperandType::Other));
		lowering_ctx.EmitInst(MI);
		lowering_ctx.AddOperand(CI, ret);
	}

	void MachineModule::LowerUnary(UnaryInst* UI)
	{
		if (UI->GetName() == "nop") return;
		MachineOperand ret = lowering_ctx.VirtualReg(UI->GetType());
		MachineInstruction MI(GetMachineOpcode(UI->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(lowering_ctx.GetOperand(UI->Operand()));
		lowering_ctx.EmitInst(MI);
		lowering_ctx.AddOperand(UI, ret);
	}

	void MachineModule::LowerRet(ReturnInst* RI)
	{
		target.GetFrameInfo().EmitReturn(RI, lowering_ctx);
	}

	void MachineModule::LowerBranch(BranchInst* BI)
	{
		if (BI->IsUnconditional())
		{
			BasicBlock* target = BI->GetTrueTarget();
			MachineOperand dst_operand = MachineOperand::Relocable(lowering_ctx.GetBlock(target));
			MachineInstruction MI(InstJump);
			MI.SetOp<0>(dst_operand);
			lowering_ctx.EmitInst(MI);
		}
		else
		{
			Value* condition = BI->GetCondition();
			BasicBlock* true_target = BI->GetTrueTarget();
			BasicBlock* false_target = BI->GetFalseTarget();

			MachineOperand const& cond_op = lowering_ctx.GetOperand(condition);

			if (!cond_op.IsImmediate())
			{
				MachineInstruction testMI(InstTest);
				testMI.SetOp<0>(cond_op);
				testMI.SetOp<1>(cond_op);
				lowering_ctx.EmitInst(testMI);

				MachineOperand true_operand = MachineOperand::Relocable(lowering_ctx.GetBlock(true_target));
				MachineInstruction jmp_true(InstJNE);
				jmp_true.SetOp<0>(true_operand);
				lowering_ctx.EmitInst(jmp_true);

				MachineOperand false_operand = MachineOperand::Relocable(lowering_ctx.GetBlock(false_target));
				MachineInstruction jmp_false(InstJump);
				jmp_false.SetOp<0>(false_operand);
				lowering_ctx.EmitInst(jmp_false);
			}
			else
			{
				int64 imm = cond_op.GetImmediate();
				if (imm != 0)
				{
					MachineOperand true_operand = MachineOperand::Relocable(lowering_ctx.GetBlock(true_target));
					MachineInstruction jmp_true(InstJump);
					jmp_true.SetOp<0>(true_operand);
					lowering_ctx.EmitInst(jmp_true);
				}
				else
				{
					MachineOperand false_operand = MachineOperand::Relocable(lowering_ctx.GetBlock(false_target));
					MachineInstruction jmp_false(InstJump);
					jmp_false.SetOp<0>(false_operand);
					lowering_ctx.EmitInst(jmp_false);
				}
			}
		}
	}

	void MachineModule::LowerLoad(LoadInst* LI)
	{
		MachineOperand const& ret = lowering_ctx.VirtualReg(LI->GetType());
		MachineOperand ptr = lowering_ctx.GetOperand(LI->GetAddressOp());
		ptr.SetType(ret.GetType());
		MachineInstruction MI(InstLoad);
		MI.SetOp<0>(ret).SetOp<1>(ptr);
		lowering_ctx.EmitInst(MI);
		lowering_ctx.AddOperand(LI, ret);
	}

	void MachineModule::LowerStore(StoreInst* SI)
	{
		MachineOperand const& ptr = lowering_ctx.GetOperand(SI->GetAddressOp());
		MachineOperand const& val = lowering_ctx.GetOperand(SI->GetValueOp());
		MachineInstruction MI(InstStore);
		MI.SetOp<0>(ptr).SetOp<1>(val);
		lowering_ctx.EmitInst(MI);
	}

	void MachineModule::LowerCall(CallInst* CI)
	{
		target.GetFrameInfo().EmitCall(CI, lowering_ctx);
	}

	void MachineModule::LowerCast(CastInst* CI)
	{
		MachineOperand ret = lowering_ctx.VirtualReg(CI->GetDestType());
		MachineInstruction MI(GetMachineOpcode(CI->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(lowering_ctx.GetOperand(CI->GetSrc()));
		lowering_ctx.EmitInst(MI);
		lowering_ctx.AddOperand(CI, ret);
	}

	void MachineModule::LowerGEP(GetElementPtrInst* GEPI)
	{
		Value* base = GEPI->GetBaseOperand();
		MachineOperand base_op = lowering_ctx.GetOperand(base);  
		MachineOperand result = lowering_ctx.VirtualReg(GEPI->GetType());  
		IRType* current_type = GEPI->GetType();  

		if (AllocaInst* AI = dyn_cast<AllocaInst>(base); AI && AI->GetAllocatedType()->IsArray())
		{
			lowering_ctx.EmitInst(MachineInstruction(InstLoadGlobalAddress)
				.SetOp<0>(result)
				.SetOp<1>(base_op));
		}
		else
		{
			lowering_ctx.EmitInst(MachineInstruction(InstMove)
				.SetOp<0>(result)
				.SetOp<1>(base_op));
		}

		for (Value* index : GEPI->Indices())
		{
			MachineOperand index_op = lowering_ctx.GetOperand(index);

			if (IRArrayType* array_type = dyn_cast<IRArrayType>(current_type))
			{
				uint32 element_size = array_type->GetElementType()->GetSize();

				MachineOperand offset = lowering_ctx.VirtualReg(index->GetType());
				lowering_ctx.EmitInst(MachineInstruction(InstSMul)
					.SetOp<0>(offset)
					.SetOp<1>(index_op)
					.SetOp<2>(MachineOperand::Immediate(element_size, index_op.GetType())));

				MachineOperand new_result = lowering_ctx.VirtualReg(GEPI->GetType());
				lowering_ctx.EmitInst(MachineInstruction(InstAdd)
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
				uint32 pointer_size = pointer_type->GetPointeeType()->GetSize();

				MachineOperand offset = lowering_ctx.VirtualReg(index->GetType());
				lowering_ctx.EmitInst(MachineInstruction(InstSMul)
					.SetOp<0>(offset)
					.SetOp<1>(index_op)
					.SetOp<2>(MachineOperand::Immediate(pointer_size, index_op.GetType())));

				MachineOperand new_result = lowering_ctx.VirtualReg(GEPI->GetType());
				lowering_ctx.EmitInst(MachineInstruction(InstAdd)
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
		lowering_ctx.AddOperand(GEPI, result);
	}

	void MachineModule::LowerPtrAdd(PtrAddInst* PAI)
	{
		Value* base = PAI->GetBase();
		ConstantInt* offset = cast<ConstantInt>(PAI->GetOffset());

		MachineOperand base_op = lowering_ctx.GetOperand(base);
		MachineOperand base_register = lowering_ctx.VirtualReg(PAI->GetType());
		if (AllocaInst* AI = dyn_cast<AllocaInst>(base); AI && AI->GetAllocatedType()->IsArray())
		{
			lowering_ctx.EmitInst(MachineInstruction(InstLoadGlobalAddress)
				.SetOp<0>(base_register)
				.SetOp<1>(base_op));
		}
		else
		{
			lowering_ctx.EmitInst(MachineInstruction(InstMove)
				.SetOp<0>(base_register)
				.SetOp<1>(base_op));
		}

		if (offset->GetValue() == 0)
		{
			lowering_ctx.AddOperand(PAI, base_register);
		}
		else
		{
			MachineOperand result = lowering_ctx.VirtualReg(MachineOperandType::Ptr);
			lowering_ctx.EmitInst(MachineInstruction(InstAdd)
				.SetOp<0>(result)
				.SetOp<1>(base_register)
				.SetOp<2>(MachineOperand::Immediate(offset->GetValue(), MachineOperandType::Int64)));
			result.SetType(GetOperandType(PAI->GetResultElementType()));
			lowering_ctx.AddOperand(PAI, result);
		}
	}

	void MachineModule::LowerSwitch(SwitchInst* SI)
	{
		if (!SI || SI->GetNumCases() == 0) return;

		Value* cond_value = SI->GetCondition();
		MachineOperand cond_op = lowering_ctx.GetOperand(cond_value);

		for (auto& case_pair : SI->Cases())
		{
			int64 case_value = case_pair.first;
			BasicBlock* case_block = case_pair.second;

			if (!cond_op.IsImmediate())
			{
				MachineInstruction testMI(InstICmp);
				testMI.SetOp<0>(cond_op);
				testMI.SetOp<1>(MachineOperand::Immediate(case_value, MachineOperandType::Int64));
				lowering_ctx.EmitInst(testMI);

				MachineOperand case_label = MachineOperand::Relocable(lowering_ctx.GetBlock(case_block));
				MachineInstruction case_jmp(InstJE);
				case_jmp.SetOp<0>(case_label);
				lowering_ctx.EmitInst(case_jmp);
			}
			else
			{
				int64 imm = cond_op.GetImmediate();
				if (imm != 0)
				{
					MachineOperand true_operand = MachineOperand::Relocable(lowering_ctx.GetBlock(case_block));
					MachineInstruction jmp_true(InstJump);
					jmp_true.SetOp<0>(true_operand);
					lowering_ctx.EmitInst(jmp_true);
				}
			}
		}

		BasicBlock* default_block = SI->GetDefaultCase();
		if(default_block) lowering_ctx.EmitInst(MachineInstruction(InstJump).SetOp<0>(MachineOperand::Relocable(lowering_ctx.GetBlock(default_block))));
	}

	void MachineModule::LowerSelect(SelectInst* SI)
	{
		Value* predicate = SI->GetPredicate();
		Value* true_value = SI->GetTrueValue();
		Value* false_value = SI->GetFalseValue();

		MachineOperand result_reg = lowering_ctx.VirtualReg(SI->GetType());
		MachineOperand true_op = lowering_ctx.GetOperand(true_value);
		MachineOperand false_op = lowering_ctx.GetOperand(false_value);
		MachineOperand predicate_op = lowering_ctx.GetOperand(predicate);

		lowering_ctx.EmitInst(MachineInstruction(InstMove)
			.SetOp<0>(result_reg)   
			.SetOp<1>(false_op));

		MachineInstruction testMI(InstTest);
		testMI.SetOp<0>(predicate_op);
		testMI.SetOp<1>(predicate_op);
		lowering_ctx.EmitInst(testMI);

		lowering_ctx.EmitInst(MachineInstruction(InstCMoveNE)
			.SetOp<0>(result_reg)    
			.SetOp<1>(true_op).SetIgnoreDef());
		lowering_ctx.AddOperand(SI, result_reg);
	}

	void MachineModule::LowerCFGAnalysis(Function* F)
	{
		CFGAnalysisPass CFG{};
		CFG.RunOn(*F);
		CFGResult const& cfg_result = CFG.GetResult();
		for (auto&& [BB, info] : cfg_result)
		{
			MachineBasicBlock* MBB = lowering_ctx.GetBlock(BB);
			for (auto* P : info.predecessors) MBB->AddPredecessor(lowering_ctx.GetBlock(P));
			for (auto* S : info.successors) MBB->AddSuccessor(lowering_ctx.GetBlock(S));
		}
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
				isel_info.LegalizeInstruction(ctx, lowering_ctx);
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