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
		fs::path output_file(input.output_file);
		output_file += ".exe";
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

			//llc input.ll -o output.s
			

			//clang input.s - o my_program
			std::string cmd2 = std::format("clang {} -o {}", assembly_file.string(), output_file.string());
			system(cmd2.c_str());

			if (output_assembly)
			{
				std::string asm_cmd = std::format("clang -S {} -o {}", ir_file.string(), assembly_file.string());
				system(asm_cmd.c_str());


				//llvm-ir -> assembly 
				//assembly -> object file
			}
			else
			{
				//llvm-ir -> object file
			}
		}

		int64 res = system(output_file.string().c_str());;

		//link all object files produced
		//call exe
		return res;
	}
}