#include "CommonTiles.h"
#include "Backend/Custom/Codegen/ISel/ISelTiler.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineContext.h"
#include "Utility/RTTI.h"

namespace ola
{
	namespace
	{
		Bool IsFloatCompare(CompareOp cmp)
		{
			return cmp >= CompareOp::FCmpOEQ;
		}
	}

	Bool MoveTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg) return false;
		if (reg->HasSource()) return false;
		matched_reg = reg;
		return true;
	}

	TileResult MoveTile::Apply(MachineContext& ctx)
	{
		TileResult result;
		result.success = true;
		return result;
	}

	Bool LoadTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* load = dyn_cast<ISelLoadNode>(reg->GetSource());
		if (!load) return false;

		matched_reg = reg;
		matched_load = load;
		return true;
	}

	TileResult LoadTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand addr_op = ResolveOperand(matched_load->GetAddress(), ctx, result.worklist);

		MachineInstruction load(InstLoad);
		load.SetOp<0>(matched_reg->GetRegister());
		load.SetOp<1>(addr_op);
		result.instructions.push_back(load);

		result.success = true;
		return result;
	}

	Bool StoreTile::Match(ISelNode* node)
	{
		auto* store = dyn_cast<ISelStoreNode>(node);
		if (!store) return false;

		matched_store = store;
		return true;
	}

	TileResult StoreTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand value_op = ResolveOperand(matched_store->GetValueNode(), ctx, result.worklist);
		MachineOperand addr_op = ResolveOperand(matched_store->GetAddress(), ctx, result.worklist);

		MachineInstruction store(InstStore);
		store.SetOp<0>(addr_op);
		store.SetOp<1>(value_op);
		result.instructions.push_back(store);

		result.success = true;
		return result;
	}

	Bool BinaryOpTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* binary = dyn_cast<ISelBinaryOpNode>(reg->GetSource());
		if (!binary) return false;

		matched_reg = reg;
		matched_binary = binary;
		return true;
	}

	TileResult BinaryOpTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand left_op = ResolveOperand(matched_binary->GetLeft(), ctx, result.worklist);
		MachineOperand right_op = ResolveOperand(matched_binary->GetRight(), ctx, result.worklist);

		Uint32 machine_opcode = GetMachineOpcode(matched_binary->GetOpcode());
		if (machine_opcode == InstUnknown)
		{
			result.success = false;
			return result;
		}

		MachineInstruction inst(machine_opcode);
		inst.SetOp<0>(matched_reg->GetRegister());
		inst.SetOp<1>(left_op);
		inst.SetOp<2>(right_op);
		result.instructions.push_back(inst);

		result.success = true;
		return result;
	}

	Bool UnaryOpTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* unary = dyn_cast<ISelUnaryOpNode>(reg->GetSource());
		if (!unary) return false;

		matched_reg = reg;
		matched_unary = unary;
		return true;
	}

	TileResult UnaryOpTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand operand = ResolveOperand(matched_unary->GetOperand(), ctx, result.worklist);

		Uint32 machine_opcode = GetMachineOpcode(matched_unary->GetOpcode());
		if (machine_opcode == InstUnknown)
		{
			result.success = false;
			return result;
		}

		MachineInstruction inst(machine_opcode);
		inst.SetOp<0>(matched_reg->GetRegister());
		inst.SetOp<1>(operand);
		result.instructions.push_back(inst);

		result.success = true;
		return result;
	}

	Bool CompareTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* cmp = dyn_cast<ISelCompareNode>(reg->GetSource());
		if (!cmp) return false;

		matched_reg = reg;
		matched_cmp = cmp;
		return true;
	}

	TileResult CompareTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand left_op = ResolveOperand(matched_cmp->GetLeft(), ctx, result.worklist);
		MachineOperand right_op = ResolveOperand(matched_cmp->GetRight(), ctx, result.worklist);

		Uint32 cmp_opcode = IsFloatCompare(matched_cmp->GetCompareOp()) ? InstFCmp : InstICmp;
		MachineInstruction cmp(cmp_opcode);
		cmp.SetOp<0>(matched_reg->GetRegister());
		cmp.SetOp<1>(left_op);
		cmp.SetOp<2>(right_op);
		cmp.SetOp<3>(MachineOperand::Immediate((Uint32)matched_cmp->GetCompareOp(), MachineType::Other));
		result.instructions.push_back(cmp);

		result.success = true;
		return result;
	}

	Bool SelectTile::Match(ISelNode* node)
	{
		auto* reg = dyn_cast<ISelRegisterNode>(node);
		if (!reg || !reg->HasSource()) return false;

		auto* select = dyn_cast<ISelSelectNode>(reg->GetSource());
		if (!select) return false;

		matched_reg = reg;
		matched_select = select;
		return true;
	}

	TileResult SelectTile::Apply(MachineContext& ctx)
	{
		TileResult result;

		MachineOperand pred_op = ResolveOperand(matched_select->GetPredicate(), ctx, result.worklist);
		MachineOperand true_op = ResolveOperand(matched_select->GetTrueValue(), ctx, result.worklist);
		MachineOperand false_op = ResolveOperand(matched_select->GetFalseValue(), ctx, result.worklist);

		MachineInstruction test(InstTest);
		test.SetOp<0>(pred_op);
		test.SetOp<1>(pred_op);
		result.instructions.push_back(test);

		MachineInstruction mov(InstMove);
		mov.SetOp<0>(matched_reg->GetRegister());
		mov.SetOp<1>(false_op);
		result.instructions.push_back(mov);

		MachineInstruction cmov(InstCMoveNE);
		cmov.SetOp<0>(matched_reg->GetRegister());
		cmov.SetOp<1>(true_op);
		result.instructions.push_back(cmov);

		result.success = true;
		return result;
	}

	void RegisterCommonTiles(ISelTiler& tiler)
	{
		tiler.RegisterTile(std::make_unique<MoveTile>());
		tiler.RegisterTile(std::make_unique<LoadTile>());
		tiler.RegisterTile(std::make_unique<StoreTile>());
		tiler.RegisterTile(std::make_unique<BinaryOpTile>());
		tiler.RegisterTile(std::make_unique<UnaryOpTile>());
		tiler.RegisterTile(std::make_unique<CompareTile>());
		tiler.RegisterTile(std::make_unique<SelectTile>());
	}
}
