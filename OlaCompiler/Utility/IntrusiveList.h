#pragma once
//https://opensource.apple.com/source/clang/clang-703.0.29/src/include/llvm/ADT/ilist.h.auto.html slightly modified

#include <algorithm>
#include <cstddef>
#include <iterator>

namespace ola
{
	template<typename NodeTy, typename Traits> class IPList;
	template<typename NodeTy> class IListIterator;

	template<typename NodeTy>
	struct IListNextPrevTraits
	{
		static NodeTy* GetPrev(NodeTy* N) { return N->GetPrev(); }
		static NodeTy* GetNext(NodeTy* N) { return N->GetNext(); }
		static const NodeTy* GetPrev(const NodeTy* N) { return N->GetPrev(); }
		static const NodeTy* GetNext(const NodeTy* N) { return N->GetNext(); }

		static void SetPrev(NodeTy* N, NodeTy* Prev) { N->SetPrev(Prev); }
		static void SetNext(NodeTy* N, NodeTy* Next) { N->SetNext(Next); }
	};

	template<typename NodeTy>
	struct IListTraits;

	template<typename NodeTy>
	struct IListSentinelTraits
	{
		static NodeTy* CreateSentinel() { return new NodeTy(); }
		static void DestroySentinel(NodeTy* N) { delete N; N = nullptr; }
		static NodeTy* ProvideInitialHead() { return nullptr; }
		static NodeTy* EnsureHead(NodeTy*& Head)
		{
			if (!Head)
			{
				Head = IListTraits<NodeTy>::CreateSentinel();
				IListTraits<NodeTy>::NoteHead(Head, Head);
				IListTraits<NodeTy>::SetNext(Head, nullptr);
				return Head;
			}
			return IListTraits<NodeTy>::GetPrev(Head);
		}
		static void NoteHead(NodeTy* NewHead, NodeTy* Sentinel)
		{
			IListTraits<NodeTy>::SetPrev(NewHead, Sentinel);
		}
	};

	template <typename NodeTy> class IListHalfNode;
	template <typename NodeTy> class IListNode;

	template <typename NodeTy> struct IListEmbeddedSentinelTraits
	{
		NodeTy* CreateSentinel() const
		{
			return static_cast<NodeTy*>(&Sentinel);
		}
		static void DestroySentinel(NodeTy*) {}
		NodeTy* ProvideInitialHead() const { return CreateSentinel(); }
		NodeTy* EnsureHead(NodeTy*) const { return CreateSentinel(); }
		static void NoteHead(NodeTy*, NodeTy*) {}

	private:
		mutable IListNode<NodeTy> Sentinel;
	};

	template <typename NodeTy> struct IListHalfEmbeddedSentinelTraits
	{
		NodeTy* CreateSentinel() const
		{
			return static_cast<NodeTy*>(&Sentinel);
		}
		static void DestroySentinel(NodeTy*) {}
		NodeTy* ProvideInitialHead() const { return CreateSentinel(); }
		NodeTy* EnsureHead(NodeTy*) const { return CreateSentinel(); }
		static void NoteHead(NodeTy*, NodeTy*) {}

	private:
		mutable IListHalfNode<NodeTy> Sentinel;
	};

	template<typename NodeTy>
	struct IListNodeTraits
	{
		static NodeTy* CreateNode(const NodeTy& V) { return new NodeTy(V); }
		static void DeleteNode(NodeTy* V) { delete V; V = nullptr; }

		void AddNodeToList(NodeTy*) {}
		void RemoveNodeFromList(NodeTy*) {}
		void TransferNodesFromList(IListNodeTraits& /*SrcTraits*/,
			IListIterator<NodeTy> /*first*/,
			IListIterator<NodeTy> /*last*/) {}
	};

	template<typename NodeTy>
	struct IListDefaultTraits : public IListNextPrevTraits<NodeTy>,
		public IListSentinelTraits<NodeTy>,
		public IListNodeTraits<NodeTy>
	{};

	template<typename NodeTy>
	struct IListTraits : public IListDefaultTraits<NodeTy> {};

	template<typename Ty>
	struct IListTraits<const Ty> : public IListTraits<Ty> {};

