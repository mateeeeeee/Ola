#pragma once
#include "Backend/Custom/Codegen/ISel/ISelTile.h"
#include "Backend/Custom/Codegen/ISel/ISelNode.h"

namespace ola
{
	class MoveTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		Int GetPriority() const override { return 1; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
	};

	class LoadTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		Int GetPriority() const override { return 10; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelLoadNode* matched_load = nullptr;
	};

	class StoreTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		Int GetPriority() const override { return 10; }

	private:
		ISelStoreNode* matched_store = nullptr;
	};

	class BinaryOpTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		Int GetPriority() const override { return 5; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_binary = nullptr;
	};

	class UnaryOpTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		Int GetPriority() const override { return 5; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelUnaryOpNode* matched_unary = nullptr;
	};

	class CompareTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		Int GetPriority() const override { return 5; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelCompareNode* matched_cmp = nullptr;
	};

	class SelectTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		Int GetPriority() const override { return 5; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelSelectNode* matched_select = nullptr;
	};

	class MulOneTile : public ISelTile
	{
	public:
		Bool Match(ISelNode* node) override;
		TileResult Apply(MachineContext& ctx) override;
		Int GetPriority() const override { return 8; }

	private:
		ISelRegisterNode* matched_reg = nullptr;
		ISelBinaryOpNode* matched_mul = nullptr;
		ISelNode* operand = nullptr;
	};

	void RegisterCommonTiles(class ISelTiler& tiler);
}
