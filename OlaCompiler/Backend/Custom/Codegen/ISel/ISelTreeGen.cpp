#include <unordered_set>
#include <unordered_map>
#include "ISelTreeGen.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/Constant.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineGlobal.h"
#include "Backend/Custom/Codegen/MachineRelocable.h"
#include "Backend/Custom/Codegen/MachineModule.h"
#include "Backend/Custom/Codegen/Target.h"
#include "Utility/RTTI.h"

namespace ola
{
	ISelTreeGen::ISelTreeGen(MachineContext& ctx)
		: ctx(ctx)
	{
	}

	ISelForest ISelTreeGen::GenerateTrees(BasicBlock& BB)
	{
		forest = ISelForest();
		value_map.Clear();
		use_count.Clear();

		CountUses(BB);
		for (Instruction& I : BB)
		{
			ProcessInstruction(I);
		}
		return std::move(forest);
	}

	void ISelTreeGen::CountUses(BasicBlock& BB)
	{
		for (Instruction& I : BB)
		{
			for (Uint32 i = 0; i < I.GetNumOperands(); ++i)
			{
				Value* operand = I.GetOperand(i);
				if (auto* node = value_map.GetNode(operand))
				{
					use_count.IncrementUse(node);
				}
			}
		}
	}

	MachineType ISelTreeGen::GetMachineTypeForValue(Value* V) const
	{
		IRType* type = V->GetType();
		return GetOperandType(type);
	}

	ISelNodePtr ISelTreeGen::CreateLeafNode(Value* V)
	{
		if (auto* CI = dyn_cast<ConstantInt>(V))
		{
			return std::make_unique<ISelImmediateNode>(
				CI->GetValue(),
				GetMachineTypeForValue(V)
			);
		}

		if (auto* CF = dyn_cast<ConstantFloat>(V))
		{
			return std::make_unique<ISelImmediateNode>(
				std::bit_cast<Int64>(CF->GetValue()),
				MachineType::Float64
			);
		}

		if (auto* GV = dyn_cast<GlobalValue>(V))
		{
			MachineGlobal* MG = ctx.GetGlobal(GV);
			if (MG)
			{
				auto reg = std::make_unique<ISelRegisterNode>(ctx.VirtualReg(MachineType::Ptr));

				MachineInstruction load_addr(InstLoadGlobalAddress);
				load_addr.SetOp<0>(reg->GetRegister());
				load_addr.SetOp<1>(MachineOperand::Relocable(MG->GetRelocable()));

				pending_leaf_instructions.push_back(load_addr);

				return reg;
			}
		}

		if (ISelNode* existing = value_map.GetNode(V))
		{
			if (auto* reg = dyn_cast<ISelRegisterNode>(existing))
			{
				return std::make_unique<ISelRegisterNode>(reg->GetRegister());
			}
		}

		MachineOperand operand = ctx.GetOperand(V);
		if (!operand.IsUndefined())
		{
			if (operand.IsImmediate())
			{
				return std::make_unique<ISelImmediateNode>(
					operand.GetImmediate(),
					operand.GetType()
				);
			}
			return std::make_unique<ISelRegisterNode>(operand);
		}

		return std::make_unique<ISelRegisterNode>(ctx.VirtualReg(GetMachineTypeForValue(V)));
	}

	ISelNodePtr ISelTreeGen::CreateNodeForValue(Value* V)
	{
		return CreateLeafNode(V);
	}

	void ISelTreeGen::AddTree(ISelNodePtr tree, std::vector<ISelNode*> const& leaves, Bool has_memory)
	{
		if (!pending_leaf_instructions.empty())
		{
			auto asm_node = std::make_unique<ISelAsmNode>(std::move(pending_leaf_instructions));
			forest.AddTree(std::move(asm_node), {}, false);
			pending_leaf_instructions.clear();
		}
		forest.AddTree(std::move(tree), leaves, has_memory);
	}