	template<typename NodeTy>
	class IListIterator
	{
	public:
		using Traits = IListTraits<NodeTy>;
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = NodeTy;
		using difference_type = ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;

	private:
		pointer node_ptr;

		// ilist_iterator is not a random-access iterator, but it has an
		// implicit conversion to pointer-type, which is. Declare (but
		// don't define) these functions as private to help catch
		// accidental misuse.
		void operator[](difference_type) const;
		void operator+(difference_type) const;
		void operator-(difference_type) const;
		void operator+=(difference_type) const;
		void operator-=(difference_type) const;
		template<class T> void operator<(T) const;
		template<class T> void operator<=(T) const;
		template<class T> void operator>(T) const;
		template<class T> void operator>=(T) const;
		template<class T> void operator-(T) const;
	public:

		explicit IListIterator(pointer NP) : node_ptr(NP) {}
		explicit IListIterator(reference NR) : node_ptr(&NR) {}
		IListIterator() : node_ptr(nullptr) {}

		template<class Node>
		IListIterator(const IListIterator<Node>& RHS)
			: node_ptr(RHS.GetNodePtrUnchecked())
		{}

		template<class Node>
		const IListIterator& operator=(const IListIterator<Node>& RHS)
		{
			node_ptr = RHS.GetNodePtrUnchecked();
			return *this;
		}

		void Reset(pointer NP) { node_ptr = NP; }

		explicit operator pointer() const
		{
			return node_ptr;
		}

		reference operator*() const
		{
			return *node_ptr;
		}
		pointer operator->() const { return &operator*(); }

		Bool operator==(const IListIterator& RHS) const
		{
			return node_ptr == RHS.node_ptr;
		}
		Bool operator!=(const IListIterator& RHS) const
		{
			return node_ptr != RHS.node_ptr;
		}

		IListIterator& operator--()
		{
			node_ptr = Traits::GetPrev(node_ptr);
			assert(node_ptr && "--'d off the beginning of an ilist!");
			return *this;
		}
		IListIterator& operator++()
		{
			node_ptr = Traits::GetNext(node_ptr);
			return *this;
		}
		IListIterator operator--(int)
		{
			IListIterator tmp = *this;
			--*this;
			return tmp;
		}
		IListIterator operator++(int)
		{
			IListIterator tmp = *this;
			++*this;
			return tmp;
		}

		// Internal interface, do not use...
		pointer GetNodePtrUnchecked() const { return node_ptr; }
	};

	// These are to catch errors when people try to use them as random access
	// iterators.
	template<typename T>
	void operator-(int, IListIterator<T>) = delete;
	template<typename T>
	void operator-(IListIterator<T>, int) = delete;

	template<typename T>
	void operator+(int, IListIterator<T>) = delete;
	template<typename T>
	void operator+(IListIterator<T>, int) = delete;

	// operator!=/operator== - Allow mixed comparisons without dereferencing
	// the iterator, which could very likely be pointing to end().
	template<typename T>
	Bool operator!=(const T* LHS, const IListIterator<const T>& RHS)
	{
		return LHS != RHS.GetNodePtrUnchecked();
	}
	template<typename T>
	Bool operator==(const T* LHS, const IListIterator<const T>& RHS)
	{
		return LHS == RHS.GetNodePtrUnchecked();
	}
	template<typename T>
	Bool operator!=(T* LHS, const IListIterator<T>& RHS)
	{
		return LHS != RHS.GetNodePtrUnchecked();
	}
	template<typename T>
	Bool operator==(T* LHS, const IListIterator<T>& RHS)
	{
		return LHS == RHS.GetNodePtrUnchecked();
	}

	// Allow ilist_iterators to convert into pointers to a node automatically when
	// used by the dyn_cast, cast, isa mechanisms...
	template<typename From> struct SimplifyType;

	template<typename NodeTy>
	struct SimplifyType<IListIterator<NodeTy> >
	{
		using SimpleType = NodeTy*;
		static SimpleType GetSimplifiedValue(IListIterator<NodeTy>& Node)
		{
			return &*Node;
		}
	};
	template<typename NodeTy>
	struct SimplifyType<const IListIterator<NodeTy>>
	{
		using SimpleType = NodeTy*;
		static SimpleType GetSimplifiedValue(const IListIterator<NodeTy>& Node)
		{
			return &*Node;
		}
	};

