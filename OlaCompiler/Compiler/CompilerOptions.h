#pragma once
#include "Utility/EnumOperators.h"

namespace ola
{
	enum CompilerFlags : uint32
	{
		CompilerFlag_None = 0x00,
		CompilerFlag_DumpAST = 0x01,
		CompilerFlag_NoLLVM = 0x02
	};
	template<>
	struct EnumBitmaskOperators<CompilerFlags>
	{
		static constexpr bool enable = true;
	};

	enum class OptimizationLevel : uint8
	{
		Od = 0,
		O0 = Od,
		O1,
		O2,
		O3
	};

	enum class CompilerOutput : uint8
	{
		Exe,
		Dll,
		Lib
	};

}