#include <assert.h>

extern "C" void Assert(bool expr)
{
	assert(expr);
}