	/// iplist - The subset of list functionality that can safely be used on nodes
	/// of polymorphic types, i.e. a heterogeneous list with a common base class that
	/// holds the next/prev pointers.  The only state of the list itself is a single
	/// pointer to the head of the list.
	///
	/// This list can be in one of three interesting states:
	/// 1. The list may be completely unconstructed.  In this case, the head
	///    pointer is null.  When in this form, any query for an iterator (e.g.
	///    begin() or end()) causes the list to transparently change to state #2.
	/// 2. The list may be empty, but contain a sentinel for the end iterator. This
	///    sentinel is created by the Traits::CreateSentinel method and is a link
	///    in the list.  When the list is empty, the pointer in the iplist points
	///    to the sentinel.  Once the sentinel is constructed, it
	///    is not destroyed until the list is.
	/// 3. The list may contain actual objects in it, which are stored as a doubly
	///    linked list of nodes.  One invariant of the list is that the predecessor
	///    of the first node in the list always points to the last node in the list,
	///    and the successor pointer for the sentinel (which always stays at the
	///    end of the list) is always null.
	///
	template<typename NodeTy, typename Traits = IListTraits<NodeTy> >
	class IPList : public Traits
	{
		mutable NodeTy* head;

		// Use the prev node pointer of 'head' as the tail pointer.  This is really a
		// circularly linked list where we snip the 'next' link from the sentinel node
		// back to the first node in the list (to preserve assertions about going off
		// the end of the list).
		NodeTy* GetTail() { return this->EnsureHead(head); }
		const NodeTy* GetTail() const { return this->EnsureHead(head); }
		void SetTail(NodeTy* N) const { this->NoteHead(head, N); }

		/// CreateLazySentinel - This method verifies whether the sentinel for the
		/// list has been created and lazily makes it if not.
		void CreateLazySentinel() const
		{
			this->EnsureHead(head);
		}

		static Bool OpLess(NodeTy& L, NodeTy& R) { return L < R; }
		static Bool OpEqual(NodeTy& L, NodeTy& R) { return L == R; }

		// No fundamental reason why iplist can't be copyable, but the default
		// copy/copy-assign won't do.
		IPList(const IPList&) = delete;
		void operator=(const IPList&) = delete;

	public:
		typedef NodeTy* pointer;
		typedef const NodeTy* const_pointer;
		typedef NodeTy& reference;
		typedef const NodeTy& const_reference;
		typedef NodeTy value_type;
		typedef IListIterator<NodeTy> iterator;
		typedef IListIterator<const NodeTy> const_iterator;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef std::reverse_iterator<const_iterator>  const_reverse_iterator;
		typedef std::reverse_iterator<iterator>  reverse_iterator;

		IPList() : head(this->ProvideInitialHead()) {}
		~IPList()
		{
			if (!head) return;
			Clear();
			Traits::DestroySentinel(GetTail());
		}

		// Iterator creation methods.
		iterator begin()
		{
			CreateLazySentinel();
			return iterator(head);
		}
		const_iterator begin() const
		{
			CreateLazySentinel();
			return const_iterator(head);
		}
		iterator end()
		{
			CreateLazySentinel();
			return iterator(GetTail());
		}
		const_iterator end() const
		{
			CreateLazySentinel();
			return const_iterator(GetTail());
		}

		// reverse iterator creation methods.
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }


		// Miscellaneous inspection routines.
		size_type MaxSize() const { return size_type(-1); }
		Bool Empty() const
		{
			return !head || head == GetTail();
		}

		// Front and back accessor functions...
		reference Front()
		{
			assert(!Empty() && "Called front() on empty list!");
			return *head;
		}
		const_reference Front() const
		{
			assert(!Empty() && "Called front() on empty list!");
			return *head;
		}
		reference Back()
		{
			assert(!Empty() && "Called back() on empty list!");
			return *this->GetPrev(GetTail());
		}
		const_reference Back() const
		{
			assert(!Empty() && "Called back() on empty list!");
			return *this->GetPrev(GetTail());
		}

