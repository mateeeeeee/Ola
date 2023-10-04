#include "Lexer.h"
#include "SourceBuffer.h"
#include "Diagnostics.h"


namespace wave
{

	Lexer::Lexer(SourceBuffer const& source) : buf_ptr(source.GetBufferStart()), cur_ptr(buf_ptr),
											   loc{ .filename = std::string(source.GetRefName().data(), source.GetRefName().size())}
	{
	}

	void Lexer::Lex()
	{
		Token current_token{};
		do
		{
			current_token.Reset();
			bool result = LexToken(current_token);

			if (!result)
			{
				//Report(diag::lexing_failed);
				return;
			}
			if (!tokens.empty())
			{
				auto const& prev_token = tokens.back();
				if (prev_token.Is(TokenKind::newline)) current_token.SetFlag(TokenFlag_BeginningOfLine);
			}
			else current_token.SetFlag(TokenFlag_BeginningOfLine);

			tokens.push_back(current_token);
		} while (current_token.IsNot(TokenKind::eof));
	}

	bool Lexer::LexToken(Token& token)
	{
		UpdatePointersAndLocation();
		if ((*cur_ptr == ' ') || (*cur_ptr == '\t'))
		{
			++cur_ptr;
			while ((*cur_ptr == ' ') || (*cur_ptr == '\t')) ++cur_ptr;
			token.SetFlag(TokenFlag_LeadingSpace);
			UpdatePointersAndLocation();
		}

		char c = *cur_ptr++;
		switch (c)
		{
		case '\0':
			return LexEndOfFile(token);
		case '\n':
		{
			bool ret = LexNewLine(token);
			loc.NewLine();
			buf_ptr = cur_ptr;
			token.ClearFlag(TokenFlag_LeadingSpace);
			return ret;
		}
		case '/':
		{
			if (*cur_ptr == '/') 
			{
				++cur_ptr;
				return LexComment(token);
			}
			else
			{
				--cur_ptr;
				return LexPunctuator(token);
			}
		}
		case '"':
		{
			return LexString(token);
		}
		case '.':
		{
			--cur_ptr;
			if (std::isdigit(*(cur_ptr + 1)))
			{
				return LexNumber(token);
			}
			else return LexPunctuator(token);
		}
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		{
			--cur_ptr;
			return LexNumber(token);
		}
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
		case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
		case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
		case 'V': case 'W': case 'X': case 'Y': case 'Z':
		case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
		case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
		case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
		case 'v': case 'w': case 'x': case 'y': case 'z':
		case '_':
		{
			--cur_ptr;
			return LexIdentifier(token);
		}
		case '[': case ']': case '(': case ')': case '{': case '}': /*case '.': */
		case '&': case '*': case '+': case '-': case '~': case '!': /*case '/':*/
		case '%': case '<': case '>': case '^': case '|': case '?': case ':':
		case ';': case '=': case ',': case '#':
		{
			--cur_ptr;
			return LexPunctuator(token);
		}
		}
		Report(diag::unknown_character, loc);
		return false;
	}

	bool Lexer::LexNumber(Token& t)
	{
		char const* tmp_ptr = cur_ptr;
		Consume(tmp_ptr, [](char c) -> bool { return std::isdigit(c); });
		if (*tmp_ptr == 'f' || *tmp_ptr == 'F') ++tmp_ptr;
		else if (std::isalpha(*tmp_ptr))
		{
			UpdatePointersAndLocation();
			Report(diag::invalid_number_literal, loc);
			return false;
		}
		FillToken(t, TokenKind::number, tmp_ptr);
		UpdatePointersAndLocation();
		return true;
	}

	bool Lexer::LexIdentifier(Token& t)
	{
		FillToken(t, TokenKind::identifier, [](char c) -> bool { return std::isalnum(c) || c == '_'; });
		std::string_view identifier = t.GetIdentifier();
		if (IsKeyword(identifier))
		{
			t.SetKind(GetKeywordType(identifier));
		}
		UpdatePointersAndLocation();
		return true;
	}

	bool Lexer::LexString(Token& t)
	{
		FillToken(t, TokenKind::string_literal, [](char c) -> bool { return c != '"'; });
		++cur_ptr;
		UpdatePointersAndLocation();
		return true;
	}

	bool Lexer::LexEndOfFile(Token& t)
	{
		t.SetKind(TokenKind::eof);
		t.SetLocation(loc);
		return true;
	}

	bool Lexer::LexNewLine(Token& t)
	{
		t.SetKind(TokenKind::newline);
		t.SetLocation(loc);
		return true;
	}

	bool Lexer::LexComment(Token& t)
	{
		FillToken(t, TokenKind::comment, [](char c) -> bool { return c != '\n' && c != '\0'; });
		UpdatePointersAndLocation();
		return true;
	}

