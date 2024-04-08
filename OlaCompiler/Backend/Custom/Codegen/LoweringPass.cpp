#include "LoweringPass.h"
#include "MIRBasicBlock.h"
#include "MIRGlobal.h"
#include "MIRModule.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/Constant.h"
#include "Backend/Custom/IR/CFGAnalysis.h"

namespace ola
{

	void LoweringPass::RunOnModule(IRModule* M)
	{
		LowerModule(M);
	}


	void LoweringPass::LowerModule(IRModule* M)
	{
		auto const& ir_globals = M->Globals();

		for (GlobalValue* GV : ir_globals)
		{
			if (GV->IsFunction())
			{
				Function* F = cast<Function>(GV);
				module.globals.emplace_back(new MIRFunction(F->GetName()), F->GetLinkage());
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

					module.globals.emplace_back(data, V->GetLinkage(), alignment);
				}
				else
				{
					module.globals.emplace_back(new MIRZeroStorage(V->GetName(), size), V->GetLinkage(), alignment);
				}
			}

			AddGlobal(GV, &module.globals.back());
		}

		for (GlobalValue* GV : ir_globals)
		{
			if (GV->IsFunction())
			{
				Function* F = cast<Function>(GV);
				LowerFunction(F);
			}
		}
	}

	void LoweringPass::LowerFunction(Function* F)
	{
		MIRGlobal* global = GetGlobal(F);
		MIRFunction& MF = *dynamic_cast<MIRFunction*>(global->GetRelocable());

		for (BasicBlock& BB : F->Blocks())
		{
			MF.Blocks().push_back(std::make_unique<MIRBasicBlock>(&MF, GetLabel()));
			auto& MBB = MF.Blocks().back();
			AddBlock(&BB, MBB.get());
			for (auto& inst : BB.Instructions())
			{
				if (inst.GetInstID() == InstructionID::Phi)
				{
					auto vreg = VirtualReg(inst.GetType());
					AddOperand(&inst, vreg);
				}
			}
		}
		LowerCFGAnalysis(F);

		auto& args = MF.Args();
		for (uint32 arg_idx = 0; arg_idx < F->GetArgCount(); ++arg_idx)
		{
			Argument* arg = F->GetArg(arg_idx);
			IRType* arg_type = F->GetArgType(arg_idx);
			auto vreg = VirtualReg(arg_type);
			AddOperand(arg, vreg);
			args.push_back(vreg);
		}
		SetCurrentBasicBlock(MF.Blocks().front().get());
		module.EmitPrologue(MF);

		SetCurrentBasicBlock(GetBlock(&F->GetEntryBlock()));

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

		for (BasicBlock& BB : F->Blocks())
		{
			MIRBasicBlock* MBB = GetBlock(&BB);
			SetCurrentBasicBlock(MBB);
			for (Instruction& inst : BB.Instructions())
			{
				LowerInstruction(&inst);
			}
		}
	}

	void LoweringPass::LowerInstruction(Instruction* inst)
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

	void LoweringPass::LowerBinary(BinaryInst* inst)
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
		MIROperand ret = VirtualReg(inst->GetType());
		MIRInstruction minst(GetMachineID(inst->GetInstID()));
		minst.SetOp<0>(ret).SetOp<1>(GetOperand(inst->GetOperand(0))).SetOp<2>(GetOperand(inst->GetOperand(1)));
		EmitInst(minst);
		AddOperand(inst, ret);
	}

	void LoweringPass::LowerUnary(UnaryInst* inst)
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

		MIROperand ret = VirtualReg(inst->GetType());
		MIRInstruction minst(GetMachineID(inst->GetInstID()));
		minst.SetOp<0>(ret).SetOp<1>(GetOperand(inst->GetOperand(0)));
		EmitInst(minst);
		AddOperand(inst, ret);
	}

	void LoweringPass::LowerRet(ReturnInst* inst)
	{
		module.EmitReturn(inst);
	}

	void LoweringPass::LowerBranch(BranchInst*)
	{

	}

	void LoweringPass::LowerLoad(LoadInst*)
	{

	}

	void LoweringPass::LowerStore(StoreInst*)
	{

	}

	void LoweringPass::LowerCall(CallInst* inst)
	{
		module.EmitCall(inst);
	}

	void LoweringPass::LowerCFGAnalysis(Function* F)
	{
		CFGAnalysisPass CFG{};
		CFG.RunOn(*F);
		CFGResult const& cfg_result = CFG.GetResult();
		for (auto&& [BB, info] : cfg_result)
		{
			MIRBasicBlock* MBB = GetBlock(BB);
			for (auto* P : info.predecessors) MBB->AddPredecessor(GetBlock(P));
			for (auto* S : info.successors) MBB->AddSuccessor(GetBlock(S));
		}
	}


	void LoweringPass::EmitInst(MIRInstruction const& minst)
	{
		auto& minst_list = current_block->Instructions();
		minst_list.emplace_back(minst);
	}

	MIROperand LoweringPass::GetOperand(Value const* V)
	{
		if (value_map.contains(V)) return value_map[V];
		OLA_ASSERT(V->IsConstant());
		Constant const* C = cast<Constant>(V);
		if (C->GetConstantID() == ConstantID::Global)
		{
			GlobalValue const* GV = cast<GlobalValue>(C);
			MIROperand ptr = VirtualReg(MIROperandType::Int64);
			MIRInstruction minst(InstLoadGlobalAddress);

			MIRGlobal* mir_global = global_map[GV];
			OLA_ASSERT(mir_global);

			MIROperand global = MIROperand::Relocable(mir_global->GetRelocable());
			minst.SetOp<0>(ptr).SetOp<1>(global);
			EmitInst(minst);
			return ptr;
		}
		else
		{
			OLA_ASSERT(false);
			return MIROperand();
		}
	}
	MIROperandType LoweringPass::GetOperandType(IRType const* type)
	{
		if (type->IsPointerType())
		{
			return MIROperandType::Ptr;
		}
		if (type->IsIntegerType())
		{
			switch (cast<IRIntType>(type)->GetWidth())
			{
			case 1:
				return MIROperandType::Bool;
			case 8:
				return MIROperandType::Int8;
			case 16:
				return MIROperandType::Int16;
			case 32:
				return MIROperandType::Int32;
			case 64:
				return MIROperandType::Int64;
			default:
				OLA_ASSERT(false);
			}
		}
		if (type->IsFloatType())
		{
			return MIROperandType::Float64;
		}
		OLA_ASSERT(false);
		return MIROperandType::Other;
	}
}

