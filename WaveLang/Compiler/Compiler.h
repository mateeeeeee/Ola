#pragma once
#include <string>
#include <vector>
#include "Utility/Enums.h"

namespace wave
{
	enum CompilerFlags : uint32
	{
		CompilerFlag_None = 0x0,
		CompilerFlag_DumpAST = 0x1,
		CompilerFlag_OutputAssembly = 0x2,
		CompilerFlag_NoLLVM = 0x4,
	};
	DEFINE_ENUM_BIT_OPERATORS(CompilerFlags);

	enum class CompilerOutput
	{
		Exe,
		Dll,
		Lib
	};

	struct CompilerInput
	{
		CompilerFlags flags;
		std::string input_directory;
		std::vector<std::string> sources;
		std::string output_file;
		CompilerOutput output_type = CompilerOutput::Exe;
	};

	int32 Compile(CompilerInput const&);
}