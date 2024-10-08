#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <utility>
#include "Utility/IteratorRange.h"
#include "Backend/Custom/PassRegistry.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/FunctionPass.h"

namespace ola
{
	//temporary to not include <algorithm> in a header file, move it somewhere 
	template<typename InputIt, typename T = typename std::iterator_traits<InputIt>::value_type>
	constexpr InputIt find(InputIt first, InputIt last, T const& value)
	{
		for (; first != last; ++first)
			if (*first == value)
				return first;
		return last;
	}

	template <typename NodeT>
	class DominatorTreeBase;

	template <typename NodeT> 
	class DominatorTreeNodeBase
	{
		friend class DominatorTreeBase<NodeT>;

	public:
		DominatorTreeNodeBase(NodeT* BB, DominatorTreeNodeBase* iDom)
			: node(BB), idom(iDom), level(idom ? idom->level + 1 : 0) {}

		auto begin() { return children.begin(); }
		auto end() { return children.end(); }

		auto& Children() { return children; }
		auto const& Children() const { return children; }

		NodeT* GetBlock() const { return node; }
		DominatorTreeNodeBase* GetIDom() const { return idom; }
		uint32 GetLevel() const { return level; }

		void AddChild(DominatorTreeNodeBase* C) { children.push_back(C); }
		bool IsLeaf() const { return children.empty(); }
		uint64 GetNumChildren() const { return children.size(); }
		void ClearAllChildren() { children.clear(); }

		uint32 GetDFSNumIn() const { return dfs_num_in; }
		uint32 GetDFSNumOut() const { return dfs_num_out; }

		void SetIDom(DominatorTreeNodeBase* NewIDom) 
		{
			OLA_ASSERT_MSG(idom, "No immediate dominator?");
			if (idom == NewIDom) return;

			auto I = find(idom->children.begin(), idom->children.end(), this);
			OLA_ASSERT_MSG(I != idom->children.end(), "Not in immediate dominator children set!");
			idom->children.erase(I);
			idom = NewIDom;
			idom->children.push_back(this);

			UpdateLevel();
		}

	private:
		NodeT* node;
		DominatorTreeNodeBase* idom;
		uint32 level;
		std::vector<DominatorTreeNodeBase*> children;
		mutable uint32 dfs_num_in = ~0;
		mutable uint32 dfs_num_out = ~0;

	private:
		bool DominatedBy(const DominatorTreeNodeBase* other) const 
		{
			return this->dfs_num_in >= other->dfs_num_in &&
				   this->dfs_num_out <= other->dfs_num_out;
		}
		void UpdateLevel() 
		{
			OLA_ASSERT(idom);
			if (level == idom->level + 1) return;

			std::vector<DominatorTreeNodeBase*> WorkStack = { this };
			while (!WorkStack.empty()) 
			{
				DominatorTreeNodeBase* Current = WorkStack.back();
				WorkStack.pop_back();
				Current->level = Current->idom->level + 1;
				for (DominatorTreeNodeBase* C : *Current) 
				{
					OLA_ASSERT(C->idom);
					if (C->level != C->idom->level + 1) WorkStack.push_back(C);
				}
			}
		}
	};

	template <typename NodeT> struct DomTreeNodeTraits
	{
		using NodeType = NodeT;
		using NodePtr = NodeT*;
		using ParentPtr = decltype(std::declval<NodePtr>()->GetParent());
		static_assert(std::is_pointer_v<ParentPtr>, "Currently NodeT's parent must be a pointer type");
		using ParentType = std::remove_pointer_t<ParentPtr>;

		static ParentPtr GetParent(NodeType const* BB) { return BB->GetParent(); }
		static ParentPtr GetParent(NodePtr* BB) { return BB->GetParent(); }
		static NodePtr GetEntryNode(ParentPtr parent) { return &parent->GetEntryBlock(); }
	};

	template <typename NodeT>
	class DominatorTreeBase
	{
		using NodeTrait = DomTreeNodeTraits<NodeT>;
		using NodeType = typename NodeTrait::NodeType;
		using NodePtr = typename NodeTrait::NodePtr;
		using ParentPtr = typename NodeTrait::ParentPtr;
		static_assert(std::is_pointer_v<ParentPtr>, "Currently NodeT's parent must be a pointer type");
		using ParentType = std::remove_pointer_t<ParentPtr>;

		using DomTreeNodeStorage = std::vector<std::unique_ptr<DominatorTreeNodeBase<NodeT>>>;
		using NodeNumberStorage = std::unordered_map<NodeT const*, uint32>;
		static constexpr uint32 INVALID_NODE_NUMBER = uint32(-1);

