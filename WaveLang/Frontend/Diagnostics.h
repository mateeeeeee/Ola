#pragma once

namespace wave
{
	class SourceLocation;

	namespace diag
	{
		enum DiagCode
		{
			#define DIAG(diag_code, diag_kind, diag_msg) diag_code,
			#include "Diagnostics.def"
		};
		
		void Initialize();
		void Report(SourceLocation const& loc, DiagCode code);
	}
}