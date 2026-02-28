#include <gtest/gtest.h>
#include "Frontend/Lexer.h"
#include "Frontend/SourceBuffer.h"
#include "Frontend/Diagnostics.h"
#include "Frontend/Token.h"
#include "Frontend/TokenKind.h"

using namespace ola;

static std::vector<Token> LexSource(std::string_view src)
{
	Diagnostics diag(false, false);
	SourceBuffer buf(src.data(), src.size(), "<test>");
	Lexer lexer(diag);
	lexer.Lex(buf);
	return lexer.GetTokens();
}

static std::vector<Token> LexFiltered(std::string_view src)
{
	auto tokens = LexSource(src);
	std::erase_if(tokens, [](Token const& t)
	{
		return t.IsOneOf(TokenKind::newline, TokenKind::comment);
	});
	return tokens;
}

TEST(Lexer, BasicTokens)
{
	auto tokens = LexFiltered("int x = 42;");

	ASSERT_GE(tokens.size(), 5u);
	EXPECT_EQ(tokens[0].GetKind(), TokenKind::KW_int);
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::identifier);
	EXPECT_EQ(tokens[1].GetData(), "x");
	EXPECT_EQ(tokens[2].GetKind(), TokenKind::equal);
	EXPECT_EQ(tokens[3].GetKind(), TokenKind::int_number);
	EXPECT_EQ(tokens[3].GetData(), "42");
	EXPECT_EQ(tokens[4].GetKind(), TokenKind::semicolon);
	EXPECT_EQ(tokens[5].GetKind(), TokenKind::eof);
}

TEST(Lexer, IntLiterals)
{
	auto tokens = LexFiltered("0 42 255");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::int_number);
	EXPECT_EQ(tokens[0].GetData(), "0");
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::int_number);
	EXPECT_EQ(tokens[1].GetData(), "42");
	EXPECT_EQ(tokens[2].GetKind(), TokenKind::int_number);
	EXPECT_EQ(tokens[2].GetData(), "255");
}

TEST(Lexer, FloatLiterals)
{
	auto tokens = LexFiltered("3.14 0.5 1.0");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::float_number);
	EXPECT_EQ(tokens[0].GetData(), "3.14");
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::float_number);
	EXPECT_EQ(tokens[1].GetData(), "0.5");
	EXPECT_EQ(tokens[2].GetKind(), TokenKind::float_number);
	EXPECT_EQ(tokens[2].GetData(), "1.0");
}

TEST(Lexer, StringLiteral)
{
	auto tokens = LexFiltered("\"hello\"");

	ASSERT_GE(tokens.size(), 1u);
	EXPECT_EQ(tokens[0].GetKind(), TokenKind::string_literal);
	EXPECT_EQ(tokens[0].GetData(), "hello");
}

TEST(Lexer, CharLiteral)
{
	auto tokens = LexFiltered("'a'");

	ASSERT_GE(tokens.size(), 1u);
	EXPECT_EQ(tokens[0].GetKind(), TokenKind::char_literal);
	EXPECT_EQ(tokens[0].GetData(), "a");
}

TEST(Lexer, BoolKeywords)
{
	auto tokens = LexFiltered("true false");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::KW_true);
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::KW_false);
}

TEST(Lexer, TypeKeywords)
{
	auto tokens = LexFiltered("void bool char int float");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::KW_void);
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::KW_bool);
	EXPECT_EQ(tokens[2].GetKind(), TokenKind::KW_char);
	EXPECT_EQ(tokens[3].GetKind(), TokenKind::KW_int);
	EXPECT_EQ(tokens[4].GetKind(), TokenKind::KW_float);
}

TEST(Lexer, ControlFlowKeywords)
{
	auto tokens = LexFiltered("if else for while do switch case default break continue return goto");

	EXPECT_EQ(tokens[0].GetKind(),  TokenKind::KW_if);
	EXPECT_EQ(tokens[1].GetKind(),  TokenKind::KW_else);
	EXPECT_EQ(tokens[2].GetKind(),  TokenKind::KW_for);
	EXPECT_EQ(tokens[3].GetKind(),  TokenKind::KW_while);
	EXPECT_EQ(tokens[4].GetKind(),  TokenKind::KW_do);
	EXPECT_EQ(tokens[5].GetKind(),  TokenKind::KW_switch);
	EXPECT_EQ(tokens[6].GetKind(),  TokenKind::KW_case);
	EXPECT_EQ(tokens[7].GetKind(),  TokenKind::KW_default);
	EXPECT_EQ(tokens[8].GetKind(),  TokenKind::KW_break);
	EXPECT_EQ(tokens[9].GetKind(),  TokenKind::KW_continue);
	EXPECT_EQ(tokens[10].GetKind(), TokenKind::KW_return);
	EXPECT_EQ(tokens[11].GetKind(), TokenKind::KW_goto);
}

