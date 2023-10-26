#include <ctype.h>

extern "C"
{
	bool IsAlnum(char ch)
	{
		return !!isalnum(ch);
	}
	bool IsAlpha(char ch)
	{
		return !!isalpha(ch);
	}
	bool IsLower(char ch)
	{
		return !!islower(ch);
	}
	bool IsUpper(char ch)
	{
		return !!isupper(ch);
	}
	bool IsDigit(char ch)
	{
		return !!isdigit(ch);
	}
	bool IsSpace(char ch)
	{
		return !!isspace(ch);
	}
	char ToLower(char ch)
	{
		return (char)tolower(ch);
	}
	char ToUpper(char ch)
	{
		return (char)toupper(ch);
	}
}