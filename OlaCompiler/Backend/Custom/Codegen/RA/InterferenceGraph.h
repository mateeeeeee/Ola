#pragma once
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include "Backend/Custom/Codegen/MachineOperand.h"

namespace ola
{
	struct IGNode
	{
		Uint32 vreg;
		Uint32 color;
		Bool is_float;
		Bool spilled;
		Bool on_stack;
		Float64 spill_cost;
		Uint32 degree;
		std::unordered_set<Uint32> neighbors;

		IGNode() : vreg(0), color(INVALID_REG), is_float(false), spilled(false), on_stack(false), spill_cost(0.0), degree(0) {}
		explicit IGNode(Uint32 vreg, Bool is_float)
			: vreg(vreg), color(INVALID_REG), is_float(is_float), spilled(false), on_stack(false), spill_cost(0.0), degree(0) {}
	};

	class InterferenceGraph
	{
	public:
		InterferenceGraph() = default;

		void AddNode(Uint32 vreg, Bool is_float);
		IGNode* GetNode(Uint32 vreg);
		IGNode const* GetNode(Uint32 vreg) const;
		Bool HasNode(Uint32 vreg) const;

		void AddInterference(Uint32 vreg1, Uint32 vreg2);
		Bool Interferes(Uint32 vreg1, Uint32 vreg2) const;

		void DecrementDegree(Uint32 vreg);
		Uint32 GetDegree(Uint32 vreg) const;

		auto begin() { return nodes.begin(); }
		auto end() { return nodes.end(); }
		auto begin() const { return nodes.begin(); }
		auto end() const { return nodes.end(); }

		Uint32 GetNodeCount() const { return static_cast<Uint32>(nodes.size()); }
		void Clear() { nodes.clear(); }

	private:
		std::unordered_map<Uint32, IGNode> nodes;
	};
}
