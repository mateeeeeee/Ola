#pragma once

namespace ola
{
	template <typename T>
	class IntrusiveList;

	template <typename T>
	class IntrusiveListIterator;

	template <typename T>
	class IntrusiveListNode
	{
		friend class IntrusiveList<T>;
		friend class IntrusiveListIterator<T>;

	protected:
		IntrusiveListNode() = default;

	protected:
		T* prev;
		T* next;
	};

	template<typename T>
	using IListNode = IntrusiveListNode<T>;


	template <typename T>
	class IntrusiveListIterator 
	{
	public:
		IntrusiveListIterator(T* node) : current(node) {}

		T* operator->() const { return current; }
		T& operator*() const { return *current; }

		IntrusiveListIterator<T>& operator++() 
		{
			current = current->next;
			return *this;
		}

		IntrusiveListIterator<T> operator++(int) 
		{
			IntrusiveListIterator<T> temp = *this;
			++(*this);
			return temp;
		}

		bool operator!=(const IntrusiveListIterator<T>& other) const 
		{
			return current != other.current;
		}

	private:
		T* current;
	};

	template <typename T> //requires std::is_base_of_v<IListNode<T>, T>
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

		IntrusiveListIterator<T> begin() const
		{
			return IntrusiveListIterator<T>(head);
		}
		IntrusiveListIterator<T> end() const
		{
			return IntrusiveListIterator<T>(nullptr);
		}

	private:
		T* head;
		T* tail;
	};

	template<typename T>
	using IList = IntrusiveList<T>;
}