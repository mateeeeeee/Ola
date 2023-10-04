#pragma once
#include<iosfwd>

namespace wave
{
	struct SourceLocation;
}
namespace wave::diag
{
	inline constexpr int32 EXIT_CODE_COMPILATION_FAILED = INT32_MAX;

	enum DiagCode : uint32
	{
		#define DIAG(diag_code, diag_kind, diag_msg) diag_code,
		#include "Diagnostics.def"
	};

	void Initialize(bool warnings_as_errors = false, bool exit_on_error = true);

	void Report(DiagCode code, SourceLocation const& loc);
	void Report(DiagCode code);
	void SetLocation(SourceLocation const& loc);
}