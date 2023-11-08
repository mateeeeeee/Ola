#pragma once
#include "Core/Defines.h"
#include "Core/CoreTypes.h"
#include "autogen/WaveConfig.h"
#include "gtest/gtest.h"

#define USE_DEBUG 0

#define WAVE_CODE(...) WAVE_STRINGIFY(__VA_ARGS__)
#define WAVE_CODE_EX(...) WAVE_STRINGIFY(public int main(){__VA_ARGS__})

#if _DEBUG && USE_DEBUG
#define WAVE_EXE_PATH WAVE_CONCAT(WAVE_BINARY_PATH, "Debug/Wave.exe")
#define WAVE(...) system(WAVE_STRINGIFY(Wave --Od --test __VA_ARGS__))
#define WAVE_SIMPLE(...) system(WAVE_STRINGIFY(Wave --testdebug --test --simple WAVE_CODE(__VA_ARGS__)))
#define WAVE_EX_SIMPLE(...) system(WAVE_STRINGIFY(Wave --testdebug --test --simple WAVE_CODE_EX(__VA_ARGS__)))
#else 
#define WAVE_EXE_PATH WAVE_CONCAT(WAVE_BINARY_PATH, "Release/Wave.exe")
#define WAVE(...) system(WAVE_STRINGIFY(WAVE_EXE_PATH --O3 --test __VA_ARGS__))
#define WAVE_SIMPLE(...) system(WAVE_STRINGIFY(WAVE_EXE_PATH --test --simple WAVE_CODE(__VA_ARGS__)))
#define WAVE_EX_SIMPLE(...) system(WAVE_STRINGIFY(WAVE_EXE_PATH --test --simple WAVE_CODE_EX(__VA_ARGS__)))
#endif