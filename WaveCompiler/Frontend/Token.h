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
		TokenFlag_PartOfImportDirective = 0x4
	};
	DEFINE_ENUM_BIT_OPERATORS(TokenFlag);
	using TokenFlags = uint32;

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
			data = {};
		}

		TokenKind GetKind() const { return kind; }
		void SetKind(TokenKind t) { kind = t; }

		bool Is(TokenKind t) const { return kind == t; }
		bool IsNot(TokenKind t) const { return kind != t; }
		template <typename... Ts>
		bool IsOneOf(TokenKind t1, Ts... ts) const
		{
			if constexpr (sizeof...(Ts) == 0) return Is(t1);
			else return Is(t1) || IsOneOf(ts...);
		}

		bool IsTypename() const
		{
			return IsTypeSpecifier() || IsTypeQualifier() || IsOneOf(TokenKind::KW_var, TokenKind::KW_alias);
		}
		bool IsTypeSpecifier() const
		{
			return IsOneOf(
				TokenKind::KW_enum,
				TokenKind::KW_bool,
				TokenKind::KW_char,
				TokenKind::KW_int,
				TokenKind::KW_float,
				TokenKind::KW_void);
		}
		bool IsTypeQualifier() const
		{
			return Is(TokenKind::KW_const);
		}
		bool IsVisibilitySpecifier() const
		{
			return IsOneOf(TokenKind::KW_private, TokenKind::KW_public);
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
		
		void SetIdentifier(char const* p_data, uint64 count)
		{
			data = std::string(p_data, count);
		}
		void SetIdentifier(char const* start, char const* end)
		{
			data = std::string(start, end - start);
		}
		void SetIdentifier(std::string_view identifier)
		{
			data = std::string(identifier);
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
		TokenKind kind;
		TokenFlags flags;
		SourceLocation loc;
		std::string data;
	};
}