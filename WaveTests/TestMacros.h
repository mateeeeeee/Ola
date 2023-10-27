#pragma once
#include "Core/Defines.h"

#define USE_DEBUG 0

#define WAVE_CODE(...) WAVE_STRINGIFY(__VA_ARGS__)
#define WAVE_CODE_EX(...) WAVE_STRINGIFY(public int main(){__VA_ARGS__})

#if _DEBUG && USE_DEBUG
#define WAVE(...) system(WAVE_STRINGIFY(Wave --testdebug --test --directory Tests __VA_ARGS__))
#define WAVE_SIMPLE(...) system(WAVE_STRINGIFY(Wave --testdebug --test --simple WAVE_CODE(__VA_ARGS__)))
#define WAVE_EX_SIMPLE(...) system(WAVE_STRINGIFY(Wave --testdebug --test --simple WAVE_CODE_EX(__VA_ARGS__)))
#else 
#define WAVE(...) system(WAVE_STRINGIFY(Wave --test --directory Tests __VA_ARGS__))
#define WAVE_SIMPLE(...) system(WAVE_STRINGIFY(Wave --test --simple WAVE_CODE(__VA_ARGS__)))
#define WAVE_EX_SIMPLE(...) system(WAVE_STRINGIFY(Wave --test --simple WAVE_CODE_EX(__VA_ARGS__)))
#endif