	public:
		DominatorTreeBase() = default;
		OLA_NONCOPYABLE(DominatorTreeBase)
		OLA_DEFAULT_MOVABLE(DominatorTreeBase)
		~DominatorTreeBase() = default;

		DominatorTreeNodeBase<NodeT>* GetNode(NodeT const* BB) const
		{
			OLA_ASSERT_MSG((!BB || parent == NodeTrait::GetParent(BB)), "cannot get DomTreeNode of block with different parent");
			if (auto Idx = GetNodeIndex(BB); Idx != INVALID_NODE_NUMBER && Idx < dom_tree_nodes.size())
				return dom_tree_nodes[Idx].get();
			return nullptr;
		}
		DominatorTreeNodeBase<NodeT>* operator[](NodeT const* BB) const
		{
			return GetNode(BB);
		}

		DominatorTreeNodeBase<NodeT>* GetRootNode() { return root_node; }
		const DominatorTreeNodeBase<NodeT>* GetRootNode() const { return root_node; }

		void GetDescendants(NodeT* R, std::vector<NodeT*>& Result) const 
		{
			Result.clear();
			DominatorTreeNodeBase<NodeT> const* RN = GetNode(R);
			if (!RN)
			{
				return;
			}

			std::vector<DominatorTreeNodeBase<NodeT> const*> WL;
			WL.push_back(RN);
			while (!WL.empty()) 
			{
				DominatorTreeNodeBase<NodeT> const* N = WL.back();
				WL.pop_back();
				Result.push_back(N->GetBlock());
				WL.insert(WL.back(),  N->begin(), N->end());
			}
		}

		bool ProperlyDominates(DominatorTreeNodeBase<NodeT> const* A, DominatorTreeNodeBase<NodeT> const* B) const
		{
			if (!A || !B)
				return false;
			if (A == B)
				return false;
			return Dominates(A, B);
		}
		bool ProperlyDominates(NodeT const* A, NodeT const* B) const
		{
			if (A == B)
				return false;
			return Dominates(GetNode(A), GetNode(B));
		}
		bool IsReachableFromEntry(DominatorTreeNodeBase<NodeT> const* A) const { return A != nullptr; }
		bool IsReachableFromEntry(NodeT const* A) const 
		{
			return IsReachableFromEntry(GetNode(A));
		}

		bool Dominates(DominatorTreeNodeBase<NodeT> const* A, DominatorTreeNodeBase<NodeT> const* B) const
		{
			// A node trivially dominates itself.
			if (B == A)
				return true;

			// An unreachable node is dominated by anything.
			if (!IsReachableFromEntry(B))
				return true;

			// And dominates nothing.
			if (!IsReachableFromEntry(A))
				return false;

			if (B->GetIDom() == A) return true;
			if (A->GetIDom() == B) return false;
			if (A->GetLevel() >= B->GetLevel()) return false;

			if (dfs_info_valid) return B->DominatedBy(A);

			return DominatedBySlowTreeWalk(A, B);
		}
		bool Dominates(NodeT const* A, NodeT const* B) const
		{
			if (A == B)
				return true;
			return Dominates(GetNode(A), GetNode(B));
		}
		
		NodeT* GetRoot() const 
		{
			return root;
		}

		/// Find nearest common dominator basic block for basic block A and B. A and B must have tree nodes.
		NodeT* FindNearestCommonDominator(NodeT* A, NodeT* B) const
		{
			OLA_ASSERT_MSG(A && B, "Pointers are not valid");
			OLA_ASSERT_MSG(NodeTrait::GetParent(A) == NodeTrait::GetParent(B), "Two blocks are not in same function");

			// If either A or B is a entry block then it is nearest common dominator
			NodeT& Entry = *DomTreeNodeTraits<NodeT>::GetEntryNode(NodeTrait::GetParent(A));
			if (A == &Entry || B == &Entry)
				return &Entry;

			DominatorTreeNodeBase<NodeT>* NodeA = GetNode(A);
			DominatorTreeNodeBase<NodeT>* NodeB = GetNode(B);
			OLA_ASSERT_MSG(NodeA, "A must be in the tree");
			OLA_ASSERT_MSG(NodeB, "B must be in the tree");

			// Use level information to go up the tree until the levels match. Then
			// continue going up til we arrive at the same node.
			while (NodeA != NodeB) 
			{
				if (NodeA->GetLevel() < NodeB->GetLevel()) std::swap(NodeA, NodeB);

				NodeA = NodeA->idom;
			}

			return NodeA->GetBlock();
		}
		NodeT const* FindNearestCommonDominator(NodeT const* A, NodeT const* B) const
		{
			return FindNearestCommonDominator(const_cast<NodeT*>(A), const_cast<NodeT*>(B));
		}

