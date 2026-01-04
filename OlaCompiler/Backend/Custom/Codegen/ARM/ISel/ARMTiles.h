#pragma once
#include "Backend/Custom/Codegen/ISel/ISelTile.h"
#include "Backend/Custom/Codegen/ISel/ISelNode.h"

namespace ola
{
	class ARMMaddTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM; }
		Int GetPriority() const override { return 20; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* mul_left = nullptr;
		ISelNode* mul_right = nullptr;
		ISelNode* addend = nullptr;
	};

	class ARMMsubTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM; }
		Int GetPriority() const override { return 20; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_sub = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* mul_left = nullptr;
		ISelNode* mul_right = nullptr;
		ISelNode* minuend = nullptr;
	};

	class ARMFMaddTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM; }
		Int GetPriority() const override { return 20; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* mul_left = nullptr;
		ISelNode* mul_right = nullptr;
		ISelNode* addend = nullptr;
	};

	class ARMFMsubTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM; }
		Int GetPriority() const override { return 20; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_sub = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* mul_left = nullptr;
		ISelNode* mul_right = nullptr;
		ISelNode* minuend = nullptr;
	};

	class ARMLoadShiftedTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM; }
		Int GetPriority() const override { return 25; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelLoadNode* matched_load = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelBinaryOpNode* matched_shift = nullptr;
		ISelNode* base = nullptr;
		ISelNode* index = nullptr;
		Int64 shift_amount = 0;
	};

	class ARMStoreShiftedTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM; }
		Int GetPriority() const override { return 25; }

	private:
		ISelStoreNode* matched_store = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelBinaryOpNode* matched_shift = nullptr;
		ISelNode* base = nullptr;
		ISelNode* index = nullptr;
		ISelNode* value = nullptr;
		Int64 shift_amount = 0;
	};

	class ARMAddShiftedTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM; }
		Int GetPriority() const override { return 15; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelBinaryOpNode* matched_shift = nullptr;
		ISelNode* base = nullptr;
		ISelNode* shifted_operand = nullptr;
		Int64 shift_amount = 0;
	};

	void RegisterARMTiles(class ISelTiler& tiler);
}