	void ISelTreeGen::ProcessInstruction(Instruction& I)
	{
		// Check for target-specific lowering first, like X86 SelectInst for Floats
		Target const& target = ctx.GetModule().GetTarget();
		Bool lowered = false;
		auto captured = CaptureEmittedInstructions([&]()
		{
			lowered = target.GetISelInfo().LowerInstruction(&I, ctx);
		});

		if (lowered && !captured.empty())
		{
			AddAsmNode(std::move(captured));
			return;
		}

		if (auto* BI = dyn_cast<BinaryInst>(&I))
		{
			ProcessBinaryInst(*BI);
		}
		else if (auto* UI = dyn_cast<UnaryInst>(&I))
		{
			ProcessUnaryInst(*UI);
		}
		else if (auto* CI = dyn_cast<CompareInst>(&I))
		{
			ProcessCompareInst(*CI);
		}
		else if (auto* CI = dyn_cast<CastInst>(&I))
		{
			ProcessCastInst(*CI);
		}
		else if (auto* LI = dyn_cast<LoadInst>(&I))
		{
			ProcessLoadInst(*LI);
		}
		else if (auto* SI = dyn_cast<StoreInst>(&I))
		{
			ProcessStoreInst(*SI);
		}
		else if (auto* BI = dyn_cast<BranchInst>(&I))
		{
			ProcessBranchInst(*BI);
		}
		else if (auto* RI = dyn_cast<ReturnInst>(&I))
		{
			ProcessReturnInst(*RI);
		}
		else if (auto* SI = dyn_cast<SwitchInst>(&I))
		{
			ProcessSwitchInst(*SI);
		}
		else if (auto* CI = dyn_cast<CallInst>(&I))
		{
			ProcessCallInst(*CI);
		}
		else if (auto* SI = dyn_cast<SelectInst>(&I))
		{
			ProcessSelectInst(*SI);
		}
		else if (auto* AI = dyn_cast<AllocaInst>(&I))
		{
			ProcessAllocaInst(*AI);
		}
		else if (auto* GEP = dyn_cast<GetElementPtrInst>(&I))
		{
			ProcessGetElementPtrInst(*GEP);
		}
		else if (auto* PA = dyn_cast<PtrAddInst>(&I))
		{
			ProcessPtrAddInst(*PA);
		}
		else if (auto* PI = dyn_cast<PhiInst>(&I))
		{
			ProcessPhiInst(*PI);
		}
	}

	void ISelTreeGen::ProcessBinaryInst(BinaryInst& I)
	{
		ISelNodePtr left = CreateNodeForValue(I.GetLHS());
		ISelNodePtr right = CreateNodeForValue(I.GetRHS());

		std::vector<ISelNode*> leaves = { left.get(), right.get() };
		auto op = std::make_unique<ISelBinaryOpNode>(
			I.GetOpcode(),
			std::move(left),
			std::move(right)
		);

		MachineOperand result_reg = ctx.VirtualReg(GetMachineTypeForValue(&I));
		auto reg = std::make_unique<ISelRegisterNode>(result_reg, std::move(op));

		value_map.MapValue(&I, reg.get());
		ctx.MapOperand(&I, result_reg);
		AddTree(std::move(reg), leaves, false);
	}

	void ISelTreeGen::ProcessUnaryInst(UnaryInst& I)
	{
		ISelNodePtr operand = CreateNodeForValue(I.GetOperand());

		std::vector<ISelNode*> leaves = { operand.get() };

		auto op = std::make_unique<ISelUnaryOpNode>(
			I.GetOpcode(),
			std::move(operand)
		);

		MachineOperand result_reg = ctx.VirtualReg(GetMachineTypeForValue(&I));
		auto reg = std::make_unique<ISelRegisterNode>(result_reg, std::move(op));

		value_map.MapValue(&I, reg.get());
		ctx.MapOperand(&I, result_reg);

		AddTree(std::move(reg), leaves, false);
	}

	void ISelTreeGen::ProcessCompareInst(CompareInst& I)
	{
		ISelNodePtr left = CreateNodeForValue(I.GetLHS());
		ISelNodePtr right = CreateNodeForValue(I.GetRHS());

		std::vector<ISelNode*> leaves = { left.get(), right.get() };

		auto cmp = std::make_unique<ISelCompareNode>(
			I.GetCompareOp(),
			std::move(left),
			std::move(right)
		);

		MachineOperand result_reg = ctx.VirtualReg(MachineType::Int8);
		auto reg = std::make_unique<ISelRegisterNode>(result_reg, std::move(cmp));

		value_map.MapValue(&I, reg.get());
		ctx.MapOperand(&I, result_reg);

		AddTree(std::move(reg), leaves, false);
	}

	void ISelTreeGen::ProcessCastInst(CastInst& I)
	{
		ISelNodePtr src = CreateNodeForValue(I.GetSrc());

		std::vector<ISelNode*> leaves = { src.get() };

		auto cast_op = std::make_unique<ISelUnaryOpNode>(
			I.GetOpcode(),
			std::move(src)
		);

		MachineOperand result_reg = ctx.VirtualReg(GetMachineTypeForValue(&I));
		auto reg = std::make_unique<ISelRegisterNode>(result_reg, std::move(cast_op));

		value_map.MapValue(&I, reg.get());
		ctx.MapOperand(&I, result_reg);

		AddTree(std::move(reg), leaves, false);
	}

