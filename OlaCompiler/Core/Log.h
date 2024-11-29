#pragma once
#include <format>
#include <string>
#include <cstdio>

namespace ola
{
	enum class LogLevel : Uint8
	{
		Debug,
		Info,
		Warning,
		Error
	};
	std::string GetLogPrefix(LogLevel level);
	std::string GetCurrentTimeString();

	void LogInit();
	void LogDestroy();
	void WriteToLogFile(std::string const&);

	template<typename... Args>
	void Log(LogLevel level, char const* fmt, Args&&... args)
	{
		std::string log_entry = std::vformat(fmt, std::make_format_args(args...));
		std::string full_log_entry = std::format("{} {} {}", GetCurrentTimeString(), GetLogPrefix(level), log_entry);
		printf("%s\n", full_log_entry.c_str());
		WriteToLogFile(full_log_entry);
	}
}

#if defined(DEBUG)
#define OLA_DEBUG(fmt, ...)		ola::Log(ola::LogLevel::Debug, fmt, __VA_ARGS__)
#define OLA_INFO(fmt, ...)		ola::Log(ola::LogLevel::Info, fmt, __VA_ARGS__)
#define OLA_WARN(fmt, ...)	ola::Log(ola::LogLevel::Warning, fmt, __VA_ARGS__)
#else 
#define OLA_DEBUG(fmt, ...)		
#define OLA_INFO(fmt, ...)		
#define OLA_WARN(fmt, ...)	
#endif
#define OLA_ERROR(fmt, ...)		ola::Log(ola::LogLevel::Error, fmt, __VA_ARGS__)