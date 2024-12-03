#include <functional>
#include <set>
#include "DominatorTree.h"
#include "CFG.h"

namespace ola
{
	//https://github.com/KhronosGroup/SPIRV-Tools/blob/main/source/cfa.h: template <class BB> std::vector<std::pair<BB*, BB*>> CFA<BB>::CalculateDominators simplified
	static std::vector<std::pair<BasicBlock const*, BasicBlock const*>> CalculateDominators(CFG const& cfg, std::vector<BasicBlock const*> const& postorder)
	{
		struct BasicBlockDomInfo 
		{
			Uint64 dominator;			///< The index of blocks's dominator in post order array
			Uint64 postorder_index;		///< The index of the block in the post order array
		};
		Uint64 const invalid_dom = postorder.size();

		std::unordered_map<BasicBlock const*, BasicBlockDomInfo> idoms;
		for (Uint64 i = 0; i < postorder.size(); i++) 
		{
			idoms[postorder[i]] = { invalid_dom, i };
		}
		idoms[postorder.back()].dominator = idoms[postorder.back()].postorder_index;

		Bool changed = true;
		while (changed) 
		{
			changed = false;
			for (auto b = postorder.rbegin() + 1; b != postorder.rend(); ++b) 
			{
				std::vector<BasicBlock const*> const& predecessors = cfg.GetPredecessors(*b);

				// Find the first processed/reachable predecessor that is reachable in the forward traversal.
				auto res = std::find_if(std::begin(predecessors), std::end(predecessors),
					[&idoms, invalid_dom](BasicBlock const* pred)
					{
						return idoms.contains(pred) && idoms[pred].dominator != invalid_dom;
					});
				if (res == end(predecessors)) continue;

				BasicBlock const* idom = *res;
				Uint64 idom_idx = idoms[idom].postorder_index;

				// all other predecessors
				for (const auto* p : predecessors) 
				{
					if (idom == p) continue;
					// Only consider nodes reachable in the forward traversal.
					// Otherwise the intersection doesn't make sense and will never
					// terminate.
					if (!idoms.contains(p)) continue;
					if (idoms[p].dominator != invalid_dom) 
					{
						Uint64 finger1 = idoms[p].postorder_index;
						Uint64 finger2 = idom_idx;
						while (finger1 != finger2) 
						{
							while (finger1 < finger2) 
							{
								finger1 = idoms[postorder[finger1]].dominator;
							}
							while (finger2 < finger1) 
							{
								finger2 = idoms[postorder[finger2]].dominator;
							}
						}
						idom_idx = finger1;
					}
				}
				if (idoms[*b].dominator != idom_idx) 
				{
					idoms[*b].dominator = idom_idx;
					changed = true;
				}
			}
		}

		std::vector<std::pair<BasicBlock const*, BasicBlock const*>> out;
		for (auto const& idom : idoms) 
		{
			// At this point if there is no dominator for the node, just make it
			// reflexive.
			auto dominator = std::get<1>(idom).dominator;
			if (dominator == invalid_dom) {
				dominator = std::get<1>(idom).postorder_index;
			}
			// NOTE: performing a const cast for convenient usage with
			// UpdateImmediateDominators
			out.push_back({ std::get<0>(idom), postorder[dominator] });
		}

		// Sort by postorder index to generate a deterministic ordering of edges.
		std::sort(
			out.begin(), out.end(),
			[&idoms](const std::pair<BasicBlock const*, BasicBlock const*>& lhs,
				const std::pair<BasicBlock const*, BasicBlock const*>& rhs) 
			{
					assert(lhs.first);
					assert(lhs.second);
					assert(rhs.first);
					assert(rhs.second);
					auto lhs_indices = std::make_pair(idoms[lhs.first].postorder_index,
						idoms[lhs.second].postorder_index);
					auto rhs_indices = std::make_pair(idoms[rhs.first].postorder_index,
						idoms[rhs.second].postorder_index);
					return lhs_indices < rhs_indices;
			});
		return out;
	}

	void DominatorTree::Initialize(CFG const& cfg)
	{
		ClearTree();

		std::vector<DominatorTreeEdge> immediate_doms = GetImmediateDominators(cfg);
		for (DominatorTreeEdge const& edge : immediate_doms)
		{
			DominatorTreeNode* first = GetOrInsertNode(edge.first);
			if (edge.first == edge.second) 
			{
				OLA_ASSERT(root == nullptr);
				root = first;
			}
			else
			{
				DominatorTreeNode* second = GetOrInsertNode(edge.second);
				first->parent = second;
				second->children.push_back(first);
			}
		}
		ResetDepthFirstIndices();
	}

	void DominatorTree::ResetDepthFirstIndices()
	{
		Int index = 0;
		ResetDepthFirstIndicesRecursive(root, index);
	}

	void DominatorTree::ResetDepthFirstIndicesRecursive(DominatorTreeNode* node, Int& index)
	{
		if (!node) return;

		node->dfs_preorder_index = ++index;
		for (DominatorTreeNode* child : *node)
		{
			ResetDepthFirstIndicesRecursive(child, index);
		}
		node->dfs_postorder_index = ++index;
	}

	std::vector<DominatorTree::DominatorTreeEdge> DominatorTree::GetImmediateDominators(CFG const& cfg)
	{
		std::vector<BasicBlock const*> postorder;
		std::function<void(BasicBlock const*, std::set<BasicBlock const*>&)> DFSPostOrder =
			[&](BasicBlock const* node, std::set<BasicBlock const*>& visited)
			{
				if (!node || visited.count(node)) return;
				visited.insert(node);
				for (auto const* succ : cfg.GetSuccessors(node))
				{ 
					DFSPostOrder(succ, visited);
				}
				postorder.push_back(node);
			};
		std::set<BasicBlock const*> visited;
		DFSPostOrder(cfg.GetEntryBlock(), visited);
		return CalculateDominators(cfg, postorder);
	}

}

