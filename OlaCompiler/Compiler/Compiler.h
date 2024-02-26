#pragma once
#include <string>
#include <vector>
#include "Utility/EnumOperators.h"

namespace ola
{
	enum CompilerFlags : uint32
	{
		CompilerFlag_None    = 0x00,
		CompilerFlag_DumpAST = 0x01,
		CompilerFlag_O0		 = 0x02,
		CompilerFlag_O1		 = 0x04,
		CompilerFlag_O2		 = 0x08,
		CompilerFlag_O3		 = 0x10,
		CompilerFlag_NoLLVM  = 0x1000,
	};
	template<>
	struct EnumBitmaskOperators<CompilerFlags>
	{
		static constexpr bool enable = true;
	};

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
	int32 CompileSimple(std::string_view input, bool debug);
}