		iterator Insert(iterator where, NodeTy* New)
		{
			NodeTy* CurNode = where.GetNodePtrUnchecked();
			NodeTy* PrevNode = this->GetPrev(CurNode);
			this->SetNext(New, CurNode);
			this->SetPrev(New, PrevNode);

			if (CurNode != head)  // Is PrevNode off the beginning of the list?
				this->SetNext(PrevNode, New);
			else
				head = New;
			this->SetPrev(CurNode, New);

			this->AddNodeToList(New);  // Notify traits that we added a node...
			return iterator(New);
		}

		iterator InsertAfter(iterator where, NodeTy* New)
		{
			if (Empty())
				return Insert(begin(), New);
			else
				return Insert(++where, New);
		}

		NodeTy* Remove(iterator& IT)
		{
			assert(IT != end() && "Cannot remove end of list!");
			NodeTy* Node = &*IT;
			NodeTy* NextNode = this->GetNext(Node);
			NodeTy* PrevNode = this->GetPrev(Node);

			if (Node != head)  // Is PrevNode off the beginning of the list?
				this->SetNext(PrevNode, NextNode);
			else
				head = NextNode;
			this->SetPrev(NextNode, PrevNode);
			IT.Reset(NextNode);
			this->RemoveNodeFromList(Node);  // Notify traits that we removed a node...

			// Set the next/prev pointers of the current node to null.  This isn't
			// strictly required, but this catches errors where a node is removed from
			// an ilist (and potentially deleted) with iterators still pointing at it.
			// When those iterators are incremented or decremented, they will assert on
			// the null next/prev pointer instead of "usually working".
			this->SetNext(Node, nullptr);
			this->SetPrev(Node, nullptr);
			return Node;
		}

		NodeTy* Remove(const iterator& IT)
		{
			iterator MutIt = IT;
			return Remove(MutIt);
		}

		NodeTy* Remove(NodeTy* IT) { return Remove(iterator(IT)); }
		NodeTy* Remove(NodeTy& IT) { return Remove(iterator(IT)); }

		// erase - remove a node from the controlled sequence... and delete it.
		iterator Erase(iterator where)
		{
			this->DeleteNode(Remove(where));
			return where;
		}

		iterator Erase(NodeTy* IT) { return Erase(iterator(IT)); }
		iterator Erase(NodeTy& IT) { return Erase(iterator(IT)); }

		/// Remove all nodes from the list like Clear(), but do not call
		/// RemoveNodeFromList() or DeleteNode().
		///
		/// This should only be used immediately before freeing nodes in bulk to
		/// avoid traversing the list and bringing all the nodes into cache.
		void ClearAndLeakNodesUnsafely()
		{
			if (head) {
				head = GetTail();
				this->SetPrev(head, head);
			}
		}

	private:
		// transfer - The heart of the splice function.  Move linked list nodes from
		// [first, last) into position.
		//
		void Transfer(iterator position, IPList& L2, iterator first, iterator last)
		{
			assert(first != last && "Should be checked by callers");
			// Position cannot be contained in the range to be transferred.
			// Check for the most common mistake.
			assert(position != first &&
				"Insertion point can't be one of the transferred nodes");

			if (position != last)
			{
				// Note: we have to be careful about the case when we move the first node
				// in the list.  This node is the list sentinel node and we can't move it.
				NodeTy* ThisSentinel = GetTail();
				SetTail(nullptr);
				NodeTy* L2Sentinel = L2.GetTail();
				L2.SetTail(nullptr);

				// Remove [first, last) from its old position.
				NodeTy* First = &*first, * Prev = this->GetPrev(First);
				NodeTy* Next = last.GetNodePtrUnchecked(), * Last = this->GetPrev(Next);
				if (Prev)
					this->SetNext(Prev, Next);
				else
					L2.head = Next;
				this->SetPrev(Next, Prev);

				// Splice [first, last) into its new position.
				NodeTy* PosNext = position.GetNodePtrUnchecked();
				NodeTy* PosPrev = this->GetPrev(PosNext);

				// Fix head of list...
				if (PosPrev)
					this->SetNext(PosPrev, First);
				else
					head = First;
				this->SetPrev(First, PosPrev);

				// Fix end of list...
				this->SetNext(Last, PosNext);
				this->SetPrev(PosNext, Last);

				this->TransferNodesFromList(L2, iterator(First), iterator(PosNext));

				// Now that everything is set, restore the pointers to the list sentinels.
				L2.SetTail(L2Sentinel);
				SetTail(ThisSentinel);
			}
		}

