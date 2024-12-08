#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <iosfwd>
#include "BasicBlock.h"
#include "Utility/TreeIterator.h"

namespace ola
{
	class DominatorTree;
	class DominatorTreeNode
	{
		friend class DominatorTree;
	public:
		using iterator = std::vector<DominatorTreeNode*>::iterator;
		using const_iterator = std::vector<DominatorTreeNode*>::const_iterator;

		using df_iterator = DFTreeIterator<DominatorTreeNode>;
		using const_df_iterator = DFTreeIterator<const DominatorTreeNode>;

		explicit DominatorTreeNode(BasicBlock* BB) : bb(BB), parent(nullptr), children(), dfs_preorder_index(-1), dfs_postorder_index(-1) {}
		BasicBlock* GetBasicBlock() const { return bb; }

		iterator	   begin()			{ return children.begin(); }
		iterator	   end()			{ return children.end(); }
		const_iterator begin()	const	{ return cbegin(); }
		const_iterator end()	const	{ return cend(); }
		const_iterator cbegin() const	{ return children.cbegin(); }
		const_iterator cend()	const	{ return children.cend(); }

		df_iterator		  df_begin()			{ return df_iterator(this); }
		df_iterator		  df_end()				{ return df_iterator(); }
		const_df_iterator df_begin()	const	{ return df_cbegin(); }
		const_df_iterator df_end()		const	{ return df_cend(); }
		const_df_iterator df_cbegin()	const	{ return const_df_iterator(this); }
		const_df_iterator df_cend()		const	{ return const_df_iterator(); }

	private:
		BasicBlock* bb;
		DominatorTreeNode* parent;
		std::vector<DominatorTreeNode*> children;
		Int dfs_preorder_index;
		Int dfs_postorder_index;
	};

	class CFG;
	class DominatorTree
	{
		using DominatorTreeNodeMap = std::unordered_map<Uint32, DominatorTreeNode>;
		using ImmediateDominatorsMap = std::unordered_map<DominatorTreeNode const*, DominatorTreeNode const*>;
		using DominatorTreeEdge = std::pair<BasicBlock*, BasicBlock*>;
	public:
		using iterator = DominatorTreeNode::df_iterator;
		using const_iterator = DominatorTreeNode::const_df_iterator;

	public:
		DominatorTree() : root(nullptr), nodes() {}

		void Initialize(CFG const& cfg);

		DominatorTreeNode* GetRoot()
		{
			return root;
		}
		DominatorTreeNode const* GetRoot() const
		{
			return root;
		}

		Bool Dominates(BasicBlock const* a, BasicBlock const* b) const
		{
			return Dominates(a->GetIndex(), b->GetIndex());
		}
		Bool Dominates(Uint32 a_idx, Uint32 b_idx) const
		{
			DominatorTreeNode const* a = GetTreeNode(a_idx);
			DominatorTreeNode const* b = GetTreeNode(b_idx);
			if (!a || !b) return false;

			return Dominates(a, b);
		}
		Bool Dominates(DominatorTreeNode const* a, DominatorTreeNode const* b) const
		{
			if (!a || !b) return false;
			if (a == b)   return true;
			return a->dfs_preorder_index < b->dfs_preorder_index && a->dfs_postorder_index > b->dfs_postorder_index;
		}

		Bool StrictlyDominates(BasicBlock const* a, BasicBlock const* b) const
		{
			return StrictlyDominates(a->GetIndex(), b->GetIndex());
		}
		Bool StrictlyDominates(Uint32 a_idx, Uint32 b_idx) const
		{
			if (a_idx == b_idx) return false;
			return Dominates(a_idx, b_idx);
		}
		Bool StrictlyDominates(DominatorTreeNode const* a, DominatorTreeNode const* b) const
		{
			if (a == b) return false;
			return Dominates(a, b);
		}

		DominatorTreeNode* GetTreeNode(BasicBlock* bb)
		{
			return GetTreeNode(bb->GetIndex());
		}
		DominatorTreeNode const* GetTreeNode(BasicBlock* bb) const
		{
			return GetTreeNode(bb->GetIndex());
		}
		DominatorTreeNode* GetTreeNode(Uint32 idx)
		{
			DominatorTreeNodeMap::iterator node_iter = nodes.find(idx);
			if (node_iter == nodes.end())
			{
				return nullptr;
			}
			return &node_iter->second;
		}
		DominatorTreeNode const* GetTreeNode(Uint32 idx) const
		{
			DominatorTreeNodeMap::const_iterator node_iter = nodes.find(idx);
			if (node_iter == nodes.end())
			{
				return nullptr;
			}
			return &node_iter->second;
		}

		Bool ReachableFromRoot(BasicBlock const* a) const
		{
			if (!a) return false;
			return ReachableFromRoot(a->GetIndex());
		}
		Bool ReachableFromRoot(Uint32 a) const
		{
			return GetTreeNode(a) != nullptr;
		}

		BasicBlock* GetImmediateDominator(BasicBlock* bb) const
		{
			return GetImmediateDominator(GetTreeNode(bb))->GetBasicBlock();
		}
		DominatorTreeNode const* GetImmediateDominator(DominatorTreeNode const* node) const
		{
			if (auto it = immediate_dominators.find(node); it != immediate_dominators.end())
			{
				return it->second;
			}
			return nullptr;
		}

		void ClearTree()
		{
			nodes.clear();
			root = nullptr;
		}

		template<typename F> requires std::is_invocable_r_v<Bool, F, DominatorTreeNode*>
		Bool Visit(F&& f)
		{
			for (auto& n : *this)
			{
				if (!f(&n)) return false;
			}
			return true;
		}
		template<typename F> requires std::is_invocable_r_v<Bool, F, DominatorTreeNode const*>
		Bool Visit(F&& f) const
		{
			for (auto const& n : *this)
			{
				if (!f(&n)) return false;
			}
			return true;
		}
		template<typename F> requires std::is_invocable_r_v<Bool, F, DominatorTreeNode*>
		Bool VisitChildrenIf(F&& f, iterator node)
		{
			if (f(&*node)) 
			{
				for (auto& n : *node) 
				{
					VisitChildrenIf(f, n->df_begin());
				}
			}
		}

		DominatorTreeNode* GetOrInsertNode(BasicBlock* bb) 
		{
			DominatorTreeNode* node = nullptr;
			auto node_iter = nodes.find(bb->GetIndex());
			if (node_iter == nodes.end())
			{
				node = &nodes.emplace(std::make_pair(bb->GetIndex(), DominatorTreeNode(bb))).first->second;
			}
			else 
			{
				node = &node_iter->second;
			}
			return node;
		}

		void ResetDepthFirstIndices();

		iterator begin() { return iterator(GetRoot()); }
		iterator end() { return iterator(); }
		const_iterator begin() const { return cbegin(); }
		const_iterator end() const { return cend(); }
		const_iterator cbegin() const { return const_iterator(GetRoot()); }
		const_iterator cend() const { return const_iterator(); }

		void Print(std::string const& function_name) const;

	private:
		DominatorTreeNode* root;
		ImmediateDominatorsMap immediate_dominators;
		DominatorTreeNodeMap nodes;

	private:
		void ResetDepthFirstIndicesRecursive(DominatorTreeNode* node, Int& index);
		std::vector<DominatorTreeEdge> GetImmediateDominators(CFG const& cfg);
		void PrintNode(std::ostream& os, DominatorTreeNode const* node) const;
	};

}

