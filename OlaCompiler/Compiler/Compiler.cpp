#include <filesystem>
#include <format>

#include "Compiler.h"
#include "CompileRequest.h"

#include "Frontend/Context.h"
#include "Frontend/Diagnostics.h"
#include "Frontend/SourceBuffer.h"
#include "Frontend/Lexer.h"
#include "Frontend/ImportProcessor.h"
#include "Frontend/Parser.h"
#include "Frontend/Sema.h"
#include "Backend/LLVM/LLVMIRGenContext.h"
#include "Backend/Custom/IR/IRGenContext.h"
#include "Backend/Custom/Codegen/MachineModule.h"
#include "Backend/Custom/Codegen/x64/x64Target.h"
#include "Utility/DebugVisitor.h"
#include "autogen/OlaConfig.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace fs = std::filesystem;

namespace ola
{
	namespace
	{
#if DEBUG
		static Char const* olalib = OLA_BINARY_PATH"Debug/olalib.lib";
#else 
		static Char const* olalib = OLA_BINARY_PATH"Release/olalib.lib";
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

		void CompileTranslationUnit(Context& context, std::string_view source_file, std::string_view ir_file, std::string_view assembly_file, OptimizationLevel opt_level, Bool use_llvm, Bool ast_dump)
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
				LLVMIRGenContext llvm_ir_gen(source_file);
				llvm_ir_gen.Generate(ast);
				llvm_ir_gen.Optimize(opt_level);
				llvm_ir_gen.EmitIR(ir_file);

				std::string compile_cmd = std::format("clang -S {} -o {} -masm=intel", ir_file, assembly_file);
				system(compile_cmd.c_str());
			}
			else
			{
				IRGenContext ir_gen(source_file);
				ir_gen.Generate(ast);
				ir_gen.Optimize(opt_level);
				ir_gen.EmitIR(ir_file);

				IRModule& module = ir_gen.GetModule();
				x64Target x64_target{};
				MachineModule machine_module(module, x64_target);
				machine_module.EmitAssembly(assembly_file.data());
			}
		}
	}

	Sint32 Compile(CompileRequest const& compile_request)
	{
		InitLogger();
		
		Bool const ast_dump = compile_request.GetCompilerFlags() & CompilerFlag_DumpAST;
		Bool const use_llvm = !(compile_request.GetCompilerFlags() & CompilerFlag_NoLLVM);
		OptimizationLevel opt_level = compile_request.GetOptimizationLevel();

		fs::path cur_path = fs::current_path();
		fs::current_path(compile_request.GetInputDirectory());

		std::vector<std::string> const& source_files = compile_request.GetSourceFiles();
		std::vector<std::string> object_files(source_files.size());
		std::string output_file = compile_request.GetOutputFile();
		
		switch (compile_request.GetOutputType())
		{
		case CompilerOutput::Exe:  output_file += ".exe"; break;
		case CompilerOutput::Dll:
		case CompilerOutput::Lib:
			OLA_ASSERT_MSG(false, "DLL and LIB outputs are not yet supported!");
		}

		Context context{};
		for (Uint64 i = 0; i < source_files.size(); ++i)
		{
			std::string file_name = fs::path(source_files[i]).stem().string();
			std::string file_ext = fs::path(source_files[i]).extension().string();

			std::string source_file = source_files[i]; source_file += ".ola";
			std::string ir_file;
			if(use_llvm) ir_file = file_name + ".ll";
			else ir_file = file_name + ".oll";
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
		link_cmd += " -Xlinker /SUBSYSTEM:CONSOLE";
		system(link_cmd.c_str());
		
		std::string const& exe_cmd = output_file;
		Sint64 res = system(exe_cmd.c_str());

		fs::current_path(cur_path);
		return res;
	}
}