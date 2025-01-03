#include <stdio.h>
#include <stdlib.h>

extern "C"
{
	void Assert(bool expr)
	{
		if (!expr)
		{
			puts("Assert failed!");
			exit(-252);
		}
	}
	void AssertMsg(bool expr, char* msg)
	{
		if (!expr)
		{
			printf("Assert failed: %s!", msg);
			exit(-252);
		}
	}
}

