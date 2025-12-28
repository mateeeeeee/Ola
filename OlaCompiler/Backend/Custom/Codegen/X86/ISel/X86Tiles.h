#pragma once
#include "Backend/Custom/Codegen/ISel/ISelTile.h"
#include "Backend/Custom/Codegen/ISel/ISelNode.h"

namespace ola
{
	class X86LeaBaseIndexScaleTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::X86; }
		Int GetPriority() const override { return 20; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelNode* base = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* index = nullptr;
		Int64 scale = 0;
	};

	class X86LeaBaseDispTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::X86; }
		Int GetPriority() const override { return 15; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelNode* base = nullptr;
		Int64 displacement = 0;
	};

	class X86LeaIndexScaleDispTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::X86; }
		Int GetPriority() const override { return 18; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* index = nullptr;
		Int64 scale = 0;
		Int64 displacement = 0;
	};

	class X86LeaBaseIndexScaleDispTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::X86; }
		Int GetPriority() const override { return 25; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* outer_add = nullptr;
		ISelBinaryOpNode* inner_add = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* base = nullptr;
		ISelNode* index = nullptr;
		Int64 scale = 0;
		Int64 displacement = 0;
	};

	class X86MulByConstTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::X86; }
		Int GetPriority() const override { return 15; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* operand = nullptr;
		Int64 multiplier = 0;
	};

	class X86LoadBaseIndexScaleTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::X86; }
		Int GetPriority() const override { return 25; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelLoadNode* matched_load = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* base = nullptr;
		ISelNode* index = nullptr;
		Int64 scale = 0;
	};

	class X86StoreBaseIndexScaleTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::X86; }
		Int GetPriority() const override { return 25; }

	private:
		ISelStoreNode* matched_store = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* base = nullptr;
		ISelNode* index = nullptr;
		ISelNode* value = nullptr;
		Int64 scale = 0;
	};

	void RegisterX86Tiles(class ISelTiler& tiler);
}
