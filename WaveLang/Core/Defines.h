#pragma once
#include <cassert>

#define _WAVE_STRINGIFY_IMPL(a) #a
#define _WAVE_CONCAT_IMPL(x, y) x##y

#define WAVE_STRINGIFY(a) _WAVE_STRINGIFY_IMPL(a)
#define WAVE_CONCAT(x, y) _WAVE_CONCAT_IMPL( x, y )

#define WAVE_ASSERT(expr)			assert(expr)
#define WAVE_ASSERT_MSG(expr, msg)  assert(expr && msg)
#define WAVE_OPTIMIZE_ON			pragma optimize("", on)
#define WAVE_OPTIMIZE_OFF			pragma optimize("", off)
#define WAVE_WARNINGS_OFF			pragma(warning(push, 0))
#define WAVE_WARNINGS_ON			pragma(warning(pop))
#define WAVE_DEBUGBREAK()			__debugbreak()
#define WAVE_FORCEINLINE			__forceinline
#define WAVE_INLINE				    inline
#define WAVE_NODISCARD				[[nodiscard]]
#define WAVE_NORETURN				[[noreturn]]
#define WAVE_DEPRECATED			    [[deprecated]]
#define WAVE_DEPRECATED_MSG(msg)	[[deprecated(#msg)]]
#define WAVE_ALIGNAS(align)         alignas(align) 

#ifdef __GNUC__ 
#define WAVE_UNREACHABLE()			___builtin_unreachable();
#elifdef _MSC_VER 
#define WAVE_UNREACHABLE()			___assume(false);
#else
#define WAVE_UNREACHABLE()	
#endif
		


#define WAVE_NONCOPYABLE(ClassName)                 \
    ClassName(ClassName const&)            = delete; \
    ClassName& operator=(ClassName const&) = delete;

#define WAVE_NONMOVABLE(ClassName)                      \
    ClassName(ClassName&&) noexcept            = delete; \
    ClassName& operator=(ClassName&&) noexcept = delete;

#define WAVE_NONCOPYABLE_NONMOVABLE(ClassName) \
        WAVE_NONCOPYABLE(ClassName)                \
        WAVE_NONMOVABLE(ClassName)

#define WAVE_DEFAULT_COPYABLE(ClassName)             \
    ClassName(ClassName const&)            = default; \
    ClassName& operator=(ClassName const&) = default;

#define WAVE_DEFAULT_MOVABLE(ClassName)                  \
    ClassName(ClassName&&) noexcept            = default; \
    ClassName& operator=(ClassName&&) noexcept = default;

#define WAVE_DEFAULT_COPYABLE_MOVABLE(ClassName) \
    WAVE_DEFAULT_COPYABLE(ClassName)             \
    WAVE_DEFAULT_MOVABLE(ClassName)


#define WAVE_COMPILATION_FAILED_EXIT_CODE INT_MAX