#pragma once

namespace ola
{
	template <char... Cs>
	struct ConstexprString
	{
		static constexpr char value[sizeof...(Cs) + 1] = { Cs..., '\0' };
	};

	template<char... Chars>
	constexpr auto ConstexprStringValue = ConstexprString<Chars...>::value;

}