#pragma once
#include "Core/Macros.h"
#include "autogen/OlaConfig.h"

#if !LLVM_BACKEND

#ifdef DEBUG
#define OLA_EXE_PATH OLA_CONCAT(OLA_BINARY_PATH, "Debug/Ola.exe")
#define OLA(...)		std::system(OLA_STRINGIFY(OLA_EXE_PATH --O0 --nollvm __VA_ARGS__))
#define OLA_TEST(...)	std::system(OLA_STRINGIFY(OLA_EXE_PATH --O0 --nollvm --timeout --test __VA_ARGS__))
#else 
#define OLA_EXE_PATH OLA_CONCAT(OLA_BINARY_PATH, "Release/Ola.exe")
#define OLA(...)		std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 --nollvm __VA_ARGS__))
#define OLA_TEST(...)	std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 --nollvm --timeout --test __VA_ARGS__))
#endif

#else

#ifdef DEBUG
#define OLA_EXE_PATH OLA_CONCAT(OLA_BINARY_PATH, "Debug/Ola.exe")
#define OLA(...)		std::system(OLA_STRINGIFY(OLA_EXE_PATH --O0 __VA_ARGS__))
#define OLA_TEST(...)	std::system(OLA_STRINGIFY(OLA_EXE_PATH --O0 --timeout --test __VA_ARGS__))
#else 
#define OLA_EXE_PATH OLA_CONCAT(OLA_BINARY_PATH, "Release/Ola.exe")
#define OLA(...)		std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 __VA_ARGS__))
#define OLA_TEST(...)	std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 --timeout --test __VA_ARGS__))
#endif

#endif

#if DEBUG
#define OLA_STATIC_LIB_PATH OLA_CONCAT(OLA_BINARY_PATH, "Debug/olalib.lib")
#else 
#define OLA_STATIC_LIB_PATH OLA_CONCAT(OLA_BINARY_PATH, "Release/olalib.lib")
#endif


#define OLA_INVALID_SOURCE_CODE			(-255)
#define OLA_INVALID_ASSEMBLY_CODE		(-254)
#define OLA_TIMEOUT_ERROR_CODE			(-253)
#define OLA_ASSERT_ERROR_CODE			(-252)