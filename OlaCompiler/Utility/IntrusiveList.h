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

	public:
		IntrusiveListNode() : prev(nullptr), next(nullptr) {}

		T* GetNext() { return next; }
		T* GetPrev() { return prev; }

		T const* GetNext() const { return next; }
		T const* GetPrev() const { return prev; }

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
		using value_type = ConditionalType<IsConst, const T, T>;
		using pointer = value_type*;
		using const_pointer = value_type const*;
		using reference = value_type&;
		using const_reference = value_type const&;

	public:
		IntrusiveListIterator(pointer node) : current(node) {}
		IntrusiveListIterator(reference node) : current(&node) {}
		IntrusiveListIterator(IntrusiveListIterator const& o) : current(o.current) {}
		IntrusiveListIterator& operator=(IntrusiveListIterator const& o) 
		{
			current = o.current;
			return *this;
		}
		~IntrusiveListIterator() = default;

		pointer operator->() { return current;  }
		const_pointer operator->() const { return current;  }
		reference operator*() { return *current; }
		const_reference operator*() const { return *current; }

		operator pointer()
		{
			return current;
		}
		operator const_pointer() const
		{
			return current;
		}

		auto& operator++()
		{
			current = IsReverse ? current->GetPrev() : current->GetNext();
			return *this;
		}
		auto operator++(int)
		{
			IntrusiveListIterator<T, IsConst, IsReverse> temp = *this;
			++(*this);
			return temp;
		}

		bool operator==(IntrusiveListIterator<T, IsConst, IsReverse> const& other) const
		{
			return current == other.current;
		}
		bool operator!=(IntrusiveListIterator<T, IsConst, IsReverse> const& other) const 
		{
			return current != other.current;
		}

	private:
		pointer current;
	};
	template<typename T, bool IsConst = false, bool IsReverse = false>
	using IListIterator = IntrusiveListIterator<T, IsConst, IsReverse>;

	template <typename T>
	class IntrusiveList
	{
	public:
		using iterator = IntrusiveListIterator<T>;
		using const_iterator = IntrusiveListIterator<T, true>;
		using reverse_iterator = IntrusiveListIterator<T, false, true>;
		using const_reverse_iterator = IntrusiveListIterator<T, true, true>;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using size_type = uint64;
		using difference_type = ptrdiff_t;

	public:
		IntrusiveList() : head(nullptr), tail(nullptr) {}
		~IntrusiveList() { Clear();  head = tail = nullptr; }

		void PushFront(pointer val) { Insert(val, head); }
		void PushBack(pointer val)
		{
			if (Empty())
			{
				Insert(val, nullptr);
			}
			else
			{
				Insert(val, tail);
			}
		}
		void PopFront()
		{
			Remove(begin());
		}
		void PopBack()
		{
			iterator t = end();
			Remove(--t);
		}

		reference Front() { return *begin(); }
		const_reference Front() const { return *begin(); }
		reference Back() { return *rbegin(); }
		const_reference Back() const { return *rbegin(); }

		pointer Insert(pointer new_node, pointer insert_before)
		{
			pointer insert_point = insert_before ? insert_before->prev : tail;

			new_node->prev = insert_point;
			new_node->next = (insert_point) ? insert_point->next : head;

			if (insert_point) insert_point->next = new_node;
			else head = new_node;

			if (new_node->next) new_node->next->prev = new_node;
			else tail = new_node;

			return new_node;
		}

		pointer InsertAfter(pointer new_node, pointer insert_after)
		{
			return Insert(new_node, insert_after->next);
		}

		void Remove(pointer node)
		{
			if (node->prev)
			{
				node->prev->next = node->next;
			}
			else
			{
				head = node->next;
			}
			if (node->next)
			{
				node->next->prev = node->prev;
			}
			else
			{
				tail = node->prev;
			}
			node->prev = node->next = nullptr;
		}

		void Erase(pointer node)
		{
			Remove(node);
			delete node;
		}

		void Clear()
		{
			while (!Empty())
			{
				pointer front_node = head;
				PopFront();
				delete front_node;
			}
		}


		size_type Size() const
		{
			size_type count = 0;
			for (const auto& node : *this) ++count;
			return count;
		}

		bool Empty() const
		{
			return head == nullptr;
		}

		iterator begin() { return iterator(head); }
		const_iterator begin() const { return const_iterator(head); }
		iterator end() { return iterator(nullptr); }
		const_iterator end() const { return const_iterator(nullptr); }
		reverse_iterator rbegin() { return reverse_iterator(tail); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(tail); }
		reverse_iterator rend() { return reverse_iterator(nullptr); }
		const_reverse_iterator rend() const { return const_reverse_iterator(nullptr); }

	private:
		pointer head;
		pointer tail;
	};

	template<typename T>
	using IList = IntrusiveList<T>;
}