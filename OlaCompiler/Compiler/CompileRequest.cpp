#include "CompileRequest.h"
#include "CLI/CLI.hpp"
#include "Core/Logger.h"
#include "autogen/OlaConfig.h"

namespace ola
{
	int32 CompileRequest::Parse(int argc, char** argv)
	{
		CLI::App cli_parser{ "Ola compiler" };
		CLI::Option* ast_dump = cli_parser.add_flag("--astdump", "Dump AST to output/log");
		CLI::Option* test_debug = cli_parser.add_flag("--testdebug", "Print debug information during tests");
		CLI::Option* no_llvm = cli_parser.add_flag("--nollvm", "Use custom backend instead of LLVM one");
		CLI::Option* test = cli_parser.add_flag("--test", "used for running g-tests");
		CLI::Option* Od = cli_parser.add_flag("--Od", "No optimizations");
		CLI::Option* O0 = cli_parser.add_flag("--O0", "No optimizations");
		CLI::Option* O1 = cli_parser.add_flag("--O1", "Optimize");
		CLI::Option* O2 = cli_parser.add_flag("--O2", "Optimize more");
		CLI::Option* O3 = cli_parser.add_flag("--O3", "Optimize even more");

		cli_parser.add_option("-i", source_files, "Input files");
		cli_parser.add_option("-o", output_file, "Output file");
		cli_parser.add_option("--directory", input_directory, "Directory of input files");
		CLI11_PARSE(cli_parser, argc, argv);

		if (*test)
		{
			bool test_debug_flag = (bool)*test_debug;
			if (!source_files.empty())
			{
				if (output_file.empty()) output_file = source_files[0];
				if (input_directory.empty()) input_directory = OLA_TESTS_PATH"Tests";
			}
			else
			{
				OLA_WARN("No test input files provided!");
				return -1;
			}
		}

		if (source_files.empty())
		{
			OLA_WARN("No input files provided!");
			return -1;
		}
		if (output_file.empty()) output_file = source_files[0];
		if (input_directory.empty()) input_directory = OLA_COMPILER_PATH"Test";

		if (*ast_dump) compiler_flags |= ola::CompilerFlag_DumpAST;
		if (*no_llvm) compiler_flags |= ola::CompilerFlag_NoLLVM;

		if (*O0 || *Od) opt_level = OptimizationLevel::O0;
		if (*O1) opt_level = OptimizationLevel::O1;
		if (*O2) opt_level = OptimizationLevel::O2;
		if (*O3) opt_level = OptimizationLevel::O3;

		return 0;
	}


}