#include "CompileRequest.h"
#include "Core/Log.h"
#include "Utility/CLIParser.h"
#include "autogen/OlaConfig.h"

namespace ola
{
	Int CompileRequest::Parse(Int argc, Char** argv)
	{
		CLIParser cli_parser{};
		{
			cli_parser.AddArg(false, "--astdump");
			cli_parser.AddArg(false, "--cfgdump");
			cli_parser.AddArg(false, "--nollvm");
			cli_parser.AddArg(false, "--test");
			cli_parser.AddArg(false, "--Od");
			cli_parser.AddArg(false, "--O0");
			cli_parser.AddArg(false, "--O1");
			cli_parser.AddArg(false, "--O2");
			cli_parser.AddArg(false, "--O3");
			cli_parser.AddArg(true, "-i", "--input");
			cli_parser.AddArg(true, "--directory");
			cli_parser.AddArg(true, "-o", "--output");
		}
		CLIParseResult cli_result = cli_parser.Parse(argc, argv);

		std::string input_file = cli_result["-i"].AsStringOr("");
		if(!input_file.empty()) input_files.push_back(input_file); //#todo add support for multiple input files
		output_file = cli_result["-o"].AsStringOr("");
		input_directory = cli_result["--directory"].AsStringOr(OLA_COMPILER_PATH"Test");

		if (cli_result["--test"])
		{
			if (!input_files.empty())
			{
				if (output_file.empty()) output_file = input_files[0];
				if (cli_result["--nollvm"])	input_directory = OLA_TESTS_PATH"Tests/Custom";
				else						input_directory = OLA_TESTS_PATH"Tests/LLVM";
			}
			else
			{
				OLA_WARN("No test input files provided!");
				return -1;
			}
		}

		if (input_files.empty())
		{
			OLA_WARN("No input files provided!");
			return -1;
		}
		if (output_file.empty()) output_file = input_files[0];
		if (input_directory.empty()) input_directory = OLA_COMPILER_PATH"Test";

		if (cli_result["--astdump"])  compiler_flags |= ola::CompilerFlag_DumpAST;
		if (cli_result["--nollvm"])   compiler_flags |= ola::CompilerFlag_NoLLVM;
		if (cli_result["--cfgdump"])  compiler_flags |= ola::CompilerFlag_DumpCFG;

		if (cli_result["--O0"] || cli_result["--Od"]) opt_level = OptimizationLevel::O0;
		if (cli_result["--O1"]) opt_level = OptimizationLevel::O1;
		if (cli_result["--O2"]) opt_level = OptimizationLevel::O2;
		if (cli_result["--O3"]) opt_level = OptimizationLevel::O3;
		return 0;
	}
}