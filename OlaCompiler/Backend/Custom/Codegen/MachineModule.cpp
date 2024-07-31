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
									const auto rem_size = array_type->GetBaseType()->GetSize() * remaining_count;
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
		case Opcode::Mul:
		case Opcode::UDiv:
		case Opcode::URem:
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
		case Opcode::ICmpEQ:
			break;
		case Opcode::Alloca:
		case Opcode::Phi:
			break;
		default:
			OLA_ASSERT_MSG(false, "Not implemented yet");
		}
	}

	void MachineModule::LowerBinary(BinaryInst* inst)
	{
		MachineOperand ret = lowering_ctx.VirtualReg(inst->GetType());
		MachineInstruction MI(GetMachineOpcode(inst->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(lowering_ctx.GetOperand(inst->LHS())).SetOp<2>(lowering_ctx.GetOperand(inst->RHS()));
		lowering_ctx.EmitInst(MI);
		lowering_ctx.AddOperand(inst, ret);
	}

	void MachineModule::LowerCompare(CompareInst* inst)
	{
		MachineOperand ret = lowering_ctx.VirtualReg(inst->GetType());
		MachineInstruction MI(GetMachineOpcode(inst->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(lowering_ctx.GetOperand(inst->LHS())).SetOp<2>(lowering_ctx.GetOperand(inst->RHS()));
		lowering_ctx.EmitInst(MI);
		lowering_ctx.AddOperand(inst, ret);
	}

	void MachineModule::LowerUnary(UnaryInst* inst)
	{
		if (inst->GetName() == "nop") return;
		MachineOperand ret = lowering_ctx.VirtualReg(inst->GetType());
		MachineInstruction MI(GetMachineOpcode(inst->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(lowering_ctx.GetOperand(inst->GetOperand(0)));
		lowering_ctx.EmitInst(MI);
		lowering_ctx.AddOperand(inst, ret);
	}

	void MachineModule::LowerRet(ReturnInst* inst)
	{
		target.GetFrameInfo().EmitReturn(inst, lowering_ctx);
	}

	void MachineModule::LowerBranch(BranchInst* inst)
	{
		if (inst->IsUnconditional())
		{
			BasicBlock* target = inst->GetTrueTarget();
			MachineOperand dst_operand = MachineOperand::Relocable(lowering_ctx.GetBlock(target));
			MachineInstruction MI(InstJump);
			MI.SetOp<0>(dst_operand);
			lowering_ctx.EmitInst(MI);
		}
		else
		{

		}
	}

	void MachineModule::LowerLoad(LoadInst* inst)
	{
		MachineOperand const& ret = lowering_ctx.VirtualReg(inst->GetType());
		MachineOperand const& ptr = lowering_ctx.GetOperand(inst->GetAddressOp());
		MachineInstruction MI(InstLoad);
		MI.SetOp<0>(ret).SetOp<1>(ptr);
		lowering_ctx.EmitInst(MI);
		lowering_ctx.AddOperand(inst, ret);
	}

	void MachineModule::LowerStore(StoreInst* inst)
	{
		MachineOperand const& ptr = lowering_ctx.GetOperand(inst->GetAddressOp());
		MachineOperand const& val = lowering_ctx.GetOperand(inst->GetValueOp());
		MachineInstruction MI(InstStore);
		MI.SetOp<1>(val).SetOp<0>(ptr);
		lowering_ctx.EmitInst(MI);
	}

	void MachineModule::LowerCall(CallInst* inst)
	{
		target.GetFrameInfo().EmitCall(inst, lowering_ctx);
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