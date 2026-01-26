#include "X86Tiles.h"
#include "Backend/Custom/Codegen/Targets/X86/X86.h"
#include "Backend/Custom/Codegen/ISel/ISelTiler.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Utility/RTTI.h"

namespace ola
{
	namespace
	{
		Bool IsMulOpcode(Opcode op)
		{
			return op == Opcode::SMul;
		}

		Bool IsValidLeaOperand(MachineOperand const& op)
		{
			if (op.IsUndefined()) return true;
			if (!op.IsReg()) return false;
			if (op.GetType() == MachineType::Int8) return false;
			return true;
		}
	}

	Bool X86LeaBaseIndexScaleTile::Match(ISelNode* node)
	{
		matched_reg = nullptr;
		matched_add = nullptr;
		base = nullptr;
		matched_mul = nullptr;
		index = nullptr;
		scale = 0;

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
		ISelNode* base_node = nullptr;
		if (auto* left_mul = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
		{
			if (IsMulOpcode(left_mul->GetOpcode()))
			{
				mul = left_mul;
				base_node = add->GetRight();
			}
		}
		if (!mul)
		{
			if (auto* right_mul = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
			{
				if (IsMulOpcode(right_mul->GetOpcode()))
				{
					mul = right_mul;
					base_node = add->GetLeft();
				}
			}
		}

		if (!mul)
		{
			return false;
		}

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
		if (!IsValidX86Scale(scale_val))
		{
			return false;
		}

		matched_reg = reg;
		matched_add = add;
		matched_mul = mul;
		base = base_node;
		index = index_node;
		scale = scale_val;
		return true;
	}

	TileResult X86LeaBaseIndexScaleTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);
		MachineOperand index_op = ResolveOperand(index, ctx, result.worklist);

		if (!IsValidLeaOperand(base_op) || !IsValidLeaOperand(index_op))
		{
			result.success = false;
			return result;
		}

		MachineInstruction lea(X86_InstLea);
		lea.SetOp<0>(matched_reg->GetRegister());
		lea.SetOp<1>(base_op);
		lea.SetOp<2>(index_op);
		lea.SetOp<3>(MachineOperand::Immediate(scale, MachineType::Int64));
		lea.SetOp<4>(MachineOperand::Immediate(0, MachineType::Int64));
		result.instructions.push_back(lea);

		result.success = true;
		return result;
	}

	Bool X86LeaBaseDispTile::Match(ISelNode* node)
	{
		matched_reg = nullptr;
		matched_add = nullptr;
		base = nullptr;
		displacement = 0;

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
		if (!imm || !base_node)
		{
			return false;
		}

		if (isa<ISelBinaryOpNode>(base_node))
		{
			return false;
		}

		matched_reg = reg;
		matched_add = add;
		base = base_node;
		displacement = imm->GetImmediate();
		return true;
	}

	TileResult X86LeaBaseDispTile::Apply(MachineContext& ctx)
	{
		TileResult result;
		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);

		if (!IsValidLeaOperand(base_op))
		{
			result.success = false;
			return result;
		}

		MachineInstruction lea(X86_InstLea);
		lea.SetOp<0>(matched_reg->GetRegister());
		lea.SetOp<1>(base_op);
		lea.SetOp<2>(MachineOperand::Undefined());
		lea.SetOp<3>(MachineOperand::Immediate(1, MachineType::Int64));
		lea.SetOp<4>(MachineOperand::Immediate(displacement, MachineType::Int64));
		result.instructions.push_back(lea);

