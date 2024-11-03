#pragma once
#include <string_view>

namespace ola
{
	enum class TokenKind : Uint16
	{
		#define TOKEN(X) X,
		#include "Tokens.def"
	};
	std::string_view GetTokenName(TokenKind t);

	Bool IsKeyword(std::string_view identifer);
	TokenKind GetKeywordType(std::string_view identifer);
}