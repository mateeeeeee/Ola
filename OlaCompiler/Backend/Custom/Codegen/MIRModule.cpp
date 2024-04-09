#include "MIRModule.h"
#include "Target.h"
#include "MIRGlobal.h"
#include "LegalizeContext.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/CFGAnalysis.h"

namespace ola
{
	MIRModule::MIRModule(IRModule& ir_module, Target const& target) : lowering_ctx(*this), legalize_ctx(*this), target(target)
	{
		LowerModule(&ir_module);
	}

	void MIRModule::LowerModule(IRModule* ir_module)
	{
		auto const& ir_globals = ir_module->Globals();

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
					for (MIRInstruction& MI : MBB->Instructions())
					{
						if (!isel_info.IsLegalInstruction(MI))
						{
							isel_info.LegalizeInstruction(MI, legalize_ctx);
						}
					}
				}
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
			for (auto& inst : BB.Instructions())
			{
				if (inst.GetInstID() == InstructionID::Phi)
				{
					auto vreg = lowering_ctx.VirtualReg(inst.GetType());
					lowering_ctx.AddOperand(&inst, vreg);
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
		lowering_ctx.SetCurrentBasicBlock(MF.Blocks().front().get());

		lowering_ctx.SetCurrentBasicBlock(lowering_ctx.GetBlock(&F->GetEntryBlock()));

		for (Instruction& inst : F->GetEntryBlock().Instructions())
		{
			if (inst.GetInstID() == InstructionID::Alloca) //#todo alloca needs to added always in entry block of a function
			{
				AllocaInst* alloca_inst = cast<AllocaInst>(&inst);
				IRType const* type = alloca_inst->GetAllocatedType();
				MF.AllocateStack(type->GetSize());
			}
			else break;
		}

		TargetISelInfo const& isel_info = target.GetISelInfo();
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
	}

	void MIRModule::LowerInstruction(Instruction* inst)
	{
		switch (inst->GetInstID())
		{
		case InstructionID::Add:
		case InstructionID::Sub:
		case InstructionID::Mul:
		case InstructionID::UDiv:
		case InstructionID::URem:
		case InstructionID::And:
		case InstructionID::Or:
		case InstructionID::Xor:
		case InstructionID::Shl:
		case InstructionID::LShr:
		case InstructionID::AShr:
		case InstructionID::FAdd:
		case InstructionID::FSub:
		case InstructionID::FMul:
		case InstructionID::FDiv:
			LowerBinary(cast<BinaryInst>(inst));
			break;
		case InstructionID::Neg:
		case InstructionID::Not:
		case InstructionID::FNeg:
			LowerUnary(cast<UnaryInst>(inst));
			break;
		case InstructionID::Ret:
			LowerRet(cast<ReturnInst>(inst));
			break;
		case InstructionID::Branch:
		case InstructionID::ConditionalBranch:
			LowerBranch(cast<BranchInst>(inst));
			break;
		case InstructionID::Load:
			LowerLoad(cast<LoadInst>(inst));
			break;
		case InstructionID::Store:
			LowerStore(cast<StoreInst>(inst));
			break;
		case InstructionID::Call:
			LowerCall(cast<CallInst>(inst));
			break;
		case InstructionID::Phi:
			break;
		default:
			OLA_ASSERT_MSG(false, "Not implemented yet");
		}
	}

	void MIRModule::LowerBinary(BinaryInst* inst)
	{
		const auto GetMachineID = [](InstructionID instID)
			{
				switch (instID)
				{
				case InstructionID::Add:
					return InstAdd;
				case InstructionID::Sub:
					return InstSub;
				case InstructionID::Mul:
					return InstMul;
				case InstructionID::UDiv:
					return InstUDiv;
				case InstructionID::URem:
					return InstURem;
				case InstructionID::And:
					return InstAnd;
				case InstructionID::Or:
					return InstOr;
				case InstructionID::Xor:
					return InstXor;
				case InstructionID::Shl:
					return InstShl;
				case InstructionID::LShr:
					return InstLShr;
				case InstructionID::AShr:
					return InstAShr;
				case InstructionID::FAdd:
					return InstFAdd;
				case InstructionID::FSub:
					return InstFSub;
				case InstructionID::FMul:
					return InstFMul;
				case InstructionID::FDiv:
					return InstFDiv;
				}
				return InstUnknown;
			};
		MIROperand ret = lowering_ctx.VirtualReg(inst->GetType());
		MIRInstruction minst(GetMachineID(inst->GetInstID()));
		minst.SetOp<0>(ret).SetOp<1>(lowering_ctx.GetOperand(inst->GetOperand(0))).SetOp<2>(lowering_ctx.GetOperand(inst->GetOperand(1)));
		lowering_ctx.EmitInst(minst);
		lowering_ctx.AddOperand(inst, ret);
	}

	void MIRModule::LowerUnary(UnaryInst* inst)
	{
		const auto GetMachineID = [](InstructionID instID)
			{
				switch (instID)
				{
				case InstructionID::Neg:
					return InstNeg;
				case InstructionID::Not:
					return InstNot;
				case InstructionID::FNeg:
					return InstFNeg;
				}
				return InstUnknown;
			};

		MIROperand ret = lowering_ctx.VirtualReg(inst->GetType());
		MIRInstruction minst(GetMachineID(inst->GetInstID()));
		minst.SetOp<0>(ret).SetOp<1>(lowering_ctx.GetOperand(inst->GetOperand(0)));
		lowering_ctx.EmitInst(minst);
		lowering_ctx.AddOperand(inst, ret);
	}

	void MIRModule::LowerRet(ReturnInst* inst)
	{
	}

	void MIRModule::LowerBranch(BranchInst*)
	{

	}

	void MIRModule::LowerLoad(LoadInst*)
	{

	}

	void MIRModule::LowerStore(StoreInst*)
	{

	}

	void MIRModule::LowerCall(CallInst* inst)
	{
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