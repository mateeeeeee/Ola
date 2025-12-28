#pragma once
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "ISelNode.h"

namespace ola
{
	class ISelForest
	{
	public:
		ISelForest() = default;
		~ISelForest() = default;

		OLA_NONCOPYABLE(ISelForest)
		OLA_DEFAULT_MOVABLE(ISelForest)

		void AddTree(ISelNodePtr root, std::vector<ISelNode*> const& leaves, Bool has_memory_op)
		{
			ISelNode* root_ptr = root.get();
			trees.push_back(std::move(root));
			leaves_map[root_ptr] = leaves;
			if (has_memory_op)
			{
				memory_trees.insert(root_ptr);
			}
		}

		void RemoveTree(ISelNode* tree)
		{
			leaves_map.erase(tree);
			memory_trees.erase(tree);
			trees.remove_if([tree](ISelNodePtr const& ptr) { return ptr.get() == tree; });
		}

		std::vector<ISelNode*> const& GetLeaves(ISelNode* tree) const
		{
			static std::vector<ISelNode*> empty;
			auto it = leaves_map.find(tree);
			return it != leaves_map.end() ? it->second : empty;
		}

		Bool HasMemoryOp(ISelNode* tree) const
		{
			return memory_trees.count(tree) > 0;
		}

		Bool IsEmpty() const { return trees.empty(); }
		Uint32 GetNumTrees() const { return static_cast<Uint32>(trees.size()); }

		using TreeIterator = std::list<ISelNodePtr>::iterator;
		using ConstTreeIterator = std::list<ISelNodePtr>::const_iterator;

		TreeIterator begin() { return trees.begin(); }
		TreeIterator end() { return trees.end(); }
		ConstTreeIterator begin() const { return trees.begin(); }
		ConstTreeIterator end() const { return trees.end(); }

		std::list<ISelNodePtr>& Trees() { return trees; }
		std::list<ISelNodePtr> const& Trees() const { return trees; }

	private:
		std::list<ISelNodePtr> trees;
		std::unordered_map<ISelNode*, std::vector<ISelNode*>> leaves_map;
		std::unordered_set<ISelNode*> memory_trees;
	};

	class Value;

	class ISelValueMap
	{
	public:
		void MapValue(Value* ir_value, ISelNode* node)
		{
			value_to_node[ir_value] = node;
		}

		ISelNode* GetNode(Value* ir_value) const
		{
			auto it = value_to_node.find(ir_value);
			return it != value_to_node.end() ? it->second : nullptr;
		}

		Bool HasMapping(Value* ir_value) const
		{
			return value_to_node.count(ir_value) > 0;
		}

		void Clear()
		{
			value_to_node.clear();
		}

	private:
		std::unordered_map<Value*, ISelNode*> value_to_node;
	};

	class ISelUseCount
	{
	public:
		void IncrementUse(ISelNode* node)
		{
			use_counts[node]++;
		}

		Uint32 GetUseCount(ISelNode* node) const
		{
			auto it = use_counts.find(node);
			return it != use_counts.end() ? it->second : 0;
		}

		Bool HasSingleUse(ISelNode* node) const
		{
			return GetUseCount(node) == 1;
		}

		void Clear()
		{
			use_counts.clear();
		}

	private:
		std::unordered_map<ISelNode*, Uint32> use_counts;
	};
}
