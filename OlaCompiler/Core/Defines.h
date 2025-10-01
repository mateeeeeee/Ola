#pragma once
#include <cassert>

#pragma once
#include <cassert>

#define _OLA_STRINGIFY_IMPL(a) #a
#define _OLA_CONCAT_IMPL(x, y) x##y

#define OLA_STRINGIFY(a) _OLA_STRINGIFY_IMPL(a)
#define OLA_CONCAT(x, y) _OLA_CONCAT_IMPL(x, y)

#define OLA_TODO(...)
#define OLA_HACK(stmt, msg) stmt

#define OLA_ASSERT(expr)            assert(expr)
#define OLA_ASSERT_MSG(expr, msg)   assert((expr) && (msg))

#if defined(_MSC_VER) 
#define OLA_DEBUGBREAK()       __debugbreak()
#define OLA_UNREACHABLE()      __assume(false)
#define OLA_FORCEINLINE        __forceinline
#define OLA_NOINLINE           __declspec(noinline)
#define OLA_DEBUGZONE_BEGIN    __pragma(optimize("", off))
#define OLA_DEBUGZONE_END      __pragma(optimize("", on))

#elif defined(__GNUC__) || defined(__clang__) 
#define OLA_DEBUGBREAK()       __builtin_trap()
#define OLA_UNREACHABLE()      __builtin_unreachable()
#define OLA_FORCEINLINE        inline __attribute__((always_inline))
#define OLA_NOINLINE           __attribute__((noinline))
#define OLA_DEBUGZONE_BEGIN    _Pragma("GCC push_options") \
                                 _Pragma("GCC optimize(\"O0\")")
#define OLA_DEBUGZONE_END      _Pragma("GCC pop_options")

#else 
#define OLA_DEBUGBREAK()       ((void)0)
#define OLA_UNREACHABLE()      ((void)0)
#define OLA_FORCEINLINE        inline
#define OLA_NOINLINE
#define OLA_DEBUGZONE_BEGIN
#define OLA_DEBUGZONE_END
#endif

#define OLA_ALIGN(x, align)         ((x) & ~((align) - 1))
#define OLA_ALIGN_UP(x, align)      (((x) + (align) - 1) & ~((align) - 1))

#define OLA_NODISCARD              [[nodiscard]]
#define OLA_NORETURN               [[noreturn]]
#define OLA_DEPRECATED             [[deprecated]]
#define OLA_MAYBE_UNUSED           [[maybe_unused]]
#define OLA_DEPRECATED_MSG(msg)    [[deprecated(msg)]]


#if defined(_WIN32) || defined(_WIN64)
#define OLA_PLATFORM_WINDOWS 1
#elif defined(__linux__)
#define OLA_PLATFORM_LINUX 1
#elif defined(__APPLE__)
#define OLA_PLATFORM_MACOS 1
#endif

#ifndef OLA_PLATFORM_WINDOWS
#define OLA_PLATFORM_WINDOWS 0
#endif

#ifndef OLA_PLATFORM_LINUX
#define OLA_PLATFORM_LINUX 0
#endif

#ifndef OLA_PLATFORM_MACOS
#define OLA_PLATFORM_MACOS 0
#endif


template<typename T, int N>
constexpr int _ArraySize(T(&arr)[N])
{
	return N;
}
#define OLA_ARRAYSIZE(arr) (_ArraySize(arr))

#define OLA_NONCOPYABLE(Class)                   \
        Class(Class const&)            = delete; \
        Class& operator=(Class const&) = delete;

#define OLA_NONMOVABLE(Class)                       \
        Class(Class&&) noexcept            = delete; \
        Class& operator=(Class&&) noexcept = delete;

#define OLA_NONCOPYABLE_NONMOVABLE(Class) \
        OLA_NONCOPYABLE(Class)            \
        OLA_NONMOVABLE(Class)

#define OLA_DEFAULT_COPYABLE(Class)               \
        Class(Class const&)            = default; \
        Class& operator=(Class const&) = default;

#define OLA_DEFAULT_MOVABLE(Class)                    \
        Class(Class&&) noexcept            = default; \
        Class& operator=(Class&&) noexcept = default;

#define OLA_DEFAULT_COPYABLE_MOVABLE(Class) \
        OLA_DEFAULT_COPYABLE(Class)         \
        OLA_DEFAULT_MOVABLE(Class)
