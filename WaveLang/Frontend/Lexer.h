#pragma once
#include <vector>
#include <string>
#include "Token.h"

namespace wave
{
	class SourceBuffer;

	template<typename P>
	concept CharPredicate = requires(P p, char a)
	{
		{ p(a) } -> std::convertible_to<bool>;
	};

	class Lexer
	{
	public:
		explicit Lexer(SourceBuffer const& source);
		Lexer(Lexer const&) = delete;
		Lexer& operator=(Lexer const&) = delete;

		void Lex();

		std::vector<Token> const& GetTokens() const { return tokens; }
	private:
		char const* buf_ptr;
		char const* cur_ptr;

		SourceLocation loc;
		std::vector<Token> tokens;
	private:

		bool LexToken(Token&);
		bool LexNumber(Token&);
		bool LexIdentifier(Token&);
		bool LexString(Token&);
		bool LexEndOfFile(Token&);
		bool LexNewLine(Token&);
		bool LexComment(Token&);
		bool LexPunctuator(Token&);

		void UpdatePointersAndLocation()
		{
			NewChars(loc, static_cast<int32>(cur_ptr - buf_ptr));
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