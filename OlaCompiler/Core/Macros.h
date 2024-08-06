#pragma once
#include <cassert>

#define _OLA_STRINGIFY_IMPL(a) #a
#define _OLA_CONCAT_IMPL(x, y) x##y

#define OLA_STRINGIFY(a) _OLA_STRINGIFY_IMPL(a)
#define OLA_CONCAT(x, y) _OLA_CONCAT_IMPL( x, y )

#define OLA_ASSERT(expr)			assert(expr)
#define OLA_ASSERT_MSG(expr, msg)   assert(expr && msg)
#define OLA_DEBUGBREAK()			__debugbreak()
#define OLA_FORCEINLINE			    __forceinline
#define OLA_NODISCARD				[[nodiscard]]
#define OLA_MAYBE_UNUSED            [[maybe_unused]]
#define OLA_DEPRECATED			    [[deprecated]]
#define OLA_DEPRECATED_MSG(msg)	    [[deprecated(#msg)]]

#ifdef __GNUC__ 
#define OLA_UNREACHABLE()			__builtin_unreachable();
#elifdef _MSC_VER 
#define OLA_UNREACHABLE()			__assume(false);
#else
#define OLA_UNREACHABLE()	
#endif
		


#define OLA_NONCOPYABLE(ClassName)                 \
    ClassName(ClassName const&)            = delete; \
    ClassName& operator=(ClassName const&) = delete;

#define OLA_NONMOVABLE(ClassName)                      \
    ClassName(ClassName&&) noexcept            = delete; \
    ClassName& operator=(ClassName&&) noexcept = delete;

#define OLA_NONCOPYABLE_NONMOVABLE(ClassName) \
        OLA_NONCOPYABLE(ClassName)                \
        OLA_NONMOVABLE(ClassName)

#define OLA_DEFAULT_COPYABLE(ClassName)             \
    ClassName(ClassName const&)            = default; \
    ClassName& operator=(ClassName const&) = default;

#define OLA_DEFAULT_MOVABLE(ClassName)                  \
    ClassName(ClassName&&) noexcept            = default; \
    ClassName& operator=(ClassName&&) noexcept = default;

#define OLA_DEFAULT_COPYABLE_MOVABLE(ClassName) \
    OLA_DEFAULT_COPYABLE(ClassName)             \
    OLA_DEFAULT_MOVABLE(ClassName)


#define OLA_COMPILATION_FAILED_EXIT_CODE -1