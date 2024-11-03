#pragma once
#include <type_traits>

namespace ola 
{
	template <typename Iterator>
	class IteratorRange 
	{
	public:
		IteratorRange(Iterator begin_iterator, Iterator end_iterator)
			: begin_iterator(std::move(begin_iterator)),
			  end_iterator(std::move(end_iterator)) {}

		Iterator begin() const { return begin_iterator; }
		Iterator end() const { return end_iterator; }
		Bool empty() const { return begin_iterator == end_iterator; }

	private:
		Iterator begin_iterator, end_iterator;
	};

	template <typename T>
	IteratorRange<T> MakeRange(T x, T y)
	{
		return IteratorRange<T>(std::move(x), std::move(y));
	}

	template <typename T> 
	IteratorRange<T> MakeRange(std::pair<T, T> p) 
	{
		return IteratorRange<T>(std::move(p.first), std::move(p.second));
	}

}
