#pragma once
#include <string>
#include <string_view>

namespace ola
{
	struct SourceLocation
	{
		std::string filename = "";
		Uint32 line = 1;
		Uint32 column = 1;

		SourceLocation operator+(Sint32 i)
		{
			return SourceLocation
			{
				.filename = filename,
				.line = line,
				.column = column + i
			};
		}

		void NewChar()
		{
			++column;
		}
		void NewChars(Sint32 i)
		{
			column += i;
		}
		void NewLine()
		{
			++line;
			column = 1;
		}
	};
}