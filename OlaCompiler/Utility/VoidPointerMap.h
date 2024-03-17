#pragma once
#include <unordered_map>

namespace ola
{
	struct VoidPointerHash
	{
		uint64 operator()(void const* ptr) const
		{
			return reinterpret_cast<uint64>(ptr);
		}
	};
	template<typename V>
	using VoidPointerMap = std::unordered_map<void const*, V, VoidPointerHash>;

}