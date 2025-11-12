#include <filesystem>
#include <format>
#include "Compiler.h"
#include "CompilerMacros.h"
#include "CompileRequest.h"
#include "Core/Log.h"
#include "Frontend/FrontendContext.h"
#include "Frontend/Diagnostics.h"
#include "Frontend/SourceBuffer.h"
#include "Frontend/Lexer.h"
#include "Frontend/ImportProcessor.h"
#include "Frontend/Parser.h"
#include "Frontend/Sema.h"
#include "Backend/Custom/IR/IRGenContext.h"
#include "Backend/Custom/IR/IRPassManager.h"
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/Codegen/MachineModule.h"
#include "Backend/Custom/Codegen/x64/Microsoft/Microsoft_x64Target.h"
#include "Backend/Custom/Codegen/x64/SysV/SysV_x64Target.h"
#include "Backend/Custom/Codegen/Arm64/ARM64Target.h"
#include "Utility/DebugVisitor.h"
#include "Utility/Command.h"
#include "autogen/OlaConfig.h"
#if HAS_LLVM
#include "Backend/LLVM/LLVMIRGenContext.h"
#include "Backend/LLVM/LLVMIRPassManager.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"
#endif

namespace fs = std::filesystem;

namespace ola
{
	namespace
	{
		void GenerateGraphVizImages(std::string const& folder_path, Bool is_llvm)
		{
			for (auto const& entry : fs::directory_iterator(folder_path))
			{
				if (entry.path().extension() == ".dot") 
				{
					std::string dot_file = entry.path().string();
					std::string output_image = dot_file.substr(0, dot_file.find_last_of('.')) + ".png";
					std::string command = std::format("dot -Tpng {} -o {}", dot_file, output_image);
					Int result = ExecuteCommand(command.c_str());
				}
			}
		}

		struct TUCompilationOptions
		{
			OptimizationLevel opt_level;
			TargetArch target_arch;
			Bool use_llvm_backend;
			Bool dump_ast;
			Bool dump_cfg;
			Bool dump_callgraph;
			Bool dump_domtree;
			Bool print_domfrontier;
		};

		void CompileTranslationUnit(FrontendContext& context,
			std::string_view source_file, std::string_view ir_file, std::string_view mir_file, std::string_view assembly_file,
			TUCompilationOptions const& opts)
		{
			Diagnostics diagnostics{};
			SourceBuffer src(source_file);
			Lexer lex(diagnostics);
			lex.Lex(src);

			ImportProcessor import_processor(&context, diagnostics);
			import_processor.ProcessImports(lex.GetTokens());

			Parser parser(&context, diagnostics);
			parser.Parse(import_processor.GetProcessedTokens());
			AST const* ast = parser.GetAST();
			if (opts.dump_ast) DebugVisitor debug_ast(ast);

			if (opts.use_llvm_backend)
			{
#if HAS_LLVM
				LLVMIRGenContext llvmir_gen_ctx(source_file);
				llvmir_gen_ctx.Generate(ast);

				llvm::Module& llvm_module = llvmir_gen_ctx.GetModule();
				LLVMIRPassManager llvmir_pass_manager(llvm_module);
				LLVMIRPassOptions pass_opts{ .domfrontier_print = opts.print_domfrontier };
				llvmir_pass_manager.Run(opts.opt_level, pass_opts);

				if (opts.dump_cfg)
				{
					std::string dot_cfg_cmd = std::format("opt -passes=dot-cfg -disable-output {}", ir_file);
					ExecuteCommand(dot_cfg_cmd.c_str());
				}
				if (opts.dump_callgraph)
				{
					std::string dot_allgraph_cmd = std::format("opt -passes=dot-callgraph -disable-output {}", ir_file);
					ExecuteCommand(dot_allgraph_cmd.c_str());
				}
				if (opts.dump_domtree)
				{
					std::string dot_domtree_cmd = std::format("opt -passes=dot-dom-only -disable-output {}", ir_file);
					ExecuteCommand(dot_domtree_cmd.c_str());
				}

				std::error_code error;
				llvm::raw_fd_ostream llvm_ir_stream(ir_file, error, llvm::sys::fs::OF_None);
				if (error)
				{
					OLA_ERROR("Error when creating llvm::raw_fd_ostream: {}", error.message());
					return;
				}
				llvm_module.print(llvm_ir_stream, nullptr);

				std::string compile_cmd = std::format("clang -S {} -o {} -masm=intel", ir_file, assembly_file);
				ExecuteCommand(compile_cmd.c_str());
#else
				OLA_ASSERT_MSG(false, "LLVM backend is disabled. Use --nollvm or generate project with -DENABLE_LLVM=ON assuming you have LLVM 17.0 installed");
#endif
			}
			else
			{
				IRGenContext ir_gen_ctx(source_file);
				ir_gen_ctx.Generate(ast);
				IRModule& ir_module = ir_gen_ctx.GetModule();

				FunctionAnalysisManager analysis_manager;
				IRPassManager ir_pass_manager(ir_module, analysis_manager);
				IRPassOptions pass_opts
				{
					.cfg_print = opts.dump_cfg,
					.domtree_print = opts.dump_domtree,
					.domfrontier_print = opts.print_domfrontier
				};
				ir_pass_manager.Run(opts.opt_level, pass_opts);

				ir_module.Print(ir_file);

				Target* x64_target = nullptr;
				Microsoft_x64Target ms_target{};
				SysV_x64Target sysv_target{};
				ARM64Target arm64_target{};

				switch (opts.target_arch)
				{
				case TargetArch::x64:
#if defined(OLA_PLATFORM_WINDOWS)
					x64_target = &ms_target;
#else
					x64_target = &sysv_target;
#endif
					break;
				case TargetArch::ARM64:
					x64_target = &arm64_target;
					break;
				default:
					OLA_ASSERT_MSG(false, "Invalid target architecture!");
					break;
				}

				MachineModule machine_module(ir_module, *x64_target, analysis_manager);
				if(!mir_file.empty())
				{
					machine_module.EmitMIR(mir_file);
				}
				machine_module.EmitAssembly(assembly_file);
			}
		}
	}