	public:

		//===----------------------------------------------------------------------===
		// Functionality derived from other functions defined above...
		//

		size_type Size() const
		{
			if (!head) return 0; // Don't require construction of sentinel if empty.
			return std::distance(begin(), end());
		}

		iterator Erase(iterator first, iterator last)
		{
			while (first != last)
				first = Erase(first);
			return last;
		}

		void Clear() 
		{ 
			if (head) Erase(begin(), end()); 
		}

		// Front and back inserters...
		void PushFront(NodeTy* val) { Insert(begin(), val); }
		void PushBack(NodeTy* val) { Insert(end(), val); }
		void PopFront()
		{
			assert(!Empty() && "pop_front() on empty list!");
			Erase(begin());
		}
		void PopBack()
		{
			assert(!Empty() && "pop_back() on empty list!");
			iterator t = end(); Erase(--t);
		}

		// Special forms of insert...
		template<class InIt> void Insert(iterator where, InIt first, InIt last)
		{
			for (; first != last; ++first) Insert(where, *first);
		}

		// Splice members - defined in terms of transfer...
		void Splice(iterator where, IPList& L2)
		{
			if (!L2.Empty())
				Transfer(where, L2, L2.begin(), L2.end());
		}
		void Splice(iterator where, IPList& L2, iterator first)
		{
			iterator last = first; ++last;
			if (where == first || where == last) return; // No change
			Transfer(where, L2, first, last);
		}
		void Splice(iterator where, IPList& L2, iterator first, iterator last)
		{
			if (first != last) Transfer(where, L2, first, last);
		}
		void Splice(iterator where, IPList& L2, NodeTy& N)
		{
			Splice(where, L2, iterator(N));
		}
		void Splice(iterator where, IPList& L2, NodeTy* N)
		{
			Splice(where, L2, iterator(N));
		}

		template <class Compare>
		void Merge(IPList& Right, Compare comp)
		{
			if (this == &Right)
				return;
			iterator First1 = begin(), Last1 = end();
			iterator First2 = Right.begin(), Last2 = Right.end();
			while (First1 != Last1 && First2 != Last2) {
				if (comp(*First2, *First1)) {
					iterator Next = First2;
					Transfer(First1, Right, First2, ++Next);
					First2 = Next;
				}
				else {
					++First1;
				}
			}
			if (First2 != Last2)
				Transfer(Last1, Right, First2, Last2);
		}
		void Merge(IPList& Right) { return Merge(Right, OpLess); }

