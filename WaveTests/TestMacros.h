#pragma once
#include "Core/Defines.h"


#define WAVE_CODE(...) WAVE_STRINGIFY(__VA_ARGS__)
#define WAVE_CODE_EX(...) WAVE_STRINGIFY(fn main() -> int {__VA_ARGS__})

#define WAVE_EX(...) system(WAVE_STRINGIFY(Wave --test -t WAVE_CODE_EX(__VA_ARGS__)))
#define WAVE_EX_DEBUG(...) system(WAVE_STRINGIFY(Wave --debug --test -t WAVE_CODE_EX(__VA_ARGS__)))

#define WAVE(...) system(WAVE_STRINGIFY(Wave --test -t WAVE_CODE(__VA_ARGS__)))
#define WAVE_DEBUG(...) system(WAVE_STRINGIFY(Wave --debug --test -t WAVE_CODE(__VA_ARGS__)))
