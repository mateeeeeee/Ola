#include <filesystem>
#include <format>
#include "Compiler.h"
#include "Frontend/Diagnostics.h"
#include "Frontend/SourceBuffer.h"
#include "Frontend/Lexer.h"
#include "Frontend/Parser.h"
#include "Frontend/Sema.h"
#include "Utility/Debug.h"
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
			src.Prepend("");
		}

		void CompileTranslationUnit(std::string_view source_filename, bool ast_dump)
		{
			SourceBuffer src(source_filename);
			AddBuiltins(src);
			Lexer lex(src);
			lex.Lex();

			Parser parser(lex.GetTokens());
			parser.Parse();
			AST* ast = parser.GetAST();
			if (ast_dump) DebugNodeVisitorAST debug_ast(ast);

			//llvmCodegen llvm(ast);
			//write llvm
		}
	}

	int32 Compile(CompilerInput const& input)
	{
		InitLogger();
		diag::Initialize();

		bool const ast_dump = input.flags & CompilerFlag_DumpAST;
		bool const use_llvm = !(input.flags & CompilerFlag_NoLLVM);
		WAVE_ASSERT_MSG(use_llvm, "Only LLVM is supported for code generation");

		fs::path directory_path = input.input_directory;
		std::vector<fs::path> object_files(input.sources.size());
		for (uint64 i = 0; i < input.sources.size(); ++i)
		{
			fs::path file_name = fs::path(input.sources[i]).stem();
			fs::path file_ext = fs::path(input.sources[i]).extension();
			fs::path assembly_file = directory_path / file_name;  assembly_file += ".asm";
			fs::path object_file = directory_path / file_name; object_file += ".obj";
			fs::path source_file = directory_path / input.sources[i];

			CompileTranslationUnit(source_file.string(), ast_dump);
			object_files[i] = object_file;
		}
		return 0;
	}
}