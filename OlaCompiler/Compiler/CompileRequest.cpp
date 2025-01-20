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
		OLA_TODO("Add support for multiple input files");
		if(!input_file.empty()) input_files.push_back(input_file); 
		output_file = cli_result["-o"].AsStringOr("");
		input_directory = cli_result["--directory"].AsStringOr("");
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
				return false;
			}
		}

		if (input_files.empty())
		{
			OLA_WARN("No input files provided!");
			return false;
		}
		if (output_file.empty()) output_file = input_files[0];

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

		if (cli_result["--O0"] || cli_result["--Od"]) opt_level = OptimizationLevel::O0;
		if (cli_result["--O1"]) opt_level = OptimizationLevel::O1;
		if (cli_result["--O2"]) opt_level = OptimizationLevel::O2;
		if (cli_result["--O3"]) opt_level = OptimizationLevel::O3;
		return true;
	}
}