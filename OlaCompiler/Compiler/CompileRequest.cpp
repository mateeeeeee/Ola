#include "CompileRequest.h"
#include "Core/Log.h"
#include "Utility/CLIParser.h"
#include "autogen/OlaConfig.h"

namespace ola
{
	Bool CompileRequest::Parse(Int argc, Char** argv)
	{
		CLIParser cli_parser{};
		{
			cli_parser.AddArg(false, "-h", "--help");
			cli_parser.AddArg(false, "--ast");
			cli_parser.AddArg(false, "--cfg");
			cli_parser.AddArg(false, "--callgraph");
			cli_parser.AddArg(false, "--domtree");
			cli_parser.AddArg(false, "--domfrontier");
			cli_parser.AddArg(false, "--emit-ir");
			cli_parser.AddArg(false, "--emit-mir");
			cli_parser.AddArg(false, "--emit-asm");
			cli_parser.AddArg(false, "--nollvm");
			cli_parser.AddArg(false, "--test");
			cli_parser.AddArg(false, "--timeout");
			cli_parser.AddArg(false, "-c", "--no-run");
			cli_parser.AddArg(false, "--Od");
			cli_parser.AddArg(false, "--O0");
			cli_parser.AddArg(false, "--O1");
			cli_parser.AddArg(false, "--O2");
			cli_parser.AddArg(false, "--O3");
			cli_parser.AddArg(true, "-i", "--input");
			cli_parser.AddArg(true, "--directory");
			cli_parser.AddArg(true, "-o", "--output");
			cli_parser.AddArg(true, "--target");
			cli_parser.AddArg(false, "--lib");
			cli_parser.AddArg(true, "-l");
		}
		CLIParseResult cli_result = cli_parser.Parse(argc, argv);

		if(cli_result["-h"])
		{
			OLA_INFO("Ola Compiler");
			OLA_INFO("Usage: ola-compiler [options]");
			OLA_INFO("Options:");
			OLA_INFO("  -h, --help               Show this help message");
			OLA_INFO("  -i, --input <files>      Input Ola source files");
			OLA_INFO("  -o, --output <file>      Output file name");
			OLA_INFO("      --directory <dir>    Input directory for test mode");
			OLA_INFO("      --ast                Dump Abstract Syntax Tree (AST)");
			OLA_INFO("      --cfg                Dump Control Flow Graph (CFG)");
			OLA_INFO("      --callgraph          Dump Call Graph");
			OLA_INFO("      --domtree            Dump Dominator Tree");
			OLA_INFO("      --domfrontier        Print Dominance Frontier");
			OLA_INFO("      --emit-ir            Emit IR");
			OLA_INFO("      --emit-mir           Emit Machine IR");
			OLA_INFO("      --emit-asm           Emit Assembly code");
			OLA_INFO("      --nollvm            Disable LLVM backend");
			OLA_INFO("      --test               Enable test mode with predefined test cases");
			OLA_INFO("      --timeout            Enable timeout detection");
			OLA_INFO("  -c, --no-run             Compile only, do not run the output");
			OLA_INFO("      --Od                 Optimization level: O0 (disable optimizations)");
			OLA_INFO("      --O0                 Optimization level: O0 (disable optimizations)");
			OLA_INFO("      --O1                 Optimization level: O1");
			OLA_INFO("      --O2                 Optimization level: O2");
			OLA_INFO("      --O3                 Optimization level: O3");
			OLA_INFO("      --target <arch>      Target architecture (x64, arm64)");
			OLA_INFO("      --lib                Build as static library");
			OLA_INFO("  -l <libs>                Libraries to link against");
			return false;
		}

		input_files = cli_result["-i"].AsStrings();
		output_file = cli_result["-o"].AsStringOr("");
		input_directory = cli_result["--directory"].AsStringOr("");
		if (cli_result["--test"])
		{
			if (!input_files.empty())
			{
				if (output_file.empty())
				{
					output_file = input_files[0];
				}
				if (cli_result["--nollvm"])
				{
					input_directory = OLA_TESTS_PATH"Tests/Custom";
				}
				else
				{
					input_directory = OLA_TESTS_PATH"Tests/LLVM";
				}
			}
			else
			{
				OLA_WARN("No test input files provided!");
				return false;
			}
		}

		if (input_files.empty())
		{
			OLA_WARN("No input files provided!");
			return false;
		}
		if (output_file.empty())
		{
			output_file = input_files[0];
		}

		if (cli_result["--ast"])				compiler_flags |= CompilerFlag_DumpAST;
		if (cli_result["--nollvm"])				compiler_flags |= CompilerFlag_NoLLVM;
		if (cli_result["--cfg"])				compiler_flags |= CompilerFlag_DumpCFG;
		if (cli_result["--callgraph"])			compiler_flags |= CompilerFlag_DumpCallGraph;
		if (cli_result["--domtree"])			compiler_flags |= CompilerFlag_DumpDomTree;
		if (cli_result["--emit-ir"])			compiler_flags |= CompilerFlag_EmitIR;
		if (cli_result["--emit-mir"])			compiler_flags |= CompilerFlag_EmitMIR;
		if (cli_result["--emit-asm"])			compiler_flags |= CompilerFlag_EmitASM;
		if (cli_result["--domfrontier"])		compiler_flags |= CompilerFlag_PrintDomFrontier;
		if (cli_result["--timeout"])			compiler_flags |= CompilerFlag_TimeoutDetection;
		if (cli_result["-c"])					compiler_flags |= CompilerFlag_NoRun;
		if (cli_result["--lib"])				compiler_flags |= CompilerFlag_StaticLib;

		libraries = cli_result["-l"].AsStrings();

		if (cli_result["--O0"] || cli_result["--Od"])	opt_level = OptimizationLevel::O0;
		if (cli_result["--O1"])							opt_level = OptimizationLevel::O1;
		if (cli_result["--O2"])							opt_level = OptimizationLevel::O2;
		if (cli_result["--O3"])							opt_level = OptimizationLevel::O3;

		std::string target_str = cli_result["--target"].AsStringOr("");
		if (target_str == "x64")
		{
			target_arch = TargetArch::X86;
		}
		else if (target_str == "arm64")
		{
#if defined(OLA_PLATFORM_MACOS)
			target_arch = TargetArch::ARM;
#else
			OLA_WARN("Target 'arm64' is only supported on macOS. Falling back to native target 'x64'.");
			target_arch = TargetArch::X86;
#endif
		}
		else if (!target_str.empty())
		{
			OLA_WARN("Unknown target '{}'. Using default target for this platform.", target_str);
			target_arch = TargetArch::Default;
		}

		return true;
	}
}