	void ISelTreeGen::ProcessLoadInst(LoadInst& I)
	{
		ISelNodePtr addr = CreateNodeForValue(I.GetAddressOp());

		std::vector<ISelNode*> leaves = { addr.get() };

		auto load = std::make_unique<ISelLoadNode>(
			std::move(addr),
			GetMachineTypeForValue(&I)
		);

		MachineOperand result_reg = ctx.VirtualReg(GetMachineTypeForValue(&I));
		auto reg = std::make_unique<ISelRegisterNode>(result_reg, std::move(load));

		value_map.MapValue(&I, reg.get());
		ctx.MapOperand(&I, result_reg);

		AddTree(std::move(reg), leaves, true);
	}

	void ISelTreeGen::ProcessStoreInst(StoreInst& I)
	{
		ISelNodePtr value = CreateNodeForValue(I.GetValueOp());
		ISelNodePtr addr = CreateNodeForValue(I.GetAddressOp());

		std::vector<ISelNode*> leaves = { value.get(), addr.get() };

		auto store = std::make_unique<ISelStoreNode>(
			std::move(value),
			std::move(addr)
		);

		AddTree(std::move(store), leaves, true);
	}

	void ISelTreeGen::ProcessBranchInst(BranchInst& I)
	{
		auto captured = CaptureEmittedInstructions([&]()
		{
			BasicBlock* src_block = I.GetBasicBlock();

			if (I.IsUnconditional())
			{
				BasicBlock* target = I.GetTrueTarget();
				EmitJumpWithPhiCopies(InstJump, target, src_block);
			}
			else
			{
				BasicBlock* true_target = I.GetTrueTarget();
				BasicBlock* false_target = I.GetFalseTarget();

				MachineOperand cond_op = ctx.GetOperand(I.GetCondition());

				MachineInstruction test(InstTest);
				test.SetOp<0>(cond_op);
				test.SetOp<1>(cond_op);
				ctx.EmitInst(test);

				EmitJumpWithPhiCopies(InstJNE, true_target, src_block);
				EmitJumpWithPhiCopies(InstJump, false_target, src_block);
			}
		});
		AddAsmNode(std::move(captured));
	}

	void ISelTreeGen::ProcessReturnInst(ReturnInst& I)
	{
		auto captured = CaptureEmittedInstructions([&]()
		{
			Target const& target = ctx.GetModule().GetTarget();
			target.GetFrameInfo().EmitReturn(&I, ctx);
		});
		AddAsmNode(std::move(captured));
	}

	void ISelTreeGen::ProcessSwitchInst(SwitchInst& I)
	{
		if (I.GetNumCases() == 0) return;

		auto captured = CaptureEmittedInstructions([&]()
		{
			BasicBlock* src_block = I.GetBasicBlock();
			MachineOperand cond_op = ctx.GetOperand(I.GetCondition());

			for (auto const& case_val : I.Cases())
			{
				BasicBlock* case_block = case_val.GetCaseBlock();

				if (!cond_op.IsImmediate())
				{
					MachineInstruction cmp(InstICmp);
					cmp.SetOp<0>(cond_op);
					cmp.SetOp<1>(MachineOperand::Immediate(case_val.GetCaseValue(), cond_op.GetType()));
					ctx.EmitInst(cmp);

					EmitJumpWithPhiCopies(InstJE, case_block, src_block);
				}
				else
				{
					Int64 imm = cond_op.GetImmediate();
					if (imm == case_val.GetCaseValue())
					{
						EmitJumpWithPhiCopies(InstJump, case_block, src_block);
					}
				}
			}

			if (BasicBlock* default_block = I.GetDefaultCase())
			{
				EmitJumpWithPhiCopies(InstJump, default_block, src_block);
			}
		});
		AddAsmNode(std::move(captured));
	}

	void ISelTreeGen::ProcessCallInst(CallInst& I)
	{
		auto captured = CaptureEmittedInstructions([&]()
		{
			Target const& target = ctx.GetModule().GetTarget();
			target.GetFrameInfo().EmitCall(&I, ctx);
		});
		AddAsmNode(std::move(captured));
	}

