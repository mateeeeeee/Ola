#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

extern "C"
{
	void PrintInteger(int64_t i)
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

	int64_t ReadInteger()
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
}
