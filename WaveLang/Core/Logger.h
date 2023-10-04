#pragma once
#include "spdlog/spdlog.h"

namespace lucc
{	
#define LU_DEBUG(fmt, ...)  spdlog::debug(fmt, __VA_ARGS__)
#define LU_INFO(fmt, ...)   spdlog::info(fmt, __VA_ARGS__)
#define LU_WARN(fmt, ...)   spdlog::warn(fmt, __VA_ARGS__)
#define LU_ERROR(fmt, ...)  spdlog::error(fmt, __VA_ARGS__)
}