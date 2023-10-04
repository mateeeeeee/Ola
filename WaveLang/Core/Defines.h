#pragma once
#include <cassert>

#define _STRINGIFY_IMPL(...) #__VA_ARGS__
#define _CONCAT_IMPL(x, y) x##y
#define LU_STRINGIFY(...) _STRINGIFY_IMPL(__VA_ARGS__)
#define LU_CONCAT(x, y) _CONCAT_IMPL( x, y )

#define LU_ASSERT(expr) assert(expr)
#define LU_ASSERT_MSG(expr, msg) assert(expr && msg)
#define LU_OPTIMIZE_ON  #pragma optimize("", on)
#define LU_OPTIMIZE_OFF #pragma optimize("", off)
#define LU_WARNINGS_OFF #pragma(warning(push, 0))
#define LU_WARNINGS_ON  #pragma(warning(pop))
#define LU_DEBUGBREAK() __debugbreak()
#define LU_FORCEINLINE	__forceinline
#define LU_UNREACHABLE() __assume(false)
#define LU_NODISCARD() [[nodiscard]]
