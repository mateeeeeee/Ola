#include "ISelLegacy.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"

namespace ola
{
	ISelLegacy::ISelLegacy(MachineContext& ctx, Target const& target)
		: ctx(ctx)
		, target(target)
	{
	}

	void ISelLegacy::SelectBasicBlock(BasicBlock& BB)
	{
		TargetISelInfo const& isel_info = target.GetISelInfo();
		for (Instruction& I : BB)
		{
			if (!isel_info.LowerInstruction(&I, ctx))
			{
				LowerInstruction(&I);
			}
		}
	}

	void ISelLegacy::LowerInstruction(Instruction* I)
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

	void ISelLegacy::LowerBinary(BinaryInst* BI)
	{
		MachineOperand ret = ctx.VirtualReg(BI->GetType());
		MachineInstruction MI(GetMachineOpcode(BI->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(ctx.GetOperand(BI->GetLHS())).SetOp<2>(ctx.GetOperand(BI->GetRHS()));
		ctx.EmitInst(MI);
		ctx.MapOperand(BI, ret);
	}

	void ISelLegacy::LowerCompare(CompareInst* CI)
	{
		MachineOperand ret = ctx.VirtualReg(CI->GetType());
		MachineInstruction MI(GetMachineOpcode(CI->GetOpcode()));

		MI.SetOp<0>(ret).SetOp<1>(ctx.GetOperand(CI->GetLHS()))
			.SetOp<2>(ctx.GetOperand(CI->GetRHS()))
			.SetOp<3>(MachineOperand::Immediate((Uint32)CI->GetCompareOp(), MachineType::Other));
		ctx.EmitInst(MI);

		ctx.MapOperand(CI, ret);
	}

	void ISelLegacy::LowerUnary(UnaryInst* UI)
	{
		if (UI->GetName() == "nop") return;
		MachineOperand ret = ctx.VirtualReg(UI->GetType());
		MachineInstruction MI(GetMachineOpcode(UI->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(ctx.GetOperand(UI->GetOperand()));
		ctx.EmitInst(MI);
		ctx.MapOperand(UI, ret);
	}

	void ISelLegacy::LowerRet(ReturnInst* RI)
	{
		target.GetFrameInfo().EmitReturn(RI, ctx);
	}

	void ISelLegacy::LowerBranch(BranchInst* BI)
	{
		BasicBlock* src_block = BI->GetBasicBlock();
		if (BI->IsUnconditional())
		{
			BasicBlock* target_block = BI->GetTrueTarget();
			EmitJump(InstJump, target_block, src_block);
		}
		else
		{
			Value* condition = BI->GetCondition();
			BasicBlock* true_target = BI->GetTrueTarget();
			BasicBlock* false_target = BI->GetFalseTarget();

			MachineOperand const& cond_op = ctx.GetOperand(condition);

			MachineInstruction testMI(InstTest);
			testMI.SetOp<0>(cond_op);
			testMI.SetOp<1>(cond_op);
			ctx.EmitInst(testMI);
			EmitJump(InstJNE, true_target, src_block);
			EmitJump(InstJump, false_target, src_block);
		}
	}

	void ISelLegacy::LowerLoad(LoadInst* LI)
	{
		IRType* load_type = LI->GetType();
		if (load_type->IsStruct())
		{
			MachineFunction* MF = ctx.GetCurrentBasicBlock()->GetFunction();
			Uint32 struct_size = load_type->GetSize();

			MachineOperand dst_slot = MF->AllocateLocalStack(struct_size);
			MachineOperand src_addr = ctx.GetOperand(LI->GetAddressOp());
			MachineOperand src_reg = ctx.VirtualReg(MachineType::Ptr);
			if (src_addr.IsStackObject() || src_addr.IsMemoryOperand())
			{
				ctx.EmitInst(MachineInstruction(InstLoadGlobalAddress)
					.SetOp<0>(src_reg)
					.SetOp<1>(src_addr));
			}
			else
			{
				ctx.EmitInst(MachineInstruction(InstMove)
					.SetOp<0>(src_reg)
					.SetOp<1>(src_addr));
			}

			MachineOperand dst_reg = ctx.VirtualReg(MachineType::Ptr);
			ctx.EmitInst(MachineInstruction(InstLoadGlobalAddress)
				.SetOp<0>(dst_reg)
				.SetOp<1>(dst_slot));

			ctx.EmitInst(MachineInstruction(InstMemCpy)
				.SetOp<0>(dst_reg)
				.SetOp<1>(src_reg)
				.SetOp<2>(MachineOperand::Immediate(struct_size, MachineType::Int64)));
			ctx.MapOperand(LI, dst_reg);
			return;
		}

		MachineOperand const& ret = ctx.VirtualReg(LI->GetType());
		MachineOperand ptr = ctx.GetOperand(LI->GetAddressOp());
		ptr.SetType(ret.GetType());
		MachineInstruction MI(InstLoad);
		MI.SetOp<0>(ret).SetOp<1>(ptr);
		ctx.EmitInst(MI);
		ctx.MapOperand(LI, ret);
	}

	void ISelLegacy::LowerStore(StoreInst* SI)
	{
		IRType* value_type = SI->GetValueOp()->GetType();
		if (value_type->IsStruct())
		{
			Uint32 struct_size = value_type->GetSize();
			MachineOperand src_addr = ctx.GetOperand(SI->GetValueOp());
			MachineOperand dst_addr = ctx.GetOperand(SI->GetAddressOp());
			MachineOperand src_reg = ctx.VirtualReg(MachineType::Ptr);
			if (src_addr.IsStackObject() || src_addr.IsMemoryOperand())
			{
				ctx.EmitInst(MachineInstruction(InstLoadGlobalAddress)
					.SetOp<0>(src_reg)
					.SetOp<1>(src_addr));
			}
			else
			{
				ctx.EmitInst(MachineInstruction(InstMove)
					.SetOp<0>(src_reg)
					.SetOp<1>(src_addr));
			}

			MachineOperand dst_reg = ctx.VirtualReg(MachineType::Ptr);
			if (dst_addr.IsStackObject() || dst_addr.IsMemoryOperand())
			{
				ctx.EmitInst(MachineInstruction(InstLoadGlobalAddress)
					.SetOp<0>(dst_reg)
					.SetOp<1>(dst_addr));
			}
			else
			{
				ctx.EmitInst(MachineInstruction(InstMove)
					.SetOp<0>(dst_reg)
					.SetOp<1>(dst_addr));
			}

			ctx.EmitInst(MachineInstruction(InstMemCpy)
				.SetOp<0>(dst_reg)
				.SetOp<1>(src_reg)
				.SetOp<2>(MachineOperand::Immediate(struct_size, MachineType::Int64)));
			return;
		}

		MachineOperand const& ptr = ctx.GetOperand(SI->GetAddressOp());
		MachineOperand const& val = ctx.GetOperand(SI->GetValueOp());
		MachineInstruction MI(InstStore);
		MI.SetOp<0>(ptr).SetOp<1>(val);
		ctx.EmitInst(MI);
	}

	void ISelLegacy::LowerCall(CallInst* CI)
	{
		target.GetFrameInfo().EmitCall(CI, ctx);
	}

	void ISelLegacy::LowerCast(CastInst* CI)
	{
		MachineOperand ret = ctx.VirtualReg(CI->GetDestType());
		MachineInstruction MI(GetMachineOpcode(CI->GetOpcode()));
		MI.SetOp<0>(ret).SetOp<1>(ctx.GetOperand(CI->GetSrc()));
		ctx.EmitInst(MI);
		ctx.MapOperand(CI, ret);
	}

	void ISelLegacy::LowerGEP(GetElementPtrInst* GEPI)
	{
		Value* base = GEPI->GetBaseOperand();
		MachineOperand base_op = ctx.GetOperand(base);
		MachineOperand result = ctx.VirtualReg(GEPI->GetType());
		IRType* current_type = GEPI->GetType();

		if (AllocaInst* AI = dyn_cast<AllocaInst>(base); AI && (AI->GetAllocatedType()->IsArray() || AI->GetAllocatedType()->IsStruct()))
		{
			ctx.EmitInst(MachineInstruction(InstLoadGlobalAddress)
				.SetOp<0>(result)
				.SetOp<1>(base_op));
		}
		else
		{
			ctx.EmitInst(MachineInstruction(InstMove)
				.SetOp<0>(result)
				.SetOp<1>(base_op));
		}

		for (Value* index : GEPI->Indices())
		{
			MachineOperand index_op = ctx.GetOperand(index);

			if (IRArrayType* array_type = dyn_cast<IRArrayType>(current_type))
			{
				Uint32 element_size = array_type->GetElementType()->GetSize();

				MachineOperand offset = ctx.VirtualReg(index->GetType());
				ctx.EmitInst(MachineInstruction(InstSMul)
					.SetOp<0>(offset)
					.SetOp<1>(index_op)
					.SetOp<2>(MachineOperand::Immediate(element_size, index_op.GetType())));

				MachineOperand new_result = ctx.VirtualReg(GEPI->GetType());
				ctx.EmitInst(MachineInstruction(InstAdd)
					.SetOp<0>(new_result)
					.SetOp<1>(result)
					.SetOp<2>(offset));

				result = new_result;
				current_type = array_type->GetElementType();
			}
			else if (IRStructType* struct_type = dyn_cast<IRStructType>(current_type))
			{
				ConstantInt* field_index_const = dyn_cast<ConstantInt>(index);
				OLA_ASSERT(field_index_const);
				Int64 field_index_value = field_index_const->GetValue();

				Uint32 field_offset = 0;
				for (Int64 i = 0; i < field_index_value; ++i)
				{
					IRType* field_type = struct_type->GetMemberType(i);
					field_offset = OLA_ALIGN_UP(field_offset, field_type->GetAlign());
					field_offset += field_type->GetSize();
				}
				if (field_index_value < (Int64)struct_type->GetMemberCount())
				{
					IRType* target_field_type = struct_type->GetMemberType(field_index_value);
					field_offset = OLA_ALIGN_UP(field_offset, target_field_type->GetAlign());
				}

				if (field_offset != 0)
				{
					MachineOperand new_result = ctx.VirtualReg(GEPI->GetType());
					ctx.EmitInst(MachineInstruction(InstAdd)
						.SetOp<0>(new_result)
						.SetOp<1>(result)
						.SetOp<2>(MachineOperand::Immediate(field_offset, MachineType::Int64)));
					result = new_result;
				}
				current_type = struct_type->GetMemberType(field_index_value);
			}
			else if (IRPtrType* pointer_type = dyn_cast<IRPtrType>(current_type))
			{
				Uint32 pointer_size = pointer_type->GetPointeeType()->GetSize();

				MachineOperand offset = ctx.VirtualReg(index->GetType());
				ctx.EmitInst(MachineInstruction(InstSMul)
					.SetOp<0>(offset)
					.SetOp<1>(index_op)
					.SetOp<2>(MachineOperand::Immediate(pointer_size, index_op.GetType())));

				MachineOperand new_result = ctx.VirtualReg(GEPI->GetType());
				ctx.EmitInst(MachineInstruction(InstAdd)
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
		ctx.MapOperand(GEPI, result);
	}

	void ISelLegacy::LowerPtrAdd(PtrAddInst* PAI)
	{
		Value* base = PAI->GetBase();
		ConstantInt* offset = cast<ConstantInt>(PAI->GetOffset());

		MachineOperand base_op = ctx.GetOperand(base);
		MachineOperand base_register = ctx.VirtualReg(PAI->GetType());
		if (AllocaInst* AI = dyn_cast<AllocaInst>(base); AI && (AI->GetAllocatedType()->IsArray() || AI->GetAllocatedType()->IsStruct()))
		{
			ctx.EmitInst(MachineInstruction(InstLoadGlobalAddress)
				.SetOp<0>(base_register)
				.SetOp<1>(base_op));
		}
		else
		{
			ctx.EmitInst(MachineInstruction(InstMove)
				.SetOp<0>(base_register)
				.SetOp<1>(base_op));
		}

		if (offset->GetValue() == 0)
		{
			ctx.MapOperand(PAI, base_register);
		}
		else
		{
			MachineOperand result = ctx.VirtualReg(MachineType::Ptr);
			ctx.EmitInst(MachineInstruction(InstAdd)
				.SetOp<0>(result)
				.SetOp<1>(base_register)
				.SetOp<2>(MachineOperand::Immediate(offset->GetValue(), MachineType::Int64)));
			result.SetType(GetOperandType(PAI->GetResultElementType()));
			ctx.MapOperand(PAI, result);
		}
	}

	void ISelLegacy::LowerSwitch(SwitchInst* SI)
	{
		if (!SI || SI->GetNumCases() == 0) return;
		BasicBlock* src_block = SI->GetBasicBlock();
		Value* cond_value = SI->GetCondition();
		MachineOperand cond_op = ctx.GetOperand(cond_value);

		for (auto& case_pair : SI->Cases())
		{
			Int64 case_value = case_pair.GetCaseValue();
			BasicBlock* case_block = case_pair.GetCaseBlock();

			if (!cond_op.IsImmediate())
			{
				MachineInstruction testMI(InstICmp);
				testMI.SetOp<0>(cond_op);
				testMI.SetOp<1>(MachineOperand::Immediate(case_value, MachineType::Int64));
				ctx.EmitInst(testMI);

				EmitJump(InstJE, case_block, src_block);
			}
			else
			{
				Int64 imm = cond_op.GetImmediate();
				if (imm == case_value)
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

	void ISelLegacy::LowerSelect(SelectInst* SI)
	{
		Value* predicate = SI->GetPredicate();
		Value* true_value = SI->GetTrueValue();
		Value* false_value = SI->GetFalseValue();

		MachineOperand result_reg = ctx.VirtualReg(SI->GetType());
		MachineOperand true_op = ctx.GetOperand(true_value);
		MachineOperand false_op = ctx.GetOperand(false_value);
		MachineOperand predicate_op = ctx.GetOperand(predicate);

		ctx.EmitInst(MachineInstruction(InstMove)
			.SetOp<0>(result_reg)
			.SetOp<1>(false_op));

		MachineInstruction testMI(InstTest);
		testMI.SetOp<0>(predicate_op);
		testMI.SetOp<1>(predicate_op);
		ctx.EmitInst(testMI);

		ctx.EmitInst(MachineInstruction(InstCMoveNE)
			.SetOp<0>(result_reg)
			.SetOp<1>(true_op));
		ctx.MapOperand(SI, result_reg);
	}

	void ISelLegacy::EmitJump(Uint32 jump_opcode, BasicBlock* dst, BasicBlock* src)
	{
		OLA_ASSERT(jump_opcode >= InstJump && jump_opcode <= InstJNE);

		std::vector<MachineOperand> dst_operands;
		std::vector<MachineOperand> src_operands;
		for (auto const& Phi : dst->PhiInsts())
		{
			Value* V = Phi->GetIncomingValueForBlock(src);
			if (V)
			{
				src_operands.push_back(ctx.GetOperand(V));
				dst_operands.push_back(ctx.GetOperand(Phi));
			}
		}

		if (!src_operands.empty())
		{
			std::unordered_set<MachineOperand> needs_staging_set;
			std::unordered_set<MachineOperand> dst_set(dst_operands.begin(), dst_operands.end());

			for (MachineOperand const& src_op : src_operands)
			{
				if (dst_set.contains(src_op)) needs_staging_set.insert(src_op);
			}

			std::unordered_map<MachineOperand, MachineOperand> dirty_reg_map;
			for (Int i = dst_operands.size() - 1; i >= 0; --i)
			{
				MachineOperand src_arg;
				if (auto iter = dirty_reg_map.find(src_operands[i]); iter != dirty_reg_map.end()) src_arg = iter->second;
				else src_arg = src_operands[i];

				MachineOperand const& dst_arg = dst_operands[i];
				if (src_arg == dst_arg) continue;

				if (needs_staging_set.count(dst_arg))
				{
					MachineOperand intermediate = ctx.VirtualReg(dst_arg.GetType());
					MachineInstruction tmp_copy(InstMove);
					tmp_copy.SetOp<0>(intermediate).SetOp<1>(dst_arg);
					ctx.EmitInst(tmp_copy);
					dirty_reg_map.emplace(dst_arg, intermediate);
				}

				MachineInstruction copy(InstMove);
				copy.SetOp<0>(dst_arg).SetOp<1>(src_arg);
				ctx.EmitInst(copy);
			}
		}

		MachineOperand dst_operand = MachineOperand::Relocable(ctx.GetBlock(dst));
		MachineInstruction MI(jump_opcode);
		MI.SetOp<0>(dst_operand);
		ctx.EmitInst(MI);
	}
}
