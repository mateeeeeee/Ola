#pragma once
#include <iterator>
#include <utility>
#include "IteratorRange.h"

namespace ola
{
	template <typename DerivedT, typename IteratorCategoryT, typename T, typename DifferenceTypeT = Int64, typename PointerT = T*, typename ReferenceT = T&>
	class IteratorFacade 
	{
	public:
		using iterator_category = IteratorCategoryT;
		using value_type = T;
		using difference_type = DifferenceTypeT;
		using pointer = PointerT;
		using reference = ReferenceT;

	protected:
		static constexpr Bool IsRandomAccess = std::is_base_of_v<std::random_access_iterator_tag, IteratorCategoryT>;
		static constexpr Bool IsBidirectional = std::is_base_of_v<std::bidirectional_iterator_tag, IteratorCategoryT>;

		class ReferenceProxy 
		{
			friend IteratorFacade;
			DerivedT I;
			ReferenceProxy(DerivedT I) : I(std::move(I)) {}
		public:
			operator ReferenceT() const { return *I; }
		};
		class PointerProxy 
		{
			friend IteratorFacade;
			ReferenceT R;
			template <typename RefT>
			PointerProxy(RefT&& R) : R(std::forward<RefT>(R)) {}

		public:
			PointerT operator->() const { return &R; }
		};

	public:
		DerivedT operator+(DifferenceTypeT n) const 
		{
			static_assert(std::is_base_of_v<IteratorFacade, DerivedT>, "Must pass the derived type to this template!");
			static_assert(IsRandomAccess, "The '+' operator is only defined for random access iterators.");
			DerivedT tmp = *static_cast<const DerivedT*>(this);
			tmp += n;
			return tmp;
		}
		friend DerivedT operator+(DifferenceTypeT n, const DerivedT& i) 
		{
			static_assert(IsRandomAccess, "The '+' operator is only defined for random access iterators.");
			return i + n;
		}
		DerivedT operator-(DifferenceTypeT n) const 
		{
			static_assert(IsRandomAccess, "The '-' operator is only defined for random access iterators.");
			DerivedT tmp = *static_cast<const DerivedT*>(this);
			tmp -= n;
			return tmp;
		}

		DerivedT& operator++() 
		{
			static_assert(std::is_base_of_v<IteratorFacade, DerivedT>, "Must pass the derived type to this template!");
			return static_cast<DerivedT*>(this)->operator+=(1);
		}
		DerivedT operator++(Int)
		{
			DerivedT tmp = *static_cast<DerivedT*>(this);
			++*static_cast<DerivedT*>(this);
			return tmp;
		}
		DerivedT& operator--() 
		{
			static_assert(IsBidirectional, "The decrement operator is only defined for bidirectional iterators.");
			return static_cast<DerivedT*>(this)->operator-=(1);
		}
		DerivedT operator--(Int)
		{
			static_assert(IsBidirectional, "The decrement operator is only defined for bidirectional iterators.");
			DerivedT tmp = *static_cast<DerivedT*>(this);
			--*static_cast<DerivedT*>(this);
			return tmp;
		}

#ifndef __cpp_impl_three_way_comparison
		Bool operator!=(const DerivedT& RHS) const 
		{
			return !(static_cast<const DerivedT&>(*this) == RHS);
		}
#endif

		Bool operator>(const DerivedT& RHS) const 
		{
			static_assert(IsRandomAccess, "Relational operators are only defined for random access iterators.");
			return !(static_cast<const DerivedT&>(*this) < RHS) && !(static_cast<const DerivedT&>(*this) == RHS);
		}
		Bool operator<=(const DerivedT& RHS) const 
		{
			static_assert(IsRandomAccess, "Relational operators are only defined for random access iterators.");
			return !(static_cast<const DerivedT&>(*this) > RHS);
		}
		Bool operator>=(const DerivedT& RHS) const 
		{
			static_assert(IsRandomAccess, "Relational operators are only defined for random access iterators.");
			return !(static_cast<const DerivedT&>(*this) < RHS);
		}

		PointerProxy operator->() const 
		{
			return static_cast<const DerivedT*>(this)->operator*();
		}
		ReferenceProxy operator[](DifferenceTypeT n) const 
		{
			static_assert(IsRandomAccess, "Subscripting is only defined for random access iterators.");
			return static_cast<const DerivedT*>(this)->operator+(n);
		}
	};
}