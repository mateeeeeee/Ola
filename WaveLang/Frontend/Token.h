#pragma once
#include <string_view>
#include "TokenTypes.h"
#include "SourceLocation.h"
#include "Utility/Enums.h"

namespace wave
{

	enum TokenFlag : uint32
	{
		TokenFlag_None = 0x0,
		TokenFlag_LeadingSpace = 0x1,
		TokenFlag_BeginningOfLine = 0x2,
		TokenFlag_PartOfPPDirective = 0x4,
		TokenFlag_SkipedByPP = 0x8
	};
	DEFINE_ENUM_BIT_OPERATORS(TokenFlag);
	using TokenFlags = uint32;

	class Token
	{
	public:
		Token() : type(TokenKind::unknown), flags(TokenFlag_None), loc{}, data{} {}
		
		void Reset()
		{
			type = TokenKind::unknown;
			flags = TokenFlag_None;
			loc = {};
			data = {};
		}

		TokenKind GetKind() const { return type; }
		void SetKind(TokenKind t) { type = t; }

		bool Is(TokenKind t) const { return type == t; }
		bool IsNot(TokenKind t) const { return type != t; }
		template <typename... Ts>
		bool IsOneOf(TokenKind t1, Ts... ts) const
		{
			if constexpr (sizeof...(Ts) == 0) return Is(t1);
			else return Is(t1) || IsOneOf(ts...);
		}

		bool IsPPKeyword() const
		{
			return IsOneOf(TokenKind::PP_define,  TokenKind::PP_defined,  TokenKind::PP_elif,
						   TokenKind::PP_elifdef, TokenKind::PP_elifndef, TokenKind::PP_else,
						   TokenKind::PP_endif,   TokenKind::PP_if,       TokenKind::PP_ifdef, 
						   TokenKind::PP_ifndef,  TokenKind::PP_include,  TokenKind::PP_undef);
		}
		bool IsDeclSpec() const
		{
			return IsOneOf(
				TokenKind::KW_inline,
				TokenKind::KW_enum,
				TokenKind::KW_struct,
				TokenKind::KW_union,
				TokenKind::KW_const,
				TokenKind::KW_volatile,
				TokenKind::KW_typedef,
				TokenKind::KW_static,
				TokenKind::KW_extern,
				TokenKind::KW_auto,
				TokenKind::KW_register,
				TokenKind::KW_restrict,
				TokenKind::KW_bool,
				TokenKind::KW_char,
				TokenKind::KW_short,
				TokenKind::KW_int,
				TokenKind::KW_signed,
				TokenKind::KW_unsigned,
				TokenKind::KW_long,
				TokenKind::KW_float,
				TokenKind::KW_double,
				TokenKind::KW_void,
				TokenKind::KW__Alignas,
				TokenKind::KW__Atomic,
				TokenKind::KW__Thread_local);
		}
		bool IsStorageSpecifier() const
		{
			return IsOneOf(
				TokenKind::KW_inline,
				TokenKind::KW_typedef,
				TokenKind::KW_static,
				TokenKind::KW_extern,
				TokenKind::KW_auto,
				TokenKind::KW_register,
				TokenKind::KW__Atomic,
				TokenKind::KW__Thread_local);
		}

		void SetFlag(TokenFlag flag)
		{
			flags |= flag;
		}
		void ClearFlag(TokenFlag flag)
		{
			flags &= ~flag;
		}
		bool HasFlag(TokenFlag flag) const
		{
			return (flags & flag) != 0;
		}
		TokenFlags GetFlags() const 
		{ 
			return flags;
		}
		void SetFlags(TokenFlags _flags) 
		{
			flags = _flags;
		}
		
		void SetIdentifier(char const* p_data, size_t count)
		{
			data = std::string(p_data, count);
		}
		void SetIdentifier(char const* start, char const* end)
		{
			data = std::string(start, end - start);
		}
		std::string_view GetIdentifier() const
		{
			return data;
		}

		void SetLocation(SourceLocation const& _loc)
		{
			loc = _loc;
		}
		SourceLocation const& GetLocation() const { return loc; }

	private:
		TokenKind type;
		TokenFlags flags;
		SourceLocation loc;
		std::string data;
	};
}