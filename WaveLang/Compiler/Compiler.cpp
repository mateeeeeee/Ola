#include <filesystem>
#include <format>
#include "Compiler.h"
#include "Frontend/Diagnostics.h"
#include "Frontend/SourceBuffer.h"
#include "Frontend/Lexer.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace fs = std::filesystem;

namespace wave
{
	namespace
	{
		void InitLogger()
		{
			auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			console_sink->set_level(spdlog::level::trace);
			console_sink->set_pattern("[%^%l%$] %v");

			auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("lu_log.txt", true);
			file_sink->set_level(spdlog::level::trace);

			std::shared_ptr<spdlog::logger> lu_logger = std::make_shared<spdlog::logger>(std::string("lucc logger"), spdlog::sinks_init_list{ console_sink, file_sink });
			lu_logger->set_level(spdlog::level::trace);
			spdlog::set_default_logger(lu_logger);

		}
		void AddBuiltins(SourceBuffer& src)
		{
			src.Prepend("#define NULL (void*)0\n");
		}
	}

	int32 Compile(CompilerInput const& input)
	{
		return 0;
	}
}