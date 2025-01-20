#pragma once
#include <cassert>

#define _OLA_STRINGIFY_IMPL(a) #a
#define _OLA_CONCAT_IMPL(x, y) x##y

#define OLA_STRINGIFY(a) _OLA_STRINGIFY_IMPL(a)
#define OLA_CONCAT(x, y) _OLA_CONCAT_IMPL( x, y )

#define OLA_ASSERT(expr)			assert(expr)
#define OLA_ASSERT_MSG(expr, msg)   assert(expr && msg)
#define OLA_UNREACHABLE()			__assume(false)
#define OLA_FORCEINLINE			    __forceinline
#define OLA_NODISCARD				[[nodiscard]]
#define OLA_NORETURN				[[noreturn]]
#define OLA_DEPRECATED			    [[deprecated]]
#define OLA_MAYBE_UNUSED            [[maybe_unused]]
#define OLA_DEPRECATED_MSG(msg)	    [[deprecated(#msg)]]
#define OLA_DEBUGZONE_BEGIN         __pragma(optimize("", off))
#define OLA_DEBUGZONE_END           __pragma(optimize("", on))
#define OLA_TODO(...)

#if defined(_MSC_VER)
#define OLA_UNREACHABLE()			__assume(false)
#define OLA_DEBUGBREAK()			__debugbreak()
#elif defined(__GNUC__)
#define OLA_UNREACHABLE()			__builtin_unreachable()
#define OLA_DEBUGBREAK()	        __builtin_trap()
#else 
#define OLA_UNREACHABLE()			
#define OLA_DEBUGBREAK()	        
#endif

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
