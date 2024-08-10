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
							if (ConstantInt* CI = dyn_cast<ConstantInt>(C))
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
							else if (ConstantFloat* CF = dyn_cast<ConstantFloat>(C))
							{
								double value = CF->GetValue();
								void* value_ptr = static_cast<void*>(&value);
								data->AppendQWord(*static_cast<uint64*>(value_ptr));
							}
							else if (ConstantArray* CA = dyn_cast<ConstantArray>(C))
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

		TargetFrameInfo const& frame_info = target.GetFrameInfo();
		TargetISelInfo const& isel_info = target.GetISelInfo();
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

					LinearScanRegisterAllocator register_allocator(*this);
					register_allocator.AssignRegisters(MF);
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
					MachineOperand const& MO = MF.AllocateStack(GetOperandType(type));
					lowering_ctx.AddOperand(AI, MO);
				}
				else if (I.GetOpcode() == Opcode::Call)
				{
					is_leaf = false;
				}
			}
		}
		if (!is_leaf) MF.AllocateStack(32);

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

	void MachineModule::LowerInstruction(Instruction* inst)
	{
		switch (inst->GetOpcode())
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
		case Opcode::ICmpEQ:
		case Opcode::ICmpNE:
		case Opcode::ICmpSGE:
		case Opcode::ICmpSGT:
		case Opcode::ICmpSLE:
		case Opcode::ICmpSLT:
			LowerBinary(cast<BinaryInst>(inst));
			break;
		case Opcode::Neg:
		case Opcode::Not:
		case Opcode::FNeg:
			LowerUnary(cast<UnaryInst>(inst));
			break;
		case Opcode::Ret:
			LowerRet(cast<ReturnInst>(inst));
			break;
		case Opcode::Branch:
			LowerBranch(cast<BranchInst>(inst));
			break;
		case Opcode::Load:
			LowerLoad(cast<LoadInst>(inst));
			break;
		case Opcode::Store:
			LowerStore(cast<StoreInst>(inst));
			break;
		case Opcode::Call:
			LowerCall(cast<CallInst>(inst));
			break;
		case Opcode::ZExt:
			LowerCast(cast<CastInst>(inst));
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
		MI.SetOp<0>(ret).SetOp<1>(lowering_ctx.GetOperand(CI->LHS())).SetOp<2>(lowering_ctx.GetOperand(CI->RHS()));
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
				if (imm > 0)
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
		MachineOperand const& ptr = lowering_ctx.GetOperand(LI->GetAddressOp());
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
		MI.SetOp<1>(val).SetOp<0>(ptr);
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
}