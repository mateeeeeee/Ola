#pragma once
#include <vector>
#include <string>
#include "Token.h"

namespace ola
{
	class SourceBuffer;
	class Diagnostics;

	template<typename P>
	concept CharPredicate = requires(P p, Char a)
	{
		{ p(a) } -> std::convertible_to<Bool>;
	};

	class Lexer
	{
	public:
		explicit Lexer(Diagnostics& diagnostics);
		OLA_NONCOPYABLE_NONMOVABLE(Lexer)
		~Lexer() = default;

		void Lex(SourceBuffer const& source);
		std::vector<Token>&& GetTokens() { return std::move(tokens); }

	private:
		Diagnostics& diagnostics;
		Char const* buf_ptr = nullptr;
		Char const* cur_ptr = nullptr;

		SourceLocation loc;
		std::vector<Token> tokens;
	private:

		Bool LexToken(Token&);
		Bool LexNumber(Token&);
		Bool LexIdentifier(Token&);
		Bool LexChar(Token&);
		Bool LexString(Token&);
		Bool LexEndOfFile(Token&);
		Bool LexNewLine(Token&);
		Bool LexComment(Token&);
		Bool LexPunctuator(Token&);

		void UpdatePointersAndLocation()
		{
			loc.NewChars(static_cast<Sint32>(cur_ptr - buf_ptr));
			buf_ptr = cur_ptr;
		}

		void FillToken(Token& t, TokenKind type, Char const* end)
		{
			t.SetLocation(loc);
			t.SetKind(type);
			t.SetData(cur_ptr, end);
			cur_ptr = end;
		}
		template<CharPredicate P>
		void Consume(Char const*& start, P&& predicate)
		{
			for (; predicate(*start); ++start);
		}
		template<CharPredicate P>
		void FillToken(Token& t, TokenKind type, P&& predicate)
		{
			t.SetLocation(loc);
			t.SetKind(type);
			Char const* tmp_ptr = cur_ptr;
			Consume(tmp_ptr, std::forward<P>(predicate));
			t.SetData(cur_ptr, tmp_ptr);
			cur_ptr = tmp_ptr;
		}
	};
}