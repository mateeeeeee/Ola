#include <fstream>
#include "MIRModule.h"
#include "Target.h"
#include "MIRGlobal.h"
#include "MIRBasicBlock.h"
#include "LinearScanRegisterAllocator.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/CFGAnalysis.h"

namespace ola
{
	namespace
	{
		void EmitMIRInstruction(std::ofstream& mir, MIRInstruction& MI)
		{
		}
	}

	MIRModule::MIRModule(IRModule& ir_module, Target const& target) : lowering_ctx(*this), target(target)
	{
		LowerModule(&ir_module);
	}

	void MIRModule::EmitAssembly(std::string_view assembly_file)
	{
		target.EmitAssembly(*this, assembly_file);
	}

	void MIRModule::LowerModule(IRModule* ir_module)
	{
		auto const& ir_globals = ir_module->Globals();
		globals.reserve(ir_globals.size());
		for (GlobalValue* GV : ir_globals)
		{
			if (GV->IsFunction())
			{
				Function* F = cast<Function>(GV);
				globals.emplace_back(new MIRFunction(F->GetName()), F->GetLinkage());
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
					MIRDataStorage* data = new MIRDataStorage(V->GetName(), read_only);

					auto ExpandValue = [&](auto&& self, Value* V) -> void
						{
							if (ConstantInt* CI = dyn_cast<ConstantInt>(C))
							{
								int64 value = CI->GetValue();
								switch (CI->GetBitWidth())
								{
								case 1:
								{
									data->AppendByte((uint8)value);
									break;
								}
								case 8:
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
					globals.emplace_back(new MIRZeroStorage(V->GetName(), size), V->GetLinkage(), alignment);
				}
			}
			lowering_ctx.AddGlobal(GV, &globals.back());
		}

		TargetISelInfo const& isel_info = target.GetISelInfo();
		for (GlobalValue* GV : ir_globals)
		{
			if (GV->IsFunction())
			{
				Function* F = cast<Function>(GV);
				LowerFunction(F);

				MIRGlobal* global = lowering_ctx.GetGlobal(F);
				MIRFunction& MF = *dynamic_cast<MIRFunction*>(global->GetRelocable());
				for (auto& MBB : MF.Blocks())
				{
					auto& instructions = MBB->Instructions();
					for (auto MIiterator = instructions.begin(); MIiterator != instructions.end(); MIiterator++)
					{
						MIRInstruction& MI = *MIiterator;
						InstLegalizeContext ctx{ MI, instructions, MIiterator };
						isel_info.LegalizeInstruction(ctx, lowering_ctx);
					}
				}

				LinearScanRegisterAllocator register_allocator(*this);
				register_allocator.AssignRegisters(MF);
			}
		}
	}

	void MIRModule::LowerFunction(Function* F)
	{
		MIRGlobal* global = lowering_ctx.GetGlobal(F);
		MIRFunction& MF = *dynamic_cast<MIRFunction*>(global->GetRelocable());

		for (BasicBlock& BB : F->Blocks())
		{
			MF.Blocks().push_back(std::make_unique<MIRBasicBlock>(&MF, lowering_ctx.GetLabel()));
			auto& MBB = MF.Blocks().back();
			lowering_ctx.AddBlock(&BB, MBB.get());
			for (auto& I : BB.Instructions())
			{
				if (I.GetOpcode() == Opcode::Phi)
				{
					auto vreg = lowering_ctx.VirtualReg(I.GetType());
					lowering_ctx.AddOperand(&I, vreg);
				}
				else if (I.GetOpcode() == Opcode::Alloca)
				{
					AllocaInst* AI = cast<AllocaInst>(&I);
					IRType const* type = AI->GetAllocatedType();
					MIROperand const& MO = MF.AllocateStack(GetOperandType(type));
					lowering_ctx.AddOperand(AI, MO);
				}
			}
		}
		LowerCFGAnalysis(F);

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

		TargetFrameInfo const& frame_info = target.GetFrameInfo();
		TargetISelInfo const& isel_info = target.GetISelInfo();

		frame_info.EmitPrologue(MF, lowering_ctx);
		for (BasicBlock& BB : F->Blocks())
		{
			MIRBasicBlock* MBB = lowering_ctx.GetBlock(&BB);
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

	void MIRModule::LowerInstruction(Instruction* inst)
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
		case Opcode::Alloca:
		case Opcode::Phi:
			break;
		default:
			OLA_ASSERT_MSG(false, "Not implemented yet");
		}
	}

	void MIRModule::LowerBinary(BinaryInst* inst)
	{
		MIROperand ret = lowering_ctx.VirtualReg(inst->GetType());
		MIRInstruction MI(GetMachineID(inst->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(lowering_ctx.GetOperand(inst->GetOperand(0))).SetOp<2>(lowering_ctx.GetOperand(inst->GetOperand(1)));
		lowering_ctx.EmitInst(MI);
		lowering_ctx.AddOperand(inst, ret);
	}

	void MIRModule::LowerUnary(UnaryInst* inst)
	{
		MIROperand ret = lowering_ctx.VirtualReg(inst->GetType());
		MIRInstruction MI(GetMachineID(inst->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(lowering_ctx.GetOperand(inst->GetOperand(0)));
		lowering_ctx.EmitInst(MI);
		lowering_ctx.AddOperand(inst, ret);
	}

	void MIRModule::LowerRet(ReturnInst* inst)
	{
		target.GetFrameInfo().EmitReturn(inst, lowering_ctx);
	}

	void MIRModule::LowerBranch(BranchInst* inst)
	{
		if (inst->IsUnconditional())
		{
			BasicBlock* target = inst->GetTrueTarget();
			MIROperand dst_operand = MIROperand::Relocable(lowering_ctx.GetBlock(target));
			MIRInstruction MI(InstJump);
			MI.SetOp<0>(dst_operand);
			lowering_ctx.EmitInst(MI);
		}
		else
		{

		}
	}

	void MIRModule::LowerLoad(LoadInst* inst)
	{
		MIROperand const& ret = lowering_ctx.VirtualReg(inst->GetType());
		MIROperand const& ptr = lowering_ctx.GetOperand(inst->GetAddressOp());
		MIRInstruction MI(InstLoad);
		MI.SetOp<0>(ret).SetOp<1>(ptr);
		lowering_ctx.EmitInst(MI);
		lowering_ctx.AddOperand(inst, ret);
	}

	void MIRModule::LowerStore(StoreInst* inst)
	{
		MIROperand const& ptr = lowering_ctx.GetOperand(inst->GetAddressOp());
		MIROperand const& val = lowering_ctx.GetOperand(inst->GetValueOp());
		MIRInstruction MI(InstStore);
		MI.SetOp<1>(val).SetOp<0>(ptr);
		lowering_ctx.EmitInst(MI);
	}

	void MIRModule::LowerCall(CallInst* inst)
	{
		target.GetFrameInfo().EmitCall(inst, lowering_ctx);
	}

	void MIRModule::LowerCFGAnalysis(Function* F)
	{
		CFGAnalysisPass CFG{};
		CFG.RunOn(*F);
		CFGResult const& cfg_result = CFG.GetResult();
		for (auto&& [BB, info] : cfg_result)
		{
			MIRBasicBlock* MBB = lowering_ctx.GetBlock(BB);
			for (auto* P : info.predecessors) MBB->AddPredecessor(lowering_ctx.GetBlock(P));
			for (auto* S : info.successors) MBB->AddSuccessor(lowering_ctx.GetBlock(S));
		}
	}


}