		result.success = true;
		return result;
	}

	Bool X86LeaIndexScaleDispTile::Match(ISelNode* node)
	{
		matched_reg = nullptr;
		matched_add = nullptr;
		matched_mul = nullptr;
		index = nullptr;
		scale = 0;
		displacement = 0;

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
		ISelImmediateNode* disp_imm = nullptr;
		if (auto* left_mul = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
		{
			if (IsMulOpcode(left_mul->GetOpcode()))
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
				if (IsMulOpcode(right_mul->GetOpcode()))
				{
					mul = right_mul;
					disp_imm = dyn_cast<ISelImmediateNode>(add->GetLeft());
				}
			}
		}
		if (!mul || !disp_imm)
		{
			return false;
		}

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
		if (!scale_imm || !index_node)
		{
			return false;
		}

		Int64 scale_val = scale_imm->GetImmediate();
		if (!IsValidX86Scale(scale_val))
		{
			return false;
		}

		matched_reg = reg;
		matched_add = add;
		matched_mul = mul;
		index = index_node;
		scale = scale_val;
		displacement = disp_imm->GetImmediate();
		return true;
	}

	TileResult X86LeaIndexScaleDispTile::Apply(MachineContext& ctx)
	{
		TileResult result;
		MachineOperand index_op = ResolveOperand(index, ctx, result.worklist);

		if (!IsValidLeaOperand(index_op))
		{
			result.success = false;
			return result;
		}

		MachineInstruction lea(X86_InstLea);
		lea.SetOp<0>(matched_reg->GetRegister());
		lea.SetOp<1>(MachineOperand::Undefined());
		lea.SetOp<2>(index_op);
		lea.SetOp<3>(MachineOperand::Immediate(scale, MachineType::Int64));
		lea.SetOp<4>(MachineOperand::Immediate(displacement, MachineType::Int64));
		result.instructions.push_back(lea);

		result.success = true;
		return result;
	}

	Bool X86LeaBaseIndexScaleDispTile::Match(ISelNode* node)
	{
		matched_reg = nullptr;
		outer_add = nullptr;
		inner_add = nullptr;
		matched_mul = nullptr;
		base = nullptr;
		index = nullptr;
		scale = 0;
		displacement = 0;

		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource())
		{
			return false;
		}

		auto* outer = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!outer || outer->GetOpcode() != Opcode::Add)
		{
			return false;
		}

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
		if (!inner || !disp_imm)
		{
			return false;
		}

		ISelBinaryOpNode* mul = nullptr;
		ISelNode* base_node = nullptr;
		if (auto* left_mul = dyn_cast<ISelBinaryOpNode>(inner->GetLeft()))
		{
			if (IsMulOpcode(left_mul->GetOpcode()))
			{
				mul = left_mul;
				base_node = inner->GetRight();
			}
		}
		if (!mul)
		{
			if (auto* right_mul = dyn_cast<ISelBinaryOpNode>(inner->GetRight()))
			{
				if (IsMulOpcode(right_mul->GetOpcode()))
				{
					mul = right_mul;
					base_node = inner->GetLeft();
				}
			}
		}
		if (!mul || !base_node)
		{
			return false;
		}

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
		if (!scale_imm || !index_node)
		{
			return false;
		}

		Int64 scale_val = scale_imm->GetImmediate();
		if (!IsValidX86Scale(scale_val))
		{
			return false;
		}

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

	TileResult X86LeaBaseIndexScaleDispTile::Apply(MachineContext& ctx)
	{
		TileResult result;
		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);
		MachineOperand index_op = ResolveOperand(index, ctx, result.worklist);

		if (!IsValidLeaOperand(base_op) || !IsValidLeaOperand(index_op))
		{
			result.success = false;
			return result;
		}

		MachineInstruction lea(X86_InstLea);
		lea.SetOp<0>(matched_reg->GetRegister());
		lea.SetOp<1>(base_op);
		lea.SetOp<2>(index_op);
		lea.SetOp<3>(MachineOperand::Immediate(scale, MachineType::Int64));
		lea.SetOp<4>(MachineOperand::Immediate(displacement, MachineType::Int64));
		result.instructions.push_back(lea);

		result.success = true;
		return result;
	}

	Bool X86MulByConstTile::Match(ISelNode* node)
	{
		matched_reg = nullptr;
		matched_mul = nullptr;
		operand = nullptr;
		multiplier = 0;

		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource())
		{
			return false;
		}

		auto* mul = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!mul || !IsMulOpcode(mul->GetOpcode())) return false;

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

		if (!imm || !op)
		{
			return false;
		}

		Int64 val = imm->GetImmediate();
		if (!IsSpecialX86Scale(val))
		{
			return false;
		}

		matched_reg = reg;
		matched_mul = mul;
		operand = op;
		multiplier = val;
		return true;
	}

	TileResult X86MulByConstTile::Apply(MachineContext& ctx)
	{
		TileResult result;
		MachineOperand op = ResolveOperand(operand, ctx, result.worklist);

		if (!IsValidLeaOperand(op))
		{
			result.success = false;
			return result;
		}

		Int64 scale_val = multiplier - 1;

		MachineInstruction lea(X86_InstLea);
		lea.SetOp<0>(matched_reg->GetRegister());
		lea.SetOp<1>(op);
		lea.SetOp<2>(op);
		lea.SetOp<3>(MachineOperand::Immediate(scale_val, MachineType::Int64));
		lea.SetOp<4>(MachineOperand::Immediate(0, MachineType::Int64));
		result.instructions.push_back(lea);

		result.success = true;
		return result;
	}

	Bool X86LeaBITile::Match(ISelNode* node)
	{
		matched_reg = nullptr;
		matched_add = nullptr;
		base = nullptr;
		index = nullptr;

		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* add = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!add || add->GetOpcode() != Opcode::Add) return false;

		if (isa<ISelImmediateNode>(add->GetLeft()) || isa<ISelImmediateNode>(add->GetRight())) return false;
		if (auto* left_bin = dyn_cast<ISelBinaryOpNode>(add->GetLeft()))
		{
			if (IsMulOpcode(left_bin->GetOpcode())) return false;
		}
		if (auto* right_bin = dyn_cast<ISelBinaryOpNode>(add->GetRight()))
		{
			if (IsMulOpcode(right_bin->GetOpcode())) return false;
		}

		matched_reg = reg;
		matched_add = add;
		base = add->GetLeft();
		index = add->GetRight();
		return true;
	}

	TileResult X86LeaBITile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);
		MachineOperand index_op = ResolveOperand(index, ctx, result.worklist);

		if (!IsValidLeaOperand(base_op) || !IsValidLeaOperand(index_op))
		{
			result.success = false;
			return result;
		}

		MachineInstruction lea(X86_InstLea);
		lea.SetOp<0>(matched_reg->GetRegister());
		lea.SetOp<1>(base_op);
		lea.SetOp<2>(index_op);
		lea.SetOp<3>(MachineOperand::Immediate(1, MachineType::Int64));
		lea.SetOp<4>(MachineOperand::Immediate(0, MachineType::Int64));
		result.instructions.push_back(lea);

		result.success = true;
		return result;
	}

	Bool X86LeaBIDTile::Match(ISelNode* node)
	{
		matched_reg = nullptr;
		outer_add = nullptr;
		inner_add = nullptr;
		base = nullptr;
		index = nullptr;
		displacement = 0;

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

		if (isa<ISelImmediateNode>(inner->GetLeft()) || isa<ISelImmediateNode>(inner->GetRight())) return false;
		if (auto* left_bin = dyn_cast<ISelBinaryOpNode>(inner->GetLeft()))
		{
			if (IsMulOpcode(left_bin->GetOpcode())) return false;
		}
		if (auto* right_bin = dyn_cast<ISelBinaryOpNode>(inner->GetRight()))
		{
			if (IsMulOpcode(right_bin->GetOpcode())) return false;
		}

		matched_reg = reg;
		outer_add = outer;
		inner_add = inner;
		base = inner->GetLeft();
		index = inner->GetRight();
		displacement = disp_imm->GetImmediate();
		return true;
	}

	TileResult X86LeaBIDTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand base_op = ResolveOperand(base, ctx, result.worklist);
		MachineOperand index_op = ResolveOperand(index, ctx, result.worklist);

		if (!IsValidLeaOperand(base_op) || !IsValidLeaOperand(index_op))
		{
			result.success = false;
			return result;
		}

		MachineInstruction lea(X86_InstLea);
		lea.SetOp<0>(matched_reg->GetRegister());
		lea.SetOp<1>(base_op);
		lea.SetOp<2>(index_op);
		lea.SetOp<3>(MachineOperand::Immediate(1, MachineType::Int64));
		lea.SetOp<4>(MachineOperand::Immediate(displacement, MachineType::Int64));
		result.instructions.push_back(lea);

		result.success = true;
		return result;
	}

	Bool X86DivTile::Match(ISelNode* node)
	{
		matched_reg = nullptr;
		matched_div = nullptr;
		dividend = nullptr;
		divisor = nullptr;

		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* div = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!div) return false;
		if (div->GetOpcode() != Opcode::SDiv) return false;

		matched_reg = reg;
		matched_div = div;
		dividend = div->GetLeft();
		divisor = div->GetRight();
		return true;
	}

	TileResult X86DivTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand dividend_op = ResolveOperand(dividend, ctx, result.worklist);
		MachineOperand divisor_op = ResolveOperand(divisor, ctx, result.worklist);
		MachineType type = matched_reg->GetRegister().GetType();

		MachineInstruction move_to_rax(InstMove);
		move_to_rax.SetOp<0>(MachineOperand::ISAReg(X86_RAX, type));
		move_to_rax.SetOp<1>(dividend_op);
		result.instructions.push_back(move_to_rax);

		MachineInstruction cqo(X86_InstCqo);
		result.instructions.push_back(cqo);

		if (divisor_op.IsImmediate())
		{
			MachineOperand temp = ctx.VirtualReg(type);
			MachineInstruction move_divisor(InstMove);
			move_divisor.SetOp<0>(temp);
			move_divisor.SetOp<1>(divisor_op);
			result.instructions.push_back(move_divisor);
			divisor_op = temp;
		}

		MachineInstruction idiv(InstSDiv);
		idiv.SetOp<0>(divisor_op);
		result.instructions.push_back(idiv);

		MachineInstruction move_result(InstMove);
		move_result.SetOp<0>(matched_reg->GetRegister());
		move_result.SetOp<1>(MachineOperand::ISAReg(X86_RAX, type));
		result.instructions.push_back(move_result);

		result.success = true;
		return result;
	}

	Bool X86RemTile::Match(ISelNode* node)
	{
		matched_reg = nullptr;
		matched_rem = nullptr;
		dividend = nullptr;
		divisor = nullptr;

		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* rem = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!rem) return false;
		if (rem->GetOpcode() != Opcode::SRem) return false;

		matched_reg = reg;
		matched_rem = rem;
		dividend = rem->GetLeft();
		divisor = rem->GetRight();
		return true;
	}

	TileResult X86RemTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand dividend_op = ResolveOperand(dividend, ctx, result.worklist);
		MachineOperand divisor_op = ResolveOperand(divisor, ctx, result.worklist);
		MachineType type = matched_reg->GetRegister().GetType();

		MachineInstruction move_to_rax(InstMove);
		move_to_rax.SetOp<0>(MachineOperand::ISAReg(X86_RAX, type));
		move_to_rax.SetOp<1>(dividend_op);
		result.instructions.push_back(move_to_rax);

		MachineInstruction cqo(X86_InstCqo);
		result.instructions.push_back(cqo);

		if (divisor_op.IsImmediate())
		{
			MachineOperand temp = ctx.VirtualReg(type);
			MachineInstruction move_divisor(InstMove);
			move_divisor.SetOp<0>(temp);
			move_divisor.SetOp<1>(divisor_op);
			result.instructions.push_back(move_divisor);
			divisor_op = temp;
		}

		MachineInstruction idiv(InstSDiv);
		idiv.SetOp<0>(divisor_op);
		result.instructions.push_back(idiv);

		MachineInstruction move_result(InstMove);
		move_result.SetOp<0>(matched_reg->GetRegister());
		move_result.SetOp<1>(MachineOperand::ISAReg(X86_RDX, type));
		result.instructions.push_back(move_result);

		result.success = true;
		return result;
	}

	void RegisterX86Tiles(ISelTiler& tiler)
	{
		tiler.RegisterTile(std::make_unique<X86LeaBaseIndexScaleDispTile>());
		tiler.RegisterTile(std::make_unique<X86LeaBaseIndexScaleTile>());
		tiler.RegisterTile(std::make_unique<X86LeaIndexScaleDispTile>());
		tiler.RegisterTile(std::make_unique<X86LeaBIDTile>());
		tiler.RegisterTile(std::make_unique<X86LeaBaseDispTile>());
		tiler.RegisterTile(std::make_unique<X86MulByConstTile>());
		tiler.RegisterTile(std::make_unique<X86LeaBITile>());
		tiler.RegisterTile(std::make_unique<X86DivTile>());
		tiler.RegisterTile(std::make_unique<X86RemTile>());
	}
}