		template <class Compare>
		void Sort(Compare comp)
		{
			// The list is empty, vacuously sorted.
			if (Empty())
				return;
			// The list has a single element, vacuously sorted.
			if (std::next(begin()) == end())
				return;
			// Find the split point for the list.
			iterator Center = begin(), End = begin();
			while (End != end() && std::next(End) != end()) {
				Center = std::next(Center);
				End = std::next(std::next(End));
			}
			// Split the list into two.
			IPList RightHalf;
			RightHalf.Splice(RightHalf.begin(), *this, Center, end());

			// Sort the two sublists.
			Sort(comp);
			RightHalf.Sort(comp);

			// Merge the two sublists back together.
			Merge(RightHalf, comp);
		}
		void Sort() { Sort(OpLess); }
	};


	template<typename NodeTy>
	struct IList : public IPList<NodeTy>
	{
		typedef typename IPList<NodeTy>::size_type size_type;
		typedef typename IPList<NodeTy>::iterator iterator;

		IList() {}
		IList(const IList& right)
		{
			Insert(this->begin(), right.begin(), right.end());
		}
		explicit IList(size_type count)
		{
			Insert(this->begin(), count, NodeTy());
		}
		IList(size_type count, const NodeTy& val)
		{
			Insert(this->begin(), count, val);
		}
		template<class InIt> 
		IList(InIt first, InIt last)
		{
			Insert(this->begin(), first, last);
		}

		using IPList<NodeTy>::Insert;
		using IPList<NodeTy>::PushFront;
		using IPList<NodeTy>::PushBack;

		iterator Insert(iterator where, const NodeTy& val)
		{
			return Insert(where, this->CreateNode(val));
		}
		iterator Insert(iterator where, const NodeTy* val)
		{
			return Insert(where, this->CreateNode(val));
		}

		void PushFront(const NodeTy& val) { Insert(this->begin(), val); }
		void PushBack(const NodeTy& val) { Insert(this->end(), val); }

		void PushFront(const NodeTy* val) { Insert(this->begin(), val); }
		void PushBack(const NodeTy* val) { Insert(this->end(), val); }

		void Insert(iterator where, size_type count, const NodeTy& val)
		{
			for (; count != 0; --count) Insert(where, val);
		}

		void Assign(size_type count, const NodeTy& val)
		{
			iterator I = this->begin();
			for (; I != this->end() && count != 0; ++I, --count)
				*I = val;
			if (count != 0)
				Insert(this->end(), val, val);
			else
				Erase(I, this->end());
		}

		template<class InIt> void Assign(InIt first1, InIt last1)
		{
			iterator first2 = this->begin(), last2 = this->end();
			for (; first1 != last1 && first2 != last2; ++first1, ++first2)
				*first1 = *first2;
			if (first2 == last2)
				Erase(first1, last1);
			else
				Insert(last1, first2, last2);
		}

		void Resize(size_type newsize, NodeTy val)
		{
			iterator i = this->begin();
			size_type len = 0;
			for (; i != this->end() && len < newsize; ++i, ++len) /* empty*/;

			if (len == newsize)
				Erase(i, this->end());
			else                                          // i == end()
				Insert(this->end(), newsize - len, val);
		}
		void Resize(size_type newsize) { Resize(newsize, NodeTy()); }
	};


	template<typename NodeTy>
	struct IListTraits;
	template <typename NodeTy> struct IListEmbeddedSentinelTraits;
	template <typename NodeTy> struct IListHalfEmbeddedSentinelTraits;


	template<typename NodeTy>
	class IListHalfNode
	{
		friend struct IListTraits<NodeTy>;
		friend struct IListHalfEmbeddedSentinelTraits<NodeTy>;
		NodeTy* prev;

	protected:
		NodeTy* GetPrev() { return prev; }
		const NodeTy* GetPrev() const { return prev; }
		void SetPrev(NodeTy* P) { prev = P; }
		IListHalfNode() : prev(nullptr) {}
	};

	template<typename NodeTy>
	struct IListNextPrevTraits;

	template <typename NodeTy> class IListIterator;

	template<typename NodeTy>
	class IListNode : private IListHalfNode<NodeTy>
	{
		friend struct IListNextPrevTraits<NodeTy>;
		friend struct IListTraits<NodeTy>;
		friend struct IListHalfEmbeddedSentinelTraits<NodeTy>;
		friend struct IListEmbeddedSentinelTraits<NodeTy>;
		NodeTy* next;
		NodeTy* GetNext() { return next; }
		const NodeTy* GetNext() const { return next; }
		void SetNext(NodeTy* N) { next = N; }

	protected:
		IListNode() : next(nullptr) {}

	public:
		IListIterator<NodeTy> GetIterator()
		{
			return IListIterator<NodeTy>(static_cast<NodeTy*>(this));
		}
		IListIterator<const NodeTy> GetIterator() const
		{
			return IListIterator<const NodeTy>(static_cast<const NodeTy*>(this));
		}

		NodeTy* GetPrevNode()
		{
			NodeTy* Prev = this->GetPrev();
			if (!Prev->GetNext()) return nullptr;
			return Prev;
		}

		const NodeTy* GetPrevNode() const
		{
			NodeTy const* Prev = this->GetPrev();
			if (!Prev->GetNext()) return nullptr;
			return Prev;
		}

		NodeTy* GetNextNode()
		{
			NodeTy* Next = GetNext();
			if (!Next->GetNext()) return nullptr;
			return Next;
		}

		const NodeTy* GetNextNode() const
		{
			const NodeTy* Next = GetNext();
			if (!Next->GetNext()) return nullptr;
			return Next;
		}
	};
}