	void ISelTreeGen::ProcessSelectInst(SelectInst& I)
	{
		ISelNodePtr pred = CreateNodeForValue(I.GetPredicate());
		ISelNodePtr true_val = CreateNodeForValue(I.GetTrueValue());
		ISelNodePtr false_val = CreateNodeForValue(I.GetFalseValue());

		std::vector<ISelNode*> leaves = { pred.get(), true_val.get(), false_val.get() };

		auto select = std::make_unique<ISelSelectNode>(
			std::move(pred),
			std::move(true_val),
			std::move(false_val)
		);

		MachineOperand result_reg = ctx.VirtualReg(GetMachineTypeForValue(&I));
		auto reg = std::make_unique<ISelRegisterNode>(result_reg, std::move(select));

		value_map.MapValue(&I, reg.get());
		ctx.MapOperand(&I, result_reg);

		AddTree(std::move(reg), leaves, false);
	}

	void ISelTreeGen::ProcessAllocaInst(AllocaInst& I)
	{
		// Allocas are pre-mapped to stack slots in MachineModule::LowerFunction
	}

	void ISelTreeGen::ProcessGetElementPtrInst(GetElementPtrInst& I)
	{
		ISelNodePtr base = CreateNodeForValue(I.GetBaseOperand());
		std::vector<ISelNode*> leaves = { base.get() };

		ISelNodePtr current = std::move(base);
		for (Uint32 i = 0; i < I.GetNumIndices(); ++i)
		{
			Value* idx = I.GetIndex(i);
			ISelNodePtr idx_node = CreateNodeForValue(idx);
			leaves.push_back(idx_node.get());
			auto add = std::make_unique<ISelBinaryOpNode>(
				Opcode::Add,
				std::move(current),
				std::move(idx_node)
			);
			current = std::move(add);
		}

		MachineOperand result_reg = ctx.VirtualReg(MachineType::Ptr);
		auto reg = std::make_unique<ISelRegisterNode>(result_reg, std::move(current));

		value_map.MapValue(&I, reg.get());
		ctx.MapOperand(&I, result_reg);

		AddTree(std::move(reg), leaves, false);
	}

	void ISelTreeGen::ProcessPtrAddInst(PtrAddInst& I)
	{
		Value* base_value = I.GetBase();
		ISelNodePtr base;

		if (AllocaInst* AI = dyn_cast<AllocaInst>(base_value); AI && AI->GetAllocatedType()->IsArray())
		{
			MachineOperand base_op = ctx.GetOperand(base_value);
			auto reg = std::make_unique<ISelRegisterNode>(ctx.VirtualReg(MachineType::Ptr));

			MachineInstruction load_addr(InstLoadGlobalAddress);
			load_addr.SetOp<0>(reg->GetRegister());
			load_addr.SetOp<1>(base_op);

			pending_leaf_instructions.push_back(load_addr);
			base = std::move(reg);
		}
		else
		{
			base = CreateNodeForValue(base_value);
		}

		ISelNodePtr offset = CreateNodeForValue(I.GetOffset());

		std::vector<ISelNode*> leaves = { base.get(), offset.get() };

		auto add = std::make_unique<ISelBinaryOpNode>(
			Opcode::Add,
			std::move(base),
			std::move(offset)
		);

		MachineOperand result_reg = ctx.VirtualReg(MachineType::Ptr);
		auto reg = std::make_unique<ISelRegisterNode>(result_reg, std::move(add));

		value_map.MapValue(&I, reg.get());
		ctx.MapOperand(&I, result_reg);

		AddTree(std::move(reg), leaves, false);
	}

	void ISelTreeGen::ProcessPhiInst(PhiInst& I)
	{
		// PHI operands are pre-mapped before ISel runs in MachineModule::LowerFunction
		// PHI copies are handled at branches via EmitJumpWithPhiCopies
	}

	void ISelTreeGen::EmitJumpWithPhiCopies(Uint32 jump_opcode, BasicBlock* dst, BasicBlock* src)
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

	void ISelTreeGen::AddAsmNode(std::vector<MachineInstruction> instructions)
	{
		if (instructions.empty()) 
		{
			return;
		}
		auto asm_node = std::make_unique<ISelAsmNode>(std::move(instructions));
		forest.AddTree(std::move(asm_node), {}, false);
	}

	template<typename Func>
	std::vector<MachineInstruction> ISelTreeGen::CaptureEmittedInstructions(Func&& f)
	{
		MachineBasicBlock* block = ctx.GetCurrentBasicBlock();
		auto& inst_list = block->Instructions();

		auto start_it = inst_list.end();
		Uint64 start_size = inst_list.size();

		// Execute the function (which emits to the basic block)
		f();

		std::vector<MachineInstruction> captured;
		Uint64 new_size = inst_list.size();
		if (new_size > start_size)
		{
			auto it = inst_list.begin();
			std::advance(it, start_size);
			while (it != inst_list.end())
			{
				captured.push_back(std::move(*it));
				it = inst_list.erase(it);
			}
		}

		return captured;
	}
}
