#pragma once
#include <cassert>

extern "C" void Assert(bool expr)
{
	assert(expr);
}
