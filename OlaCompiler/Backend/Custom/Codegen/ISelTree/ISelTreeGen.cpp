#include "ISelTreeGen.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/Constant.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineGlobal.h"
#include "Backend/Custom/Codegen/MachineRelocable.h"
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

				std::vector<MachineInstruction*> insts;
				ctx.EmitInst(load_addr);

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
		forest.AddTree(std::move(tree), leaves, has_memory);
	}

	void ISelTreeGen::ProcessInstruction(Instruction& I)
	{
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
		MachineBasicBlock* true_mbb = ctx.GetBlock(I.GetTrueTarget());

		if (I.IsUnconditional())
		{
			MachineInstruction jmp(InstJump);
			jmp.SetOp<0>(MachineOperand::Relocable(true_mbb));
			ctx.EmitInst(jmp);
		}
		else
		{
			MachineBasicBlock* false_mbb = ctx.GetBlock(I.GetFalseTarget());

			ISelNodePtr cond = CreateNodeForValue(I.GetCondition());
			MachineOperand cond_op = ctx.GetOperand(I.GetCondition());

			MachineInstruction test(InstTest);
			test.SetOp<0>(cond_op);
			test.SetOp<1>(cond_op);
			ctx.EmitInst(test);

			MachineInstruction jne(InstJNE);
			jne.SetOp<0>(MachineOperand::Relocable(true_mbb));
			ctx.EmitInst(jne);

			MachineInstruction jmp(InstJump);
			jmp.SetOp<0>(MachineOperand::Relocable(false_mbb));
			ctx.EmitInst(jmp);
		}
	}

	void ISelTreeGen::ProcessReturnInst(ReturnInst& I)
	{
		if (!I.IsVoid())
		{
			ISelNodePtr ret_val = CreateNodeForValue(I.GetReturnValue());
		}
		MachineInstruction ret(InstRet);
		ctx.EmitInst(ret);
	}

	void ISelTreeGen::ProcessSwitchInst(SwitchInst& I)
	{
		MachineOperand cond_op = ctx.GetOperand(I.GetCondition());
		MachineBasicBlock* default_mbb = ctx.GetBlock(I.GetDefaultCase());

		for (auto const& case_val : I.Cases())
		{
			MachineBasicBlock* case_mbb = ctx.GetBlock(case_val.GetCaseBlock());

			MachineInstruction cmp(InstICmp);
			cmp.SetOp<0>(cond_op);
			cmp.SetOp<1>(MachineOperand::Immediate(case_val.GetCaseValue(), cond_op.GetType()));
			ctx.EmitInst(cmp);

			MachineInstruction je(InstJE);
			je.SetOp<0>(MachineOperand::Relocable(case_mbb));
			ctx.EmitInst(je);
		}

		MachineInstruction jmp(InstJump);
		jmp.SetOp<0>(MachineOperand::Relocable(default_mbb));
		ctx.EmitInst(jmp);
	}

	void ISelTreeGen::ProcessCallInst(CallInst& I)
	{
		// Calls are handled specially - delegate to TargetFrameInfo
		// For now, just mark that this instruction produces a value
		if (!I.GetType()->IsVoid())
		{
			MachineOperand result_reg = ctx.VirtualReg(GetMachineTypeForValue(&I));
			auto reg = std::make_unique<ISelRegisterNode>(result_reg);
			value_map.MapValue(&I, reg.get());
			ctx.MapOperand(&I, result_reg);
		}
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
		MachineOperand result_reg = ctx.VirtualReg(MachineType::Ptr);
		auto reg = std::make_unique<ISelRegisterNode>(result_reg);

		value_map.MapValue(&I, reg.get());
		ctx.MapOperand(&I, result_reg);
	}

	void ISelTreeGen::ProcessGetElementPtrInst(GetElementPtrInst& I)
	{
		ISelNodePtr base = CreateNodeForValue(I.GetBaseOperand());
		std::vector<ISelNode*> leaves = { base.get() };

		// For now, create a simple address computation
		// This will be enhanced to build proper address nodes
		ISelNodePtr current = std::move(base);

		for (Uint32 i = 0; i < I.GetNumIndices(); ++i)
		{
			Value* idx = I.GetIndex(i);
			ISelNodePtr idx_node = CreateNodeForValue(idx);
			leaves.push_back(idx_node.get());

			// Add index computation
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
		ISelNodePtr base = CreateNodeForValue(I.GetBase());
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
		MachineOperand result_reg = ctx.VirtualReg(GetMachineTypeForValue(&I));
		auto phi = std::make_unique<ISelPhiNode>(GetMachineTypeForValue(&I));

		for (Uint32 i = 0; i < I.GetNumIncomingValues(); ++i)
		{
			ISelNodePtr val = CreateNodeForValue(I.GetIncomingValue(i));
			phi->AddIncoming(std::move(val), I.GetIncomingBlock(i));
		}

		auto reg = std::make_unique<ISelRegisterNode>(result_reg, std::move(phi));

		value_map.MapValue(&I, reg.get());
		ctx.MapOperand(&I, result_reg);

		AddTree(std::move(reg), {}, false);
	}
}
