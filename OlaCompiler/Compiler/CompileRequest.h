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

		Bool Parse(Int argc, Char** argv);

		CompilerFlags GetCompilerFlags() const { return compiler_flags; }
		OptimizationLevel GetOptimizationLevel() const { return opt_level; }
		TargetArch GetTargetArch() const { return target_arch; }
		std::string_view GetInputDirectory() const { return input_directory; }
		std::string const& GetOutputFile() const { return output_file; }
		std::vector<std::string> const& GetSourceFiles() const { return input_files; }
		std::vector<std::string> const& GetLibraries() const { return libraries; }

	private:
		CompilerFlags compiler_flags = CompilerFlag_None;
		OptimizationLevel opt_level = OptimizationLevel::O0;
		TargetArch target_arch = TargetArch::Default;
		std::string input_directory;
		std::vector<std::string> input_files;
		std::string output_file;
		std::vector<std::string> libraries;
	};
}