TEST(Lexer, DeclKeywords)
{
	auto tokens = LexFiltered("class interface enum alias extern const ref new delete null");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::KW_class);
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::KW_interface);
	EXPECT_EQ(tokens[2].GetKind(), TokenKind::KW_enum);
	EXPECT_EQ(tokens[3].GetKind(), TokenKind::KW_alias);
	EXPECT_EQ(tokens[4].GetKind(), TokenKind::KW_extern);
	EXPECT_EQ(tokens[5].GetKind(), TokenKind::KW_const);
	EXPECT_EQ(tokens[6].GetKind(), TokenKind::KW_ref);
	EXPECT_EQ(tokens[7].GetKind(), TokenKind::KW_new);
	EXPECT_EQ(tokens[8].GetKind(), TokenKind::KW_delete);
	EXPECT_EQ(tokens[9].GetKind(), TokenKind::KW_null);
}

TEST(Lexer, FunctionAttributes)
{
	auto tokens = LexFiltered("inline noinline nomangle noopt deprecated");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::KW_inline);
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::KW_noinline);
	EXPECT_EQ(tokens[2].GetKind(), TokenKind::KW_nomangle);
	EXPECT_EQ(tokens[3].GetKind(), TokenKind::KW_noopt);
	EXPECT_EQ(tokens[4].GetKind(), TokenKind::KW_deprecated);
}

TEST(Lexer, OopKeywords)
{
	auto tokens = LexFiltered("this super virtual pure final public private");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::KW_this);
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::KW_super);
	EXPECT_EQ(tokens[2].GetKind(), TokenKind::KW_virtual);
	EXPECT_EQ(tokens[3].GetKind(), TokenKind::KW_pure);
	EXPECT_EQ(tokens[4].GetKind(), TokenKind::KW_final);
	EXPECT_EQ(tokens[5].GetKind(), TokenKind::KW_public);
	EXPECT_EQ(tokens[6].GetKind(), TokenKind::KW_private);
}

TEST(Lexer, ArithmeticOperators)
{
	auto tokens = LexFiltered("+ - * / %");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::plus);
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::minus);
	EXPECT_EQ(tokens[2].GetKind(), TokenKind::star);
	EXPECT_EQ(tokens[3].GetKind(), TokenKind::slash);
	EXPECT_EQ(tokens[4].GetKind(), TokenKind::modulo);
}

TEST(Lexer, ComparisonOperators)
{
	auto tokens = LexFiltered("== != < > <= >=");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::equal_equal);
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::not_equal);
	EXPECT_EQ(tokens[2].GetKind(), TokenKind::less);
	EXPECT_EQ(tokens[3].GetKind(), TokenKind::greater);
	EXPECT_EQ(tokens[4].GetKind(), TokenKind::less_equal);
	EXPECT_EQ(tokens[5].GetKind(), TokenKind::greater_equal);
}

TEST(Lexer, LogicalOperators)
{
	auto tokens = LexFiltered("&& || !");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::amp_amp);
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::pipe_pipe);
	EXPECT_EQ(tokens[2].GetKind(), TokenKind::exclaim);
}

TEST(Lexer, BitwiseOperators)
{
	auto tokens = LexFiltered("& | ^ ~ << >>");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::amp);
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::pipe);
	EXPECT_EQ(tokens[2].GetKind(), TokenKind::caret);
	EXPECT_EQ(tokens[3].GetKind(), TokenKind::tilde);
	EXPECT_EQ(tokens[4].GetKind(), TokenKind::less_less);
	EXPECT_EQ(tokens[5].GetKind(), TokenKind::greater_greater);
}

TEST(Lexer, AssignmentOperators)
{
	auto tokens = LexFiltered("= += -= *= /= %= &= |= ^= <<= >>=");

	EXPECT_EQ(tokens[0].GetKind(),  TokenKind::equal);
	EXPECT_EQ(tokens[1].GetKind(),  TokenKind::plus_equal);
	EXPECT_EQ(tokens[2].GetKind(),  TokenKind::minus_equal);
	EXPECT_EQ(tokens[3].GetKind(),  TokenKind::star_equal);
	EXPECT_EQ(tokens[4].GetKind(),  TokenKind::slash_equal);
	EXPECT_EQ(tokens[5].GetKind(),  TokenKind::modulo_equal);
	EXPECT_EQ(tokens[6].GetKind(),  TokenKind::amp_equal);
	EXPECT_EQ(tokens[7].GetKind(),  TokenKind::pipe_equal);
	EXPECT_EQ(tokens[8].GetKind(),  TokenKind::caret_equal);
	EXPECT_EQ(tokens[9].GetKind(),  TokenKind::less_less_equal);
	EXPECT_EQ(tokens[10].GetKind(), TokenKind::greater_greater_equal);
}

