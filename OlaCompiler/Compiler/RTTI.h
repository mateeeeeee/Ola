#pragma once
#include <concepts>

namespace ola
{
	namespace rtti
	{
		template <typename>
		concept AlwaysFalse = false;

		template<typename To, typename From>
		using MergeConstT = std::conditional_t<std::is_const_v<From>, std::add_const_t<To>, To>;

		template <Bool checked, typename To, typename From>
		auto cast_impl(From&& value)
		{
			static_assert(std::is_same_v<std::remove_cvref_t<To>, std::remove_const_t<To>>, "Target type of class may at most be const-qualified");
			static_assert(std::is_class_v<To>, "Target type of cast must be a (const-qualified) class type");
			static_assert(std::is_pointer_v<std::remove_cvref_t<From>>, "Argument of cast function must be a pointer to a class type");
			using ClassT = std::remove_pointer_t<std::remove_reference_t<From>>;
			static_assert(std::is_class_v<ClassT>, "Value type of cast must be a (const-qualified) pointer or to a class type");
			using ResultT = MergeConstT<To, ClassT>*;

			if constexpr (std::is_same_v<ClassT, To> || std::is_base_of_v<To, ClassT>)
			{
				return static_cast<ResultT>(value);
			}
			else if constexpr (std::is_base_of_v<ClassT, To>)
			{
				if (!value) return static_cast<ResultT>(nullptr);
				if (To::ClassOf(value)) return static_cast<ResultT>(value);

				if constexpr (checked) OLA_ASSERT_MSG(false, "Unexpected dynamic type");
				return static_cast<ResultT>(nullptr);
			}
			else
			{
				static_assert(AlwaysFalse<To>, "Cannot cast between unrelated types");
			}
			return static_cast<ResultT>(nullptr);
		}
	}

	template <typename Type>
	concept ClassPointer = std::is_pointer_v<std::remove_reference_t<Type>> &&
						   std::is_class_v<std::remove_pointer_t<std::remove_reference_t<Type>>>;

	template <typename To, typename From> requires ClassPointer<From>
	inline Bool isa(From&& value) { return rtti::cast_impl<false, To>(std::forward<From>(value)) != nullptr; }

	template <typename... Ts, typename From> requires ClassPointer<From>
	inline Bool isoneof(From&& value) { return (Bool(isa<Ts>(value)) || ...); }

	template<typename To, typename From> requires ClassPointer<From>
	inline auto cast(From&& value)
	{
		return rtti::cast_impl<true, To>(std::forward<From>(value));
	}

	template<typename To, typename From> requires ClassPointer<From>
	inline auto dyn_cast(From&& value)
	{
		return rtti::cast_impl<false, To>(std::forward<From>(value));
	}
}