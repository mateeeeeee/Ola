#pragma once
#include <type_traits>
#include <concepts>

namespace ola
{
	template <typename E> requires std::is_enum_v<E>
	struct EnumBitmaskOperators
	{
		static constexpr Bool enable = false;
	};
	template <typename E>
	constexpr Bool EnableEnumBitmaskOperators = EnumBitmaskOperators<E>::enable;

	template <typename E>
	typename std::enable_if_t<EnableEnumBitmaskOperators<E>, E> operator|(E lhs, E rhs)
	{
		using T = std::underlying_type_t<E>;
		return static_cast<E>(static_cast<T>(lhs) | static_cast<T>(rhs));
	}
	template <typename E>
	typename std::enable_if_t<EnableEnumBitmaskOperators<E>, E> operator&(E lhs, E rhs)
	{
		using T = std::underlying_type_t<E>;
		return static_cast<E>(static_cast<T>(lhs) & static_cast<T>(rhs));
	}
	template <typename E>
	typename std::enable_if_t<EnableEnumBitmaskOperators<E>, E> operator^(E lhs, E rhs)
	{
		using T = std::underlying_type_t<E>;
		return static_cast<E>(static_cast<T>(lhs) ^ static_cast<T>(rhs));
	}
	template <typename E>
	typename std::enable_if_t<EnableEnumBitmaskOperators<E>, E> operator~(E e)
	{
		using T = std::underlying_type_t<E>;
		return static_cast<E>(~static_cast<T>(e));
	}

	template <typename E>
	typename std::enable_if_t<EnableEnumBitmaskOperators<E>, E&> operator|=(E& lhs, E rhs)
	{
		using T = std::underlying_type_t<E>;
		return lhs = static_cast<E>(static_cast<T>(lhs) | static_cast<T>(rhs));
	}
	template <typename E>
	typename std::enable_if_t<EnableEnumBitmaskOperators<E>, E&> operator&=(E& lhs, E rhs)
	{
		using T = std::underlying_type_t<E>;
		return lhs = static_cast<E>(static_cast<T>(lhs) & static_cast<T>(rhs));
	}
	template <typename E>
	typename std::enable_if_t<EnableEnumBitmaskOperators<E>, E&> operator^=(E& lhs, E rhs)
	{
		using T = std::underlying_type_t<E>;
		return lhs = static_cast<E>(static_cast<T>(lhs) ^ static_cast<T>(rhs));
	}

	template<typename Enum> requires std::is_enum_v<Enum>
	inline constexpr Bool HasAllFlags(Enum value, Enum flags)
	{
		using T = std::underlying_type_t<Enum>;
		return (((T)value) & (T)flags) == ((T)flags);
	}

	template<typename Enum> requires std::is_enum_v<Enum>
	inline constexpr Bool HasAnyFlag(Enum value, Enum flags)
	{
		using T = std::underlying_type_t<Enum>;
		return (((T)value) & (T)flags) != 0;
	}

#define ENABLE_ENUM_BIT_OPERATORS(EnumType) \
	template<> struct EnumBitmaskOperators<EnumType> \
	{ static constexpr Bool enable = true; }

}