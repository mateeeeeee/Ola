#pragma once
#include <string_view>

namespace ola
{
	enum class TokenKind : uint16
	{
		#define TOKEN(X) X,
		#include "Tokens.def"
	};
	std::string_view GetTokenName(TokenKind t);

	bool IsKeyword(std::string_view identifer);
	TokenKind GetKeywordType(std::string_view identifer);
}