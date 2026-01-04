#include "ARMTiles.h"
#include "Backend/Custom/Codegen/ARM/ARM.h"
#include "Backend/Custom/Codegen/ISel/ISelTiler.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Utility/RTTI.h"

namespace ola
{
	namespace
	{
		Bool IsValidARMShiftAmount(Int64 amount)
		{
			return amount == 0 || amount == 1 || amount == 2 || amount == 3;
		}

		Int64 ScaleToShift(Int64 scale)
		{
			switch (scale)
			{
			case 1: return 0;
			case 2: return 1;
			case 4: return 2;
			case 8: return 3;
			default: return -1;
			}
		}
	}

	Bool ARMMaddTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource())
		{
			return false;
		}

		auto* add = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!add || add->GetOpcode() != Opcode::Add) 
		{
			return false;
		}

		ISelBinaryOpNode* mul = nullptr;
		ISelNode* add_operand = nullptr;
		if (auto* left_mul = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
		{
			if (left_mul->GetOpcode() == Opcode::SMul)
			{
				mul = left_mul;
				add_operand = add->GetRight();
			}
		}
		if (!mul)
		{
			if (auto* right_mul = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
			{
				if (right_mul->GetOpcode() == Opcode::SMul)
				{
					mul = right_mul;
					add_operand = add->GetLeft();
				}
			}
		}
		if (!mul || !add_operand) 
		{
			return false;
		}

		matched_reg = reg;
		matched_add = add;
		matched_mul = mul;
		mul_left = mul->GetLeft();
		mul_right = mul->GetRight();
		addend = add_operand;
		return true;
	}

	TileResult ARMMaddTile::Apply(MachineContext& ctx)
	{
		TileResult result;
		MachineOperand ml = ResolveOperand(mul_left, ctx, result.worklist);
		MachineOperand mr = ResolveOperand(mul_right, ctx, result.worklist);
		MachineOperand add_op = ResolveOperand(addend, ctx, result.worklist);

		MachineInstruction madd(ARM_InstMadd);
		madd.SetOp<0>(matched_reg->GetRegister());
		madd.SetOp<1>(ml);
		madd.SetOp<2>(mr);
		madd.SetOp<3>(add_op);
		result.instructions.push_back(madd);

		result.success = true;
		return result;
	}

	Bool ARMMsubTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) 
		{
			return false;
		}

		auto* sub = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!sub || sub->GetOpcode() != Opcode::Sub) 
		{
			return false;
		}

		auto* mul = dyn_cast<ISelBinaryOpNode>(sub->GetRight());
		if (!mul || mul->GetOpcode() != Opcode::SMul)
		{
			return false;
		}

		matched_reg = reg;
		matched_sub = sub;
		matched_mul = mul;
		mul_left = mul->GetLeft();
		mul_right = mul->GetRight();
		minuend = sub->GetLeft();
		return true;
	}

	TileResult ARMMsubTile::Apply(MachineContext& ctx)
	{
		TileResult result;
		MachineOperand ml = ResolveOperand(mul_left, ctx, result.worklist);
		MachineOperand mr = ResolveOperand(mul_right, ctx, result.worklist);
		MachineOperand min_op = ResolveOperand(minuend, ctx, result.worklist);

		MachineInstruction msub(ARM_InstMsub);
		msub.SetOp<0>(matched_reg->GetRegister());
		msub.SetOp<1>(ml);
		msub.SetOp<2>(mr);
		msub.SetOp<3>(min_op);
		result.instructions.push_back(msub);
		result.success = true;
		return result;
	}

	Bool ARMFMaddTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) 
		{
			return false;
		}

		auto* add = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!add || add->GetOpcode() != Opcode::FAdd) 
		{
			return false;
		}

		ISelBinaryOpNode* mul = nullptr;
		ISelNode* add_operand = nullptr;
		if (auto* left_mul = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
		{
			if (left_mul->GetOpcode() == Opcode::FMul)
			{
				mul = left_mul;
				add_operand = add->GetRight();
			}
		}
		if (!mul)
		{
			if (auto* right_mul = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
			{
				if (right_mul->GetOpcode() == Opcode::FMul)
				{
					mul = right_mul;
					add_operand = add->GetLeft();
				}
			}
		}
		if (!mul || !add_operand) 
		{
			return false;
		}

		matched_reg = reg;
		matched_add = add;
		matched_mul = mul;
		mul_left = mul->GetLeft();
		mul_right = mul->GetRight();
		addend = add_operand;
		return true;
	}

	TileResult ARMFMaddTile::Apply(MachineContext& ctx)
	{
		TileResult result;
		MachineOperand ml = ResolveOperand(mul_left, ctx, result.worklist);
		MachineOperand mr = ResolveOperand(mul_right, ctx, result.worklist);
		MachineOperand add_op = ResolveOperand(addend, ctx, result.worklist);

		MachineInstruction fmadd(ARM_InstFMadd);
		fmadd.SetOp<0>(matched_reg->GetRegister());
		fmadd.SetOp<1>(ml);
		fmadd.SetOp<2>(mr);
		fmadd.SetOp<3>(add_op);
		result.instructions.push_back(fmadd);
		result.success = true;
		return result;
	}

	Bool ARMFMsubTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) 
		{
			return false;
		}

		auto* sub = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!sub || sub->GetOpcode() != Opcode::FSub) 
		{
			return false;
		}

		auto* mul = dyn_cast<ISelBinaryOpNode>(sub->GetRight());
		if (!mul || mul->GetOpcode() != Opcode::FMul) 
		{
			return false;
		}

		matched_reg = reg;
		matched_sub = sub;
		matched_mul = mul;
		mul_left = mul->GetLeft();
		mul_right = mul->GetRight();
		minuend = sub->GetLeft();
		return true;
	}

	TileResult ARMFMsubTile::Apply(MachineContext& ctx)
	{
		TileResult result;
		MachineOperand ml = ResolveOperand(mul_left, ctx, result.worklist);
		MachineOperand mr = ResolveOperand(mul_right, ctx, result.worklist);
		MachineOperand min_op = ResolveOperand(minuend, ctx, result.worklist);

		MachineInstruction fmsub(ARM_InstFMsub);
		fmsub.SetOp<0>(matched_reg->GetRegister());
		fmsub.SetOp<1>(ml);
		fmsub.SetOp<2>(mr);
		fmsub.SetOp<3>(min_op);
		result.instructions.push_back(fmsub);
		result.success = true;
		return result;
	}

	Bool ARMLoadShiftedTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) 
		{
			return false;
		}

		auto* load = dyn_cast<ISelLoadNode>(reg->GetSource());
		if (!load) 
		{
			return false;
		}

		auto* add = dyn_cast<ISelBinaryOpNode>(load->GetAddress());
		if (!add || add->GetOpcode() != Opcode::Add) 
		{
			return false;
		}

		ISelBinaryOpNode* shift = nullptr;
		ISelNode* base_node = nullptr;
		if (auto* left_shift = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
		{
			if (left_shift->GetOpcode() == Opcode::Shl)
			{
				shift = left_shift;
				base_node = add->GetRight();
			}
		}
		if (!shift)
		{
			if (auto* right_shift = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
			{
				if (right_shift->GetOpcode() == Opcode::Shl)
				{
					shift = right_shift;
					base_node = add->GetLeft();
				}
			}
		}

		if (!shift)
		{
			if (auto* left_mul = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
			{
				if (left_mul->GetOpcode() == Opcode::SMul)
				{
					if (auto* imm = dyn_cast<ISelImmediateNode>(left_mul->GetRight()))
					{
						Int64 s = ScaleToShift(imm->GetImmediate());
						if (s >= 0)
						{
							matched_reg = reg;
							matched_load = load;
							matched_add = add;
							matched_shift = nullptr;
							base = add->GetRight();
							index = left_mul->GetLeft();
							shift_amount = s;
							return true;
						}
					}
					if (auto* imm = dyn_cast<ISelImmediateNode>(left_mul->GetLeft()))
					{
						Int64 s = ScaleToShift(imm->GetImmediate());
						if (s >= 0)
						{
							matched_reg = reg;
							matched_load = load;
							matched_add = add;
							matched_shift = nullptr;
							base = add->GetRight();
							index = left_mul->GetRight();
							shift_amount = s;
							return true;
						}
					}
				}
			}
			if (auto* right_mul = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
			{
				if (right_mul->GetOpcode() == Opcode::SMul)
				{
					if (auto* imm = dyn_cast<ISelImmediateNode>(right_mul->GetRight()))
					{
						Int64 s = ScaleToShift(imm->GetImmediate());
						if (s >= 0)
						{
							matched_reg = reg;
							matched_load = load;
							matched_add = add;
							matched_shift = nullptr;
							base = add->GetLeft();
							index = right_mul->GetLeft();
							shift_amount = s;
							return true;
						}
					}
					if (auto* imm = dyn_cast<ISelImmediateNode>(right_mul->GetLeft()))
					{
						Int64 s = ScaleToShift(imm->GetImmediate());
						if (s >= 0)
						{
							matched_reg = reg;
							matched_load = load;
							matched_add = add;
							matched_shift = nullptr;
							base = add->GetLeft();
							index = right_mul->GetRight();
							shift_amount = s;
							return true;
						}
					}
				}
			}
			return false;
		}

		auto* shift_imm = dyn_cast<ISelImmediateNode>(shift->GetRight());
		if (!shift_imm) 
		{
			return false;
		}

		Int64 amount = shift_imm->GetImmediate();
		if (!IsValidARMShiftAmount(amount)) 
		{
			return false;
		}

		matched_reg = reg;
		matched_load = load;
		matched_add = add;
		matched_shift = shift;
		base = base_node;
		index = shift->GetLeft();
		shift_amount = amount;
		return true;
	}

	TileResult ARMLoadShiftedTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);
		MachineOperand index_op = ResolveOperand(index, ctx, result.worklist);

		MachineInstruction ldr(ARM_InstLdrShifted);
		ldr.SetOp<0>(matched_reg->GetRegister());
		ldr.SetOp<1>(base_op);
		ldr.SetOp<2>(index_op);
		ldr.SetOp<3>(MachineOperand::Immediate(shift_amount, MachineType::Int64));
		result.instructions.push_back(ldr);

		result.success = true;
		return result;
	}

	Bool ARMStoreShiftedTile::Match(ISelNode* node)
	{
		auto* store = dyn_cast<ISelStoreNode>(node);
		if (!store) 
		{
			return false;
		}

		auto* add = dyn_cast<ISelBinaryOpNode>(store->GetAddress());
		if (!add || add->GetOpcode() != Opcode::Add) 
		{
			return false;
		}

		ISelBinaryOpNode* shift = nullptr;
		ISelNode* base_node = nullptr;
		if (auto* left_shift = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
		{
			if (left_shift->GetOpcode() == Opcode::Shl)
			{
				shift = left_shift;
				base_node = add->GetRight();
			}
		}
		if (!shift)
		{
			if (auto* right_shift = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
			{
				if (right_shift->GetOpcode() == Opcode::Shl)
				{
					shift = right_shift;
					base_node = add->GetLeft();
				}
			}
		}

		if (!shift)
		{
			if (auto* left_mul = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
			{
				if (left_mul->GetOpcode() == Opcode::SMul)
				{
					if (auto* imm = dyn_cast<ISelImmediateNode>(left_mul->GetRight()))
					{
						Int64 s = ScaleToShift(imm->GetImmediate());
						if (s >= 0)
						{
							matched_store = store;
							matched_add = add;
							matched_shift = nullptr;
							base = add->GetRight();
							index = left_mul->GetLeft();
							value = store->GetValueNode();
							shift_amount = s;
							return true;
						}
					}
					if (auto* imm = dyn_cast<ISelImmediateNode>(left_mul->GetLeft()))
					{
						Int64 s = ScaleToShift(imm->GetImmediate());
						if (s >= 0)
						{
							matched_store = store;
							matched_add = add;
							matched_shift = nullptr;
							base = add->GetRight();
							index = left_mul->GetRight();
							value = store->GetValueNode();
							shift_amount = s;
							return true;
						}
					}
				}
			}
			if (auto* right_mul = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
			{
				if (right_mul->GetOpcode() == Opcode::SMul)
				{
					if (auto* imm = dyn_cast<ISelImmediateNode>(right_mul->GetRight()))
					{
						Int64 s = ScaleToShift(imm->GetImmediate());
						if (s >= 0)
						{
							matched_store = store;
							matched_add = add;
							matched_shift = nullptr;
							base = add->GetLeft();
							index = right_mul->GetLeft();
							value = store->GetValueNode();
							shift_amount = s;
							return true;
						}
					}
					if (auto* imm = dyn_cast<ISelImmediateNode>(right_mul->GetLeft()))
					{
						Int64 s = ScaleToShift(imm->GetImmediate());
						if (s >= 0)
						{
							matched_store = store;
							matched_add = add;
							matched_shift = nullptr;
							base = add->GetLeft();
							index = right_mul->GetRight();
							value = store->GetValueNode();
							shift_amount = s;
							return true;
						}
					}
				}
			}
			return false;
		}

		auto* shift_imm = dyn_cast<ISelImmediateNode>(shift->GetRight());
		if (!shift_imm) 
		{
			return false;
		}

		Int64 amount = shift_imm->GetImmediate();
		if (!IsValidARMShiftAmount(amount))
		{
			return false;
		}

		matched_store = store;
		matched_add = add;
		matched_shift = shift;
		base = base_node;
		index = shift->GetLeft();
		value = store->GetValueNode();
		shift_amount = amount;
		return true;
	}

	TileResult ARMStoreShiftedTile::Apply(MachineContext& ctx)
	{
		TileResult result;
		MachineOperand value_op = ResolveOperand(value, ctx, result.worklist);
		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);
		MachineOperand index_op = ResolveOperand(index, ctx, result.worklist);

		MachineInstruction str(ARM_InstStrShifted);
		str.SetOp<0>(value_op);
		str.SetOp<1>(base_op);
		str.SetOp<2>(index_op);
		str.SetOp<3>(MachineOperand::Immediate(shift_amount, MachineType::Int64));
		result.instructions.push_back(str);
		result.success = true;
		return result;
	}

	Bool ARMAddShiftedTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource())
		{
			return false;
		}

		auto* add = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!add || add->GetOpcode() != Opcode::Add)
		{
			return false;
		}

		ISelBinaryOpNode* shift = nullptr;
		ISelNode* base_node = nullptr;
		if (auto* left_shift = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
		{
			if (left_shift->GetOpcode() == Opcode::Shl)
			{
				shift = left_shift;
				base_node = add->GetRight();
			}
		}
		if (!shift)
		{
			if (auto* right_shift = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
			{
				if (right_shift->GetOpcode() == Opcode::Shl)
				{
					shift = right_shift;
					base_node = add->GetLeft();
				}
			}
		}
		if (!shift) return false;

		auto* shift_imm = dyn_cast<ISelImmediateNode>(shift->GetRight());
		if (!shift_imm) 
		{
			return false;
		}

		Int64 amount = shift_imm->GetImmediate();
		if (!IsValidARMShiftAmount(amount)) 
		{
			return false;
		}

		matched_reg = reg;
		matched_add = add;
		matched_shift = shift;
		base = base_node;
		shifted_operand = shift->GetLeft();
		shift_amount = amount;
		return true;
	}

	TileResult ARMAddShiftedTile::Apply(MachineContext& ctx)
	{
		TileResult result;
		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);
		MachineOperand shifted_op = ResolveOperand(shifted_operand, ctx, result.worklist);

		MachineInstruction add(ARM_InstAddShifted);
		add.SetOp<0>(matched_reg->GetRegister());
		add.SetOp<1>(base_op);
		add.SetOp<2>(shifted_op);
		add.SetOp<3>(MachineOperand::Immediate(shift_amount, MachineType::Int64));
		result.instructions.push_back(add);
		result.success = true;
		return result;
	}

	void RegisterARMTiles(ISelTiler& tiler)
	{
		tiler.RegisterTile(std::make_unique<ARMMaddTile>());
		tiler.RegisterTile(std::make_unique<ARMMsubTile>());
		tiler.RegisterTile(std::make_unique<ARMFMaddTile>());
		tiler.RegisterTile(std::make_unique<ARMFMsubTile>());
		tiler.RegisterTile(std::make_unique<ARMLoadShiftedTile>());
		tiler.RegisterTile(std::make_unique<ARMStoreShiftedTile>());
		tiler.RegisterTile(std::make_unique<ARMAddShiftedTile>());
	}
}
