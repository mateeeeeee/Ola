#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#pragma warning( push )
#pragma warning( disable : 6031 )

extern "C"
{

	void PrintInt(int64_t i)
	{
		printf("%" PRId64 "\n", i);
	}
	void PrintFloat(double d)
	{
		printf("%lf\n", d);
	}
	void PrintChar(char c)
	{
		printf("%c\n", c);
	}
	void PrintString(char* str)
	{
		printf("%s", str);
	}
	
	int64_t ReadInt()
	{
		int64_t i;
		scanf("%" SCNd64, &i);
		return i;
	}
	double ReadFloat()
	{
		double d;
		scanf("%lf", &d);
		return d;
	}
	char ReadChar()
	{
		char c;
		scanf("%c", &c);
		return c;
	}
	void ReadString(char* str, int64_t str_size)
	{
		unsigned int buf_size = (unsigned int)str_size;
		scanf_s("%s", str, buf_size);
	}
}
#pragma warning( pop )

