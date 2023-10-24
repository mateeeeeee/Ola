#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

extern "C"
{
	void PrintInteger(int64_t i)
	{
		printf("%" PRIx64 "\n", i);
	}
	void PrintFloat(double d)
	{
		printf("%lf\n", d);
	}
	void PrintChar(char c)
	{
		printf("%c\n", c);
	}

	int64_t ReadInteger()
	{
		int64_t i;
		int ret = scanf("%" PRIx64 "\n", &i);
		return i;
	}
	double ReadFloat()
	{
		double d;
		int ret = scanf("%lf\n", &d);
		return d;
	}
	char ReadChar()
	{
		char c;
		int ret = scanf("%c\n", &c);
		return c;
	}
}