	Int Compile(CompileRequest const& compile_request)
	{
		Bool const ast_dump = compile_request.GetCompilerFlags() & CompilerFlag_DumpAST;
		Bool const cfg_dump = compile_request.GetCompilerFlags() & CompilerFlag_DumpCFG;
		Bool const callgraph_dump = compile_request.GetCompilerFlags() & CompilerFlag_DumpCallGraph;
		Bool const domtree_dump = compile_request.GetCompilerFlags() & CompilerFlag_DumpDomTree;
		Bool const no_llvm = compile_request.GetCompilerFlags() & CompilerFlag_NoLLVM;
		Bool const emit_ir = compile_request.GetCompilerFlags() & CompilerFlag_EmitIR;
		Bool const emit_mir = compile_request.GetCompilerFlags() & CompilerFlag_EmitMIR;
		Bool const emit_asm = compile_request.GetCompilerFlags() & CompilerFlag_EmitASM;
		Bool const print_domfrontier = compile_request.GetCompilerFlags() & CompilerFlag_PrintDomFrontier;
		Bool const timeout_detection = compile_request.GetCompilerFlags() & CompilerFlag_TimeoutDetection;
		Bool const no_run = compile_request.GetCompilerFlags() & CompilerFlag_NoRun;
		OptimizationLevel opt_level = compile_request.GetOptimizationLevel();

		fs::path cur_path = fs::current_path();
		std::string input_directory(compile_request.GetInputDirectory());
		if(!input_directory.empty()) fs::current_path(input_directory);

		std::vector<std::string> const& source_files = compile_request.GetSourceFiles();
		std::vector<std::string> object_files(source_files.size());
		std::string output_file = compile_request.GetOutputFile();
#if defined(OLA_PLATFORM_WINDOWS)
		output_file += ".exe";
#endif

		TargetArch target_arch = compile_request.GetTargetArch();
		if (target_arch == TargetArch::Default)
		{
#if defined(OLA_PLATFORM_WINDOWS)
			target_arch = TargetArch::x64;
#elif defined(OLA_PLATFORM_MACOS)
			target_arch = TargetArch::ARM64;
#else
			target_arch = TargetArch::x64;
#endif
		}

		FrontendContext context{};
		for (Uint64 i = 0; i < source_files.size(); ++i)
		{
			std::string file_name = fs::path(source_files[i]).stem().string();
			std::string file_ext = fs::path(source_files[i]).extension().string();

			std::string source_file = source_files[i]; source_file += ".ola";
			std::string ir_file;
			if (no_llvm) ir_file = file_name + ".oll";
			else		 ir_file = file_name + ".ll";
			std::string assembly_file = file_name + ".s";
			std::string mir_file = emit_mir ? file_name + ".omll" : "";

			TUCompilationOptions tu_comp_opts
			{
				.opt_level = opt_level,
				.target_arch = target_arch,
				.use_llvm_backend = !no_llvm,
				.dump_ast = ast_dump,
				.dump_cfg = cfg_dump,
				.dump_callgraph = callgraph_dump,
				.dump_domtree = domtree_dump,
				.print_domfrontier = print_domfrontier,
			};
			CompileTranslationUnit(context, source_file, ir_file, mir_file, assembly_file, tu_comp_opts);

			std::string object_file = file_name + ".obj";
			object_files[i] = object_file;
			std::string assembly_cmd = "clang -c ";
#if defined(OLA_PLATFORM_MACOS)
			if (target_arch == TargetArch::x64)
			{
				assembly_cmd += "-arch x86_64 ";
			}
			else if (target_arch == TargetArch::ARM64)
			{
				assembly_cmd += "-arch arm64 ";
			}
#endif
			assembly_cmd += std::format("{} -o {}", assembly_file, object_file);
			Int assembly_exit_code = ExecuteCommand(assembly_cmd.c_str());

			if (!emit_ir)
			{
				Bool deleted = fs::remove(ir_file);
				OLA_ASSERT(deleted);
			}
			if (!emit_asm)
			{
				Bool deleted = fs::remove(assembly_file);
				OLA_ASSERT(deleted);
			}

			if (assembly_exit_code != 0)
			{
				return OLA_INVALID_ASSEMBLY_CODE;
			}
		}

		if (cfg_dump || callgraph_dump || domtree_dump)
		{
			GenerateGraphVizImages(input_directory, !no_llvm);
		}

		Bool const build_static_lib = compile_request.GetCompilerFlags() & CompilerFlag_StaticLib;
		if (build_static_lib)
		{
			std::string lib_output = output_file;
#if defined(OLA_PLATFORM_WINDOWS)
			if (!lib_output.ends_with(".lib"))
			{
				lib_output += ".lib";
			}
			std::string ar_cmd = "lib /OUT:" + lib_output + " ";
#else
			if (!lib_output.ends_with(".a"))
			{
				lib_output += ".a";
			}
			std::string ar_cmd = "ar rcs " + lib_output + " ";
#endif
			for (auto const& obj_file : object_files) ar_cmd += obj_file + " ";
			ExecuteCommand(ar_cmd.c_str());
		}
		else
		{
			// Link executable
			std::string link_cmd = "clang ";
#if defined(OLA_PLATFORM_MACOS)
			if (target_arch == TargetArch::x64)
			{
				link_cmd += "-arch x86_64 ";
			}
			else if (target_arch == TargetArch::ARM64)
			{
				link_cmd += "-arch arm64 ";
			}
#endif
			for (auto const& obj_file : object_files) link_cmd += obj_file + " ";

			auto const& libraries = compile_request.GetLibraries();
			for (auto const& lib : libraries) link_cmd += lib + " ";

			link_cmd += OLA_STATIC_LIB_PATH;
			link_cmd += " -o " + output_file;
#if defined(OLA_PLATFORM_WINDOWS)
			link_cmd += " -Xlinker /SUBSYSTEM:CONSOLE";
#endif
			ExecuteCommand(link_cmd.c_str());
		}

		Int res = 0;
		if (!no_run)
		{
			std::string exe_cmd = output_file;
#if !defined(OLA_PLATFORM_WINDOWS)
			// Prefix with ./ if it's a relative path without directory separators
			if (exe_cmd.find('/') == std::string::npos)
			{
				exe_cmd = "./" + exe_cmd;
			}
#endif
#if defined(OLA_PLATFORM_MACOS)
			// Use Rosetta 2 to run x64 executables on macOS (Apple Silicon)
			if (target_arch == TargetArch::x64)
			{
				exe_cmd = "arch -x86_64 " + exe_cmd;
			}
#endif
			res = timeout_detection ? ExecuteCommand_NonBlocking(exe_cmd.c_str(), 1.0f) : ExecuteCommand(exe_cmd.c_str());
			OLA_INFO("Program exited with code: {}", res);
		}
		fs::current_path(cur_path);
		return res;

	}
}