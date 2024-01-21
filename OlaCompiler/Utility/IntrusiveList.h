#pragma once

namespace ola
{
	template <bool _Test, class _Ty1, class _Ty2>
	struct Conditional
	{
		using type = _Ty1;
	};
	template <class _Ty1, class _Ty2>
	struct Conditional<false, _Ty1, _Ty2>
	{
		using type = _Ty2;
	};
	template <bool _Test, class _Ty1, class _Ty2>
	using ConditionalType = typename Conditional<_Test, _Ty1, _Ty2>::type;


	template <typename>
	class IntrusiveList;
	template <typename T, bool IsConst, bool IsReverse>
	class IntrusiveListIterator;

	template <typename T>
	class IntrusiveListNode
	{
		friend IntrusiveList<T>;
		friend IntrusiveListIterator<T, false, false>;
		friend IntrusiveListIterator<T, true, false>;
		friend IntrusiveListIterator<T, false, true>;
		friend IntrusiveListIterator<T, true, true>;

	protected:
		IntrusiveListNode() : prev(nullptr), next(nullptr) {}

		T* GetNext() const { return next; }
		T* GetPrev() const { return prev; }

	private:
		T* prev;
		T* next;
	};
	template<typename T>
	using IListNode = IntrusiveListNode<T>;

	template <typename T, bool IsConst = false, bool IsReverse = false>
	class IntrusiveListIterator
	{
	public:
		using NodeType = ConditionalType<IsConst, const T, T>;

		IntrusiveListIterator(NodeType* node) : current(node) {}

		NodeType* operator->() const { return current;  }
		NodeType& operator*() const  { return *current; }

		IntrusiveListIterator<T, IsConst, IsReverse>& operator++()
		{
			current = IsReverse ? current->GetPrev() : current->GetNext();
			return *this;
		}
		IntrusiveListIterator<T, IsConst, IsReverse> operator++(int) 
		{
			IntrusiveListIterator<T, IsConst, IsReverse> temp = *this;
			++(*this);
			return temp;
		}

		bool operator!=(IntrusiveListIterator<T, IsConst, IsReverse> const& other) const 
		{
			return current != other.current;
		}

	private:
		NodeType* current;
	};
	template<typename T, bool IsConst = false, bool IsReverse = false>
	using IListIterator = IntrusiveListIterator<T, IsConst, IsReverse>;

	template <typename T> 
	class IntrusiveList 
	{
	public:

		IntrusiveList() { head = tail = nullptr; }
		void InsertBefore(T* new_node, T* insert_before) 
		{
			new_node->prev = insert_before->prev;
			new_node->next = insert_before;
			if (insert_before->prev) 
			{
				insert_before->prev->next = new_node;
			}
			insert_before->prev = new_node;

			if (head == insert_before) 
			{
				head = new_node;
			}
		}
		void InsertAfter(T* new_node, T* insert_after) 
		{
			new_node->prev = insert_after;
			new_node->next = insert_after->next;
			if (insert_after->next) 
			{
				insert_after->next->prev = new_node;
			}
			insert_after->next = new_node;

			if (tail == insert_after) 
			{
				tail = new_node;
			}
		}
		void InsertAtEnd(T* new_node) 
		{
			new_node->prev = tail;
			new_node->next = nullptr;

			if (tail == nullptr) 
			{
				head = tail = new_node;
			}
			else 
			{
				tail->next = new_node;
				tail = new_node;
			}
		}
		void InsertAtBegin(T* new_node)
		{
			new_node->prev = nullptr;
			new_node->next = head;

			if (head == nullptr) 
			{
				head = tail = new_node;
			}
			else {
				head->prev = new_node;
				head = new_node;
			}
		}
		void Remove(T* node) 
		{
			if (node->prev != nullptr) 
			{
				node->prev->next = node->next;
			}
			else 
			{
				head = node->next;
			}

			if (node->next != nullptr) 
			{
				node->next->prev = node->prev;
			}
			else 
			{
				tail = node->prev;
			}
		}

		using iterator = IListIterator<T>;
		using const_iterator = IListIterator<T, true>;
		using reverse_iterator = IListIterator<T, false, true>;
		using const_reverse_iterator = IListIterator<T, true, true>;

		iterator begin() { return iterator(head); }
		const_iterator begin() const { return const_iterator(head); }
		iterator end() { return iterator(nullptr); }
		const_iterator end() const { return const_iterator(nullptr); }
		reverse_iterator rbegin() { return reverse_iterator(tail); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(tail); }
		reverse_iterator rend() { return reverse_iterator(nullptr); }
		const_reverse_iterator rend() const { return const_reverse_iterator(nullptr); }

		T& front() { return *begin(); }
		T const& front() const { return *begin(); }
		T& back() { return *rbegin(); }
		T const& back() const { return *rbegin(); }

		bool empty() const { return head == nullptr; }
		uint64 size() const 
		{
			uint64 count = 0;
			for (const auto& node : *this) ++count;
			return count;
		}

	private:
		T* head;
		T* tail;
	};

	template<typename T>
	using IList = IntrusiveList<T>;
}