#pragma once
#include "Core/Defines.h"
#include "autogen/OlaConfig.h"

// MSVC requires OLA_CONCAT (##), Clang/GCC can use direct string concatenation
#if defined(_MSC_VER)
	#define OLA_PATH_CONCAT(base, suffix) OLA_CONCAT(base, suffix)
#else
	#define OLA_PATH_CONCAT(base, suffix) base suffix
#endif

// OLA_EXE_PATH is now provided by CMake at configure time via target_compile_definitions
#define OLA_VERIFY_IR 0

#if OLA_VERIFY_IR
	#define OLA_VERIFY_FLAG --verify-ir
#else
	#define OLA_VERIFY_FLAG
#endif

#if LLVM_BACKEND

#ifdef DEBUG
#define OLA(...)					std::system(OLA_STRINGIFY(OLA_EXE_PATH --O0 --llvm OLA_VERIFY_FLAG __VA_ARGS__))
#define OLA_TEST(...)				std::system(OLA_STRINGIFY(OLA_EXE_PATH --O0 --llvm --timeout --test OLA_VERIFY_FLAG __VA_ARGS__))
#define OLA_TEST_INTERPRET(...)		std::system(OLA_STRINGIFY(OLA_EXE_PATH --O0 --interpret --timeout --test OLA_VERIFY_FLAG __VA_ARGS__))
#else
#define OLA(...)					std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 --llvm OLA_VERIFY_FLAG __VA_ARGS__))
#define OLA_TEST(...)				std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 --llvm --timeout --test OLA_VERIFY_FLAG __VA_ARGS__))
#define OLA_TEST_INTERPRET(...)		std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 --interpret --timeout --test OLA_VERIFY_FLAG __VA_ARGS__))
#endif

#else

#ifdef DEBUG
#define OLA(...)					std::system(OLA_STRINGIFY(OLA_EXE_PATH --O0 OLA_VERIFY_FLAG __VA_ARGS__))
#define OLA_TEST(...)				std::system(OLA_STRINGIFY(OLA_EXE_PATH --O0 --timeout --test OLA_VERIFY_FLAG __VA_ARGS__))
#define OLA_TEST_INTERPRET(...)		std::system(OLA_STRINGIFY(OLA_EXE_PATH --O0 --interpret --timeout --test OLA_VERIFY_FLAG __VA_ARGS__))
#else
#define OLA(...)					std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 OLA_VERIFY_FLAG __VA_ARGS__))
#define OLA_TEST(...)				std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 --timeout --test OLA_VERIFY_FLAG __VA_ARGS__))
#define OLA_TEST_INTERPRET(...)		std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 --interpret --timeout --test OLA_VERIFY_FLAG __VA_ARGS__))
#endif

#endif

#if defined(OLA_PLATFORM_WINDOWS)
	#if DEBUG
		#define OLA_STATIC_LIB_PATH OLA_PATH_CONCAT(OLA_BINARY_PATH, "Debug/olalib.lib")
	#else
		#define OLA_STATIC_LIB_PATH OLA_PATH_CONCAT(OLA_BINARY_PATH, "Release/olalib.lib")
	#endif
#else
	#define OLA_STATIC_LIB_PATH OLA_PATH_CONCAT(OLA_BINARY_PATH, "libOlaLib.a")
#endif


#define OLA_INVALID_SOURCE_CODE			(-255)
#define OLA_INVALID_ASSEMBLY_CODE		(-254)
#define OLA_TIMEOUT_ERROR_CODE			(-253)
#define OLA_ASSERT_ERROR_CODE			(-252)
