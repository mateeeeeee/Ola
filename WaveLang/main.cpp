#include "CLI/CLI.hpp"
#include "Core/Logger.h"
#include "Compiler/Compiler.h"

int main(int argc, char** argv)
{
	CLI::App cli_parser{ "Wave compiler" };
	CLI::Option* ast_dump = cli_parser.add_flag("--astdump", "Dump AST to output/log");
	CLI::Option* test_debug = cli_parser.add_flag("--testdebug", "Print debug information during compilation process");
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
			wave::int32 exit_code = wave::CompileSimple(simple_input, test_debug_flag);
			return exit_code;
		}
		else if (!input_files.empty())
		{
			if (output_file.empty()) output_file = "test";

			wave::CompilerInput compiler_input{};
			compiler_input.flags = test_debug_flag ? wave::CompilerFlag_DumpAST | wave::CompilerFlag_O0 : wave::CompilerFlag_O3;
			compiler_input.input_directory = directory;
			compiler_input.sources = input_files;
			compiler_input.output_file = output_file;
			compiler_input.output_type = wave::CompilerOutput::Exe;
			wave::int32 exit_code = wave::Compile(compiler_input);
			return exit_code;
		}
		else
		{
			WAVE_WARN("No test input files provided!");
			return 1;
		}
	}

	if (input_files.empty())
	{
		WAVE_WARN("No input files provided!");
		return 0;
	}
	if (output_file.empty()) output_file = "out";
	if (directory.empty()) directory = "Test";

	wave::CompilerFlags compiler_flags = wave::CompilerFlag_None;
	if(*ast_dump) compiler_flags |= wave::CompilerFlag_DumpAST;

	wave::CompilerFlags optimization_flag = wave::CompilerFlag_None;
	if (*O0 || *Od) optimization_flag = wave::CompilerFlag_O0;
	if (*O1) optimization_flag = wave::CompilerFlag_O1;
	if (*O2) optimization_flag = wave::CompilerFlag_O2;
	if (*O3) optimization_flag = wave::CompilerFlag_O3;

	compiler_flags |= optimization_flag;

	wave::CompilerInput compiler_input{};
	compiler_input.flags = compiler_flags;
	compiler_input.input_directory = directory;
	compiler_input.sources = input_files;
	compiler_input.output_file = output_file;
	compiler_input.output_type = wave::CompilerOutput::Exe;

	wave::int32 exit_code = wave::Compile(compiler_input);
	return exit_code;
}
