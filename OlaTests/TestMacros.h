#pragma once
#include "Core/Macros.h"
#include "Core/Types.h"
#include "autogen/OlaConfig.h"
#include "gtest/gtest.h"

#define OLA_CODE(...) OLA_STRINGIFY(__VA_ARGS__)
#define OLA_CODE_EX(...) OLA_STRINGIFY(public int main(){__VA_ARGS__})

#ifdef DEBUG
#define OLA_EXE_PATH OLA_CONCAT(OLA_BINARY_PATH, "Debug/Ola.exe")
#define OLA(...) system(OLA_STRINGIFY(OLA_EXE_PATH --Od --test __VA_ARGS__))
#define OLA_SIMPLE(...) system(OLA_STRINGIFY(OLA_EXE_PATH --testdebug --test --simple OLA_CODE(__VA_ARGS__)))
#define OLA_EX_SIMPLE(...) system(OLA_STRINGIFY(OLA_EXE_PATH --testdebug --test --simple OLA_CODE_EX(__VA_ARGS__)))
#else 
#define OLA_EXE_PATH OLA_CONCAT(OLA_BINARY_PATH, "Release/Ola.exe")
#define OLA(...) system(OLA_STRINGIFY(OLA_EXE_PATH --O3 --test __VA_ARGS__))
#define OLA_SIMPLE(...) system(OLA_STRINGIFY(OLA_EXE_PATH --test --simple OLA_CODE(__VA_ARGS__)))
#define OLA_EX_SIMPLE(...) system(OLA_STRINGIFY(OLA_EXE_PATH --test --simple OLA_CODE_EX(__VA_ARGS__)))
#endif
