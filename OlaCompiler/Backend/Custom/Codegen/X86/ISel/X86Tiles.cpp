#include "X86Tiles.h"
#include "Backend/Custom/Codegen/X86/X86.h"
#include "Backend/Custom/Codegen/ISel/ISelTiler.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Utility/RTTI.h"

namespace ola
{
	Bool x64LeaBaseIndexScaleTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* add = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!add || add->GetOpcode() != Opcode::Add) return false;

		ISelBinaryOpNode* mul = nullptr;
		ISelNode* base_node = nullptr;

		if (auto* left_mul = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
		{
			if (left_mul->GetOpcode() == Opcode::SMul)
			{
				mul = left_mul;
				base_node = add->GetRight();
			}
		}
		if (!mul)
		{
			if (auto* right_mul = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
			{
				if (right_mul->GetOpcode() == Opcode::SMul)
				{
					mul = right_mul;
					base_node = add->GetLeft();
				}
			}
		}
		if (!mul) return false;

		ISelImmediateNode* scale_imm = nullptr;
		ISelNode* index_node = nullptr;

		if (auto* imm = dyn_cast<ISelImmediateNode>(mul->GetLeft()))
		{
			scale_imm = imm;
			index_node = mul->GetRight();
		}
		else if (auto* imm = dyn_cast<ISelImmediateNode>(mul->GetRight()))
		{
			scale_imm = imm;
			index_node = mul->GetLeft();
		}
		if (!scale_imm || !index_node) return false;

		Int64 scale_val = scale_imm->GetImmediate();
		if (!IsValidx64Scale(scale_val)) return false;

		matched_reg = reg;
		matched_add = add;
		matched_mul = mul;
		base = base_node;
		index = index_node;
		scale = scale_val;
		return true;
	}

	TileResult x64LeaBaseIndexScaleTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);
		MachineOperand index_op = ResolveOperand(index, ctx, result.worklist);

		MachineInstruction lea(x64_InstLea);
		lea.SetOp<0>(matched_reg->GetRegister());
		lea.SetOp<1>(base_op);
		lea.SetOp<2>(index_op);
		lea.SetOp<3>(MachineOperand::Immediate(scale, MachineType::Int64));
		lea.SetOp<4>(MachineOperand::Immediate(0, MachineType::Int64));
		result.instructions.push_back(lea);

		result.success = true;
		return result;
	}

	Bool x64LeaBaseDispTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* add = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!add || add->GetOpcode() != Opcode::Add) return false;

		ISelImmediateNode* imm = nullptr;
		ISelNode* base_node = nullptr;

		if (auto* left_imm = dyn_cast<ISelImmediateNode>(add->GetLeft()))
		{
			imm = left_imm;
			base_node = add->GetRight();
		}
		else if (auto* right_imm = dyn_cast<ISelImmediateNode>(add->GetRight()))
		{
			imm = right_imm;
			base_node = add->GetLeft();
		}
		if (!imm || !base_node) return false;

		if (isa<ISelBinaryOpNode>(base_node)) return false;

		matched_reg = reg;
		matched_add = add;
		base = base_node;
		displacement = imm->GetImmediate();
		return true;
	}

	TileResult x64LeaBaseDispTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);

		MachineInstruction lea(x64_InstLea);
		lea.SetOp<0>(matched_reg->GetRegister());
		lea.SetOp<1>(base_op);
		lea.SetOp<2>(MachineOperand::Undefined());
		lea.SetOp<3>(MachineOperand::Immediate(1, MachineType::Int64));
		lea.SetOp<4>(MachineOperand::Immediate(displacement, MachineType::Int64));
		result.instructions.push_back(lea);

		result.success = true;
		return result;
	}

	Bool x64LeaIndexScaleDispTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* add = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!add || add->GetOpcode() != Opcode::Add) return false;

		ISelBinaryOpNode* mul = nullptr;
		ISelImmediateNode* disp_imm = nullptr;

		if (auto* left_mul = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
		{
			if (left_mul->GetOpcode() == Opcode::SMul)
			{
				mul = left_mul;
				disp_imm = dyn_cast<ISelImmediateNode>(add->GetRight());
			}
		}
		if (!mul || !disp_imm)
		{
			mul = nullptr;
			disp_imm = nullptr;
			if (auto* right_mul = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
			{
				if (right_mul->GetOpcode() == Opcode::SMul)
				{
					mul = right_mul;
					disp_imm = dyn_cast<ISelImmediateNode>(add->GetLeft());
				}
			}
		}
		if (!mul || !disp_imm) return false;

		ISelImmediateNode* scale_imm = nullptr;
		ISelNode* index_node = nullptr;

		if (auto* imm = dyn_cast<ISelImmediateNode>(mul->GetLeft()))
		{
			scale_imm = imm;
			index_node = mul->GetRight();
		}
		else if (auto* imm = dyn_cast<ISelImmediateNode>(mul->GetRight()))
		{
			scale_imm = imm;
			index_node = mul->GetLeft();
		}
		if (!scale_imm || !index_node) return false;

		Int64 scale_val = scale_imm->GetImmediate();
		if (!IsValidx64Scale(scale_val)) return false;

		matched_reg = reg;
		matched_add = add;
		matched_mul = mul;
		index = index_node;
		scale = scale_val;
		displacement = disp_imm->GetImmediate();
		return true;
	}

	TileResult x64LeaIndexScaleDispTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand index_op = ResolveOperand(index, ctx, result.worklist);

		MachineInstruction lea(x64_InstLea);
		lea.SetOp<0>(matched_reg->GetRegister());
		lea.SetOp<1>(MachineOperand::Undefined());
		lea.SetOp<2>(index_op);
		lea.SetOp<3>(MachineOperand::Immediate(scale, MachineType::Int64));
		lea.SetOp<4>(MachineOperand::Immediate(displacement, MachineType::Int64));
		result.instructions.push_back(lea);

		result.success = true;
		return result;
	}

	Bool x64LeaBaseIndexScaleDispTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* outer = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!outer || outer->GetOpcode() != Opcode::Add) return false;

		ISelBinaryOpNode* inner = nullptr;
		ISelImmediateNode* disp_imm = nullptr;

		if (auto* left_add = dyn_cast<ISelBinaryOpNode>(outer->GetLeft()))
		{
			if (left_add->GetOpcode() == Opcode::Add)
			{
				inner = left_add;
				disp_imm = dyn_cast<ISelImmediateNode>(outer->GetRight());
			}
		}
		if (!inner || !disp_imm)
		{
			inner = nullptr;
			disp_imm = nullptr;
			if (auto* right_add = dyn_cast<ISelBinaryOpNode>(outer->GetRight()))
			{
				if (right_add->GetOpcode() == Opcode::Add)
				{
					inner = right_add;
					disp_imm = dyn_cast<ISelImmediateNode>(outer->GetLeft());
				}
			}
		}
		if (!inner || !disp_imm) return false;

		ISelBinaryOpNode* mul = nullptr;
		ISelNode* base_node = nullptr;

		if (auto* left_mul = dyn_cast<ISelBinaryOpNode>(inner->GetLeft()))
		{
			if (left_mul->GetOpcode() == Opcode::SMul)
			{
				mul = left_mul;
				base_node = inner->GetRight();
			}
		}
		if (!mul)
		{
			if (auto* right_mul = dyn_cast<ISelBinaryOpNode>(inner->GetRight()))
			{
				if (right_mul->GetOpcode() == Opcode::SMul)
				{
					mul = right_mul;
					base_node = inner->GetLeft();
				}
			}
		}
		if (!mul || !base_node) return false;

		ISelImmediateNode* scale_imm = nullptr;
		ISelNode* index_node = nullptr;

		if (auto* imm = dyn_cast<ISelImmediateNode>(mul->GetLeft()))
		{
			scale_imm = imm;
			index_node = mul->GetRight();
		}
		else if (auto* imm = dyn_cast<ISelImmediateNode>(mul->GetRight()))
		{
			scale_imm = imm;
			index_node = mul->GetLeft();
		}
		if (!scale_imm || !index_node) return false;

		Int64 scale_val = scale_imm->GetImmediate();
		if (!IsValidx64Scale(scale_val)) return false;

		matched_reg = reg;
		outer_add = outer;
		inner_add = inner;
		matched_mul = mul;
		base = base_node;
		index = index_node;
		scale = scale_val;
		displacement = disp_imm->GetImmediate();
		return true;
	}

	TileResult x64LeaBaseIndexScaleDispTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);
		MachineOperand index_op = ResolveOperand(index, ctx, result.worklist);

		MachineInstruction lea(x64_InstLea);
		lea.SetOp<0>(matched_reg->GetRegister());
		lea.SetOp<1>(base_op);
		lea.SetOp<2>(index_op);
		lea.SetOp<3>(MachineOperand::Immediate(scale, MachineType::Int64));
		lea.SetOp<4>(MachineOperand::Immediate(displacement, MachineType::Int64));
		result.instructions.push_back(lea);

		result.success = true;
		return result;
	}

	Bool x64MulByConstTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* mul = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!mul || mul->GetOpcode() != Opcode::SMul) return false;

		ISelImmediateNode* imm = nullptr;
		ISelNode* op = nullptr;

		if (auto* left_imm = dyn_cast<ISelImmediateNode>(mul->GetLeft()))
		{
			imm = left_imm;
			op = mul->GetRight();
		}
		else if (auto* right_imm = dyn_cast<ISelImmediateNode>(mul->GetRight()))
		{
			imm = right_imm;
			op = mul->GetLeft();
		}
		if (!imm || !op) return false;

		Int64 val = imm->GetImmediate();
		if (!IsSpecialx64Scale(val)) return false;

		matched_reg = reg;
		matched_mul = mul;
		operand = op;
		multiplier = val;
		return true;
	}

	TileResult x64MulByConstTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand op = ResolveOperand(operand, ctx, result.worklist);

		Int64 scale_val = multiplier - 1;

		MachineInstruction lea(x64_InstLea);
		lea.SetOp<0>(matched_reg->GetRegister());
		lea.SetOp<1>(op);
		lea.SetOp<2>(op);
		lea.SetOp<3>(MachineOperand::Immediate(scale_val, MachineType::Int64));
		lea.SetOp<4>(MachineOperand::Immediate(0, MachineType::Int64));
		result.instructions.push_back(lea);

		result.success = true;
		return result;
	}

	Bool x64LoadBaseIndexScaleTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* load = dyn_cast<ISelLoadNode>(reg->GetSource());
		if (!load) return false;

		auto* add = dyn_cast<ISelBinaryOpNode>(load->GetAddress());
		if (!add || add->GetOpcode() != Opcode::Add) return false;

		ISelBinaryOpNode* mul = nullptr;
		ISelNode* base_node = nullptr;

		if (auto* left_mul = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
		{
			if (left_mul->GetOpcode() == Opcode::SMul)
			{
				mul = left_mul;
				base_node = add->GetRight();
			}
		}
		if (!mul)
		{
			if (auto* right_mul = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
			{
				if (right_mul->GetOpcode() == Opcode::SMul)
				{
					mul = right_mul;
					base_node = add->GetLeft();
				}
			}
		}
		if (!mul) return false;

		ISelImmediateNode* scale_imm = nullptr;
		ISelNode* index_node = nullptr;

		if (auto* imm = dyn_cast<ISelImmediateNode>(mul->GetLeft()))
		{
			scale_imm = imm;
			index_node = mul->GetRight();
		}
		else if (auto* imm = dyn_cast<ISelImmediateNode>(mul->GetRight()))
		{
			scale_imm = imm;
			index_node = mul->GetLeft();
		}
		if (!scale_imm || !index_node) return false;

		Int64 scale_val = scale_imm->GetImmediate();
		if (!IsValidx64Scale(scale_val)) return false;

		matched_reg = reg;
		matched_load = load;
		matched_add = add;
		matched_mul = mul;
		base = base_node;
		index = index_node;
		scale = scale_val;
		return true;
	}

	TileResult x64LoadBaseIndexScaleTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);
		MachineOperand index_op = ResolveOperand(index, ctx, result.worklist);

		MachineInstruction load(InstLoad);
		load.SetOp<0>(matched_reg->GetRegister());
		load.SetOp<1>(base_op);
		load.SetOp<2>(index_op);
		load.SetOp<3>(MachineOperand::Immediate(scale, MachineType::Int64));
		load.SetOp<4>(MachineOperand::Immediate(0, MachineType::Int64));
		result.instructions.push_back(load);

		result.success = true;
		return result;
	}

	Bool x64StoreBaseIndexScaleTile::Match(ISelNode* node)
	{
		auto* store = dyn_cast<ISelStoreNode>(node);
		if (!store) return false;

		auto* add = dyn_cast<ISelBinaryOpNode>(store->GetAddress());
		if (!add || add->GetOpcode() != Opcode::Add) return false;

		ISelBinaryOpNode* mul = nullptr;
		ISelNode* base_node = nullptr;

		if (auto* left_mul = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
		{
			if (left_mul->GetOpcode() == Opcode::SMul)
			{
				mul = left_mul;
				base_node = add->GetRight();
			}
		}
		if (!mul)
		{
			if (auto* right_mul = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
			{
				if (right_mul->GetOpcode() == Opcode::SMul)
				{
					mul = right_mul;
					base_node = add->GetLeft();
				}
			}
		}
		if (!mul) return false;

		ISelImmediateNode* scale_imm = nullptr;
		ISelNode* index_node = nullptr;

		if (auto* imm = dyn_cast<ISelImmediateNode>(mul->GetLeft()))
		{
			scale_imm = imm;
			index_node = mul->GetRight();
		}
		else if (auto* imm = dyn_cast<ISelImmediateNode>(mul->GetRight()))
		{
			scale_imm = imm;
			index_node = mul->GetLeft();
		}
		if (!scale_imm || !index_node) return false;

		Int64 scale_val = scale_imm->GetImmediate();
		if (!IsValidx64Scale(scale_val)) return false;

		matched_store = store;
		matched_add = add;
		matched_mul = mul;
		base = base_node;
		index = index_node;
		value = store->GetValueNode();
		scale = scale_val;
		return true;
	}

	TileResult x64StoreBaseIndexScaleTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand value_op = ResolveOperand(value, ctx, result.worklist);
		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);
		MachineOperand index_op = ResolveOperand(index, ctx, result.worklist);

		MachineInstruction store(InstStore);
		store.SetOp<0>(base_op);
		store.SetOp<1>(index_op);
		store.SetOp<2>(MachineOperand::Immediate(scale, MachineType::Int64));
		store.SetOp<3>(MachineOperand::Immediate(0, MachineType::Int64));
		store.SetOp<4>(value_op);
		result.instructions.push_back(store);

		result.success = true;
		return result;
	}

	void RegisterX86Tiles(ISelTiler& tiler)
	{
		tiler.RegisterTile(std::make_unique<x64LeaBaseIndexScaleDispTile>());
		tiler.RegisterTile(std::make_unique<x64LeaBaseIndexScaleTile>());
		tiler.RegisterTile(std::make_unique<x64LeaIndexScaleDispTile>());
		tiler.RegisterTile(std::make_unique<x64LeaBaseDispTile>());
		tiler.RegisterTile(std::make_unique<x64MulByConstTile>());
		tiler.RegisterTile(std::make_unique<x64LoadBaseIndexScaleTile>());
		tiler.RegisterTile(std::make_unique<x64StoreBaseIndexScaleTile>());
	}
}
