#pragma once
#include <string_view>
#include "TokenKind.h"
#include "SourceLocation.h"
#include "Utility/EnumOperators.h"

namespace ola
{

	enum TokenFlag : Uint32
	{
		TokenFlag_None = 0x0,
		TokenFlag_LeadingSpace = 0x1,
		TokenFlag_BeginningOfLine = 0x2,
		TokenFlag_PartOfImportDirective = 0x4
	};
	ENABLE_ENUM_BIT_OPERATORS(TokenFlag);

	using TokenFlags = Uint32;

	class Token
	{
	public:
		Token() : kind(TokenKind::unknown), flags(TokenFlag_None), loc{}, data{} {}
		Token(TokenKind kind) : kind(kind), flags(TokenFlag_None), loc{}, data{} {}
		
		void Reset()
		{
			kind = TokenKind::unknown;
			flags = TokenFlag_None;
			loc = {};
			data.clear();
		}

		TokenKind GetKind() const { return kind; }
		void SetKind(TokenKind t) { kind = t; }

		Bool Is(TokenKind t) const { return kind == t; }
		Bool IsNot(TokenKind t) const { return kind != t; }
		template <typename... Ts>
		Bool IsOneOf(TokenKind t1, Ts... ts) const
		{
			if constexpr (sizeof...(Ts) == 0) return Is(t1);
			else return Is(t1) || IsOneOf(ts...);
		}

		Bool IsTypename() const
		{
			return IsTypeSpecifier() || IsTypeQualifier() || IsOneOf(TokenKind::KW_auto, TokenKind::KW_alias, TokenKind::KW_ref);
		}
		Bool IsTypeSpecifier() const
		{
			return IsOneOf(
				TokenKind::KW_enum,
				TokenKind::KW_bool,
				TokenKind::KW_char,
				TokenKind::KW_int,
				TokenKind::KW_float,
				TokenKind::KW_void);
		}
		Bool IsTypeQualifier() const
		{
			return Is(TokenKind::KW_const);
		}
		Bool IsVisibilitySpecifier() const
		{
			return IsOneOf(TokenKind::KW_private, TokenKind::KW_public);
		}
		Bool IsFunctionAttribute() const
		{
			return IsOneOf(TokenKind::KW_inline, TokenKind::KW_noinline, TokenKind::KW_nomangle, TokenKind::KW_noopt, TokenKind::KW_deprecated);
		}
		Bool IsMethodAttribute() const
		{
			return IsOneOf(TokenKind::KW_const, TokenKind::KW_virtual, TokenKind::KW_pure, TokenKind::KW_final);
		}

		void SetFlag(TokenFlag flag)
		{
			flags |= flag;
		}
		void ClearFlag(TokenFlag flag)
		{
			flags &= ~flag;
		}
		Bool HasFlag(TokenFlag flag) const
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
		
		void SetData(Char const* p_data, Uint64 count)
		{
			data = std::string(p_data, count);
		}
		void SetData(Char const* start, Char const* end)
		{
			data = std::string(start, end - start);
		}
		void SetData(std::string_view identifier)
		{
			data = std::string(identifier);
		}
		std::string_view GetData() const
		{
			return data;
		}

		void SetLocation(SourceLocation const& _loc)
		{
			loc = _loc;
		}
		SourceLocation const& GetLocation() const { return loc; }

	private:
		TokenKind kind;
		TokenFlags flags;
		SourceLocation loc;
		std::string data;
	};
}