#include "ISelTreeGen.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/Constant.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"
#include "Backend/Custom/Codegen/MachineGlobal.h"
#include "Backend/Custom/Codegen/MachineRelocable.h"
#include "Backend/Custom/Codegen/MachineModule.h"
#include "Backend/Custom/Codegen/Targets/Target.h"
#include "Utility/RTTI.h"

namespace ola
{
	ISelTreeGen::ISelTreeGen(MachineContext& ctx, ISelLowering& lowering)
		: ctx(ctx)
		, lowering(lowering)
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
				MachineType value_type = GetMachineTypeForValue(V);
				auto addr_reg = std::make_unique<ISelRegisterNode>(ctx.VirtualReg(MachineType::Ptr));

				MachineInstruction load_addr(InstLoadGlobalAddress);
				load_addr.SetOp<0>(addr_reg->GetRegister());
				load_addr.SetOp<1>(MachineOperand::Relocable(MG->GetRelocable()));
				pending_leaf_instructions.push_back(load_addr);

				if (value_type != MachineType::Ptr)
				{
					auto value_reg = std::make_unique<ISelRegisterNode>(ctx.VirtualReg(value_type));
					MachineInstruction load_val(InstLoad);
					load_val.SetOp<0>(value_reg->GetRegister());
					load_val.SetOp<1>(addr_reg->GetRegister());
					pending_leaf_instructions.push_back(load_val);
					return value_reg;
				}

				return addr_reg;
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
		if (I.GetOpcode() == Opcode::Bitcast && I.GetSrcType()->IsPointer() && I.GetDestType()->IsPointer())
		{
			ISelNodePtr src = CreateNodeForValue(I.GetSrc());
			if (auto* reg = dyn_cast<ISelRegisterNode>(src.get()))
			{
				ctx.MapOperand(&I, reg->GetRegister());
			}
			return;
		}

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
		IRType* load_type = I.GetType();
		if (load_type->IsAggregate())
		{
			auto captured = CaptureEmittedInstructions([&]() { lowering.LowerLoad(&I); });
			AddAsmNode(std::move(captured));
			return;
		}

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
		IRType* value_type = I.GetValueOp()->GetType();

