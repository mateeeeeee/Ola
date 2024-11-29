#pragma once
#include "Utility/EnumOperators.h"

namespace ola
{
	enum CompilerFlags : Uint32
	{
		CompilerFlag_None = 0x00,
		CompilerFlag_DumpAST = 0x01,
		CompilerFlag_NoLLVM = 0x02,
		CompilerFlag_DumpCFG = 0x04
	};
	template<>
	struct EnumBitmaskOperators<CompilerFlags>
	{
		static constexpr Bool enable = true;
	};

	enum class OptimizationLevel : Uint8
	{
		Od = 0,
		O0 = Od,
		O1,
		O2,
		O3
	};

	enum class CompilerOutput : Uint8
	{
		Exe,
		Dll,
		Lib
	};

}