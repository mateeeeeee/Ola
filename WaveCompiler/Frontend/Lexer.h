#pragma once
#include <vector>
#include <string>
#include "Token.h"

namespace wave
{
	class SourceBuffer;
	class Diagnostics;

	template<typename P>
	concept CharPredicate = requires(P p, char a)
	{
		{ p(a) } -> std::convertible_to<bool>;
	};

	class Lexer
	{
	public:
		explicit Lexer(Diagnostics& diagnostics);
		Lexer(Lexer const&) = delete;
		Lexer& operator=(Lexer const&) = delete;

		void Lex(SourceBuffer const& source);

		std::vector<Token>&& GetTokens() { return std::move(tokens); }

	private:
		Diagnostics& diagnostics;
		char const* buf_ptr = nullptr;
		char const* cur_ptr = nullptr;

		SourceLocation loc;
		std::vector<Token> tokens;
	private:

		bool LexToken(Token&);
		bool LexNumber(Token&);
		bool LexIdentifier(Token&);
		bool LexChar(Token&);
		bool LexString(Token&);
		bool LexEndOfFile(Token&);
		bool LexNewLine(Token&);
		bool LexComment(Token&);
		bool LexPunctuator(Token&);

		void UpdatePointersAndLocation()
		{
			loc.NewChars(static_cast<int32>(cur_ptr - buf_ptr));
			buf_ptr = cur_ptr;
		}

		void FillToken(Token& t, TokenKind type, char const* end)
		{
			t.SetLocation(loc);
			t.SetKind(type);
			t.SetIdentifier(cur_ptr, end);
			cur_ptr = end;
		}
		template<CharPredicate P>
		void Consume(char const*& start, P&& predicate)
		{
			for (; predicate(*start); ++start);
		}
		template<CharPredicate P>
		void FillToken(Token& t, TokenKind type, P&& predicate)
		{
			t.SetLocation(loc);
			t.SetKind(type);
			char const* tmp_ptr = cur_ptr;
			Consume(tmp_ptr, std::forward<P>(predicate));
			t.SetIdentifier(cur_ptr, tmp_ptr);
			cur_ptr = tmp_ptr;
		}
	};
}