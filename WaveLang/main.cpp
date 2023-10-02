#include "Compiler/Compiler.h"
#include "CLI/CLI.hpp"


int main(int argc, char** argv)
{
	CLI::App cli_parser{ "Wave compiler" };

	std::vector<std::string> input_files;
	cli_parser.add_option("-i", input_files, "Input files")->required(true);
	std::string output_file;
	cli_parser.add_option("-o", output_file, "Output file")->default_val("wave");

	CLI11_PARSE(cli_parser, argc, argv);
	wave::CompilerFlags flags = wave::CompilerFlag_None;

	wave::CompilerInput compiler_input{};
	compiler_input.flags = flags;
	compiler_input.input_directory = "";
	compiler_input.sources = input_files;
	compiler_input.output_file = output_file;
	compiler_input.output_type = wave::CompilerOutput::Exe;

	int exit_code = Compile(compiler_input);
	return exit_code;
}
