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

	class X86LeaBITile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::X86; }
		Int GetPriority() const override { return 12; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_add = nullptr;
		ISelNode* base = nullptr;
		ISelNode* index = nullptr;
	};

	class X86LeaBIDTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::X86; }
		Int GetPriority() const override { return 17; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* outer_add = nullptr;
		ISelBinaryOpNode* inner_add = nullptr;
		ISelNode* base = nullptr;
		ISelNode* index = nullptr;
		Int64 displacement = 0;
	};

	class X86DivTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::X86; }
		Int GetPriority() const override { return 10; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_div = nullptr;
		ISelNode* dividend = nullptr;
		ISelNode* divisor = nullptr;
	};

	class X86RemTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		TargetArch GetTarget() const override { return TargetArch::X86; }
		Int GetPriority() const override { return 10; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_rem = nullptr;
		ISelNode* dividend = nullptr;
		ISelNode* divisor = nullptr;
	};

	void RegisterX86Tiles(class ISelTiler& tiler);
}