		void UpdateDFSNumbers() const
		{
			if (dfs_info_valid) 
			{
				return;
			}
			using DomTreeNodeBaseIteratorType = decltype(std::declval<DominatorTreeNodeBase<NodeT>*>()->begin());
			std::vector<std::pair<DominatorTreeNodeBase<NodeT> const*, DomTreeNodeBaseIteratorType>> WorkStack;

			DominatorTreeNodeBase<NodeT> const* this_root = GetRootNode();
			OLA_ASSERT_MSG((!parent || this_root), "Empty constructed DomTree");
			if (!this_root)
			{
				return;
			}
			WorkStack.push_back({ this_root, this_root->begin() });

			uint32 dfs_num = 0;
			this_root->dfs_num_in = dfs_num++;

			while (!WorkStack.empty()) 
			{
				const DominatorTreeNodeBase<NodeT>* Node = WorkStack.back().first;
				const auto ChildIt = WorkStack.back().second;

				// If we visited all of the children of this node, "recurse" back up the
				// stack setting the DFOutNum.
				if (ChildIt == Node->end()) 
				{
					Node->dfs_num_out = dfs_num++;
					WorkStack.pop_back();
				}
				else 
				{
					// Otherwise, recursively visit this child.
					const DominatorTreeNodeBase<NodeT>* Child = *ChildIt;
					++WorkStack.back().second;

					WorkStack.push_back({ Child, Child->begin() });
					Child->dfs_num_in = dfs_num++;
				}
			}
			dfs_info_valid = true;
		}

		void ChangeImmediateDominator(DominatorTreeNodeBase<NodeT>* N, DominatorTreeNodeBase<NodeT>* NewIDom) 
		{
			OLA_ASSERT_MSG(N && NewIDom, "Cannot change null node pointers!");
			dfs_info_valid = false;
			N->SetIDom(NewIDom);
		}

		void ChangeImmediateDominator(NodeT* BB, NodeT* NewBB) 
		{
			ChangeImmediateDominator(GetNode(BB), GetNode(NewBB));
		}

		/// eraseNode - Removes a node from the dominator tree. Block must not
		/// dominate any other blocks. Removes node from its immediate dominator's
		/// children list. Deletes dominator node associated with basic block BB.
		void EraseNode(NodeT* BB) 
		{
			uint32 Idx = GetNodeIndex(BB);
			OLA_ASSERT_MSG(Idx != INVALID_NODE_NUMBER && dom_tree_nodes[Idx], "Removing node that isn't in dominator tree.");
			DominatorTreeNodeBase<NodeT>* Node = dom_tree_nodes[Idx].get();
			OLA_ASSERT_MSG(Node->IsLeaf(), "Node is not a leaf node.");

			dfs_info_valid = false;
			DominatorTreeNodeBase<NodeT>* idom = Node->GetIDom();
			if (idom) 
			{
				const auto I = find(idom->children.begin(), idom->children.end(), Node);
				OLA_ASSERT_MSG(I != idom->children.end(), "Not in immediate dominator children set!");
				std::swap(*I, idom->children.back());
				idom->children.pop_back();
			}

			dom_tree_nodes[Idx] = nullptr;
			node_number_map.erase(BB);
		}

		DominatorTreeNodeBase<NodeT>* AddNewBlock(NodeT* BB, NodeT* DomBB) 
		{
			OLA_ASSERT_MSG(GetNode(BB) == nullptr, "Block already in dominator tree!");
			DominatorTreeNodeBase<NodeT>* idom_node = GetNode(DomBB);
			OLA_ASSERT_MSG(idom_node, "Not immediate dominator specified for block!");
			dfs_info_valid = false;
			return CreateNode(BB, idom_node);
		}

		DominatorTreeNodeBase<NodeT>* SetNewRoot(NodeT* BB) 
		{
			OLA_ASSERT_MSG(GetNode(BB) == nullptr, "Block already in dominator tree!");
			dfs_info_valid = false;
			DominatorTreeNodeBase<NodeT>* new_node = CreateNode(BB);
			if (!root)
			{
				SetRoot(BB);
			}
			else 
			{
				NodeT* old_root = root;
				DominatorTreeNodeBase<NodeT>* old_node = GetNode(old_root);
				new_node->AddChild(old_node);
				old_node->idom = new_node;
				old_node->UpdateLevel();
				SetRoot(BB);
			}
			return root_node = new_node;
		}

