#pragma once
#include "Backend/Custom/Codegen/ISel/ISelTile.h"
#include "Backend/Custom/Codegen/ISel/ISelNode.h"

namespace ola
{
	class ARM64MaddTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM64; }
		Int GetPriority() const override { return 20; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* mul_left = nullptr;
		ISelNode* mul_right = nullptr;
		ISelNode* addend = nullptr;
	};

	class ARM64MsubTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM64; }
		Int GetPriority() const override { return 20; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_sub = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* mul_left = nullptr;
		ISelNode* mul_right = nullptr;
		ISelNode* minuend = nullptr;
	};

	class ARM64FMaddTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM64; }
		Int GetPriority() const override { return 20; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* mul_left = nullptr;
		ISelNode* mul_right = nullptr;
		ISelNode* addend = nullptr;
	};

	class ARM64FMsubTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM64; }
		Int GetPriority() const override { return 20; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_sub = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* mul_left = nullptr;
		ISelNode* mul_right = nullptr;
		ISelNode* minuend = nullptr;
	};

	class ARM64LoadShiftedTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM64; }
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

	class ARM64StoreShiftedTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM64; }
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

	class ARM64AddShiftedTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::ARM64; }
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
