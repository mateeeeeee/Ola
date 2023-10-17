#include <filesystem>
#include <format>
#include "Compiler.h"
#include "Frontend/Diagnostics.h"
#include "Frontend/SourceBuffer.h"
#include "Frontend/Lexer.h"
#include "Frontend/Parser.h"
#include "Frontend/Sema.h"
#include "Backend/LLVMIRGenerator.h"
#include "Utility/DebugVisitor.h"
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

			auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("wavelog.txt", true);
			file_sink->set_level(spdlog::level::trace);

			std::shared_ptr<spdlog::logger> lu_logger = std::make_shared<spdlog::logger>(std::string("wave logger"), spdlog::sinks_init_list{ console_sink, file_sink });
			lu_logger->set_level(spdlog::level::trace);
			spdlog::set_default_logger(lu_logger);

		}
		void AddBuiltins(SourceBuffer& src)
		{
			src.Prepend("");
		}

		void CompileTranslationUnit(std::string_view source_file, std::string_view ir_file, bool ast_dump)
		{
			Diagnostics diagnostics{};
			SourceBuffer src(source_file);
			AddBuiltins(src);
			Lexer lex(diagnostics, src);
			lex.Lex();

			Parser parser(diagnostics, lex.GetTokens());
			parser.Parse();
			AST const* ast = parser.GetAST();
			if (ast_dump) DebugVisitor debug_ast(ast);

			LLVMIRGenerator llvm_ir_generator(ir_file);
			llvm_ir_generator.Generate(ast);
		}
	}

	int32 Compile(CompilerInput const& input)
	{
		InitLogger();

		bool const ast_dump = input.flags & CompilerFlag_DumpAST;
		bool const output_assembly = input.flags & CompilerFlag_OutputAssembly;
		bool const use_llvm = !(input.flags & CompilerFlag_NoLLVM);
		WAVE_ASSERT_MSG(use_llvm, "Only LLVM is supported for code generation");

		fs::path directory_path = input.input_directory;
		std::vector<fs::path> assembly_files(input.sources.size());
		std::vector<fs::path> object_files(input.sources.size());
		fs::path output_file = directory_path /input.output_file; output_file += ".exe";
		int64 res;
		for (uint64 i = 0; i < input.sources.size(); ++i)
		{
			fs::path file_name = fs::path(input.sources[i]).stem();
			fs::path file_ext = fs::path(input.sources[i]).extension();

			fs::path ir_file = directory_path / file_name; ir_file += ".ll";
			fs::path source_file = directory_path / input.sources[i];

			CompileTranslationUnit(source_file.string(), ir_file.string(), ast_dump);

			fs::path assembly_file = directory_path / file_name;  assembly_file += ".s";
			fs::path object_file = directory_path / file_name; object_file += ".obj";

			object_files[i] = object_file;
			assembly_files[i] = assembly_file;

			std::string compile_cmd = std::format("clang -S {} -o {}", ir_file.string(), assembly_file.string());
			system(compile_cmd.c_str());

			std::string assembly_cmd = std::format("clang -c {} -o {}", assembly_file.string(), object_file.string());
			system(assembly_cmd.c_str());
		}
		std::string link_cmd = "clang "; 
		for (auto const& obj_file : object_files) link_cmd += obj_file.string() + " ";
		link_cmd += "-o " + output_file.string();
		system(link_cmd.c_str());
		
		std::string const& exe_cmd = output_file.string();
		res = system(exe_cmd.c_str());
		return res;
	}

	int32 CompileTest(std::string_view input, bool debug)
	{
		InitLogger();
		std::string code(input);

		fs::path tmp_directory = std::filesystem::current_path() / "Tmp";
		fs::create_directory(tmp_directory);

		fs::path file_name = "tmp";
		fs::path ir_file = tmp_directory / file_name; ir_file += ".ll";
		fs::path assembly_file	= tmp_directory / file_name; assembly_file += ".s";
		fs::path output_file	= tmp_directory / file_name; output_file += ".exe";

		//compilation
		{
			Diagnostics diagnostics{};
			SourceBuffer src(code.data(), code.size());
			AddBuiltins(src);
			Lexer lex(diagnostics, src);
			lex.Lex();

			Parser parser(diagnostics, lex.GetTokens());
			parser.Parse();

			AST const* ast = parser.GetAST();
			if (debug) DebugVisitor debug_ast(ast);

			LLVMIRGenerator llvm_ir_generator(ir_file.string());
			llvm_ir_generator.Generate(ast);
		}
		std::string compile_cmd = std::format("clang -S {} -o {}", ir_file.string(), assembly_file.string());
		system(compile_cmd.c_str());

		std::string assembly_cmd = std::format("clang {} -o {}", assembly_file.string(), output_file.string());
		system(assembly_cmd.c_str());

		std::string exe_cmd = std::format("{}", output_file.string());
		int32 exitcode = system(exe_cmd.c_str());
		fs::remove_all(tmp_directory);
		return exitcode;
	}

}