		if (value_type->IsAggregate())
		{
			auto captured = CaptureEmittedInstructions([&]() { lowering.LowerStore(&I); });
			AddAsmNode(std::move(captured));
			return;
		}

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
		auto captured = CaptureEmittedInstructions([&]() { lowering.LowerBranch(&I); });
		AddAsmNode(std::move(captured));
	}

	void ISelTreeGen::ProcessReturnInst(ReturnInst& I)
	{
		auto captured = CaptureEmittedInstructions([&]() { lowering.LowerRet(&I); });
		AddAsmNode(std::move(captured));
	}

	void ISelTreeGen::ProcessSwitchInst(SwitchInst& I)
	{
		if (I.GetNumCases() == 0) return;
		auto captured = CaptureEmittedInstructions([&]() { lowering.LowerSwitch(&I); });
		AddAsmNode(std::move(captured));
	}

	void ISelTreeGen::ProcessCallInst(CallInst& I)
	{
		auto captured = CaptureEmittedInstructions([&]() { lowering.LowerCall(&I); });
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
		Value* base_value = I.GetBaseOperand();
		ISelNodePtr base;
		if (AllocaInst* AI = dyn_cast<AllocaInst>(base_value); AI && AI->GetAllocatedType()->IsAggregate())
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

		Uint32 num_indices = I.GetNumIndices();
		if (num_indices == 0)
		{
			if (auto* base_reg = dyn_cast<ISelRegisterNode>(base.get()))
			{
				value_map.MapValue(&I, base_reg);
				ctx.MapOperand(&I, base_reg->GetRegister());
				if (!pending_leaf_instructions.empty())
				{
					auto asm_node = std::make_unique<ISelAsmNode>(std::move(pending_leaf_instructions));
					forest.AddTree(std::move(asm_node), {}, false);
					pending_leaf_instructions.clear();
				}
			}
			return;
		}

		MachineOperand current_reg;
		if (auto* base_reg = dyn_cast<ISelRegisterNode>(base.get()))
		{
			current_reg = base_reg->GetRegister();
		}
		else
		{
			current_reg = ctx.VirtualReg(MachineType::Ptr);
		}

		IRType* current_type = I.GetType();
		Uint32 idx_num = 0;
		for (Value* index : I.Indices())
		{
			ISelNodePtr left = std::make_unique<ISelRegisterNode>(current_reg);
			ISelNodePtr idx_node = CreateNodeForValue(index);

			Uint32 element_size = 1;
			Bool is_struct = false;
			Uint32 struct_field_offset = 0;
			if (IRArrayType* array_type = dyn_cast<IRArrayType>(current_type))
			{
				element_size = array_type->GetElementType()->GetSize();
				current_type = array_type->GetElementType();
			}
			else if (IRPtrType* pointer_type = dyn_cast<IRPtrType>(current_type))
			{
				element_size = pointer_type->GetPointeeType()->GetSize();
				current_type = pointer_type->GetPointeeType();
			}
			else if (IRStructType* struct_type = dyn_cast<IRStructType>(current_type))
			{
				is_struct = true;
				ConstantInt* field_index_const = dyn_cast<ConstantInt>(index);
				OLA_ASSERT(field_index_const);
				Int64 field_index_value = field_index_const->GetValue();

				for (Int64 i = 0; i < field_index_value; ++i)
				{
					IRType* field_type = struct_type->GetMemberType(i);
					struct_field_offset = OLA_ALIGN_UP(struct_field_offset, field_type->GetAlign());
					struct_field_offset += field_type->GetSize();
				}
				if (field_index_value < (Int64)struct_type->GetMemberCount())
				{
					IRType* target_field_type = struct_type->GetMemberType(field_index_value);
					struct_field_offset = OLA_ALIGN_UP(struct_field_offset, target_field_type->GetAlign());
					current_type = target_field_type;
				}
			}

			MachineOperand result_reg = ctx.VirtualReg(MachineType::Ptr);

			if (is_struct)
			{
				if (struct_field_offset != 0)
				{
					ISelNodePtr offset_imm = std::make_unique<ISelImmediateNode>(struct_field_offset, MachineType::Int64);
					std::vector<ISelNode*> leaves = { left.get(), offset_imm.get() };

					auto add = std::make_unique<ISelBinaryOpNode>(
						Opcode::Add,
						std::move(left),
						std::move(offset_imm)
					);

					auto reg = std::make_unique<ISelRegisterNode>(result_reg, std::move(add));

					if (idx_num == num_indices - 1)
					{
						value_map.MapValue(&I, reg.get());
						ctx.MapOperand(&I, result_reg);
					}

					AddTree(std::move(reg), leaves, false);
					current_reg = result_reg;
				}
				else
				{
					if (idx_num == num_indices - 1)
					{
						auto reg = std::make_unique<ISelRegisterNode>(current_reg);
						value_map.MapValue(&I, reg.get());
						ctx.MapOperand(&I, current_reg);
					}
				}
			}
			else
			{
				ISelNodePtr scale_imm = std::make_unique<ISelImmediateNode>(element_size, MachineType::Int64);
				auto mul = std::make_unique<ISelBinaryOpNode>(
					Opcode::SMul,
					std::move(idx_node),
					std::move(scale_imm)
				);
				MachineOperand scaled_offset_reg = ctx.VirtualReg(MachineType::Int64);
				auto scaled_reg = std::make_unique<ISelRegisterNode>(scaled_offset_reg, std::move(mul));
				AddTree(std::move(scaled_reg), {}, false);

				ISelNodePtr scaled_offset_node = std::make_unique<ISelRegisterNode>(scaled_offset_reg);
				std::vector<ISelNode*> leaves = { left.get(), scaled_offset_node.get() };

				auto add = std::make_unique<ISelBinaryOpNode>(
					Opcode::Add,
					std::move(left),
					std::move(scaled_offset_node)
				);

				auto reg = std::make_unique<ISelRegisterNode>(result_reg, std::move(add));

				if (idx_num == num_indices - 1)
				{
					value_map.MapValue(&I, reg.get());
					ctx.MapOperand(&I, result_reg);
				}

				AddTree(std::move(reg), leaves, false);
				current_reg = result_reg;
			}
			++idx_num;
		}
	}

	void ISelTreeGen::ProcessPtrAddInst(PtrAddInst& I)
	{
		Value* base_value = I.GetBase();
		ISelNodePtr base;

		if (AllocaInst* AI = dyn_cast<AllocaInst>(base_value); AI && AI->GetAllocatedType()->IsAggregate())
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
		// PHI copies are handled at branches via ISelLowering::EmitJump
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
