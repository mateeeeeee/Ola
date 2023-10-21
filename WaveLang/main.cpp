#include "CLI/CLI.hpp"
#include "Core/Logger.h"
#include "Compiler/Compiler.h"

int main(int argc, char** argv)
{
	CLI::App cli_parser{ "Wave compiler" };
	CLI::Option* ast_dump = cli_parser.add_flag("--astdump", "Dump AST to output/log");
	CLI::Option* debug = cli_parser.add_flag("--debug", "Print debug information during compilation process");
	CLI::Option* test = cli_parser.add_flag("--test", "used for running g-tests");

	std::vector<std::string> input_files;
	cli_parser.add_option("-i", input_files, "Input files");
	std::string output_file;
	cli_parser.add_option("-o", output_file, "Output file");
	std::string directory;
	cli_parser.add_option("--directory", directory, "Directory of input files");
	std::string test_input;
	CLI::Option* test_input_opt = cli_parser.add_option("-t", test_input, "input test code in form of a string");

	CLI11_PARSE(cli_parser, argc, argv);

	if (*test)
	{
		if (test_input.empty())
		{
			WAVE_WARN("Test input is empty!");
			return 0;
		}
		wave::int32 exit_code = wave::CompileTest(test_input, (bool)*debug);
		return exit_code;
	}

	if (input_files.empty())
	{
		WAVE_WARN("No input files provided!");
		return 0;
	}
	if (output_file.empty()) output_file = "out";
	if (directory.empty()) directory = "Test";


	wave::CompilerFlags flags = wave::CompilerFlag_None;
	if(*ast_dump) flags |= wave::CompilerFlag_DumpAST;

	wave::CompilerInput compiler_input{};
	compiler_input.flags = flags;
	compiler_input.input_directory = directory;
	compiler_input.sources = input_files;
	compiler_input.output_file = output_file;
	compiler_input.output_type = wave::CompilerOutput::Exe;

	wave::int32 exit_code = wave::Compile(compiler_input);
	return exit_code;
}

#undef _DEBUG