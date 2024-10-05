#pragma once
#include <string>
#include <vector>
#include "CompilerOptions.h"

namespace ola
{
	class Compiler;
	class CompileRequest
	{
	public:
		CompileRequest() = default;
		~CompileRequest() = default;

		int32 Parse(int argc, char** argv);

		CompilerFlags GetCompilerFlags() const { return compiler_flags; }
		OptimizationLevel GetOptimizationLevel() const { return opt_level; }
		CompilerOutput GetOutputType() const { return output_type; }
		std::string_view GetInputDirectory() const { return input_directory; }
		std::string const& GetOutputFile() const { return output_file; }
		std::vector<std::string> const& GetSourceFiles() const { return source_files; }

	private:
		CompilerFlags compiler_flags = CompilerFlag_None;
		OptimizationLevel opt_level = OptimizationLevel::O0;
		CompilerOutput output_type = CompilerOutput::Exe;
		std::string input_directory;
		std::vector<std::string> source_files;
		std::string output_file;
	};
}