	bool Lexer::LexPunctuator(Token& t)
	{
		char c = *cur_ptr++;
		switch (c)
		{
		case '=':
			if (*cur_ptr == '=')
			{
				++cur_ptr;
				t.SetKind(TokenKind::equal_equal);
			}
			else t.SetKind(TokenKind::equal);
			break;
		case '!':
			if (*cur_ptr == '=')
			{
				++cur_ptr;
				t.SetKind(TokenKind::not_equal);
			}
			else t.SetKind(TokenKind::exclaim);
			break;
		case '>':
			if (*cur_ptr == '=')
			{
				++cur_ptr;
				t.SetKind(TokenKind::greater_equal);
			}
			else if (*cur_ptr == '>')
			{
				++cur_ptr;
				if (*cur_ptr == '=')
				{
					++cur_ptr;
					t.SetKind(TokenKind::greater_greater_equal);
				}
				else t.SetKind(TokenKind::greater_greater);
			}
			else t.SetKind(TokenKind::greater);
			break;
		case '<':
			if (*cur_ptr == '=')
			{
				++cur_ptr;
				t.SetKind(TokenKind::less_equal);
			}
			else if (*cur_ptr == '<')
			{
				++cur_ptr;
				if (*cur_ptr == '=')
				{
					++cur_ptr;
					t.SetKind(TokenKind::less_less_equal);
				}
				else t.SetKind(TokenKind::less_less);
			}
			else t.SetKind(TokenKind::less);
			break;
		case '+':
			if (*cur_ptr == '+')
			{
				++cur_ptr;
				t.SetKind(TokenKind::plus_plus);
			}
			else if (*cur_ptr == '=')
			{
				++cur_ptr;
				t.SetKind(TokenKind::plus_equal);
			}
			else t.SetKind(TokenKind::plus);
			break;
		case '-':
			if (*cur_ptr == '-')
			{
				++cur_ptr;
				t.SetKind(TokenKind::minus_minus);
			}
			else if (*cur_ptr == '=')
			{
				++cur_ptr;
				t.SetKind(TokenKind::minus_equal);
			}
			else if (*cur_ptr == '>')
			{
				++cur_ptr;
				t.SetKind(TokenKind::arrow);
			}
			else t.SetKind(TokenKind::minus);
			break;
		case '*':
			if (*cur_ptr == '=')
			{
				++cur_ptr;
				t.SetKind(TokenKind::star_equal);
			}
			else t.SetKind(TokenKind::star);
			break;
		case '&':
			if (*cur_ptr == '&')
			{
				++cur_ptr;
				t.SetKind(TokenKind::amp_amp);
			}
			else if (*cur_ptr == '=')
			{
				++cur_ptr;
				t.SetKind(TokenKind::amp_equal);
			}
			else t.SetKind(TokenKind::amp);
			break;
		case '|':
			if (*cur_ptr == '|')
			{
				++cur_ptr;
				t.SetKind(TokenKind::pipe_pipe);
			}
			else if (*cur_ptr == '=')
			{
				++cur_ptr;
				t.SetKind(TokenKind::pipe_equal);
			}
			else t.SetKind(TokenKind::pipe);
			break;
		case '^':
			if (*cur_ptr == '=')
			{
				++cur_ptr;
				t.SetKind(TokenKind::caret_equal);
			}
			else t.SetKind(TokenKind::caret);
			break;
		case '/':
			if (*cur_ptr == '=')
			{
				++cur_ptr;
				t.SetKind(TokenKind::slash_equal);
			}
			else t.SetKind(TokenKind::slash);
			break;
		case '?':
			t.SetKind(TokenKind::question);
			break;
		case '[':
			t.SetKind(TokenKind::left_square);
			break;
		case ']':
			t.SetKind(TokenKind::right_square);
			break;
		case '(':
			t.SetKind(TokenKind::left_round);
			break;
		case ')':
			t.SetKind(TokenKind::right_round);
			break;
		case '{':
			t.SetKind(TokenKind::left_brace);
			break;
		case '}':
			t.SetKind(TokenKind::right_brace);
			break;
		case ',':
			t.SetKind(TokenKind::comma);
			break;
		case ';':
			t.SetKind(TokenKind::semicolon);
			break;
		case ':':
			t.SetKind(TokenKind::colon);
			break;
		case '#':
			if (*cur_ptr == '#')
			{
				t.SetKind(TokenKind::hash_hash);
				++cur_ptr;
			}
			else t.SetKind(TokenKind::hash);
			break;
		case '.':
			if (cur_ptr[0] == '.' && cur_ptr[1] == '.')
			{
				t.SetKind(TokenKind::ellipsis);
				cur_ptr += 2;
			}
			else 
			{
				t.SetKind(TokenKind::period);
			}
			break;
		case '~':
			t.SetKind(TokenKind::tilde);
			break;
		}
		t.SetLocation(loc);
		UpdatePointersAndLocation();
		return true;
	}

}