	private:
		NodeT* root;
		DominatorTreeNodeBase<NodeT>* root_node = nullptr;
		ParentPtr parent = nullptr;
		DomTreeNodeStorage dom_tree_nodes;
		NodeNumberStorage node_number_map;
		mutable bool dfs_info_valid = false;

	private:
		uint32 GetNodeIndex(NodeT const* BB) const
		{
			if (auto It = node_number_map.find(BB); It != node_number_map.end()) return It->second;
			else return INVALID_NODE_NUMBER;
		}
		uint32 GetNodeIndexForInsert(NodeT const* BB)
		{
			uint32 Idx = node_number_map.try_emplace(BB, dom_tree_nodes.size()).first->second;
			if (Idx >= dom_tree_nodes.size()) dom_tree_nodes.resize(Idx + 1);
			return Idx;
		}

		bool DominatedBySlowTreeWalk(DominatorTreeNodeBase<NodeT> const* A, DominatorTreeNodeBase<NodeT> const* B) const 
		{
			OLA_ASSERT(A != B);
			OLA_ASSERT(IsReachableFromEntry(B));
			OLA_ASSERT(IsReachableFromEntry(A));

			uint32 const a_level = A->GetLevel();
			DominatorTreeNodeBase<NodeT> const* idom = nullptr;
			// Don't walk nodes above A's subtree. When we reach A's level, we must
			// either find A or be in some other subtree not dominated by A.
			while ((idom = B->GetIDom()) != nullptr && idom->GetIDom() >= a_level) B = idom;  // Walk up the tree
			return B == A;
		}

	protected:
		void SetRoot(NodeT* BB) { root = BB; }
		DominatorTreeNodeBase<NodeT>* CreateNode(NodeT* BB, DominatorTreeNodeBase<NodeT>* idom = nullptr) 
		{
			auto node = std::make_unique<DominatorTreeNodeBase<NodeT>>(BB, idom);
			auto* node_ptr = node.get();
			uint32 node_idx = GetNodeIndexForInsert(BB);
			dom_tree_nodes[node_idx] = std::move(node);
			if (idom) idom->AddChild(node_ptr);
			return node_ptr;
		}
	};

	class BasicBlockEdge 
	{
		const BasicBlock* Start;
		const BasicBlock* End;

	public:
		BasicBlockEdge(BasicBlock const* Start_, BasicBlock const* End_) : Start(Start_), End(End_) {}

		BasicBlock const* GetStart() const { return Start; }

		BasicBlock const* GetEnd() const { return End; }

		bool isSingleEdge() const
		{
			unsigned NumEdgesToEnd = 0;
			for (BasicBlock* Succ : Start->Successors())
			{
				if (Succ == End) ++NumEdgesToEnd;
				if (NumEdgesToEnd >= 2) return false;
			}
			OLA_ASSERT(NumEdgesToEnd == 1);
			return true;
		}
	};
	class DominatorTree : public DominatorTreeBase<BasicBlock>
	{
		using Super = DominatorTreeBase<BasicBlock>;
	public:
		DominatorTree() = default;
		explicit DominatorTree(Function& F) {  }

		using Super::Dominates;

		bool Dominates(const BasicBlock* BB, const Use& U) const;
		bool Dominates(const Value* Def, const Use& U) const;
		bool Dominates(const Value* Def, const Instruction* User) const;
		bool Dominates(const Instruction* Def, const BasicBlock* BB) const;
		bool Dominates(const BasicBlockEdge& BBE, const Use& U) const;
		bool Dominates(const BasicBlockEdge& BBE, const BasicBlock* BB) const;
		bool Dominates(const BasicBlockEdge& BBE1, const BasicBlockEdge& BBE2) const;

		using Super::IsReachableFromEntry;
		bool IsReachableFromEntry(const Use& U) const;

		using Super::FindNearestCommonDominator;
		Instruction* FindNearestCommonDominator(Instruction* I1, Instruction* I2) const;
	};

	class DominatorTreeAnalysisPass : public FunctionPass
	{
	public:
		inline static char id = 0;
		using Result = DominatorTree;
	public:
		DominatorTreeAnalysisPass() : FunctionPass(id) {}

		virtual bool RunOn(Function& F, FunctionAnalysisManager& FAM) override;
		Result const& GetResult() const { return info; }
		static void const* ID() { return &id; }

	private:
		Result info;
	};
	OLA_REGISTER_ANALYSIS_PASS(DominatorTreeAnalysisPass, "Dominator Tree Analysis");
}