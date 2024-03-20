#pragma once
#include "spdlog/spdlog.h"

namespace ola
{	
#define OLA_DEBUG(fmt, ...)  spdlog::debug(fmt, ##__VA_ARGS__)
#define OLA_INFO(fmt, ...)   spdlog::info(fmt, ##__VA_ARGS__)
#define OLA_WARN(fmt, ...)   spdlog::warn(fmt, ##__VA_ARGS__)
#define OLA_ERROR(fmt, ...)  spdlog::error(fmt, ##__VA_ARGS__)
}