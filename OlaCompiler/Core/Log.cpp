#include <chrono>
#include <iostream>
#include "Log.h"

namespace ola
{
	static FILE* gLogFile = nullptr;

	std::string GetLogPrefix(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::Debug:	return "[DEBUG]";
		case LogLevel::Info:	return "[INFO]";
		case LogLevel::Warning: return "[WARNING]";
		case LogLevel::Error:	return "[ERROR]";
		}
		return "";
	}
	std::string GetCurrentTimeString()
	{
		auto now = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(now);
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

		std::tm* localTime = std::localtime(&in_time_t);
		Char timestamp[64];
		std::snprintf(timestamp, sizeof(timestamp), "[%04d-%02d-%02d %02d:%02d:%02d.%03d]",
			localTime->tm_year + 1900,
			localTime->tm_mon + 1,
			localTime->tm_mday,
			localTime->tm_hour,
			localTime->tm_min,
			localTime->tm_sec,
			static_cast<Int>(ms.count()));

		return timestamp;
	}

	void LogInit()
	{
		if (!gLogFile)
		{
			static Char const* gLogFileName = "olalog.txt";
			gLogFile = fopen(gLogFileName, "w+");
			setbuf(gLogFile, nullptr);
		}
		setbuf(stdout, nullptr);
	}

	void LogDestroy()
	{
		if (gLogFile)
		{
			fclose(gLogFile);
		}
	}

	void WriteToLogFile(std::string const& log_entry)
	{
		if (gLogFile)
		{
			fprintf(gLogFile, "%s\n", log_entry.c_str());
		}
	}

}