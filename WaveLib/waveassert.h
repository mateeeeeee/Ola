#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

extern "C"
{
	void Assert(bool expr)
	{
		if (!expr)
		{
			puts("Assert failed!");
			abort();
		}
	}
	void AssertMsg(bool expr, char* msg)
	{
		if (!expr)
		{
			printf("Assert failed: %s!", msg);
			abort();
		}
	}
}

