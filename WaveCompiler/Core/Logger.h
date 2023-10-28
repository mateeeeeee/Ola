#pragma once
#include "spdlog/spdlog.h"

namespace wave
{	
#define WAVE_DEBUG(fmt, ...)  spdlog::debug(fmt, __VA_ARGS__)
#define WAVE_INFO(fmt, ...)   spdlog::info(fmt, __VA_ARGS__)
#define WAVE_WARN(fmt, ...)   spdlog::warn(fmt, __VA_ARGS__)
#define WAVE_ERROR(fmt, ...)  spdlog::error(fmt, __VA_ARGS__)
}