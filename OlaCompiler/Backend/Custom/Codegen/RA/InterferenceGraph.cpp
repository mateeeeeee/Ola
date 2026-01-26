#include "InterferenceGraph.h"

namespace ola
{
	void InterferenceGraph::AddNode(Uint32 vreg, Bool is_float)
	{
		if (!HasNode(vreg))
		{
			nodes.emplace(vreg, IGNode(vreg, is_float));
		}
	}

	IGNode* InterferenceGraph::GetNode(Uint32 vreg)
	{
		auto it = nodes.find(vreg);
		return it != nodes.end() ? &it->second : nullptr;
	}

	IGNode const* InterferenceGraph::GetNode(Uint32 vreg) const
	{
		auto it = nodes.find(vreg);
		return it != nodes.end() ? &it->second : nullptr;
	}

	Bool InterferenceGraph::HasNode(Uint32 vreg) const
	{
		return nodes.find(vreg) != nodes.end();
	}

	void InterferenceGraph::AddInterference(Uint32 vreg1, Uint32 vreg2)
	{
		if (vreg1 == vreg2) return;

		IGNode* node1 = GetNode(vreg1);
		IGNode* node2 = GetNode(vreg2);

		if (!node1 || !node2) return;
		if (node1->is_float != node2->is_float) return;

		if (node1->neighbors.insert(vreg2).second)
		{
			node1->degree++;
		}
		if (node2->neighbors.insert(vreg1).second)
		{
			node2->degree++;
		}
	}

	Bool InterferenceGraph::Interferes(Uint32 vreg1, Uint32 vreg2) const
	{
		IGNode const* node1 = GetNode(vreg1);
		if (!node1) return false;
		return node1->neighbors.contains(vreg2);
	}

	void InterferenceGraph::DecrementDegree(Uint32 vreg)
	{
		IGNode* node = GetNode(vreg);
		if (node && node->degree > 0)
		{
			node->degree--;
		}
	}

	Uint32 InterferenceGraph::GetDegree(Uint32 vreg) const
	{
		IGNode const* node = GetNode(vreg);
		return node ? node->degree : 0;
	}
}
