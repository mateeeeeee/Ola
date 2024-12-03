#pragma once
#include <concepts>
#include <utility>
#include <stack>


namespace ola
{
	template<typename NodeT>
	class DepthFirstTreeIterator
	{
		static_assert(!std::is_pointer_v<NodeT> && !std::is_reference_v<NodeT>,"NodeTy should be a class");
		using NodeIterator = std::conditional_t<std::is_const_v<NodeT>, typename NodeT::const_iterator, typename NodeT::iterator>;
		using NodeIteratorPairStack = std::stack<std::pair<NodeT*, NodeIterator>>;
	public:
		DepthFirstTreeIterator() : DepthFirstTreeIterator(nullptr) {}
		explicit DepthFirstTreeIterator(NodeT* node) : current(node)
		{
			if (current && current->begin() != current->end())
				parent_iterators.emplace(std::make_pair(current, current->begin()));
		}

		Bool operator==(DepthFirstTreeIterator const& it) const 
		{
			return current == it.current;
		}
		Bool operator!=(DepthFirstTreeIterator const& it) const 
		{ 
			return current != it.current;
		}

		NodeT& operator*()  const { return *current; }
		NodeT* operator->() const { return current;  }

		DepthFirstTreeIterator& operator++()
		{
			MoveToNextNode();
			return *this;
		}
		DepthFirstTreeIterator operator++(Int)
		{
			DepthFirstTreeIterator tmp = *this;
			++*this;
			return tmp;
		}

	private:
		NodeT* current;
		NodeIteratorPairStack parent_iterators;

	private:
		void MoveToNextNode()
		{
			if (!current) return;

			if (parent_iterators.empty()) 
			{
				current = nullptr;
				return;
			}

			auto& next_it = parent_iterators.top();
			current = *next_it.second;
			++next_it.second;
			if (next_it.first->end() == next_it.second) parent_iterators.pop();
			if (current->begin() != current->end()) parent_iterators.emplace(std::make_pair(current, current->begin()));
		}
	};

	template<typename NodeT>
	using DFTreeIterator = DepthFirstTreeIterator<NodeT>;
}