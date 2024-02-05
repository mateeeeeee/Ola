#include <filesystem>
#include <cstdio>
#include "CLI/CLI.hpp"
#include "Core/Logger.h"
#include "Compiler/Compiler.h"
#include "autogen/OlaConfig.h"


int main(int argc, char** argv)
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

	std::vector<std::string> input_files;
	cli_parser.add_option("-i", input_files, "Input files");
	std::string output_file;
	cli_parser.add_option("-o", output_file, "Output file");
	std::string directory;
	cli_parser.add_option("--directory", directory, "Directory of input files");
	std::string simple_input;
	CLI::Option* test_input_opt = cli_parser.add_option("--simple", simple_input, "input code in the form of a string");

	CLI11_PARSE(cli_parser, argc, argv);

	if (*test)
	{
		bool test_debug_flag = (bool)*test_debug;
		if (!simple_input.empty())
		{
			ola::int32 exit_code = ola::CompileSimple(simple_input, test_debug_flag);
			return exit_code;
		}
		else if (!input_files.empty())
		{
			if (output_file.empty()) output_file = input_files[0];
			if (directory.empty()) directory = OLA_CONCAT(OLA_TESTS_PATH, "Tests");

			ola::CompilerInput compiler_input{};
			compiler_input.flags = test_debug_flag ? ola::CompilerFlag_DumpAST | ola::CompilerFlag_O0 : ola::CompilerFlag_O3;
			if (*no_llvm) compiler_input.flags |= ola::CompilerFlag_NoLLVM;
			compiler_input.input_directory = directory;
			compiler_input.sources = input_files;
			compiler_input.output_file = output_file;
			compiler_input.output_type = ola::CompilerOutput::Exe;
			ola::int32 exit_code = ola::Compile(compiler_input);
			return exit_code;
		}
		else
		{
			OLA_WARN("No test input files provided!");
			return 1;
		}
	}

	if (input_files.empty())
	{
		OLA_WARN("No input files provided!");
		return 0;
	}
	if (output_file.empty()) output_file = input_files[0];
	if (directory.empty()) directory = OLA_CONCAT(OLA_COMPILER_PATH, "Test");

	ola::CompilerFlags compiler_flags = ola::CompilerFlag_None;
	if(*ast_dump) compiler_flags |= ola::CompilerFlag_DumpAST;

	ola::CompilerFlags optimization_flag = ola::CompilerFlag_None;
	if (*O0 || *Od) optimization_flag = ola::CompilerFlag_O0;
	if (*O1) optimization_flag = ola::CompilerFlag_O1;
	if (*O2) optimization_flag = ola::CompilerFlag_O2;
	if (*O3) optimization_flag = ola::CompilerFlag_O3;

	compiler_flags |= optimization_flag;
	if (*no_llvm) compiler_flags |= ola::CompilerFlag_NoLLVM;

	ola::CompilerInput compiler_input{};
	compiler_input.flags = compiler_flags;
	compiler_input.input_directory = directory;
	compiler_input.sources = input_files;
	compiler_input.output_file = output_file;
	compiler_input.output_type = ola::CompilerOutput::Exe;

	ola::int32 exit_code = ola::Compile(compiler_input);
	return exit_code;
}
