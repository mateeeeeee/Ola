#include "Compiler/Compiler.h"
#include "CLI/CLI.hpp"
#include "Core/Logger.h"


int main(int argc, char** argv)
{
	CLI::App cli_parser{ "Wave compiler" };
	CLI::Option* ast_dump = cli_parser.add_flag("--astdump", "Dump AST to output/log");

	std::vector<std::string> input_files;
	cli_parser.add_option("-i", input_files, "Input files");
	std::string output_file;
	cli_parser.add_option("-o", output_file, "Output file");

	CLI11_PARSE(cli_parser, argc, argv);

	if (input_files.empty())
	{
		WAVE_WARN("No input files provided!");
		return 0;
	}
	if (output_file.empty()) output_file = "out";
	wave::CompilerFlags flags = wave::CompilerFlag_None;
	if(*ast_dump) flags |= wave::CompilerFlag_DumpAST;

	wave::CompilerInput compiler_input{};
	compiler_input.flags = flags;
	compiler_input.input_directory = "";
	compiler_input.sources = input_files;
	compiler_input.output_file = output_file;
	compiler_input.output_type = wave::CompilerOutput::Exe;

	wave::int32 exit_code = wave::Compile(compiler_input);
	return exit_code;
}
