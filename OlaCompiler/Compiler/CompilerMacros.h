#pragma once
#include "Core/Macros.h"
#include "autogen/OlaConfig.h"

#if OLA_NOLLVM

#ifdef DEBUG
#define OLA_EXE_PATH OLA_CONCAT(OLA_BINARY_PATH, "Debug/Ola.exe")
#define OLA(...)		std::system(OLA_STRINGIFY(OLA_EXE_PATH --Od --nollvm __VA_ARGS__))
#define OLA_TEST(...)	std::system(OLA_STRINGIFY(OLA_EXE_PATH --Od --nollvm --test __VA_ARGS__))
#else 
#define OLA_EXE_PATH OLA_CONCAT(OLA_BINARY_PATH, "Release/Ola.exe")
#define OLA(...)		std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 --nollvm __VA_ARGS__))
#define OLA_TEST(...)	std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 --nollvm --test __VA_ARGS__))
#endif

#else

#ifdef DEBUG
#define OLA_EXE_PATH OLA_CONCAT(OLA_BINARY_PATH, "Debug/Ola.exe")
#define OLA(...)		std::system(OLA_STRINGIFY(OLA_EXE_PATH --Od __VA_ARGS__))
#define OLA_TEST(...)	std::system(OLA_STRINGIFY(OLA_EXE_PATH --Od --test __VA_ARGS__))
#else 
#define OLA_EXE_PATH OLA_CONCAT(OLA_BINARY_PATH, "Release/Ola.exe")
#define OLA(...)		std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 __VA_ARGS__))
#define OLA_TEST(...)	std::system(OLA_STRINGIFY(OLA_EXE_PATH --O3 --test __VA_ARGS__))
#endif

#endif

#if DEBUG
#define OLA_LIB_PATH OLA_CONCAT(OLA_BINARY_PATH, "Debug/olalib.lib")
#else 
#define OLA_LIB_PATH OLA_CONCAT(OLA_BINARY_PATH, "Release/olalib.lib")
#endif