TEST(Lexer, IncrementDecrement)
{
	auto tokens = LexFiltered("++ --");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::plus_plus);
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::minus_minus);
}

TEST(Lexer, Punctuators)
{
	auto tokens = LexFiltered("( ) { } [ ] , ; : . ?");

	EXPECT_EQ(tokens[0].GetKind(),  TokenKind::left_round);
	EXPECT_EQ(tokens[1].GetKind(),  TokenKind::right_round);
	EXPECT_EQ(tokens[2].GetKind(),  TokenKind::left_brace);
	EXPECT_EQ(tokens[3].GetKind(),  TokenKind::right_brace);
	EXPECT_EQ(tokens[4].GetKind(),  TokenKind::left_square);
	EXPECT_EQ(tokens[5].GetKind(),  TokenKind::right_square);
	EXPECT_EQ(tokens[6].GetKind(),  TokenKind::comma);
	EXPECT_EQ(tokens[7].GetKind(),  TokenKind::semicolon);
	EXPECT_EQ(tokens[8].GetKind(),  TokenKind::colon);
	EXPECT_EQ(tokens[9].GetKind(),  TokenKind::period);
	EXPECT_EQ(tokens[10].GetKind(), TokenKind::question);
}

TEST(Lexer, Arrow)
{
	auto tokens = LexFiltered("->");
	EXPECT_EQ(tokens[0].GetKind(), TokenKind::arrow);
}

TEST(Lexer, LineComment)
{
	// Line comment should be emitted as a comment token (not stripped internally)
	auto tokens = LexFiltered("int x; // comment\nfloat y;");

	EXPECT_EQ(tokens[0].GetKind(), TokenKind::KW_int);
	EXPECT_EQ(tokens[1].GetKind(), TokenKind::identifier);
	EXPECT_EQ(tokens[1].GetData(), "x");
	EXPECT_EQ(tokens[2].GetKind(), TokenKind::semicolon);
	EXPECT_EQ(tokens[3].GetKind(), TokenKind::KW_float);
	EXPECT_EQ(tokens[4].GetKind(), TokenKind::identifier);
	EXPECT_EQ(tokens[4].GetData(), "y");
	EXPECT_EQ(tokens[5].GetKind(), TokenKind::semicolon);
}

TEST(Lexer, BlockComment)
{
	// The lexer does not support block comments; /* is lexed as slash + star.
	// Verify the tokens are present (not stripped).
	auto tokens = LexFiltered("int /* block comment */ x;");
	bool has_slash = false;
	for (auto const& t : tokens)
		if (t.GetKind() == TokenKind::slash) { has_slash = true; break; }
	EXPECT_TRUE(has_slash);
}

TEST(Lexer, NewlinesProduced)
{
	// Without filtering, newlines appear as separate tokens
	auto tokens = LexSource("int\nfloat");

	bool found_newline = false;
	for (auto const& t : tokens)
		if (t.GetKind() == TokenKind::newline) { found_newline = true; break; }
	EXPECT_TRUE(found_newline);
}

TEST(Lexer, SourceLocationLine)
{
	auto tokens = LexFiltered("int\nx");

	EXPECT_EQ(tokens[0].GetLocation().line, 1u);
	EXPECT_EQ(tokens[1].GetLocation().line, 2u);
}

TEST(Lexer, SourceLocationColumn)
{
	auto tokens = LexFiltered("int x");

	EXPECT_EQ(tokens[0].GetLocation().column, 1u);
	EXPECT_EQ(tokens[1].GetLocation().column, 5u);
}

TEST(Lexer, EmptyInput)
{
	auto tokens = LexFiltered("");

	ASSERT_GE(tokens.size(), 1u);
	EXPECT_EQ(tokens[0].GetKind(), TokenKind::eof);
}

TEST(Lexer, TokenFlagsLeadingSpace)
{
	auto tokens = LexFiltered("int x");

	EXPECT_FALSE(tokens[0].HasFlag(TokenFlag_LeadingSpace));
	EXPECT_TRUE(tokens[1].HasFlag(TokenFlag_LeadingSpace));
}

TEST(Lexer, IsTypenameQuery)
{
	auto tokens = LexFiltered("int float bool char void const alias ref");

	for (Uint32 i = 0; i < 8; ++i)
		EXPECT_TRUE(tokens[i].IsTypename()) << "token " << i << " should be typename";
}

TEST(Lexer, IsFunctionAttribute)
{
	auto tokens = LexFiltered("inline noinline nomangle noopt deprecated");

	for (Uint32 i = 0; i < 5; ++i)
		EXPECT_TRUE(tokens[i].IsFunctionAttribute()) << "token " << i << " should be func attr";
}
