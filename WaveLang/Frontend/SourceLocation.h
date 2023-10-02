#pragma once
#include <string>

namespace wave
{
	struct SourceLocation
	{
		std::string filename = "";
		uint32 line = 1;
		uint32 column = 1;
	};

	inline SourceLocation operator+(SourceLocation const& loc, int32 i)
	{
		return SourceLocation
		{
			.filename = loc.filename,
			.line = loc.line,
			.column = loc.column + i
		};
	}
	inline void NewChar(SourceLocation& loc)
	{
		++loc.column;
	}
	inline void NewChars(SourceLocation& loc, int32 i)
	{
		loc.column += i;
	}
	inline void NewLine(SourceLocation& loc)
	{
		++loc.line;
		loc.column = 1;
	}
}