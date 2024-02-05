#include <filesystem>
#include <format>

#include "Compiler.h"

#include "Frontend/Context.h"
#include "Frontend/Diagnostics.h"
#include "Frontend/SourceBuffer.h"
#include "Frontend/Lexer.h"
#include "Frontend/ImportProcessor.h"
#include "Frontend/Parser.h"
#include "Frontend/Sema.h"

#include "Backend/LLVM/LLVMIRGen.h"
#include "Backend/Custom/IR/IRGen.h"
#include "Backend/Custom/Codegen/MachineCodeGen.h"

#include "Utility/DebugVisitor.h"
#include "Utility/Managed.h"
#include "autogen/OlaConfig.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace fs = std::filesystem;

namespace ola
{
	namespace
	{
#if OLA_DEBUG_BUILD
		static char const* olalib = OLA_BINARY_PATH"Debug/olalib.lib";
#else 
		static char const* olalib = OLA_BINARY_PATH"Release/olalib.lib";
#endif
		void InitLogger()
		{
			auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			console_sink->set_level(spdlog::level::trace);
			console_sink->set_pattern("[%^%l%$] %v");

			std::shared_ptr<spdlog::logger> ola_logger = std::make_shared<spdlog::logger>(std::string("ola logger"), spdlog::sinks_init_list{ console_sink });
			ola_logger->set_level(spdlog::level::trace);
			spdlog::set_default_logger(ola_logger);
		}
		void AddBuiltins(SourceBuffer& src)
		{
			src.Prepend("");
		}
		OptimizationLevel GetOptimizationLevelFromFlags(CompilerFlags flags)
		{
			if (flags & CompilerFlag_O0) return OptimizationLevel::O0;
			if (flags & CompilerFlag_O1) return OptimizationLevel::O1;
			if (flags & CompilerFlag_O2) return OptimizationLevel::O2;
			if (flags & CompilerFlag_O3) return OptimizationLevel::O3;
			return OptimizationLevel::O0;
		}

		void CompileTranslationUnit(Context& context, std::string_view source_file, std::string_view ir_file, std::string_view assembly_file, OptimizationLevel opt_level, bool use_llvm, bool ast_dump)
		{
			Diagnostics diagnostics{};
			SourceBuffer src(source_file);
			AddBuiltins(src);
			Lexer lex(diagnostics);
			lex.Lex(src);

			ImportProcessor import_processor(&context, diagnostics);
			import_processor.ProcessImports(lex.GetTokens());

			Parser parser(&context, diagnostics);
			parser.Parse(import_processor.GetProcessedTokens());
			AST const* ast = parser.GetAST();
			if (ast_dump) DebugVisitor debug_ast(ast);

			if (use_llvm)
			{
				LLVMIRGen llvm_ir_gen(source_file);
				llvm_ir_gen.Generate(ast);
				llvm_ir_gen.Optimize(opt_level);
				llvm_ir_gen.PrintIR(ir_file);

				std::string compile_cmd = std::format("clang -S {} -o {} -masm=intel", ir_file, assembly_file);
				system(compile_cmd.c_str());
			}
			else
			{
				IRGen ir_gen(source_file);
				ir_gen.Generate(ast);
				ir_gen.PrintIR(ir_file);
				MachineCodeGen machine_codegen(MachineArch::x64, ir_gen.GetModule());
				machine_codegen.Generate(assembly_file);
				ManagedRegistry::Cleanup();
			}
		}
	}

	int32 Compile(CompilerInput const& input)
	{
		InitLogger();
		bool const ast_dump = input.flags & CompilerFlag_DumpAST;
		bool const use_llvm = !(input.flags & CompilerFlag_NoLLVM);
		OptimizationLevel opt_level = GetOptimizationLevelFromFlags(input.flags);

		fs::path cur_path = fs::current_path();
		fs::current_path(input.input_directory);

		std::vector<std::string> object_files(input.sources.size());
		std::string output_file = input.output_file; output_file += ".exe";

		Context context{};
		for (uint64 i = 0; i < input.sources.size(); ++i)
		{
			std::string file_name = fs::path(input.sources[i]).stem().string();
			std::string file_ext = fs::path(input.sources[i]).extension().string();

			std::string source_file = input.sources[i]; source_file += ".ola";
			std::string ir_file = file_name + ".ll";
			std::string assembly_file = file_name + ".s";

			CompileTranslationUnit(context, source_file, ir_file, assembly_file, opt_level, use_llvm, ast_dump);

			std::string object_file = file_name + ".obj";  
			object_files[i] = object_file;
			std::string assembly_cmd = std::format("clang -c {} -o {}", assembly_file, object_file);
			system(assembly_cmd.c_str());
		}
		
		std::string link_cmd = "clang "; 
		for (auto const& obj_file : object_files) link_cmd += obj_file + " ";
		link_cmd += olalib;
		link_cmd += " -o " + output_file;
		link_cmd += " -Xlinker /SUBSYSTEM:CONSOLE ";
		system(link_cmd.c_str());
		
		std::string const& exe_cmd = output_file;
		int64 res = system(exe_cmd.c_str());

		fs::current_path(cur_path);
		return res;
	}

	int32 CompileSimple(std::string_view input, bool debug)
	{
		InitLogger();
		std::string code(input);

		fs::path tmp_directory = std::filesystem::current_path() / "Tmp";
		fs::create_directory(tmp_directory);

		fs::path file_name = "tmp";
		fs::path ir_file = tmp_directory / file_name; ir_file += ".ll";
		fs::path assembly_file	= tmp_directory / file_name; assembly_file += ".s";
		fs::path output_file	= tmp_directory / file_name; output_file += ".exe";

		{
			Diagnostics diagnostics{};
			SourceBuffer src(code.data(), code.size());
			AddBuiltins(src);
			src.Prepend("import std.assert;\n");
			Lexer lex(diagnostics);
			lex.Lex(src);

			Context context{};
			Parser parser(&context, diagnostics);
			parser.Parse(lex.GetTokens());

			AST const* ast = parser.GetAST();
			if (debug) DebugVisitor debug_ast(ast);

			LLVMIRGen llvm_ir_generator("tmp.ola");
			llvm_ir_generator.Generate(ast);
			llvm_ir_generator.Optimize(debug ? OptimizationLevel::Od : OptimizationLevel::O3);
			llvm_ir_generator.PrintIR(ir_file.string());

			std::string compile_cmd = std::format("clang -S {} -o {} -masm=intel", ir_file.string(), assembly_file.string());
			system(compile_cmd.c_str());
		}

		std::string assembly_cmd = std::format("clang {} -o {}", assembly_file.string(), output_file.string());
		system(assembly_cmd.c_str());

		std::string exe_cmd = std::format("{}", output_file.string());
		int32 exitcode = system(exe_cmd.c_str());
		fs::remove_all(tmp_directory);
		return exitcode;
	}

}